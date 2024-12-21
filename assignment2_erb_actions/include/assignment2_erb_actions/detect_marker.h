#ifndef DETECT_MARKER_H
#define DETECT_MARKER_H

#include <ros/ros.h>
#include <rosplan_action_interface/RPActionInterface.h>
#include <rosplan_dispatch_msgs/ActionDispatch.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

#include <string>
#include <utility>

namespace KCL_rosplan {

class DetectMarker : public RPActionInterface
{
private:

public:
    DetectMarker(ros::NodeHandle &nh);
    bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr &msg) override;
};

} 

#endif

