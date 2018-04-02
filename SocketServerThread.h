/*
 * SocketServerThread.h
 *
 *  Created on: Mar 31, 2018
 *      Author: longneicool
 */

#ifndef SOCKETSERVERTHREAD_H_
#define SOCKETSERVERTHREAD_H_

#include <string>
#include <netinet/in.h>

class SocketServerThread {
public:
	SocketServerThread(std::string ip, int port);
	virtual ~SocketServerThread();

	void startThread();
	void stopThread();

private:
	int createSocketServer();
	std::string ntop(sockaddr_in addr);

	bool isStopped_;
	int socketFd_;
	std::string ip_;
	int port_;
};

#endif /* SOCKETSERVERTHREAD_H_ */
