#ifndef USER_H
#define USER_H

#include <list>
#include <QString>
#include <QTextStream>

class User
{
public:
    User();
    User(int id);
    User(int id, QString name);
    User(int id, QString name, QString password);
    void setFocusList();
    std::list<User> getFocusList();
    QString getName();
    QString getPassword();
    int getId();
private:
    int id;
    QString name;
    QString password;
    std::list<User> focusList;

    friend QTextStream & operator<< (QTextStream &s, const User &user);
    friend QTextStream & operator>> (QTextStream &s, User &user);
};

#endif // USER_H
