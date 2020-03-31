#include "commandparse.h"





Serverbuilder::Serverbuilder()
{
    this->mcp=NULL;
}

void Serverbuilder::BuildAndStart()
{
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (publisher, this->adress.c_str());
    //assert (rc == 0);

    int major, minor, patch;
    zmq_version (&major, &minor, &patch); printf ("Current ØMQ version is %d.%d.%d\n", major, minor, patch);
    while (1) {
        char szBuf[1024] = {0};

        int ret = zmq_recv(publisher, szBuf, sizeof(szBuf) - 1, 0);
        if(ret!=0){

            string test1;
            test1=szBuf;
            vector<string> vec1;
            boost::split(vec1, test1, boost::is_any_of(", "));//支持同时使用多个分割符
            string command=vec1[0];
            if(command=="chunk"){
                this->mcp->chunkset(1);
            }
            else if(command=="single"){
               this->mcp->singleset(1);
            }else if(command=="select"){
               this->mcp->select(1);
            }

            snprintf(szBuf, sizeof(szBuf), "10002 come from c++");
            zmq_send(publisher, szBuf, strlen(szBuf) + 1, 0);
        }
    }
    //新建一个线程负责zmq接收
}

void Serverbuilder::AddListeningPort(string server_adress)
{
    this->adress=server_adress;
}

void Serverbuilder::RegisterService(I2cService *cp)
{
    this->mcp=cp;
}




I2cService::I2cService()
{

}
