#include "I2CzmqInterface.h"
#include <sstream>

void *Serverbuilder::threadproc()
{
    cout << "我的线程开始执行了" << endl;
    while (1) {
        char szBuf[1024] = {0};

        int ret = zmq_recv(publisher, szBuf, sizeof(szBuf) - 1, 0);
        if(ret!=0){
            string recv_str=szBuf;
            string command;
            istringstream istrStream(recv_str); //建立src到istrStream的联系
            istrStream>>command;

            if(command=="chunk"){
                int num ;
                for (int i=0;i<16;i++){
                   istrStream>>num ;
                   std::cout<<num<<" ";
                }

                std::cout<<std::endl;

                mcp->chunkset(1);

            }
            else if(command=="single"){
                int port,value;
                istrStream>>port>>value;
               mcp->singleset(port,value);
            }else if(command=="select"){
                int port;
                istrStream>>port;
               mcp->select(port);
            }

            snprintf(szBuf, sizeof(szBuf), "10002 come from c++");
            int aaa=strlen(szBuf);
            zmq_send(publisher, szBuf, strlen(szBuf) + 1, 0);
        }
    }
    cout << "我的线程执行结束了" << endl;
}

void Serverbuilder::Wait()
{
    this->mythread->join();
}

Serverbuilder::Serverbuilder()
{

    this->mcp=NULL;
}

void Serverbuilder::BuildAndStart()
{
    void *context = zmq_ctx_new ();
    this->publisher = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (publisher, this->adress.c_str());
    assert (rc == 0);

    int major, minor, patch;
    zmq_version (&major, &minor, &patch); printf ("Current ØMQ version is %d.%d.%d\n", major, minor, patch);

    boost::function0< void> f =  boost::bind(&Serverbuilder::threadproc,this);
    //boost::thread th(this->f);
    this->mythread=new boost::thread(f);
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
