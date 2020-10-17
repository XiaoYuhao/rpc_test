#ifndef _PROCEDURE_H
#define _PROCEDURE_H

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
#include <functional>
using namespace std;

typedef function<int(int, int)> Procedure;

class Call_Table{
    map<int, Procedure> table;
    static Call_Table* _instance;           //单例模式
    Call_Table(){}
public:
    static Call_Table* create();
    int add_procedure(int id, Procedure pro);
    int del_procedure(int id);
    int find_procedure(Procedure &p, int id);
};

#endif