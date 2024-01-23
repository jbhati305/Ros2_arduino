#include <arduinobot_controller/arduinobot_interface.hpp>

using namespace arduinobot_controller
{
    ArduinobotInterface::ArduinobotInterface()
    {
    }

    ArduinobotInterface::~ArduinobotInterface()
    {
        if (arduino_.IsOpen())
        {
            try
            {
                arduino_.close();
            }
            catch (...)
            {
                RCLCPP_FATAL_STREAM(rclcpp::get_logger("ArduinobotInterface"), "Something went wrong while closing the connection with port: " << port_);
            }
        }
    }

    CallbackReturn ArduinobotInterface::on_init(const hardware_interface::HardwareInfo & hardware_info)
    {
        CallbackReturn result = hardware_interface::SystemInterface::on_init(hardware_info);

        if(result != CallbackReturn::SUCCESS)
        {
            return result;
        }

        try
        {
            port_ = info_.harware_parameters.at("port");
        }
        catch(const std::out_of_range &e)
        {
           RCLCPP_FATAL(rclcpp::get_logger("ArduinobotInterface"), "No Serial port provided!! Aborting");
           return CallbackReturn::FAILURE;
           
        }
        
    }
}