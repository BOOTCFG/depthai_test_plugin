#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "depthai_ros_driver/dai_nodes/base_node.hpp"
#include "depthai_ros_driver/pipeline/base_pipeline.hpp"

namespace dai {
class Pipeline;
class Device;
}  // namespace dai

namespace rclcpp {
class Node;
}
namespace depthai_test_plugin {
namespace pipeline_gen {
class RGB_test_pipeline : public depthai_ros_driver::pipeline_gen::BasePipeline {
   public:
    std::vector<std::unique_ptr<depthai_ros_driver::dai_nodes::BaseNode>> createPipeline(rclcpp::Node* node,
                                                                     std::shared_ptr<dai::Device> device,
                                                                     std::shared_ptr<dai::Pipeline> pipeline,
                                                                     const std::string& nnType) override;
};
}  // namespace pipeline_gen
}  // namespace depthai_test_plugin