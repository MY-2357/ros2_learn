import rclpy
from demo_python_pkg.person_node import PersonNode

class WriterNode(PersonNode):
    def __init__(self, name_value: str, age_value: int, book_name: str) -> None:
        super().__init__(name_value, age_value)
        self.book_name = book_name
    def write_book(self) -> None:
        self.get_logger().info(f"{self.name} is writing {self.book_name}.")

def main():
    rclpy.init()
    writer = WriterNode("John", 30, "The Great Gatsby")
    writer.eat("steak")
    writer.write_book()
    rclpy.spin(writer)
    rclpy.shutdown()
