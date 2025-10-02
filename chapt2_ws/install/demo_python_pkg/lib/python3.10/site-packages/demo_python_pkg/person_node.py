from rclpy.node import Node

class PersonNode(Node):
    def __init__(self, name_value: str, age_value: int) -> None:
        super().__init__(name_value)
        self.name = name_value
        self.age = age_value

    def eat(self, food_name: str) -> None:
        print(f"{self.name} is eating {food_name}s.")


def main():
    person = PersonNode("John", 25)
    person.eat("apple")
