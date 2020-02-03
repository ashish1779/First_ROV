/*
  Code written by Ashish 3rd Feb 2020
 */
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>
 
ros::NodeHandle nh;

int depth_setpoint;     //subscribe
float kp,kd,ki; //subscribe

int depth;  //Publisher
int set_point;  //Publisher for looping data

float Front_sonar, Side_sonar;   //Publishing

//Subscribe data from nodes
void message1(const std_msgs::Int32 &msg1)
{
  depth_setpoint=msg1.data;
}

void message2(const std_msgs::Float32 &msg2)
{
  kp=msg2.data;
}

void message3(const std_msgs::Float32 &msg3)
{
  kd=msg3.data;
}

void message4(const std_msgs::Float32 &msg4)
{
  ki=msg4.data;
}

ros::Subscriber<std_msgs::Int32> sub1("SetPoint_depth", &message1);
ros::Subscriber<std_msgs::Float32> sub2("Kp", &message2);
ros::Subscriber<std_msgs::Float32> sub3("Kd", &message3);
ros::Subscriber<std_msgs::Float32> sub4("Ki", &message4);

sensor_msgs::Range sonar_msg; 
ros::Publisher pub1("/Front_sonar", &sonar_msg); 

ros::Publisher pub2("/Side_sonar2", &sonar_msg);

std_msgs::Int32 depth_msg;
ros::Publisher pub_depth("Depth", &depth_msg);

std_msgs::Int32 setpoint_msg;
ros::Publisher pub_setpoint("SetPoint", &setpoint_msg);

char frameid[] ="/sonar_ranger";
unsigned long publisher_timer;

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.advertise(pub1);
  nh.advertise(pub2);
    sonar_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
    sonar_msg.header.frame_id =  frameid;
    sonar_msg.field_of_view = (10.0/180.0) * 3.14;
    sonar_msg.min_range = 0.0;
    sonar_msg.max_range = 10.0;
  
  nh.advertise(pub_depth);
  nh.advertise(pub_setpoint);
    
}

void loop()
{
  if(depth_setpoint>80 && kp>5 &&kd>5 &&ki>5)   //Just to check getting value or not
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  if ((millis() - publisher_timer)> 50 ) 
   {
   Front_sonar = random(0, 30);
   Side_sonar = random(0, 30);
   sonar_msg.range = Front_sonar;
   sonar_msg.range = Side_sonar;
   sonar_msg.header.stamp = nh.now();
   pub1.publish(&sonar_msg);
   pub2.publish(&sonar_msg);
   publisher_timer = millis(); //publish once a second
   }

   
   setpoint_msg.data = depth_setpoint;
   pub_setpoint.publish(&setpoint_msg);

   depth = random(0,80);
   depth_msg.data = depth;
   pub_depth.publish(&depth_msg);

   nh.spinOnce();

}

void pid()
{
  ;//Kp,Kd,Ki
}
 
