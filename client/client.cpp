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
#include "package.h"  


int connect_to_server(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(11234);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");
    socklen_t len = sizeof(sockaddr_in);

    int ret = 0;
    ret = connect(sockfd, (sockaddr*)&server, len);
    if(ret<0){
        printf("connect server failed...\n");
        return -1;
    }
    return sockfd;
}

int remote_call(int id, int para1, int para2, int &res){
    int fd = connect_to_server();
    procedure_call_package pcp(id, para1, para2);
    int ret = 0;
    ret = send(fd, (void*)&pcp, sizeof(pcp), 0);
    procedure_result_package prp;
    ret = recv(fd, (void*)&prp, sizeof(prp), MSG_WAITALL);
    close(fd);
    prp.tohost();
    res = prp.result;
    return prp.status;
}

int add(int a, int b){
    int res;
    int status = remote_call(0, a, b, res);
    if(status == PROCEDURE_ERROR){
        printf("remote call error.\n");
        exit(0);
    }
    if(status == PROCEDURE_NOT_FOUND){
        printf("remote call is not found in server.\n");
        exit(0);
    }
    if(status == PROCEDURE_SUCCESS){
        return res;
    }
    return 0;
}

int sub(int a, int b){
    int res;
    int status = remote_call(1, a, b, res);
    if(status == PROCEDURE_ERROR){
        printf("remote call error.\n");
        exit(0);
    }
    if(status == PROCEDURE_NOT_FOUND){
        printf("remote call is not found in server.\n");
        exit(0);
    }
    if(status == PROCEDURE_SUCCESS){
        return res;
    }
    return 0;
}

int mul(int a, int b){
    int res;
    int status = remote_call(2, a, b, res);
    if(status == PROCEDURE_ERROR){
        printf("remote call error.\n");
        exit(0);
    }
    if(status == PROCEDURE_NOT_FOUND){
        printf("remote call is not found in server.\n");
        exit(0);
    }
    if(status == PROCEDURE_SUCCESS){
        return res;
    }
    return 0;
}

int divide(int a, int b){
    int res;
    int status = remote_call(3, a, b, res);
    if(status == PROCEDURE_ERROR){
        printf("remote call error.\n");
        exit(0);
    }
    if(status == PROCEDURE_NOT_FOUND){
        printf("remote call is not found in server.\n");
        exit(0);
    }
    if(status == PROCEDURE_SUCCESS){
        return res;
    }
    return 0;
}

int mod(int a, int b){
    int res;
    int status = remote_call(4, a, b, res);
    if(status == PROCEDURE_ERROR){
        printf("remote call error.\n");
        exit(0);
    }
    if(status == PROCEDURE_NOT_FOUND){
        printf("remote call is not found in server.\n");
        exit(0);
    }
    if(status == PROCEDURE_SUCCESS){
        return res;
    }
    return 0;
}

int main(){
    int a, b, res;
    a = 256;
    b = 16;
    res = add(a, b);
    printf("remote call: %d add %d result is %d \n", a, b, res);

    res = sub(a, b);
    printf("remote call: %d subtract %d result is %d \n", a, b, res);

    res = mul(a, b);
    printf("remote call: %d multiply %d result is %d \n", a, b, res);

    res = divide(a, b);
    printf("remote call: %d divide %d result is %d \n", a, b, res);

    res = mod(a, b);
    printf("remote call: %d mod %d result is %d \n", a, b, res);
    return 0;
}