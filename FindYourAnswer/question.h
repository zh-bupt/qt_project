#ifndef QUESTION_H
#define QUESTION_H

#include "baseinfo.h"
#include <QString>
#include <QTextStream>

using namespace std;

class Question : public BaseInfo
{
public:
    Question();
    Question(int creator_id, QString title, QString context);
    Question(int id, QString title, QString context, QString createdTime, QString creator);
    void setTitle(QString title);
    QString getTitle();
    virtual void save();
private:
    QString title;

    friend QTextStream & operator<< (QTextStream &s, const Question &q);
    friend QTextStream & operator>> (QTextStream &s, Question &q);
};

#endif // QUESTION_H
