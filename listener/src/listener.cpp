#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>

#include <std_msgs/msg/string.hpp>
#include <std_srvs/srv/empty.hpp>


class Listener : public rclcpp::Node
{
public:
  explicit Listener()
  : Node("listener")
  {
    declare_parameter("heard_word");
    
    get_parameter("heard_word", heard_word_);

    auto callback =
      [this](std_msgs::msg::String::ConstSharedPtr msg) -> void
      {
        RCLCPP_INFO(get_logger(), "I %s: [%s]", heard_word_.c_str(), msg->data.c_str());
      };
    sub_ = create_subscription<std_msgs::msg::String>("chatter", 10, callback);

    service_ = create_service<std_srvs::srv::Empty>("good_bye",[this](const std::shared_ptr<std_srvs::srv::Empty::Request>, std::shared_ptr<std_srvs::srv::Empty::Response>){
      RCLCPP_INFO(get_logger(), "Message from the goodbye service");
    });
  }
  ~Listener(){
    std::cout << "HEEEERERRERERERERERE" << std::endl;
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
  std::string heard_word_{"heard"};
  rclcpp::Service<std_srvs::srv::Empty>::SharedPtr service_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>());
  rclcpp::shutdown();
  return 0;
}
