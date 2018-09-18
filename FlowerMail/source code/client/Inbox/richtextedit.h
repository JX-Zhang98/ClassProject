#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextCharFormat>
#include <QTextListFormat>
#include <QTextList>

namespace Ui {
class RichTextEdit;
}

class RichTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit RichTextEdit(QWidget *parent = nullptr);
    ~RichTextEdit();
    QString ContentInHtml();
    void clear();
    void SetContent(QString);

private slots:
    void on_textMiddleButton_clicked();
    void on_textRightButton_clicked();
    void on_textLeftButton_clicked();
    void on_textBoldButton_clicked();
    void on_colorButton_clicked();
    void on_textItalicButton_clicked();
    void on_textUnderlineButton_clicked();
    void on_fontSizeBox_currentTextChanged(const QString &arg1);
    void on_listButton_clicked();

    void on_numberListButton_clicked();

private:
    Ui::RichTextEdit *ui;
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void textStyle(int styleIndex);
    void changePixColor(QColor color);
    void currentCharFormatChanged(const QTextCharFormat & format);
    void cursorPositionChanged();
};

#endif // WIDGET_H
