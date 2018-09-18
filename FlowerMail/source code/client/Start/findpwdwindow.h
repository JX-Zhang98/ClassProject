#ifndef FINDPWDWINDOW_H
#define FINDPWDWINDOW_H

#include <QWidget>
#include "secquestion.h"

namespace Ui {
class FindpwdWindow;
}

class FindpwdWindow : public QWidget
{
    Q_OBJECT

public:
    SecQuestion *sec;
    explicit FindpwdWindow(QWidget *parent = 0);
    ~FindpwdWindow();
private slots:
    void on_Confirm_clicked();

private:
    Ui::FindpwdWindow *ui;
};

#endif // FINDPWDWINDOW_H
