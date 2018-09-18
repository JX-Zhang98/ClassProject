#include "richtextedit.h"
#include "ui_richTextEdit.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QColorDialog>
#include <QDebug>

RichTextEdit::RichTextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RichTextEdit)
{
    ui->setupUi(this);
    QPixmap pix(16, 16);
    pix.fill("Black");
    ui->colorButton->setIcon(pix);
    connect(ui->textEdit,&QTextEdit::currentCharFormatChanged,this,&RichTextEdit::currentCharFormatChanged);
    connect(ui->textEdit,&QTextEdit::cursorPositionChanged,this,&RichTextEdit::cursorPositionChanged);
}

RichTextEdit::~RichTextEdit()
{
    delete ui;
}

void RichTextEdit::clear()
{
    ui->textEdit->clear();
}

void RichTextEdit::SetContent(QString content)
{
    ui->textEdit->setHtml(content);
}

//大小
void RichTextEdit::on_fontSizeBox_currentTextChanged(const QString &arg1)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(arg1.toInt());
    mergeFormatOnWordOrSelection(fmt);
}
//加粗
void RichTextEdit::on_textBoldButton_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->textBoldButton->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}
//斜体
void RichTextEdit::on_textItalicButton_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->textItalicButton->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
//下划线
void RichTextEdit::on_textUnderlineButton_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->textUnderlineButton->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
//字体颜色
void RichTextEdit::on_colorButton_clicked()
{
    QColor col = QColorDialog::getColor(ui->textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    changePixColor(col);
}
//合并格式
void RichTextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}

//setAlignment选择本行对其方式
//居中对齐
void RichTextEdit::on_textMiddleButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignHCenter);
    ui->textLeftButton->setChecked(false);
    ui->textRightButton->setChecked(false);
}
//右对齐
void RichTextEdit::on_textRightButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    ui->textLeftButton->setChecked(false);
    ui->textMiddleButton->setChecked(false);
}
//左对齐
void RichTextEdit::on_textLeftButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    ui->textRightButton->setChecked(false);
    ui->textMiddleButton->setChecked(false);
}
//圆点列表
void RichTextEdit::on_listButton_clicked()
{
    if(!ui->listButton->isChecked())
    {
        textStyle(0);
        ui->listButton->setChecked(false);
    }
    else
    {
        textStyle(1);
        ui->listButton->setChecked(true);
    }
}
//数字列表
void RichTextEdit::on_numberListButton_clicked()
{
    QPushButton a;
    if(!ui->numberListButton->isChecked())
    {
        textStyle(0);
        ui->numberListButton->setChecked(false);
    }
    else
    {
        textStyle(2);
        ui->numberListButton->setChecked(true);
    }
}
//调整列表格式
void RichTextEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;
        switch (styleIndex) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListDecimal;
                break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}
//更改调色盘标志颜色
void RichTextEdit::changePixColor(QColor col)
{
    QPixmap pix(16, 16);
    pix.fill(col);
    ui->colorButton->setIcon(pix);
}
//光标移动是字符格式改变操作
void RichTextEdit::currentCharFormatChanged(const QTextCharFormat & format)
{
    changePixColor(format.foreground().color());
    ui->textBoldButton->setChecked(format.font().bold());
    ui->textItalicButton->setChecked(format.font().italic());
    ui->textUnderlineButton->setChecked(format.font().underline());
    //qDebug()<<format.font().pointSize();
    ui->fontSizeBox->setCurrentText(QString::number(format.font().pointSize()));
}
//光标移动时对其方式改变操作
void RichTextEdit::cursorPositionChanged()
{
    ui->textLeftButton->setChecked(false);
    ui->textRightButton->setChecked(false);
    ui->textMiddleButton->setChecked(false);
    switch (ui->textEdit->alignment())
    {
        case Qt::AlignLeft:
            ui->textLeftButton->setChecked(true);
            break;
        case Qt::AlignRight:
            ui->textRightButton->setChecked(true);
            break;
        case Qt::AlignCenter:
            ui->textMiddleButton->setChecked(true);
            break;
    }
    QTextCursor cursor=ui->textEdit->textCursor();
    if(cursor.currentList())
    {
        QTextListFormat::Style style=cursor.currentList()->format().style();
        switch(style)
        {
            case QTextListFormat::ListDisc:
                ui->listButton->setChecked(true);
                ui->numberListButton->setChecked(false);
            break;
            case QTextListFormat::ListDecimal:
                ui->listButton->setChecked(false);
                ui->numberListButton->setChecked(true);
            break;
            default:
            break;
        }
    }
    else
    {
        ui->listButton->setChecked(false);
        ui->numberListButton->setChecked(false);
    }

}

//以HTML格式返回内容
QString RichTextEdit::ContentInHtml()
{
    return ui->textEdit->toHtml();
}
