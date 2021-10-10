#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <assert.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <errno.h>  
#include <string.h>  
#include <string>
#include <map>
#include <fcntl.h>  
#include <stdlib.h>  
#include <sys/epoll.h>  
#include <signal.h>  
#include <sys/wait.h>  
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include "pthreadpool.h"
#include "network.h"
#include "package.h"
#include "procedure.h"
using namespace std;

Call_Table* Call_Table::_instance = NULL;       //远程调用函数表，单例模式
Call_Table* call_table = Call_Table::create();
ThreadPool* ThreadPool::_instance = NULL;       //线程池，用于处理单个远程调用，单例模式
ThreadPool* threadpool = ThreadPool::create();

int add(int a, int b){
    return a + b;
}

int subtract(int a, int b){
    return a - b;
}

int multiply(int a, int b){
    return a * b;
}

int divide(int a, int b){
    return a / b;
}

int mod(int a, int b){
    return a % b;
}

void remote_call(int epfd, int fd, int id, int para1, int para2){
    procedure_result_package prp;
    Procedure procedure;
    int ret = call_table->find_procedure(procedure, id);
    if(ret==0){
        prp.setdata(PROCEDURE_NOT_FOUND, 0);
    }
    else{
        ret = procedure(para1, para2);
        printf("(server)remote call(id: %d) p1: %d p2: %d result: %d \n", fd, para1, para2, ret);
        prp.setdata(PROCEDURE_SUCCESS, ret);
    }
    ret = send(fd, (void*)&prp, sizeof(prp), MSG_DONTWAIT);
    removefd(epfd, fd);                                             //采用短连接的方式，调用结束后即断开连接
    close(fd);
}

void work(){
    int listen_sock = startup(11234);
    struct sockaddr_in remote;
    socklen_t len=sizeof(struct sockaddr_in);
    
    int epfd = epoll_create(1024);
    struct epoll_event events[1024];

    addfd(epfd, listen_sock);

    int ret = 0;
    for(;;){
        int nfds = epoll_wait(epfd, events, 1024, -1);
        if((nfds<0)&&(errno!=EINTR)){
            printf("epoll failure.\n");
            break;
        }
        for(int i=0;i<nfds;i++){
            int sockfd = events[i].data.fd;
            if(sockfd == listen_sock){
                int client_sock = accept(listen_sock, (struct sockaddr*)&remote, &len);
                addfd(epfd, client_sock);
            }
            else if(events[i].events&EPOLLIN){
                package_header header;
                ret = recv(sockfd, (void*)&header, sizeof(header), MSG_PEEK);
                if((ret<0)&&(errno!=EINTR)){
                    continue;
                }
                if(ret<=0){             //接收到0，表示客户端已经断开连接
                    continue;
                }
                if(header.package_type == PROCEDURE_CALL){
                    procedure_call_package pcp;
                    ret = recv(sockfd, (void*)&pcp, sizeof(pcp), MSG_DONTWAIT);
                    pcp.tohost();
                    printf("server recv remote call require: id:%d  p1:%d  p2:%d  \n", pcp.procedure_id, pcp.para1, pcp.para2);
                    threadpool->append(bind(remote_call, epfd, sockfd, pcp.procedure_id, pcp.para1, pcp.para2));
                }
            }
        }
    }
}

int main(){
    call_table->add_procedure(0, add);          //注册远程调用函数
    call_table->add_procedure(1, subtract);
    call_table->add_procedure(2, multiply);
    call_table->add_procedure(3, divide);
    call_table->add_procedure(4, mod);
    work();                                     //启动服务器
    return 0;
}





