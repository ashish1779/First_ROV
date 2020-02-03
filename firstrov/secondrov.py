#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32
from random import randint
 
def ball_coordinate():
    rnd= randint(0,100)
    #rnd = int(input())
    return rnd

if __name__=='__main__':
    rospy.init_node('ball_coordinate')
    pub=rospy.Publisher('ball_coord', Int32, queue_size=10)
    rate= rospy.Rate(5)
 
    while not rospy.is_shutdown():
	ball_coord=ball_coordinate()
        rospy.loginfo("Location of ball: %s", ball_coord)
        pub.publish(ball_coord)

rate.sleep()
