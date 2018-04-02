/*
 * main.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: longneicool
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "SocketServerThread.h"

void * startNewThread(void* arg)
{
	SocketServerThread *thread = (SocketServerThread *) arg;
	thread->startThread();

	return (void*) 0;
}

int main(int argc, char** argv)
{
    pthread_t tid;
    SocketServerThread thread("192.168.56.101", 8080);
    if(0 != pthread_create(&tid, NULL, startNewThread, &thread))
    {
    	std::cerr << "Failed to create thread" << std::endl;

    	return 0;
    }

    std::cout << "create thread success" << std::endl;

    if(0 != pthread_join(tid, NULL))
    {
    	std::cerr << "Failed to join the child thread" << std::endl;

    	return 0;
    }

    return 0;
}




