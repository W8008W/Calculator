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
    Calculator cal;
    ui->lineEdit->setText((cal.getResult(str)));
}
