#ifndef USERINFO_H
#define USERINFO_H
#include "publicinfo.h"

class UserInfo:public PublicInfo
{
public:
    UserInfo(QString,QString,QString,QString,QString,QString);
    QString GetPassword();
    QString GetSecureQuestion();
    QString GetSecureAnswer();
    void SetPassword(QString);
    void SetSecureQuestion(QString);
    void SetSecureAnswer(QString);
private:
    QString password;
    QString secureQuestion;
    QString secureAnswer;
};

#endif // USERINFO_H
