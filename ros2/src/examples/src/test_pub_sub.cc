#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include "huron/utils/time.h"
#include "huron/locomotion/zero_moment_point_ft_sensor.h"
#include "huron_ros2/huron.h"
#include "huron_ros2/force_torque_sensor.h"
#include "huron_ros2/joint_state_provider.h"
#include "huron_ros2/joint_group_controller.h"

using namespace huron;  //NOLINT

// Joint names order from ROS2
const std::array<std::string, 12> joint_names = {
  "l_hip_yaw_joint",
  "l_hip_roll_joint",
  "l_knee_pitch_joint",
  "l_ankle_pitch_joint",
  "r_hip_roll_joint",
  "r_hip_pitch_joint",
  "r_knee_pitch_joint",
  "l_hip_pitch_joint",
  "l_ankle_roll_joint",
  "r_ankle_pitch_joint",
  "r_hip_yaw_joint",
  "r_ankle_roll_joint"
};

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  auto huron_node = std::make_shared<ros2::HuronNode>();
  // Instantiate a Huron object
  ros2::Huron robot(huron_node);
  robot.GetModel()->AddModelImpl(multibody::ModelImplType::kPinocchio);
  robot.GetModel()->BuildFromUrdf(
      ament_index_cpp::get_package_share_directory("huron_description") +
        "/urdf/huron.urdf",
      multibody::JointType::kFreeFlyer);

  auto root_joint_sp = std::make_shared<ros2::JointStateProvider>(
        0, 7,
        0, 6, huron_node);
  robot.GetModel()->SetJointStateProvider(1, root_joint_sp);
  for (size_t i = 0; i < joint_names.size(); ++i) {
    // Prints joint names in the internal model order
    auto joint = robot.GetModel()->GetJoint(i);
    std::cout << "Joint " << i
              << ", name = " << joint->Info()->name()
              << ", id_q = " << joint->id_q()
              << ", nq = " << joint->nq()
              << ", id_v = " << joint->id_v()
              << ", nv = " << joint->nv()
              << std::endl;
    auto joint_sp = std::make_shared<ros2::JointStateProvider>(
        i + 7, 1,
        i + 6, 1,
        huron_node);
    robot.RegisterStateProvider(joint_sp, true);
    robot.GetModel()->SetJointStateProvider(
      robot.GetModel()->GetJointIndex(joint_names[i]),
      joint_sp);
  }

  robot.GetModel()->Finalize();

  // Register force torque sensors
  std::shared_ptr<huron::ForceTorqueSensor> l_ft_sensor =
    std::make_shared<ros2::ForceTorqueSensor>(
      0,
      false,  // reverse wrench direction
      robot.GetModel()->GetFrame("l_ankle_roll_joint"),
      huron_node);
  robot.RegisterStateProvider(l_ft_sensor);
  std::shared_ptr<huron::ForceTorqueSensor> r_ft_sensor =
    std::make_shared<ros2::ForceTorqueSensor>(
      1,
      false,  // reverse wrench direction
      robot.GetModel()->GetFrame("r_ankle_roll_joint"),
      huron_node);
  robot.RegisterStateProvider(r_ft_sensor);

  // Initialize ZMP
  std::vector<std::shared_ptr<ForceTorqueSensor>> ft_sensor_list;
  ft_sensor_list.push_back(l_ft_sensor);
  ft_sensor_list.push_back(r_ft_sensor);
  std::shared_ptr<ZeroMomentPoint> zmp =
    std::make_shared<ZeroMomentPointFTSensor>(
      robot.GetModel()->GetFrame("universe"),
      0.005,
      ft_sensor_list);
  robot.InitializeZmp(zmp);

  // Register joint group controller
  robot.AddToGroup(
    std::make_shared<ros2::JointGroupController>(huron_node));

  auto start = std::chrono::steady_clock::now();
  bool moved = false;

  while (rclcpp::ok()) {
    robot.Loop();
    robot.UpdateAllStates();
    // Prints out joint states
    Eigen::VectorXd joint_positions = robot.GetJointPositions();
    Eigen::VectorXd joint_velocities = robot.GetJointVelocities();
    std::cout << "Positions:\n" << joint_positions.transpose() << std::endl;
    std::cout << "Velocities:\n" << joint_velocities.transpose() << std::endl;
    std::cout << "\n\n";

    // After 10 seconds, move the joints
    if (since(start).count() > 10000 && !moved) {
      moved = true;
      robot.Move({0.0,
                  0.0,
                  0.0,
                  10.0,
                  0.0,
                  0.0,
                  0.0,
                  0.0,
                  0.0,
                  10.0,
                  0.0,
                  0.0
      });
    }
  }
  rclcpp::shutdown();

  return 0;
}
