import rclpy
from status_interfaces.msg import SystemStatus
from rclpy.node import Node
import psutil
import platform

class SysStatusPub(Node):
    def __init__(self,node_name:str):
        super().__init__(node_name)
        self.publisher_ = self.create_publisher(SystemStatus, 'system_status', 10)
        self.timer_ = self.create_timer(1.0, self.timer_callback)
    def timer_callback(self):
        msg = SystemStatus()
        msg.stamp=self.get_clock().now().to_msg()
        msg.host_name=platform.node()
        msg.cpu_percent=psutil.cpu_percent()
        msg.memory_percent=psutil.virtual_memory().percent
        msg.memory_total=psutil.virtual_memory().total/1024/1024
        msg.memory_avaliable=psutil.virtual_memory().available/1024/1024
        msg.net_sent=psutil.net_io_counters().bytes_sent/1024/1024
        msg.net_recv=psutil.net_io_counters().bytes_recv/1024/1024

        self.get_logger().info(f"发布：{str(msg)}")
        self.publisher_.publish(msg)

def main():
    rclpy.init()
    node = SysStatusPub('sys_status_pub')
    rclpy.spin(node)
    rclpy.shutdown()
