import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/zmy/Desktop/ros2_learn/lesson3/topic_practice_ws/install/status_publisher'
