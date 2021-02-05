#include "../include/client.h"
void Client::addClient(int fd) 
{ 
    if(clientFds.size() < 1024)
    {
        clientFds.push_back(fd);
    }
    else
    {
        std::cerr << __func__ << " INFO: Maxx connections exceed dropping connection" << std::endl;
        close(fd);
    } 
} 
void Client::removeClient(int fd) 
{
    std::vector<int>::iterator new_end;
    std::cerr << __func__ << " INFO:Closing fd=" << fd << std::endl;
    ::close(fd);
    clientFds.erase(std::remove(clientFds.begin(), clientFds.end(), fd), clientFds.end());
}
int Client::addClientDescriptors(fd_set & readfds, int max_fds)
{
    for(const auto& cfds: clientFds) {
        FD_SET(cfds, &readfds);
        max_fds = (cfds > max_fds) ? cfds : max_fds; 
    }
    return max_fds;
}
void Client::processClients(fd_set & readfds, Counter & cnt)
{
    for(const auto& cfds: clientFds) {
         if (FD_ISSET( cfds, &readfds))
         {
             //Check whether message incoming or connection was closing
             int readCnt = -1;
             if ((readCnt = ::read(cfds, buffer, 1024)==0))
             {
                 std::cerr << __func__ << " INFO: Socket closing received on fd " << cfds << std::endl;
                 removeClient(cfds);
             }
             else
             {
                 std::string message(buffer);
                 bool bMsg = false;
                 std::cout << __func__ << " INFO: Recvd Message was " << message << std::endl;
                 int val = cnt.processCommand(message, bMsg);
                 if(bMsg)
                 {
                     std::cout << __func__ << " INFO: Broadcast counter " << val << std::endl;
                     sendAll(val);
                 }
                 else
                 {
                     std::cout << __func__ << " INFO: Single cast counter " << val << std::endl;
                     send(cfds, val);
                 }
             }
         }
    }

}
void Client::send(int fd, int value)
{
    std::string msg = "COUNTER VALUE=" + std::to_string(value) +"\r\n";
    ::send(fd, msg.c_str(), msg.length(), 0);
}
void Client::sendAll(int value)
{
    for(const auto& fd: clientFds) {
        send(fd, value);
    }
    
}
void Client::closeAllConnetions()
{
   for(const auto& fd: clientFds) {
        removeClient(fd);
    } 
}