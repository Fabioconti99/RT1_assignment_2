#include "ros/ros.h"
#include "second_assignment/Accelerate.h"
#include "std_srvs/Empty.h"

// Global variable of the velocity factor that will be set as the value of the server's response.
float acc=0;

// bool function of the server.
bool char_input (second_assignment::Accelerate::Request &req, second_assignment::Accelerate::Response &res)
{
    // Declaration of the server needed to call the reset function.
	std_srvs::Empty reset_srv;
    
    // If the input service is 'a', a .5 factor will be added to the acc global variable.
	if (req.input=='a'){
	
		std::cout<<"got a\n";
		acc =acc+0.5;
		
		
	}
    
    // If the input service is 's', a .5 factor will be taken off the acc global variable.
	if (req.input == 's'){
	
		std::cout<<"got s\n";
		acc =acc-0.5;
		
	}
    
    // If the input service is 'r', the position of the robot will be reset to the starting position.
	if (req.input == 'r'){
	
		std::cout<<"got r\n";
		
		ros::service::call("/reset_positions", reset_srv);
		
	}
	
    // If any other character is pressed an error message will show up.
	if (req.input != 's' && req.input != 'r' && req.input != 'a' ){
		std::cout<<"wrong char\n";
		
	}
	
    
	res.val = acc;
	std::cout<<res.val<<"\n";
	return true; 
}


int main(int argc, char **argv) {

    // Initialize the node, setup the NodeHandle for handling the communication with the ROS system.
	ros::init(argc, argv, "input");
	ros::NodeHandle n;
    
    // Initialize the service.
	ros::ServiceServer service = n.advertiseService("/accelerate",char_input);
    
    
	ros::spin();
    
    // Function to loop the callback function.
	return 0; 
}
