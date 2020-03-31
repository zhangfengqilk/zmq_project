#include <zmq.hpp>
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

int main (void)
{
    printf("Hello world!\n");

    void* context = zmq_ctx_new();
    assert(context != NULL);

    void* subscriber = zmq_socket(context, ZMQ_REQ);
    assert(subscriber != NULL);

    int ret = zmq_connect(subscriber, "tcp://localhost:5555");
    assert(ret == 0);

    //  设置订阅信息，默认为纽约，邮编10001
    //char *filter = "10001 ";
    //ret = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "10001", 5);

    assert(ret == 0);

    while(1)
    {
        char szBuf[1024] = {0};
        std::cout<<"[1] chunk 1 0 1 0 1 0 1 0 1 0 1 1 1 1 1 1"<<std::endl;
        std::cout<<"[2] single 3 1"<<std::endl;
        std::cout<<"[3] select 4"<<std::endl;
        int sendnum;
        std::cin>>sendnum;
        if(sendnum==1){
            snprintf(szBuf, sizeof(szBuf), "chunk 121 0 1 0 1 0 1 0 1 0 1 1 1 1 1 1");
        }else if(sendnum==2){
            snprintf(szBuf, sizeof(szBuf), "single 1 3");
        }else if(sendnum==3){
            snprintf(szBuf, sizeof(szBuf), "select 1");
        }

        zmq_send(subscriber, szBuf, strlen(szBuf) + 1, 0);
        ret = zmq_recv(subscriber, szBuf, sizeof(szBuf) - 1, 0);
        if (ret > 0)
        {
            printf("%s\n", szBuf);
        }
        //sleep(1);
    }

    zmq_close(subscriber);
    zmq_ctx_destroy(context);

    return 0;
}
