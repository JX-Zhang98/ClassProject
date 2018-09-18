#ifndef SECQUESTION_H
#define SECQUESTION_H

#include <QWidget>
#include <QMessageBox>
#include"changepwdwindow.h"
#include "userinfocontrol.h"
namespace Ui {
class SecQuestion;
}

class SecQuestion : public QWidget
{
    Q_OBJECT

public:
    explicit SecQuestion(QWidget *parent = 0);
    void setusername(QString inputs){
        username=inputs;

    }
    ChangepwdWindow *change;
    ~SecQuestion();
    void Exec1(QString);
    void Exec2(QString);

private slots:
    void on_OK_clicked();

private:
    Ui::SecQuestion *ui;
    QString username;
};

#endif // SECQUESTION_H
