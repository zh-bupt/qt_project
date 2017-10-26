#include "global.h"
#include <QString>

User* Global::currentUser = NULL;

Global::Global()
{

}

void Global::setCurrentUser(int id)
{
    currentUser = new User(id);
}
