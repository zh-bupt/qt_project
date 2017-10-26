#ifndef GLOBAL_H
#define GLOBAL_H

#include "user.h"

class Global
{
public:
    Global();
    static User* currentUser;
    static void setCurrentUser(int id);
};

#endif // GLOBAL_H
