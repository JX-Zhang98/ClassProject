#ifndef STACKWIDGETTEST2_H
#define STACKWIDGETTEST2_H

#include <QWidget>

namespace Ui {
class StackWidgetTest2;
}

class StackWidgetTest2 : public QWidget
{
    Q_OBJECT

public:
    explicit StackWidgetTest2(QWidget *parent = nullptr);
    ~StackWidgetTest2();

private:
    Ui::StackWidgetTest2 *ui;
};

#endif // STACKWIDGETTEST2_H
