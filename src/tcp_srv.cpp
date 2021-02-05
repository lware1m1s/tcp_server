/*

File Name: tcp_srv.cpp

*/
#include "../include/tcp_srv.h"
#include "../include/counter.h"

// Call back routine for signal handling.
//  
void Server::handler_cb(void)
{
    std::cerr << __func__ <<" Server shutting down" << std::endl;
    c.closeAllConnetions(); //close all client connections.
    ::close(serverFd); // close server file descriptor.
    return;
}
int Server::start(int port)
{
	serverFd = 0;
    int ret;
    // socket initialization
    serverFd = socket(AF_INET,SOCK_STREAM,0);
    if (serverFd == -1) { //socket failed
        std::cerr << strerror(errno) << std::endl;
        return ret;
    }
    // set socket address for reuse.
    int option = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    

    memset(&m_serverAddress, 0, sizeof(m_serverAddress));
    m_serverAddress.sin_family = AF_INET;
    m_serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    m_serverAddress.sin_port = htons(port);

    ret = bind(serverFd, (struct sockaddr *)&m_serverAddress, sizeof(m_serverAddress));
    if (ret == -1) { // bind failed
        std::cerr << __func__ << " bind failed " << strerror(errno) << std::endl;
        return ret;
    }

    const int maxConnections = 1024;
    ret = listen(serverFd, maxConnections);
    if (ret == -1) { // listen failed
        std::cerr << __func__ << " listen failed "<< strerror(errno) << std::endl;
        return ret;
    }

    std::cout << __func__ << " Lisenting on port=" << port << std::endl;
    sockUp = true;
    return ret;
	
}

// Server::run()
// handle connections from clients.

void Server::run()
{
    // Setup up infinte loop to gather and service connections.
    int max_fds = -1, sel;
    while(sockUp)
    {
        FD_ZERO(&readfds);
        // listend for connections.
        FD_SET(serverFd, &readfds);
        max_fds = serverFd;
        // setup current listing of connections.
        max_fds = c.addClientDescriptors(readfds, max_fds);

        sel = select(max_fds + 1, &readfds, NULL, NULL, NULL);

        if((sel < 0) && errno!=EINTR)
        {
            std::cerr << "select failed reason: " << strerror(errno) << std::endl;
        }
        // Incoming connection
        if (FD_ISSET(serverFd, &readfds))
        {
            int client = accept(serverFd, (struct sockaddr *)&m_clientAddress,
                (socklen_t *)&addrlen);
                std::cout << "Client on fd=" << client << std::endl;
                c.addClient(client); // add latest client to descriptors.
        }
        else
        {
            c.processClients(readfds, cnt);
        }

    }
}
