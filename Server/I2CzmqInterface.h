#ifndef COMMANDPARSE_H
#define COMMANDPARSE_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <zmq.h>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <commandparse.h>
#include <boost/thread/thread.hpp>

using namespace std;


class I2cService
{
public:    
    I2cService();

    virtual void chunkset(int value)=0;
    virtual void singleset(int port,int value)=0;
    virtual int select(int port)=0;
    virtual int selectAll()=0;
};
class Serverbuilder
{
private:
    std::string adress;
    void* threadproc();
    pthread_t th;
    void *publisher;
    boost::thread *mythread;

public:
    I2cService *mcp;
    void Wait();


    Serverbuilder();
    void AddListeningPort(std::string server_adress);
    void RegisterService(I2cService* cp);
    void BuildAndStart();

};

#endif // COMMANDPARSE_H
