#include "Messenger.h"

#ifndef LOG
#define LOG(c) std::cerr
#endif

void receiveInt(const std::shared_ptr<int>& msg){
    LOG(INFO)<<"Received "<<*msg<<" in thread "
            <<std::this_thread::get_id()<<std::endl;
}

class ObjectCaller
{
public:
    void receiveInt(const std::shared_ptr<int>& msg){
        LOG(INFO)<<"Received "<<*msg<<" with para "<<para<<" in thread "
                <<std::this_thread::get_id()<<std::endl;
    }

    void receiveString(const std::shared_ptr<std::string>& msg){
        LOG(INFO)<<"Received "<<*msg<<" with para "<<para<<" in thread "
                <<std::this_thread::get_id()<<std::endl;
    }
    int para=1;
};

int main(int argc,char** argv){
    using namespace GSLAM;
    Messenger  messenger;
    ObjectCaller caller;
    Publisher  pubInt=messenger.advertise<int>("int",2);
    Subscriber subInt=messenger.subscribe("int",0,receiveInt);
    Subscriber subInt1=messenger.subscribe("int",1,&ObjectCaller::receiveInt,&caller);


    Publisher  pubString=messenger.advertise<std::string>("string");
    Subscriber subString=messenger.subscribe("string",0,&ObjectCaller::receiveString,&caller);

    pubInt.publish(100);
    pubString.publish(std::string("hello world"));
    pubString.publish(std::shared_ptr<std::string>(new std::string("hello again")));

    LOG(INFO)<<pubInt.getNumSubscribers()<<","
            <<subInt.getNumPublishers()<<","
           <<subInt1.getNumPublishers()<<","
          <<pubString.getNumSubscribers()<<","
         <<subString.getNumPublishers()<<std::endl;
    std::this_thread::sleep_for(std::chrono::duration<double>(1));
    return 0;
}
