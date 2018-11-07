# Messenger from GSLAM

This is a tiny tool which implemented an intra process message transfer like ROS. 
It's a part of GSLAM(https://github.com/zdzhaoyong/GSLAM).

The tool has the following features:
* Header only based on c++11, no extra dependency, makes it portable.
* Thread safe and support multi-thread condition notify mode by setting the queue size.
* Able to transfer any classes efficiently, including ROS defined messages, which means it can replace ROS messagging or work with it.
