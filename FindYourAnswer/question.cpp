#include "question.h"
#include <QSqlQuery>
#include <QVariant>

Question::Question()
{

}

Question::Question(int creator_id, QString title, QString context) :
    BaseInfo(creator_id, context)
{
    this->creatorId = creator_id;
    this->title = title;
    this->context = context;
}

Question::Question(int id, QString title, QString context, QString createdTime, QString creator) :
    BaseInfo(id, context, createdTime, creator)
{
    this->title = title;
}

void Question::setTitle(QString title)
{
    this->title = title;
}

QString Question::getTitle()
{
    return this->title;
}

void Question::save()
{
    QSqlQuery query;
    QString queryString = "insert into question (title, context, creator_id) values (:title, :context, :creator_id)";
    query.prepare(queryString);
    query.bindValue(":title", this->title);
    query.bindValue(":context", this->context);
    query.bindValue(":creator_id", this->creatorId);
    query.exec();
}

QTextStream & operator<< (QTextStream &s, const Question &q) {
    s << q.id << ":" << q.title;
    return s;
}

QTextStream & operator>> (QTextStream &s, Question &q) {
    s >> q.title >> q.context;
    return s;
}
