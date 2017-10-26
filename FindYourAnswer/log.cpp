#include "log.h"
#include <fstream>
#include "fileexception.h"
#include <QDebug>

using namespace std;

Log::Log()
{

}

Log::Log(string info)
{
    this->info = info;
}

Log::~Log()
{

}

void Log::write()
{
    ofstream f("log.txt", ios::app);

    if (f.is_open()) {
        f << info;
        f.close ();
    } else {
        throw FileException("file open failed!");
        qDebug() << "文件错误";
    }
}


ostream & operator << (ostream &o, const Log &log) {
    o << log.info << std::endl;
    return o;
}

istream & operator >> (istream &i, Log &log) {
    i >> log.info;
    return i;
}


