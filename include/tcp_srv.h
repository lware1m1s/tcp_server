#ifndef TCP_SRV_H
#define TCP_SRV_H
/*
File Name: tcp_srv.h
*/
#include <cstring>    
#include <iostream>
#include <string>  
#include <vector>


#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>    

#include "../include/client.h"
class Server
{
	private:
		bool sockUp = false;
		int serverFd;
		struct sockaddr_in m_serverAddress;
    	struct sockaddr_in m_clientAddress;
		int addrlen = 0;
		
		char buffer[1024];
		fd_set readfds;
		Client c;
		Counter cnt;

	public:
		int start(int port);
		void run(void);
		void handler_cb(void);
};
#endif