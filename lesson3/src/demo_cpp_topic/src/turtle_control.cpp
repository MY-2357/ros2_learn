#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"

class TurtleControlNode : public rclcpp::Node
{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
    double target_x{1.0};
    double target_y{1.0};
    double k_{1.0};
    double max_speed_{1.5};

public:
    explicit TurtleControlNode(const std::string node_name) : Node(node_name)
    {
        RCLCPP_INFO(get_logger(), "%s,启动！", node_name.c_str());
        publisher_ = create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        subscriber_ = create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&TurtleControlNode::on_pose_received, this, std::placeholders::_1));
    }

    void on_pose_received(const turtlesim::msg::Pose::SharedPtr pose)
    {
        auto current_x = pose->x;
        auto current_y = pose->y;
        RCLCPP_INFO(get_logger(), "当前：x=%f,y=%f", current_x, current_y);

        int distance = std::sqrt(
            (current_x - target_x) * (current_x - target_x) +
            (current_y - target_y) * (current_y - target_y));
        auto angle = std::atan2(target_y - current_y, target_x-current_x) - pose->theta;

        auto msg = geometry_msgs::msg::Twist();
        if (distance > 0.1)
        {
            if (fabs(angle)>0.2)
            {
                msg.angular.z = fabs(angle);
            }
            else
            {
                msg.linear.x = k_ * distance;
            }
            if (msg.linear.x > max_speed_)
                msg.linear.x = max_speed_;
        }
        publisher_->publish(msg);
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleControlNode>("turtle_control");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}