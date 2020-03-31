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
using namespace std;


class I2cService
{
public:    
    I2cService();

    virtual void chunkset(int a)=0;
    virtual void singleset(int a)=0;
    virtual void select(int a)=0;
};
class Serverbuilder
{
private:
    std::string adress;
public:
    I2cService *mcp;

    Serverbuilder();
    void AddListeningPort(std::string server_adress);
    void RegisterService(I2cService* cp);
    void BuildAndStart();

};

#endif // COMMANDPARSE_H
