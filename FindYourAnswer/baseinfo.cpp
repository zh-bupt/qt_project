#include "baseinfo.h"

BaseInfo::BaseInfo()
{

}

BaseInfo::BaseInfo(int creator_id, QString context)
{
    this->creatorId = creator_id;
    this->context = context;
}

BaseInfo::BaseInfo(int id, QString context, QString createdTime, QString creator)
{
    this->id = id;
    this->context = context;
    this->createdTime = createdTime;
    this->creator = creator;
}

int BaseInfo::getCreatorId()
{
    return this->creatorId;
}

QString BaseInfo::getContext()
{
    return this->context;
}

void BaseInfo::setContext(QString context)
{
    this->context = context;
}

void BaseInfo::setCreatorId(int id)
{
    this->creatorId = id;
}

QString BaseInfo::getCreatedTime()
{
    return this->createdTime;
}

void BaseInfo::setCreatedTime(QString time)
{
    this->createdTime = time;
}

void BaseInfo::setId(int id)
{
    this->id = id;
}

int BaseInfo::getId()
{
    return this->id;
}

void BaseInfo::setCreator(QString creator)
{
    this->creator = creator;
}

QString BaseInfo::getCreator()
{
    return this->creator;
}
