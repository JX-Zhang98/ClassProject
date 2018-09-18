#ifndef CONTACTLISTCONTROL_H
#define CONTACTLISTCONTROL_H
#include "publicinfo.h"
#include "networksocket.h"
#include "userinfocontrol.h"
#include <QList>
#define sep "!@"
#define spc "@#"

class ContactlistControl
{
public:
    ContactlistControl();
    static void AddContact(QString);
    static void ShowContact();
    static void ShowBlacklist();
    static void AddBlacklist(QList<PublicInfo>);
    static void RestoreBlacklist(QList<PublicInfo>);
    static void DeleteContact(QList<PublicInfo>);
};

#endif // CONTACTLISTCONTROL_H
