#ifndef PUBLICINFO_H
#define PUBLICINFO_H
#include<QString>

class PublicInfo
{
public:
    PublicInfo(QString,QString,QString);
    QString GetUserName();
    QString GetPhoneNumber();
    QString GetRealName();
    void SetUserName(QString);
    void SetPhoneNumber(QString);
    void SetRealName(QString);
private:
    QString userName;
    QString phoneNumber;
    QString realName;
};

#endif // PUBLICINFO_H
