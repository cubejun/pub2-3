#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>
#include <chrono>
#include <functional>
//#include <string>
using namespace std::chrono_literals;
void callback(rclcpp::Node::SharedPtr node, rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub)
{
    //auto message = std_msgs::msg::String();
    auto input = geometry_msgs::msg::Twist();
    input.linear.x=8.0;//직진속도 8
    input.angular.z=2.0;//각속도 2로 거북이 움직임
    RCLCPP_INFO(node->get_logger(), "linear.x: %f angular.z: %f", input.linear.x, input.angular.z);
    pub->publish(input);
    
}
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("mynode");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile);
    ///turtle1/cmd_vel으로 퍼블리시하는 퍼블리셔 생성. 
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(1s, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}