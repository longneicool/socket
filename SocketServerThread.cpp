/*
 * SocketServerThread.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: longneicool
 */

#include "SocketServerThread.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

SocketServerThread::SocketServerThread(std::string ip, int port) :
		isStopped_(true), socketFd_(-1), ip_(ip), port_(port) {

}

SocketServerThread::~SocketServerThread() {
}

void SocketServerThread::startThread() {
	if(createSocketServer() == -1)
	{
		std::cerr << "Failed to create socket server" << std::endl;

		return;
	}

	isStopped_ = false;

	while(!isStopped_)
	{
		sockaddr_in myaddr;
		unsigned int len;
		int result = accept(socketFd_, (sockaddr*)&myaddr, &len);
		if(result == -1)
		{
			continue;
		}

		uint16_t port = ntohs(myaddr.sin_port);
		std::cout << ntop(myaddr) << ": " << port << std::endl;
        close(result);
		//@TODO add the received buff
	}

	close(socketFd_);
}

int SocketServerThread::createSocketServer() {
	socketFd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd_ == -1) {
		std::cout << "Failed to create the socket" << std::endl;
		return -1;
	}

	std::cout << "create socket success " << std::endl;

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_);
	addr.sin_addr.s_addr = inet_addr(ip_.c_str()); // INADDR_ANY - tell os tp choose ip address
	int result = bind(socketFd_, (sockaddr*) &addr, sizeof(addr));
	if(result == -1)
	{
		std::cerr << "Failed to bind the socket to " << ip_ << ":" << port_;
		return -1;
 	}

	std::cout << "bind success " << ip_ << ":" << port_ << std::endl;

	result = listen(socketFd_, 128);
	if(result == -1)
	{
		std::cerr << "Failed to listen " << std::endl;
		return -1;
	}

	std::cout << "start listen " << ip_ << ":" << port_ << std::endl;

	return 0;
}

std::string SocketServerThread::ntop(sockaddr_in addr)
{
#if 1
	char buff[INET_ADDRSTRLEN];
	char* res = inet_ntoa(addr.sin_addr);
	if(res == NULL)
	{
		return std::string();
	}

	return std::string(res);
#else

	char buff[INET_ADDRSTRLEN]; // INET6_ADDRSTRLEN
	const char * res = inet_ntop(AF_INET, &(addr.sin_addr), buff, INET_ADDRSTRLEN);
	if(res == NULL)
	{
		return std::string();
	}
#endif

	return std::string(res);
}
