#include <iostream>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "std_srvs/Empty.h"


class TurtleController
{
private:
    //A publisher to publish messages
    ros::Publisher cmd_vel_pub;
    
    // A service server to stop and start the robot
    ros::ServiceServer stop_service;
    
    // The current linear and angular speeds
    float lin_speed;
    float ang_speed;
    
    // Tells us whether the turtle is moving
    bool is_running;

    geometry_msgs::Twist calculateCommand()
    {
        auto msg = geometry_msgs::Twist();
        
        // TODO: Control code goes here
        if (this->is_running){
        	//Get the message stored in private variables and push it
        	msg.linear.x = this->lin_speed;
        	msg.angular.z = this->ang_speed;
        }
        
	//Return the message
        return msg;
    }
    
    bool flip_state(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
    {   
        // Flip the flags
        if (this->is_running)
            this->is_running = false;
        else
            this->is_running = true;

        // Services must always return a bool
        return true;
    }

public:
    TurtleController(){
        // Initialize ROS
        ros::NodeHandle n;
        
        // We're running by default
        this->is_running = true;
        
        n.param<float>("linear_speed", this->lin_speed,5.0);
        n.param<float>("angular_speed", this->ang_speed,5.0);

        // Create a publisher object, able to push messages
        // TODO
        this->cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
        
        // Create a service handler for stopping and re-starting the robot
        this->stop_service = n.advertiseService("stop_turtle", &TurtleController::flip_state, this);
    }

    void run(){
        // Send messages in a loop
        ros::Rate loop_rate(10);
        while (ros::ok())
        {
            // Calculate the command to apply (message received)
            auto msg = calculateCommand();

            // Publish the new command
            // TODO
            this->cmd_vel_pub.publish(msg);

            // And throttle the loop
            loop_rate.sleep();
        }
    }

};


int main(int argc, char **argv){
    // Initialize ROS
    ros::init(argc, argv, "talker");

    // Create our controller object
    // The object now has given lin_speed,ang_speed and a publisher object
    auto controller = TurtleController();
    
    //Run the controller object (loop inside)
    controller.run();

    // And make good on our promise
    return 0;
}
