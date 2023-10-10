import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, GroupAction
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource, FrontendLaunchDescriptionSource
from launch_ros.actions import (
    LoadComposableNodes,
    Node,
    ComposableNodeContainer,
    SetRemap,
)
from launch_ros.descriptions import ComposableNode
from launch.conditions import IfCondition


def generate_launch_description():
    depthai_prefix = get_package_share_directory("depthai_ros_driver")
    
    params_file = os.path.join(
        get_package_share_directory("depthai_test_plugin"), "config", "rgbtest.yaml"
    )
    name = "oak"

    driver = LoadComposableNodes(
        # condition=IfCondition(LaunchConfiguration("rectify_rgb")),
        target_container=name + "_container",
        composable_node_descriptions=[
            ComposableNode(
                package="depthai_ros_driver",
                plugin="depthai_ros_driver::Camera",
                name=name,
                parameters=[params_file],
            )
        ])
    return LaunchDescription(
        [
            # oak_container,
            driver,
        ]
    )
