#ifndef STACKWIDGETTEST1_H
#define STACKWIDGETTEST1_H

#include <QWidget>

namespace Ui {
class StackWidgetTest1;
}

class StackWidgetTest1 : public QWidget
{
    Q_OBJECT

public:
    explicit StackWidgetTest1(QWidget *parent = nullptr);
    ~StackWidgetTest1();

private:
    Ui::StackWidgetTest1 *ui;
};

#endif // STACKWIDGETTEST1_H
