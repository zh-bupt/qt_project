#include "user.h"
#include <QSqlQuery>
#include <QVariant>

User::User()
{

}

User::User(int id)
{
    this->id = id;
    QSqlQuery query;
    QString queryString = "select * from user where id = :id";
    query.prepare(queryString);
    query.bindValue(":id", id);
    if (query.exec()){
        while (query.next()) {
            this->name = query.value(1).toString();
            this->password = query.value(2).toString();
        }
    }
    setFocusList();
}

User::User(int id, QString name)
{
    this->id = id;
    this->name = name;
}

User::User(int id, QString name, QString password) :
    User(id, name)
{
    this->password = password;
}

void User::setFocusList()
{
    QSqlQuery query;
    QString queryString = "select * from focus_list where focusing = :id";
    query.prepare(queryString);
    query.bindValue(":id", this->id);
    if (query.exec()){
        while(query.next()){
            int focusedId = query.value("focused").toInt();
            QSqlQuery queryUser;
            QString queryString2 = "select * from user where id = :id";
            queryUser.prepare(queryString2);
            queryUser.bindValue(":id", focusedId);
            if (queryUser.exec()) {
                while (queryUser.next()){
                    QString focusedName = queryUser.value("name").toString();
                    User u = User(focusedId, focusedName);
                    this->focusList.push_back(u);
                }
            }
        }
    }
}

std::list<User> User::getFocusList()
{
    return this->focusList;
}

QString User::getName()
{
    return this->name;
}

QString User::getPassword()
{
    return this->password;
}

int User::getId()
{
    return this->id;
}

QTextStream & operator << (QTextStream &s, const User &user) {
    s << user.id << ":" << user.name;
    return s;
}

QTextStream & operator >> (QTextStream &s, User &user) {
    s >> user.name >> user.password;
    return s;
}
