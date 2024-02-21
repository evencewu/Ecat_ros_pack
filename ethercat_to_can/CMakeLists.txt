cmake_minimum_required(VERSION 3.0.2)
project(ethercat_to_can)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  soem
)

catkin_package(
 INCLUDE_DIRS include
 CATKIN_DEPENDS roscpp rospy std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(test_demo_dm4310
src/ecat_can_base/ecat_base.cpp
src/ecat_motor_dlc/ecat_DM4310.cpp
src/ecat_motor_dlc/ecat_GM6020.cpp
src/test_demo_DM4310.cpp
)

target_link_libraries(test_demo_dm4310
  /home/evence/ros_ws/ecat/devel/lib/soem/libsoem.a
  ${catkin_LIBRARIES}
)


