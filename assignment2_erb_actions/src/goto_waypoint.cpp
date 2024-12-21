#include "assignment2_erb_actions/goto_waypoint.h"
#include <unistd.h>
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <unordered_map>

namespace KCL_rosplan {

    GotoWaypoint::GotoWaypoint(ros::NodeHandle &nh) {
        // Initialize waypoints
        waypoints_["wp1"] = std::make_pair(-7.0, -1.5);
        waypoints_["wp2"] = std::make_pair(-3.0, -8.0);
        waypoints_["wp3"] = std::make_pair(6.0, 2.0);
        waypoints_["wp4"] = std::make_pair(7.0, -5.0);
    }

    bool GotoWaypoint::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr &msg) {
        // Extract the waypoint name
        std::string waypoint = msg->parameters[2].value;

        // Check if the waypoint exists in the dictionary
        if (waypoints_.find(waypoint) == waypoints_.end()) {
            ROS_ERROR("Waypoint %s not found!", waypoint.c_str());
            return false;
        }

        // Get the coordinates of the waypoint
        auto coords = waypoints_[waypoint];
        double x = coords.first;
        double y = coords.second;

        // Create a SimpleActionClient for move_base
        actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base", true);

        // Wait for the action server to start
        ROS_INFO("Waiting for the move_base action server to start...");
        ac.waitForServer();

        // Create a goal to send to move_base
        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        goal.target_pose.pose.position.x = x;
        goal.target_pose.pose.position.y = y;
        goal.target_pose.pose.orientation.w = 1.0;

        // Send the goal
        ROS_INFO("Sending goal to move_base: waypoint %s (x: %.2f, y: %.2f)", waypoint.c_str(), x, y);
        ac.sendGoal(goal);

        // Wait for the result
        ac.waitForResult();

        // Check the result
        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
            ROS_INFO("Successfully reached waypoint %s!", waypoint.c_str());
            return true;
        } else {
            ROS_WARN("Failed to reach waypoint %s.", waypoint.c_str());
            return false;
        }
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "goto_waypoint", ros::init_options::AnonymousName);
    ros::NodeHandle nh("~");
    KCL_rosplan::GotoWaypoint my_aci(nh);
    my_aci.runActionInterface();
    return 0;
}

