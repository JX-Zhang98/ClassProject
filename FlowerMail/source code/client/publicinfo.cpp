#include "publicinfo.h"
//参数列表顺序：用户名（必填），电话号码（选填），真实姓名（选填）
PublicInfo::PublicInfo(QString username,QString phonenumber,QString realname)
{
    userName=username;
    phoneNumber=phonenumber;
    realName=realname;
}
QString PublicInfo::GetPhoneNumber()
{
    return phoneNumber;
}
QString PublicInfo::GetUserName()
{
    return userName;
}
QString PublicInfo::GetRealName()
{
    return realName;
}
void PublicInfo::SetPhoneNumber(QString phonenumber)
{
    phoneNumber=phonenumber;
}
void PublicInfo::SetUserName(QString username)
{
    userName=username;
}
void PublicInfo::SetRealName(QString realname)
{
    realName=realname;
}
