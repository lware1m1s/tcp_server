/*
File Name: counter.cpp
*/

#include "../include/counter.h"

void Counter::increment(int value)
{
    std::cout << __func__ << " INFO: Counter is being incremented by " << value << std::endl;
    counter += value;
    std::cout << __func__ << " INFO: New counter is " << counter << std::endl;
    
}

void Counter::decrement(int value)
{
    std::cout << __func__ << " INFO: Counter is being decremented by " << value << std::endl;
    counter -= value;
    std::cout << __func__ << " INFO: New counter is " << counter << std::endl;
}

std::vector<std::string> Counter::split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

int Counter::processCommand(std::string cmd, bool & broadcastMessage)
{

    std::vector<std::string> parts = Counter::split(cmd, ' ');
    int foundIncr = -1;
    broadcastMessage = true;
    std::cerr << __func__ << " INFO: Message: " << cmd << std::endl;

    if(parts[0].find("INCR")!=std::string::npos)
    {

        increment(std::stoi(parts[1]));
    }
    else if (parts[0].find("DECR")!=std::string::npos)
    {
        decrement(std::stoi(parts[1]));
    }
    else if (parts[0].find("OUTPUT")!=std::string::npos)
    {
        broadcastMessage = false;
    }
    return counter;

}