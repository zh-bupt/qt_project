#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include "baseinfo.h"
#include <QTextStream>

using namespace std;

class Comment : public BaseInfo
{
public:
    Comment();
    Comment(int creator_id, QString context);
    Comment(int creator_id, QString context, int questionId);
    Comment(int id,int creator_id, QString context, QString createdTime, int praiseNum);
    void setPraiseNum(int praise_num);
    int getPraiseNum();
    void setQuestionTitle(QString title);
    QString getQuestionTitle();
    int getQuestionId();
    void setQuestionId(int id);
    virtual void save();
private:
    int praiseNum;
    int questionId;
    QString questionTitle;

    friend QTextStream & operator<< (QTextStream &s, const Comment &c);
    friend QTextStream & operator>> (QTextStream &s, Comment &c);
};

#endif // COMMENT_H
