#include "assignment2_erb_actions/detect_marker.h"
#include <unistd.h>
#include <aruco_ros/aruco_ros_utils.h>
#include <ros/ros.h>

namespace KCL_rosplan {

    DetectMarker::DetectMarker(ros::NodeHandle &nh) {
    
    }

    bool DetectMarker::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr &msg) {
    
        std::string waypoint = msg->parameters[1].value;

        // Send the goal
        ROS_INFO("Detecting marker linked to waypoint %s ", waypoint.c_str());
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "detect_marker", ros::init_options::AnonymousName);
    ros::NodeHandle nh("~");
    KCL_rosplan::DetectMarker my_aci(nh);
    my_aci.runActionInterface();
    return 0;
}

