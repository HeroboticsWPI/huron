#include <functional>
#include "huron_driver/can/huron_odrive_can.h"


bool HuronODriveCAN::init() {
	return true;
}

bool HuronODriveCAN::GetMotorError(uint64_t& motor_error) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_MOTOR_ERROR;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  motor_error = can_getSignal<uint64_t>(msg, 0, 64, true);
  return true;
}
bool HuronODriveCAN::GetEncoderError(uint32_t& encoder_error) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_ENCODER_ERROR;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  encoder_error = can_getSignal<uint32_t>(msg, 0, 32, true);
  return true;
}

bool HuronODriveCAN::GetControllerError(uint32_t& controller_error) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_CONTROLLER_ERROR;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  controller_error = can_getSignal<uint32_t>(msg, 0, 32, true);
  return true;
}

bool HuronODriveCAN::GetSensorlessError(uint32_t& sensorless_error) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_SENSORLESS_ERROR;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  sensorless_error = can_getSignal<uint32_t>(msg, 0, 32, true);
  return true;
}

bool HuronODriveCAN::GetEncoderEstimates(float& pos, float& vel) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_ENCODER_ESTIMATES;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  pos = can_getSignal<float>(msg, 0, 32, true);
  vel = can_getSignal<float>(msg, 32, 32, true);
  return true;
}

bool HuronODriveCAN::GetEncoderCount(int32_t& shadow_cnt, int32_t& cnt_cpr) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_ENCODER_COUNT;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  shadow_cnt = can_getSignal<int32_t>(msg, 0, 32, true);
  cnt_cpr = can_getSignal<int32_t>(msg, 32, 32, true);
  return true;
}

bool HuronODriveCAN::GetIq(float& iq_setpoint, float& iq_measured) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_IQ;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  iq_setpoint = can_getSignal<float>(msg, 0, 32, true);
  iq_measured = can_getSignal<float>(msg, 32, 32, true);
  return true;
}

bool HuronODriveCAN::GetSensorlessEstimates(float& pos, float& vel) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_SENSORLESS_ESTIMATES;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  pos = can_getSignal<float>(msg, 0, 32, true);
  vel = can_getSignal<float>(msg, 32, 32, true);
  return true;
}

bool HuronODriveCAN::GetBusVoltageCurrent(float& bus_voltage, float& bus_current) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_BUS_VOLTAGE_CURRENT;
	msg.rtr = true;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  bus_voltage = can_getSignal<float>(msg, 0, 32, true);
  bus_current = can_getSignal<float>(msg, 32, 32, true);
  return true;
}

bool HuronODriveCAN::GetAdcVoltage(float& adc_voltage) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_GET_ADC_VOLTAGE;
	msg.rtr = false;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	canbus_->send_message(msg);
	if (!canbus_->recv_message(msg)) {
		return false;
	}
  adc_voltage = can_getSignal<float>(msg, 0, 32, true);
  return true;
}

bool HuronODriveCAN::SetAxisNodeid(uint32_t axis_id) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_AXIS_NODE_ID;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<uint32_t>(msg, axis_id, 0, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetAxisRequestedState(uint32_t state) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_AXIS_REQUESTED_STATE;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<uint32_t>(msg, state, 0, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetAxisStartupConfig() {
	// Not Implemented
	return false;
}

bool HuronODriveCAN::SetInputPos(float input_pos, int16_t vel_ff, int16_t torque_ff) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_INPUT_POS;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, input_pos, 0, 32, true);
  can_setSignal<int16_t>(msg, input_pos, 32, 16, true, 0.001, 0);
  can_setSignal<int16_t>(msg, input_pos, 48, 16, true, 0.001, 0);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetInputVel(float input_vel, float torque_ff) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_INPUT_VEL;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, input_vel, 0, 32, true);
  can_setSignal<float>(msg, torque_ff, 32, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetInputTorque(float input_torque) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_INPUT_TORQUE;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, input_torque, 0, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetControllerModes(int32_t control_mode, int32_t input_mode) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_CONTROLLER_MODES;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<int32_t>(msg, control_mode, 0, 32, true);
  can_setSignal<int32_t>(msg, input_mode, 32, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetLimits(float velocity_limit, float current_limit) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_LIMITS;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, velocity_limit, 0, 32, true);
  can_setSignal<float>(msg, current_limit, 32, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetTrajVelLimit(float traj_vel_limit) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_TRAJ_VEL_LIMIT;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, traj_vel_limit, 0, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetTrajAccelLimits(float traj_accel_limit, float traj_decel_limit) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_TRAJ_ACCEL_LIMITS;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, traj_accel_limit, 0, 32, true);
  can_setSignal<float>(msg, traj_decel_limit, 32, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetTrajInertia(float traj_inertia) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_TRAJ_INERTIA;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, traj_inertia, 0, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetLinearCount(int32_t position) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_LINEAR_COUNT;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<int32_t>(msg, position, 0, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetPosGain(float pos_gain) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_POS_GAIN;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, pos_gain, 0, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::SetVelGains(float vel_gain, float vel_interator_gain) {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_SET_VEL_GAINS;
  msg.isExt = false;
  msg.len = 8;
  can_setSignal<float>(msg, vel_gain, 0, 32, true);
  can_setSignal<float>(msg, vel_interator_gain, 32, 32, true);
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::Nmt() {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_CO_NMT_CTRL;
  msg.isExt = false;
  msg.len = 8;
  return canbus_->send_message(msg);
}

bool HuronODriveCAN::Estop() {
	can_Message_t msg;
  msg.id = axis_id_ << HuronODriveCAN::NUM_CMD_ID_BITS;
  msg.id += HuronODriveCAN::MSG_ODRIVE_ESTOP;
  msg.isExt = false;
  msg.len = 8;
	// Sends message with RTR on
	return canbus_->send_message(msg);
}

