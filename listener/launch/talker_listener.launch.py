from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare
import launch_ros.actions
import os


def generate_launch_description():

    ld = LaunchDescription()

    print('======================')
    print(os.environ['AMENT_PREFIX_PATH'])

    default_config_file : str

    if "SNAP_COMMON" in os.environ:
        default_config_file = os.path.join(os.environ.get("SNAP_COMMON"), "robot-config", "listener.yaml")
    else:
        default_config_file = os.path.join(
            get_package_share_directory("listener"), "config", "listener.yaml"
        )

    ld.add_action(
        launch_ros.actions.Node(
            package="listener",
            executable="listener",
            output="screen",
            parameters=[default_config_file],
        )
    )

    talker_pkg = FindPackageShare(package='talker').find('talker')
    talker_launch = os.path.join(talker_pkg, 'launch/talker.launch.py')
    print(talker_launch)


    ld.add_action(
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(talker_launch)
            )
        )
    return ld
