
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"


float front_dist;
float right_dist;
float left_dist;

void scanCallback(const sensor_msgs::LaserScan &msg) {

   front_dist = msg.ranges[0];
   right_dist = msg.ranges[270];
   left_dist = msg.ranges[90];
    }
    int main(int argc, char** argv) {

    ros::init(argc, argv, "avoid_obstacle");

    ros::NodeHandle n;

    geometry_msgs::Twist vel_msg;

    ros::Subscriber sub = n.subscribe("/scan", 100, scanCallback);
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

    ros::Rate loop_rate(30);

    while (ros::ok()) {
 if (front_dist > 1.0 && right_dist > 1.0 && left_dist > 1.0 )
    {
      vel_msg.linear.x = 0.4;
      vel_msg.angular.y =0.0;
      vel_msg.angular.z = 0.0; 
      ROS_INFO(" Move Forward: [%f]",front_dist);

    }
     if (front_dist < 1.0 || right_dist <= 1.0)
    {
      vel_msg.linear.x = 0.0;
      vel_msg.angular.y =0.0;
      vel_msg.angular.z = 0.3; 

      ROS_INFO("Turn Left: [%f]",right_dist);
    }
    if (left_dist <= 1.0){
      vel_msg.linear.x = 0.0; 
      vel_msg.angular.y =0.0;
      vel_msg.angular.z = -0.3;

      ROS_INFO("Turn Right : [%f]",left_dist);

    }
    pub.publish(vel_msg);
    loop_rate.sleep();
    ros::spinOnce();
 
 }

    return 0;
    }

    
