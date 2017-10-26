#ifndef BASEINFO_H
#define BASEINFO_H

#include <QString>

class BaseInfo {
public:
    BaseInfo();
    BaseInfo(int creator_id, QString context);
    BaseInfo(int id, QString context, QString createdTime, QString creator);
    void setId(int id);
    int getId();
    void setCreatorId(int id);
    int getCreatorId();
    void setContext(QString context);
    QString getContext();
    QString getCreatedTime();
    void setCreatedTime(QString time);
    void setCreator(QString creator);
    QString getCreator();
    virtual void save() = 0;
protected:
    int id;
    int creatorId;
    QString createdTime;
    QString context;
    QString creator;
};

#endif // BASEINFO_H
