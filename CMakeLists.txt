cmake_minimum_required(VERSION 3.8)
project(depthai_test_plugin)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

set(SENSOR_DEPS
cv_bridge 
camera_info_manager
depthai 
depthai_bridge 
rclcpp  
std_msgs 
sensor_msgs 
image_transport
pluginlib
depthai_ros_driver
)

include_directories(include)

set(SENSOR_LIB_NAME ${PROJECT_NAME})

add_library(
  ${SENSOR_LIB_NAME} SHARED
  src/test_pipeline.cpp
  src/dai_nodes/sensors/rgb_test.cpp
)


ament_target_dependencies(${SENSOR_LIB_NAME} ${SENSOR_DEPS})
target_link_libraries(
  ${SENSOR_LIB_NAME}
)

pluginlib_export_plugin_description_file(depthai_ros_driver depthai_test_plugin.xml)
ament_export_include_directories(include)

ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${COMMON_DEPS} ${SENSOR_DEPS} ${NN_DEPS} )

install(DIRECTORY launch config DESTINATION share/${PROJECT_NAME})


install(TARGETS ${SENSOR_LIB_NAME}
EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)
install(EXPORT ${PROJECT_NAME}Targets
      DESTINATION share/${PROJECT_NAME}/cmake)

ament_export_include_directories(
  include
)

install(
    DIRECTORY include/
    DESTINATION include
)
ament_export_libraries(
  ${SENSOR_LIB_NAME}
)
ament_export_targets(
  ${PROJECT_NAME}Targets
)

ament_package()
