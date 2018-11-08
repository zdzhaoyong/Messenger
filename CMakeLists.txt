cmake_minimum_required(VERSION 2.8)
include(cmake/PICMake.cmake)

set(CMAKE_CXX_FLAGS -std=c++11)
pi_add_target(messenger BIN src REQUIRED System MODULES ROS)
pi_report_targets()
