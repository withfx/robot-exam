#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "add_two_ints_srv/srv/add_two_ints.hpp"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("add_two_ints_client");

    // 服务名和 a、b 都可以在 params.yaml 里改
    node->declare_parameter<std::string>("service_name", "add_two_ints");
    node->declare_parameter("a", 3);
    node->declare_parameter("b", 5);

    std::string service_name = node->get_parameter("service_name").as_string();
    int a = node->get_parameter("a").as_int();
    int b = node->get_parameter("b").as_int();

    auto client = node->create_client<add_two_ints_srv::srv::AddTwoInts>(service_name);

    // 等服务器启动，等不到就一直等，按 Ctrl+C 可以退出
    while (!client->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node->get_logger(), "等待服务时程序被中断");
            return 0;
        }
        RCLCPP_INFO(node->get_logger(), "等待服务 %s 启动...", service_name.c_str());
    }

    auto request = std::make_shared<add_two_ints_srv::srv::AddTwoInts::Request>();
    request->a = a;
    request->b = b;

    RCLCPP_INFO(node->get_logger(), "发送请求：%d + %d", a, b);

    auto future = client->async_send_request(request);

    if (rclcpp::spin_until_future_complete(node, future) == rclcpp::FutureReturnCode::SUCCESS) {
        auto response = future.get();
        RCLCPP_INFO(node->get_logger(), "收到响应：%ld + %ld = %ld",
                    (long)a, (long)b, (long)response->sum);
    } else {
        RCLCPP_ERROR(node->get_logger(), "调用服务失败");
    }

    // 发完请求不退出，保持节点在运行，方便 ros2 node list 看到
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
