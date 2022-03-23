from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
import launch_ros.actions
import os


def generate_launch_description():

    ld = LaunchDescription()

    default_config_file : str

    ld.add_action(
        launch_ros.actions.Node(
            package="talker", executable="talker", output="screen"
        )
    )
    return ld
