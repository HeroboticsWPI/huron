cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Configure target build platform. Defaults to building for Raspberry Pi (arm64).
set(BUILD_TYPE "arm64" CACHE STRING "Choose the build type: [x86_64, armv7l, arm64]")

# Conditionally set the toolchain file based on the build type
if(BUILD_TYPE STREQUAL "armv7l")
    set(CMAKE_TOOLCHAIN_FILE "tools/armhf-toolchain.cmake")
elseif(BUILD_TYPE STREQUAL "arm64")
    set(CMAKE_TOOLCHAIN_FILE "tools/arm64-toolchain.cmake")
elseif(BUILD_TYPE STREQUAL "x86_64")
    set(CMAKE_TOOLCHAIN_FILE "tools/x86_64-toolchain.cmake")
else()
    message(FATAL_ERROR "Invalid build type. Use -DBUILD_TYPE=x86_64 or -DBUILD_TYPE=armv7l")
endif()

project(huron)

# Find pinocchio
if (DEFINED USE_PINOCCHIO)
  find_package(pinocchio REQUIRED)
  message(pinocchio_INCLUDE_DIRS="${pinocchio_INCLUDE_DIRS}")
endif()

# Find sockcanpp
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(sockcanpp REQUIRED)

message(sockcanpp_INCLUDE_DIRS="${sockcanpp_INCLUDE_DIRS}")

# Find Serial
find_package(serial REQUIRED)
message(serial_INCLUDE_DIRS="${serial_INCLUDE_DIRS}")

find_package (Eigen3 REQUIRED)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL http://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# libhuron
add_library(huron SHARED huron.cc)
set_target_properties(huron PROPERTIES LINKER_LANGUAGE CXX)

# Test target
enable_testing()

add_executable(huron_tests huron.cc)

# Add subpackages
add_subdirectory(common)
add_subdirectory(math)
add_subdirectory(driver)
add_subdirectory(utils)
add_subdirectory(system)
add_subdirectory(control)
add_subdirectory(multibody)
# add_subdirectory(third_party)

target_link_libraries(huron
  PUBLIC
    sockcanpp
    serial
)
target_include_directories(huron
    PUBLIC
    ${sockcanpp_INCLUDE_DIRS}/..
    ${serial_INCLUDE_DIRS}/..
    ${EIGEN3_INCLUDE_DIR}/..)

if (DEFINED USE_PINOCCHIO)
  target_link_libraries(huron
    PUBLIC
      pinocchio::pinocchio)
    target_compile_definitions(huron PUBLIC HURON_USE_PINOCCHIO=1)
endif()

# Copy urdf files to build directory
add_custom_command(TARGET huron PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                       ${CMAKE_SOURCE_DIR}/multibody/test/*.urdf $<TARGET_FILE_DIR:huron>)

# Install the "huronConfig.cmake" file and export the target
install(TARGETS huron
  EXPORT huronTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  # FILE_SET HEADERS DESTINATION include
)

# Generate and install the export targets for "huron"
install(EXPORT huronTargets
  FILE huronTargets.cmake
  NAMESPACE huron::
  DESTINATION lib/cmake/huron
)

# Generate and install huronConfig.cmake
include(CMakePackageConfigHelpers)

# Generate ${PROJECT_NAME}Config.cmake
configure_package_config_file(
  huronConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/huronConfig.cmake
  INSTALL_DESTINATION lib/cmake/huron
)
# Install the generated "huronConfig.cmake" file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/huronConfig.cmake
    DESTINATION lib/cmake/huron
)
# Also install Findsockcanpp.cmake
install(
  FILES Findsockcanpp.cmake Findserial.cmake
  DESTINATION lib/cmake/huron/Modules
)

# Uninstall target
# Source: https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#can-i-do-make-uninstall-with-cmake
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# Build examples
# add_subdirectory(examples)

target_link_libraries(
  huron_tests
  huron
  sockcanpp
  serial
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(huron_tests)
