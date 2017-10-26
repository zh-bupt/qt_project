#include "comment.h"
#include <QSqlQuery>
#include <QVariant>

Comment::Comment()
{

}

Comment::Comment(int creator_id, QString context)
{
    this->creatorId = creator_id;
    this->context = context;
}

Comment::Comment(int creator_id, QString context, int questionId) :
    Comment(creator_id, context)
{
    this->questionId = questionId;
}

Comment::Comment(int id,int creator_id, QString context, QString createdTime, int praiseNum) :
    Comment(creator_id, context)
{
    this->praiseNum = praiseNum;
    this->createdTime = createdTime;
    this->id = id;
    QSqlQuery queryCreator;
    QString queryString = "select * from user where id = :id";
    queryCreator.prepare(queryString);
    queryCreator.bindValue(":id", creator_id);
    if (queryCreator.exec()) {
        while(queryCreator.next()) {
            this->setCreator(queryCreator.value("name").toString());
        }
    }
}

void Comment::setPraiseNum(int praise_num)
{
    this->praiseNum = praise_num;
}

int Comment::getPraiseNum()
{
    return this->praiseNum;
}

void Comment::setQuestionTitle(QString title)
{
    this->questionTitle = title;
}

QString Comment::getQuestionTitle()
{
    return this->questionTitle;
}

int Comment::getQuestionId()
{
    return this->questionId;
}

void Comment::setQuestionId(int id)
{
    this->questionId = id;
}

void Comment::save()
{
    QSqlQuery query;
    QString queryString = "insert into comment (context, creator_id, question_id) values (:context, :creator_id, :question_id)";
    query.prepare(queryString);
    query.bindValue(":context", this->context);
    query.bindValue(":creator_id", this->creatorId);
    query.bindValue(":question_id", this->questionId);
    query.exec();
}

QTextStream & operator<< (QTextStream &s, const Comment &c)
{
    s << c.id << ":" << c.context;
    return s;
}

QTextStream & operator>> (QTextStream &s, Comment &c)
{
    s >> c.context;
    return s;
}
