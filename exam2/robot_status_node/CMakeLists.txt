cmake_minimum_required(VERSION 3.8)
project(robot_status_node)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(robot_status_msg REQUIRED)

# 发布者
add_executable(publisher src/publisher.cpp)
ament_target_dependencies(publisher rclcpp robot_status_msg)

# 订阅者
add_executable(subscriber src/subscriber.cpp)
ament_target_dependencies(subscriber rclcpp robot_status_msg)

install(TARGETS publisher subscriber
  DESTINATION lib/${PROJECT_NAME})

# launch 文件和参数文件也一起装到 share 目录
install(DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME})

ament_package()
