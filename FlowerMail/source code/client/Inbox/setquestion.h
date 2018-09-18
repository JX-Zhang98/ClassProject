#ifndef SETQUESTION_H
#define SETQUESTION_H

#include <QWidget>

namespace Ui {
class setquestion;
}

class setquestion : public QWidget
{
    Q_OBJECT

public:
    explicit setquestion(QWidget *parent = 0);
    ~setquestion();

private:
    Ui::setquestion *ui;
};

#endif // SETQUESTION_H
