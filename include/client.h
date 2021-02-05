#ifndef CLIENT_H
#define CLIENT_H

#include <cstring>    // sizeof()
#include <iostream>
#include <string>  
#include <vector>

// headers for socket(), getaddrinfo() and friends
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#include "../include/counter.h"

class Client
{
    private: 
        std::vector<int> clientFds;
        char buffer[1024];
        int retrieveSocket(int fd);
        void send(int fd, int value);
        void sendAll(int value);

    public:
        void addClient(int fd);
        void removeClient(int fd);
        void processClients(fd_set & readfds, Counter & cnt);
        int addClientDescriptors(fd_set & readfds, int max_fds);
        void closeAllConnetions();
        

};
#endif