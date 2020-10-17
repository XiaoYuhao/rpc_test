#ifndef _PTHREADPOOL_H
#define _PTHREADPOOL_H

#include<vector>
#include<queue>
#include<thread>
#include<iostream>
#include<stdexcept>
#include<condition_variable>
#include<memory>
#include<functional>
using namespace std;

typedef function<void(void)> Task;

class ThreadPool{
    vector<thread> work_threads;
    queue<Task> task_queue;
    bool stop;
    mutex queue_mutex;
    condition_variable cv;
    static ThreadPool* _instance;
    ThreadPool(int num=20);
public:
    static ThreadPool* create(int num=20);
    ~ThreadPool();
    static void *worker(void *arg);
    void run();
    int append(Task t);
};

#endif