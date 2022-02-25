#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

// global declaration for publisher
ros::Publisher trans_pub;

// declaration of functions
void trans(double linear_x, double linear_y);
void makingStandarHouse();
void making3DHouse();
void addGridtoRoof();

int main(int argc, char **argv){
    // node inisialization
	ros::init(argc, argv, "turtle_trans");

    // for covering all communication function in ROS
	ros::NodeHandle nh;

    // pub and sub assignment
	trans_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    // making the house
    makingStandarHouse();
    making3DHouse();
    addGridtoRoof();
    
	ros::spin();

	return 0;
}

void trans(double linear_x, double linear_y){
    // object declaration
    geometry_msgs::Twist msg;

    // assign the turtle track
    msg.linear.x = linear_x;
    msg.linear.y = linear_y;
    msg.linear.z = 0;
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = 0;

    // measuring distance of turtle will take
    double distance = sqrt(pow(linear_x, 2) + pow(linear_y, 2));

    double current_distance = 0.0;

    // i make it 100 Hz so the track will be made more accurate
    ros::Rate loop_rate(1000);
    double t0 = ros::Time::now().toSec();
    while(current_distance < distance){  // turtle will keep moving until the distance exceeded
        double t1 = ros::Time::now().toSec();
        current_distance = distance * (t1-t0);
        trans_pub.publish(msg);  // make the turtle move
        ros::spinOnce();
        loop_rate.sleep();
    }
    // reset the value so the turtle will no longer move 
    msg.linear.x = 0;
    msg.linear.y = 0;
    trans_pub.publish(msg);
}

void makingStandarHouse(){
    // making triangle
	trans(-3, 0); trans(1.5, 2);trans(1.5, -2); trans(-3, 0);
    // making rectangle (and the door)
    trans(0, -3); trans(2, 0); trans(0, 1.3); trans(-1, 0); trans(0, -1.3); trans(2, 0); trans(0, 3);
}

void making3DHouse(){
    // making the right side of house
    trans(2.5, 2.5); trans(0, -2); trans(-2.5, -3.5); trans(0, 3);
    // making the roof
    trans(2.5, 2.5); trans(-1.35, 1.35); trans(-2.65, -1.85);   
}

void addGridtoRoof(){
    // making roof grid
    trans(0.3, -0.4); trans(2.62, 1.98); trans(0.27, -0.27); trans(-2.51, -2.11);
    trans(0.3, -0.4); trans(2.46, 2.24); trans(0.27, -0.27); trans(-2.53, -2.37);
}
