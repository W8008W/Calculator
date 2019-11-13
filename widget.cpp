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
    QList<QString> list =cal.convertToList(str);
    for (int i=0;i<list.size();i++)
    {
          str2.append(list[i]);
		  str2.append("|");
    }
    ui->lineEdit->setText(str2);

}
