#include "rclcpp/rclcpp.hpp"

class PersonNode : public rclcpp::Node
{
protected:
    std::string name_;
    int age_;

public:
    PersonNode(const std::string &node_name, const std::string &name, const int age);
    void Eat(const std::string &food);
};

PersonNode::PersonNode(const std::string &node_name, const std::string &name, const int age) : Node(node_name)
{
    name_ = name;
    age_ = age;
}

void PersonNode::Eat(const std::string &food)
{
    RCLCPP_INFO(get_logger(), "I am %s, I am %d years old, and I am eating %s", name_.c_str(), age_, food.c_str());
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node=std::make_shared<PersonNode>("cpp_person_node", "John", 25);
    RCLCPP_INFO(node->get_logger(), "Hello C++ Person Node");
    node->Eat("apple");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}