#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robot_status_msg/msg/robot_status.hpp"

// 订阅机器人状态的节点
class RobotStatusSubscriber : public rclcpp::Node
{
public:
    RobotStatusSubscriber() : Node("robot_status_subscriber")
    {
        // 话题名从参数里读，和发布者保持一致
        this->declare_parameter<std::string>("topic_name", "robot_status");
        topic_name_ = this->get_parameter("topic_name").as_string();

        subscription_ = this->create_subscription<robot_status_msg::msg::RobotStatus>(
            topic_name_, 10,
            std::bind(&RobotStatusSubscriber::topic_callback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "订阅者已启动：话题 %s", topic_name_.c_str());
    }

private:
    void topic_callback(const robot_status_msg::msg::RobotStatus::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "收到：%s 速度 %.2f 坐标 (%.2f, %.2f)",
                    msg->robot_name.c_str(), msg->speed, msg->position_x, msg->position_y);
    }

    rclcpp::Subscription<robot_status_msg::msg::RobotStatus>::SharedPtr subscription_;
    std::string topic_name_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotStatusSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
