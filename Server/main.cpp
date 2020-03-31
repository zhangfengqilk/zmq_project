#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <zmq.h>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <I2CzmqInterface.h>
using namespace std;

class myimpl :public I2cService{


    // I2cService interface
public:
    void chunkset(int a){
       std::cout<<a<<std::endl;
    }
    void singleset(int port, int value){
       std::cout<<port+value<<std::endl;
    }
    int select(int port){
        std::cout<<port<<std::endl;
        return 0;
    }
    int selectAll(){
        return 0;
    }
};
    // I2cService interface


int main (void)
{
    myimpl service;
    std::string server_adress("tcp://*:5555");
    Serverbuilder serverbuilder;
    serverbuilder.AddListeningPort(server_adress);
    serverbuilder.RegisterService(&service);
    serverbuilder.BuildAndStart();

    printf ("Start server\n");
    serverbuilder.Wait();
    return 0;
}
