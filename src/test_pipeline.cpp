#include "depthai_test_plugin/pipeline/test_base_types.hpp"

#include "depthai/device/Device.hpp"
#include "depthai/pipeline/Pipeline.hpp"
#include "depthai_ros_driver/dai_nodes/base_node.hpp"
#include "depthai_ros_driver/dai_nodes/nn/nn_helpers.hpp"
#include "depthai_ros_driver/dai_nodes/nn/nn_wrapper.hpp"
#include "depthai_ros_driver/dai_nodes/nn/spatial_nn_wrapper.hpp"
#include "depthai_ros_driver/dai_nodes/sensors/imu.hpp"
#include "depthai_ros_driver/dai_nodes/sensors/sensor_helpers.hpp"
#include "depthai_test_plugin/dai_nodes/sensors/rgb_test.hpp"
#include "depthai_ros_driver/dai_nodes/sensors/rgb.hpp"
#include "depthai_ros_driver/dai_nodes/stereo.hpp"
#include "depthai_ros_driver/pipeline/base_pipeline.hpp"
#include "depthai_ros_driver/utils.hpp"
#include "rclcpp/node.hpp"

namespace depthai_test_plugin
{
    namespace pipeline_gen
    {
        std::vector<std::unique_ptr<depthai_ros_driver::dai_nodes::BaseNode>> RGB_test_pipeline::createPipeline(rclcpp::Node *node,
                                                                               std::shared_ptr<dai::Device> device,
                                                                               std::shared_ptr<dai::Pipeline> pipeline,
                                                                               const std::string &nnType)
        { 
            auto sensorName = device->getCameraSensorNames().at(dai::CameraBoardSocket::CAM_A);
            std::vector<std::unique_ptr<depthai_ros_driver::dai_nodes::BaseNode>> daiNodes;
            std::vector<depthai_ros_driver::dai_nodes::sensor_helpers::ImageSensor>::iterator sensorIt =
            std::find_if(depthai_ros_driver::dai_nodes::sensor_helpers::availableSensors.begin(), depthai_ros_driver::dai_nodes::sensor_helpers::availableSensors.end(), [&sensorName](const depthai_ros_driver::dai_nodes::sensor_helpers::ImageSensor& s) {
                    return s.name == sensorName;
                });
            if(sensorIt == depthai_ros_driver::dai_nodes::sensor_helpers::availableSensors.end()) {
                RCLCPP_ERROR(node->get_logger(), "Sensor %s not supported!", sensorName.c_str());
                throw std::runtime_error("Sensor not supported!");
            }

            auto rgb = std::make_unique<depthai_test_plugin::dai_nodes::RGB_test>("RGB_test", node, pipeline, dai::CameraBoardSocket::CAM_A, (*sensorIt), true);
            // auto rgb = std::make_unique<depthai_ros_driver::dai_nodes::RGB>("RGB_test", node, pipeline, dai::CameraBoardSocket::CAM_A, (*sensorIt), true);

            daiNodes.push_back(std::move(rgb));
            return daiNodes;
        }
    }
}

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(depthai_test_plugin::pipeline_gen::RGB_test_pipeline, depthai_ros_driver::pipeline_gen::BasePipeline)