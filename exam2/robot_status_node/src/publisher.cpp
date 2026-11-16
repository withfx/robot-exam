#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "robot_status_msg/msg/robot_status.hpp"

// 发布机器人状态的节点
class RobotStatusPublisher : public rclcpp::Node
{
public:
    RobotStatusPublisher() : Node("robot_status_publisher")
    {
        // 下面三个参数都可以在 params.yaml 里改，代码里不用写死
        this->declare_parameter<std::string>("topic_name", "robot_status");
        this->declare_parameter<double>("publish_rate", 1.0);
        this->declare_parameter<std::string>("robot_name", "atil_1");

        topic_name_ = this->get_parameter("topic_name").as_string();
        publish_rate_ = this->get_parameter("publish_rate").as_double();
        robot_name_ = this->get_parameter("robot_name").as_string();

        publisher_ = this->create_publisher<robot_status_msg::msg::RobotStatus>(topic_name_, 10);

        // 每隔 1/publish_rate 秒执行一次 timer_callback
        timer_ = this->create_wall_timer(
            std::chrono::duration<double>(1.0 / publish_rate_),
            std::bind(&RobotStatusPublisher::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "发布者已启动：话题 %s，频率 %.1f Hz",
                    topic_name_.c_str(), publish_rate_);
    }

private:
    void timer_callback()
    {
        auto msg = robot_status_msg::msg::RobotStatus();
        msg.robot_name = robot_name_;
        msg.speed = 0.5f;

        // 让坐标慢慢变大，看起来像机器人在动
        position_x_ = position_x_ + 0.5f;
        position_y_ = position_y_ + 0.25f;
        msg.position_x = position_x_;
        msg.position_y = position_y_;

        publisher_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "发布：%s 速度 %.2f 坐标 (%.2f, %.2f)",
                    msg.robot_name.c_str(), msg.speed, msg.position_x, msg.position_y);
    }

    rclcpp::Publisher<robot_status_msg::msg::RobotStatus>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::string topic_name_;
    std::string robot_name_;
    double publish_rate_ = 1.0;
    float position_x_ = 0.0f;
    float position_y_ = 0.0f;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotStatusPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
