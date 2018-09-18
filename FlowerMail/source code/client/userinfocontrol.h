#ifndef USERINFOCONTROL_H
#define USERINFOCONTROL_H
#include "networksocket.h"
#include "userinfo.h"
#define sep "!@"

class UserInfoControl
{
public:
    UserInfoControl();
    static void Login(QString,QString);
    static void Register(QString,QString);
    static void ChangePsd(QString,QString);
    static void ChangePsd(QString);
    static void CheckSecureQuestion(QString ,QString);
    static void GetSecureQuestion(QString);
    static void GetAllInfo(QString);
    static UserInfo user;
    static QStringList UserInfoSplit(QString);
};

#endif // USERINFOCONTROL_H
