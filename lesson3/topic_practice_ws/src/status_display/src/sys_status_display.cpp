#include <QString>
#include <QLabel>
#include <QApplication>
#include <rclcpp/rclcpp.hpp>
#include <status_interfaces/msg/system_status.hpp>

using SystemStatus = status_interfaces::msg::SystemStatus;

class SystemStatusDisplay : public rclcpp::Node
{
private:
    rclcpp::Subscription<SystemStatus>::SharedPtr subscriber_;
    QLabel *label_;

public:
    SystemStatusDisplay() : Node("sys_status_display")
    {
        label_ = new QLabel();
        subscriber_ = create_subscription<SystemStatus>("system_status", 10, [&](const SystemStatus::SharedPtr msg) -> void
                                                        { label_->setText(get_qstring_from_msg(msg)); });
        label_->setText(get_qstring_from_msg(std::make_shared<SystemStatus>()));
        label_->show();
    }

protected:
    QString get_qstring_from_msg(const SystemStatus::SharedPtr msg)
    {
        std::stringstream show_str;
        show_str << "==========系统状态可视化显示工具==========\n"
                 << "数 据 时 间\t" << msg->stamp.sec << "\ts\n"
                 << "主 机 名 字\t" << msg->host_name << "\n"
                 << "CPU使用率\t" << msg->cpu_percent << "%\n"
                 << "内存使用率\t" << msg->memory_percent << "%\n"
                 << "内存总量\t\t" << msg->memory_total << "MB\n"
                 << "内存可用量\t" << msg->memory_avaliable << "MB\n"
                 << "网络发送量\t" << msg->net_sent << "MB\n"
                 << "网络接收量\t" << msg->net_recv << "MB\n"
                 << "=====================================";
        return show_str.str().c_str();
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);
    auto node = std::make_shared<SystemStatusDisplay>();
    std::thread spin_thread([&]() -> void
                            { rclcpp::spin(node); });
    spin_thread.detach();
    app.exec();
    rclcpp::shutdown();
    return 0;
}