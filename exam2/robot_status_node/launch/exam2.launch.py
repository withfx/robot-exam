#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""exam2 一键启动：4 个节点 + 统一命名空间 + 统一参数文件"""

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # params.yaml 编译后被装到 share/robot_status_node/config 下面
    default_params = os.path.join(
        get_package_share_directory('robot_status_node'), 'config', 'params.yaml')

    params_file = LaunchConfiguration('params_file')
    namespace = LaunchConfiguration('namespace')

    return LaunchDescription([
        DeclareLaunchArgument('params_file', default_value=default_params,
                              description='参数文件路径'),
        DeclareLaunchArgument('namespace', default_value='robot1',
                              description='统一命名空间'),

        # 发布者：重命名为 atil_1
        Node(package='robot_status_node', executable='publisher',
             name='atil_1', namespace=namespace, output='screen',
             parameters=[params_file]),

        # 订阅者
        Node(package='robot_status_node', executable='subscriber',
             name='atil_1_subscriber', namespace=namespace, output='screen',
             parameters=[params_file]),

        # 服务端
        Node(package='service_node', executable='server',
             name='atil_1_server', namespace=namespace, output='screen',
             parameters=[params_file]),

        # 客户端
        Node(package='service_node', executable='client',
             name='atil_1_client', namespace=namespace, output='screen',
             parameters=[params_file]),
    ])
