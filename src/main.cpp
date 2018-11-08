#include "Messenger.h"

#ifdef HAS_ROS
#include "ros/ros.h"
#include <sensor_msgs/Image.h>
#endif

#ifndef LOG
#define LOG(c) std::cerr
#endif

void receiveInt(const std::shared_ptr<int>& msg){
    LOG(INFO)<<"Received "<<*msg<<" in thread "
            <<std::this_thread::get_id()<<std::endl;
}

void receiveIntRef(const int& msg){
    LOG(INFO)<<"Received ref "<<msg<<" in thread "
            <<std::this_thread::get_id()<<std::endl;
}

class ObjectCaller
{
public:
    void receiveInt(const std::shared_ptr<int>& msg){
        LOG(INFO)<<"receiveInt "<<*msg<<" with para "<<para<<" in thread "
                <<std::this_thread::get_id()<<std::endl;
    }

    void receiveStringPtr(const std::shared_ptr<std::string>& msg){
        LOG(INFO)<<"receiveStringPtr "<<*msg<<" with para "<<para<<" in thread "
                <<std::this_thread::get_id()<<std::endl;
    }

    void receiveString(const std::string& msg){
        LOG(INFO)<<"receiveString "<<msg<<" with para "<<para<<" in thread "
                <<std::this_thread::get_id()<<std::endl;
    }
    int para=1;
};


#ifdef HAS_ROS
void rosMessageCallback(const sensor_msgs::Image& img)
{
    LOG(INFO)<<"rosMessageCallback "<<img.header.frame_id;
}

void testROS()
{
    using namespace GSLAM;
    auto publisher=GSLAM::Messenger::instance().advertise<sensor_msgs::Image>("ros_image");
    GSLAM::Messenger::instance().subscribe("ros_image",0,rosMessageCallback);

    sensor_msgs::Image msg;
    msg.header.frame_id="frame_id:100";
    publisher.publish(msg);
}

#else

void testROS()
{

}

#endif

int main(int argc,char** argv){
    using namespace GSLAM;
    ObjectCaller caller;
    Publisher  pubInt=Messenger::instance().advertise<int>("int",2);
    Subscriber subInt=Messenger::instance().subscribe("int",0,receiveInt);
    Subscriber subInt1=Messenger::instance().subscribe("int",1,&ObjectCaller::receiveInt,&caller);
    Subscriber subInt2=Messenger::instance().subscribe("int",0,receiveIntRef);


    Subscriber subString=Messenger::instance().subscribe("string",0,&ObjectCaller::receiveString,&caller);
    Subscriber subString1=Messenger::instance().subscribe("string",0,&ObjectCaller::receiveStringPtr,&caller);
    Publisher  pubString=Messenger::instance().advertise<std::string>("string");

    pubInt.publish(100);
    pubString.publish(std::string("hello world"));
    pubString.publish(std::shared_ptr<std::string>(new std::string("hello again")));

    LOG(INFO)<<pubInt.getNumSubscribers()<<","
            <<subInt.getNumPublishers()<<","
           <<subInt1.getNumPublishers()<<","
          <<pubString.getNumSubscribers()<<","
         <<subString.getNumPublishers()<<std::endl;
    std::this_thread::sleep_for(std::chrono::duration<double>(1));

    testROS();
    return 0;
}
