#ifndef MAILCONTROL_H
#define MAILCONTROL_H
#include "userinfocontrol.h"
#include "mail.h"
#include <QStringList>
#define sep "!@"
#define spm "@#"

class MailControl
{
public:
    MailControl();
    static void SendMail(QList<Mail>);
    static void ReceiveMail(int);
    static void SaveDraft(Mail);
    static void DeleteMail(QList<Mail>);
    static void DeleteSendingMail(QList<Mail>);
    static void UndeleteMail(QList<Mail>);
    static void CompleteDeleteMail(QList<Mail>);
    static void IsReadMail(QList<Mail>);
    static void SetAutoReplay(QString);
    static QStringList MailSplit(QString);
private:
    static int getMailNum();
    static QList<Mail> getMail(int);

};

#endif // MAILCONTROL_H
