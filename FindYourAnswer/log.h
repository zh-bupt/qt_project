#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Log
{
public:
    Log();
    Log(string info);
    void write();
    ~Log();
private:
    string info;

    friend ostream & operator << (ostream &o, const Log &log);
    friend istream & operator >> (istream &i, Log &log);
};

#endif // LOG_H
