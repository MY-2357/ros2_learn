import rclpy
from rclpy.node import Node
import requests
from example_interfaces.msg import String
from queue import Queue


class NovelPubNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.get_logger().info(f"{node_name}，启动！")
        self.novels_queue_ = Queue()
        self.novel_publisher_ = self.create_publisher(String, "novel", 10)

    def timer_callback(self):
        if self.novels_queue_.qsize() > 0:
            msg = String()
            msg.data = self.novels_queue_.get()
            self.novel_publisher_.publish(msg)
            self.get_logger().info(f"{msg.data}")

    def download(self, url: str):
        response = requests.get(url)
        response.encoding = "utf-8"
        text = response.text
        self.get_logger().info(f"下载{url} ,{len(text)}")
        for line in text.splitlines():
            self.novels_queue_.put(line)
        self.create_timer(2, self.timer_callback)

def main():
    rclpy.init()
    node = NovelPubNode("novel_publish_node")
    node.download("http://127.0.0.1:8000/novel1.txt")
    rclpy.spin(node)
    rclpy.shutdown()
