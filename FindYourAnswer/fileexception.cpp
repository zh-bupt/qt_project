#include "fileexception.h"

FileException::FileException()
{                                          
}

FileException::FileException(const string info)
{
    this->info = info;
}

const char* FileException::what() const _NOEXCEPT
{
    return info.c_str();
}
