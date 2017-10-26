#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;


class FileException
{
public:
    FileException();
    FileException(const string info);
    const char* what () const _NOEXCEPT;
private:
    string info;
};

#endif // FILEEXCEPTION_H
