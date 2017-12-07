#include <JY901.h>
#include <ros.h>
#include<geometry_msgs/Vector3.h>
#include <Wire.h>

ros::NodeHandle  nh;
geometry_msgs::Vector3 vector3_msg;  
ros::Publisher pub_vector3("vector3_data",&vector3_msg);  
char frameid[] = "/ult_vector3";  

void setup()
{
  nh.initNode();
  nh.advertise(pub_vector3);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
   while (Serial1.available()) 
  {
    JY901.CopeSerialData(Serial1.read()); //Call JY901 data cope function
  }
  vector3_msg.x= (int)JY901.stcGyro.w[0];  
  vector3_msg.y= (int)JY901.stcGyro.w[1]; 
  vector3_msg.z= (int)JY901.stcGyro.w[2]; 

  pub_vector3.publish(&vector3_msg); 
  nh.spinOnce();
  delay(50);
}
