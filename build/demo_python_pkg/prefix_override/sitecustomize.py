import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/zmy/Desktop/ros2_learn/install/demo_python_pkg'
