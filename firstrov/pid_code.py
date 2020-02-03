#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float32

dd_data = 0
def callback1(data):
    #print ("Depth",data.data)
    global x
    rospy.loginfo("I heard1 %s", data.data)
    x=data

def callback2(data):
    #print ("Kp",data.data)
    rospy.loginfo("I heard2 %s", data.data)
 
def callback3(data):
    #print ("Ki",data.data)
    rospy.loginfo("I heard3 %s", data.data)
 
def callback4(data):
    #print ("Ki",data.data)
    rospy.loginfo("I heard4 %s", data.data)
     
def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener')

    rospy.Subscriber("Measure_depth", Int32, callback1)
    rospy.Subscriber("Kp", Float32, callback2)
    rospy.Subscriber("Kd", Float32, callback3)
    rospy.Subscriber("Ki", Float32, callback4)

    rospy.spin()

if __name__ == '__main__':
    #listener()
    
    rospy.init_node('listener')
    while not rospy.is_shutdown():
	rospy.Subscriber("Measure_depth", Int32, callback1)	
	rospy.Subscriber("Kp", Float32, callback2)
        rospy.Subscriber("Kd", Float32, callback3)
        rospy.Subscriber("Ki", Float32, callback4)
        print("x",x)
        rospy.spin()	

#rate.sleep()

    
