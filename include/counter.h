#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#ifndef COUNTER_H
#define COUNTER_H
class Counter
{
    private:
        int counter=0;
        void increment(int value);
        void decrement(int value);
        std::vector<std::string> split(std::string strToSplit, char delimeter);

    public:
        int processCommand(std::string cmd, bool & broadcast);
};
#endif