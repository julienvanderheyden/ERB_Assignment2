#ifndef GOTO_WAYPOINT_H
#define GOTO_WAYPOINT_H

#include <ros/ros.h>
#include <rosplan_action_interface/RPActionInterface.h>
#include <rosplan_dispatch_msgs/ActionDispatch.h>
#include <unordered_map>
#include <string>
#include <utility>

namespace KCL_rosplan {

class GotoWaypoint : public RPActionInterface
{
private:
    // Dictionary to store waypoint names and coordinates
    std::unordered_map<std::string, std::pair<double, double>> waypoints_;

public:
    GotoWaypoint(ros::NodeHandle &nh);
    bool concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr &msg) override;
};

} 

#endif

