cmake_minimum_required(VERSION 3.8)
project(robot_status_msg)

# 编译时打开常用警告
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 根据 msg/RobotStatus.msg 生成 C++ 头文件
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RobotStatus.msg"
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
