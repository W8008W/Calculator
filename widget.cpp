#include "widget.h"
#include "ui_widget.h"
#include "calculator.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnResult_clicked()
{
    QString str=ui->lineEdit->text();
    QString str2;
    Calculator cal;
    cal.list=cal.convertToList(str);
    if(cal.isLineCorrect(cal.list))
    {
        ui->lineEdit->setText(QString::fromLocal8Bit("输入正确"));
    }
    else
    {
        ui->lineEdit->setText(cal.errorMessage);
    }
}
