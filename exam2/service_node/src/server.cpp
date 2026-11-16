#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "add_two_ints_srv/srv/add_two_ints.hpp"

// 加法服务端：收到 a、b，返回 a+b
class AddTwoIntsServer : public rclcpp::Node
{
public:
    AddTwoIntsServer() : Node("add_two_ints_server")
    {
        // 服务名从参数里读，方便在 params.yaml 里改
        this->declare_parameter<std::string>("service_name", "add_two_ints");
        service_name_ = this->get_parameter("service_name").as_string();

        service_ = this->create_service<add_two_ints_srv::srv::AddTwoInts>(
            service_name_,
            std::bind(&AddTwoIntsServer::handle_add, this,
                      std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "服务端已启动：%s", service_name_.c_str());
    }

private:
    void handle_add(
        const std::shared_ptr<add_two_ints_srv::srv::AddTwoInts::Request> request,
        std::shared_ptr<add_two_ints_srv::srv::AddTwoInts::Response> response)
    {
        response->sum = request->a + request->b;

        RCLCPP_INFO(this->get_logger(), "收到请求：%ld + %ld = %ld",
                    request->a, request->b, response->sum);
    }

    rclcpp::Service<add_two_ints_srv::srv::AddTwoInts>::SharedPtr service_;
    std::string service_name_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
