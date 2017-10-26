#ifndef LOG_H
#define LOG_H

#include "QString"
#include "QFile"

class Log
{
public:
    Log(QString file_path);
    ~Log();
    void e(QString error);
    void i(QString info);
private:
    QString file_path;
    QFile *file=NULL;
};

#endif // LOG_H
