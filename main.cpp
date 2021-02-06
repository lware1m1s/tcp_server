#include <iostream>
#include <csignal>

#include "include/tcp_srv.h"

// declare the server
Server server;

void signal_handler( int sig )
{
    std::cout << "INFO: Sig(" << sig << "). caught" << std::endl;
    server.handler_cb();
    exit(0);
}

int main(int argc, char *argv[])
{
    signal(SIGTERM, signal_handler); //Ensure graceful exit upon signal.
    
    int startRet = server.start(8089);
    if (startRet == 0) {
        std::cout << "Server setup succeeded" << std::endl;
    } else {
        std::cout << "Server setup failed: " << std::endl;
        return EXIT_FAILURE;
    }
    server.run();
    return 0;
}
