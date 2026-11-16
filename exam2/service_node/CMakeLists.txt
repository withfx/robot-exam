cmake_minimum_required(VERSION 3.8)
project(service_node)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(add_two_ints_srv REQUIRED)

# 服务端
add_executable(server src/server.cpp)
ament_target_dependencies(server rclcpp add_two_ints_srv)

# 客户端
add_executable(client src/client.cpp)
ament_target_dependencies(client rclcpp add_two_ints_srv)

install(TARGETS server client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
