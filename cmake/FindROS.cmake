
find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    sensor_msgs
    )

if(catkin_FOUND)
  set(ROS_FOUND 1)
  set(ROS_VERSION ${catkin_VERSION})
  set(ROS_INCLUDES ${catkin_INCLUDE_DIRS})
  set(ROS_LIBS ${catkin_LIBRARIES})
endif()
