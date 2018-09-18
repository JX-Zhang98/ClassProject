#ifndef SHOWBOX_H
#define SHOWBOX_H

#include <QWidget>
#include "mail.h"

namespace Ui {
class ShowBox;
}

class ShowBox : public QWidget
{
    Q_OBJECT

public:
    explicit ShowBox(QWidget *parent = nullptr);
    ~ShowBox();

    void showmail(Mail mail);

private:
    Ui::ShowBox *ui;
};

#endif // SHOWBOX_H
