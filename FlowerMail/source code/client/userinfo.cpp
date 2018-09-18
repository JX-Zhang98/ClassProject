#include "userinfo.h"
//可以用UserInfo对象初始化publicInfo对象，只提取其public部分
//顺序为用户名，电话号码，真实姓名，密码，密保问题，密保问题答案
UserInfo::UserInfo(QString username,QString phonenumber,QString realname
                   ,QString psd,QString securequestion,QString secureanswer)
    :PublicInfo (username,phonenumber,realname)
{
    password=psd;
    secureQuestion=securequestion;
    secureAnswer=secureanswer;
}
QString UserInfo::GetPassword()
{
    return password;
}
QString UserInfo::GetSecureAnswer()
{
    return secureAnswer;
}
QString UserInfo::GetSecureQuestion()
{
    return secureQuestion;
}
void UserInfo::SetPassword(QString psd)
{
    password=psd;
}
void UserInfo::SetSecureAnswer(QString securequestion)
{
    secureQuestion=securequestion;
}
void UserInfo::SetSecureQuestion(QString secureanswer)
{
    secureAnswer=secureanswer;
}
