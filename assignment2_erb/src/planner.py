#!/usr/bin/env python

import rospy
from std_srvs.srv import Empty
from std_msgs.msg import String
from rosplan_dispatch_msgs.msg import CompletePlan
from rosplan_dispatch_msgs.srv import DispatchService


class Planner:
    def __init__(self):
        # Initialize the ROS node
        rospy.init_node('planner')
        
        #class variables
        self.problem_generated = False
        self.plan_generated = False
        self.plan_parsed = False
        
        # Initialize subscribers
        self.problem_subscriber = rospy.Subscriber('/rosplan_problem_interface/problem_instance', String, self.problem_instance_callback)
        self.plan_subscriber = rospy.Subscriber('/rosplan_planner_interface/planner_output', String, self.planner_output_callback)
        self.complete_plan_subscriber = rospy.Subscriber('/rosplan_parsing_interface/complete_plan', CompletePlan, self.complete_plan_callback)
        
        ################### GENERATE PROBLEM  ###################

        rospy.wait_for_service('/rosplan_problem_interface/problem_generation_server')

        self.problem_generation_service = rospy.ServiceProxy('/rosplan_problem_interface/problem_generation_server', Empty)
        
        self.call(self.problem_generation_service, "Problem Generation")
        
        while not self.problem_generated : 
        	rospy.sleep(0.1)
        	
        rospy.loginfo("Problem generated")
        
        ################### GENERATE PLAN  ###################
        
        rospy.wait_for_service('/rosplan_planner_interface/planning_server')
        
        self.plan_generation_service = rospy.ServiceProxy('/rosplan_planner_interface/planning_server', Empty)
        
        self.call(self.plan_generation_service, "Plan Generation")
        
        while not self.plan_generated : 
        	rospy.sleep(0.1)
        	
        rospy.loginfo("Plan generated")      
        
        ################### PARSE PLAN  ###################  
        
        rospy.wait_for_service('/rosplan_parsing_interface/parse_plan')
        
        self.plan_parsing_service = rospy.ServiceProxy('/rosplan_parsing_interface/parse_plan', Empty)
        
        self.call(self.plan_parsing_service, "Plan Parsing")

        while not self.plan_parsed:
        	rospy.sleep(0.1)
        	
        rospy.loginfo("Plan parsed")
        
        ################### DISPATCH PLAN  ################### 
        
        rospy.wait_for_service('/rosplan_plan_dispatcher/dispatch_plan')
        
        self.plan_dispatching_service = rospy.ServiceProxy('/rosplan_plan_dispatcher/dispatch_plan', DispatchService)
        
        self.call(self.plan_dispatching_service, "Plan Dispatching")
        

    def call(self, service, name):
        try:
            # Call the service
            service()
                
        except rospy.ServiceException as e:
            rospy.logerr("%s service call failed: %s" % name % e)

    def problem_instance_callback(self, msg):
        """Callback function to handle received problem instance."""
        self.problem_generated = True

    def planner_output_callback(self, msg):
    	self.plan_generated = True
    
    def complete_plan_callback(self, msg):
    	self.plan_parsed = True


if __name__ == '__main__':
    try:
        
        planner = Planner()
        rospy.spin()

    except rospy.ROSInterruptException:
        rospy.loginfo("User node shut down.")


