#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include"setquestion.h"
#include "mailcontrol.h"

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();

private slots:
    void on_changepassword_clicked();

    void on_setquestion_clicked();

    void on_setting_2_clicked();



    void on_saveReplayButton_clicked();

private:
    Ui::setting *ui;
    setquestion *set;
};

#endif // SETTING_H
