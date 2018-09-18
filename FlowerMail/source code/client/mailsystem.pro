#-------------------------------------------------
#
# Project created by QtCreator 2018-08-29T15:27:46
#
#-------------------------------------------------

QT       += core gui widgets
QT+=network
QT+=sql

TARGET = mailsystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    mailwidget.cpp \
    commonhelper.cpp \
    stackwidgettest1.cpp \
    stackwidgettest2.cpp \
    networksocket.cpp \
    userinfocontrol.cpp \
    publicinfo.cpp \
    userinfo.cpp \
    mail.cpp \
    Inbox/blackcontractlist.cpp \
    Inbox/blacklistbox.cpp \
    Inbox/contractbox.cpp \
    Inbox/deletedbox.cpp \
    Inbox/draftbox.cpp \
    Inbox/inbox.cpp \
    Inbox/mailedit.cpp \
    Inbox/publicinfoinui.cpp \
    Inbox/qcommondelegate.cpp \
    Inbox/richtextedit.cpp \
    Inbox/sendbox.cpp \
    Inbox/showbox.cpp \
    Inbox/tablemodelforcontract.cpp \
    Inbox/tablemodelforsendbox.cpp \
    Inbox/tablemodle.cpp \
    Inbox/setquestion.cpp \
    Inbox/setting.cpp \
    mailcontrol.cpp \
    contactlistcontrol.cpp \
    Start/adduser.cpp \
    Start/changepwdwindow.cpp \
    Start/findpwdwindow.cpp \
    Start/secquestion.cpp \
    Start/setting.cpp \
    controlapp.cpp \
    Start/loginwidget.cpp \
    Inbox/changepsdwithlast.cpp

HEADERS += \
    mailwidget.h \
    commonhelper.h \
    stackwidgettest1.h \
    stackwidgettest2.h \
    networksocket.h \
    userinfocontrol.h \
    publicinfo.h \
    userinfo.h \
    mail.h \
    Inbox/blackcontractlist.h \
    Inbox/blacklistbox.h \
    Inbox/contractbox.h \
    Inbox/deletedbox.h \
    Inbox/draftbox.h \
    Inbox/inbox.h \
    Inbox/mailedit.h \
    Inbox/publicinfoinui.h \
    Inbox/qcommondelegate.h \
    Inbox/richtextedit.h \
    Inbox/sendbox.h \
    Inbox/showbox.h \
    Inbox/tablemodelforcontract.h \
    Inbox/tablemodelforsendbox.h \
    Inbox/tablemodle.h \
    subwidget.h \
    Inbox/setquestion.h \
    Inbox/setting.h \
    mailcontrol.h \
    contactlistcontrol.h \
    Start/adduser.h \
    Start/changepwdwindow.h \
    Start/findpwdwindow.h \
    Start/secquestion.h \
    Start/setting.h \
    controlapp.h \
    Start/loginwidget.h \
    Inbox/changepsdwithlast.h

FORMS += \
    mailwidget.ui \
    stackwidgettest1.ui \
    stackwidgettest2.ui \
    Inbox/blackcontractlist.ui \
    Inbox/blacklistbox.ui \
    Inbox/contractbox.ui \
    Inbox/deletedbox.ui \
    Inbox/draftbox.ui \
    Inbox/inbox.ui \
    Inbox/mailedit.ui \
    Inbox/richTextEdit.ui \
    Inbox/sendbox.ui \
    Inbox/showbox.ui \
    Inbox/setquestion.ui \
    Inbox/setting.ui \
    Start/adduser.ui \
    Start/Changepwdwindow.ui \
    Start/findpwdwindow.ui \
    Start/secquestion.ui \
    Start/setting.ui \
    Start/loginwidget.ui \
    Inbox/changepsdwithlast.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    icon.qrc \
    Inbox/icon.qrc
