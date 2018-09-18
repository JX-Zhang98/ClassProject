#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
}

setting::~setting()
{
    delete ui;
}

void setting::on_changepassword_clicked()
{
    //加载到changepassword界面
}

void setting::on_setquestion_clicked()
{
    set=new setquestion;
    set->show();
}

void setting::on_setting_2_clicked()
{

}

void setting::on_saveReplayButton_clicked()
{
    if(ui->replayCheckBox->checkState()==Qt::Checked)
    {
        MailControl::SetAutoReplay(ui->textEdit->toPlainText());
    }
}
