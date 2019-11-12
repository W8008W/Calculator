#include "widget.h"
#include "ui_widget.h"

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
    int posL=str.lastIndexOf("(");
    int posR=-1;
    QString strTemp="";
    ui->lineEdit->setText(QString::asprintf("%d",str.length()));
    if(posL)
    {
        for (int i=posL;i<str.length();i++)
        {
            if (str[i]==")")
            {
               posR=i ;
            }
        }
    }
    if(posR>posL)
    {
        for (int i=posL+1;i<posR;i++)
        {
            strTemp+=str[i];
        }
    }

    //ui->lineEdit->setText(strTemp);
    //ui->lineEdit->setText(QString::asprintf("%d----%d",posL,posR));
}

QString Widget::BasicCalculate(QString str)
{
    QList<QString> list,poslist;
    QString strOp="+-*/";
    QString tempStr="";
    QString tempOp="";
    QString strReturn="";
    int temp =0;
    int pos=0;
    for (int i=0;i<str.length();i++)
    {
        for (int j=0;j<strOp;j++)
        {
            if(str[i]==strOp[j])
            {
               temp++;
               tempOp+=str[i];
               poslist.append(tempOp);
               tempOp.clear();
               for (int k=pos;k<i;k++)
               {
                    tempStr+=str[k];
                    tempOp+=strOp[j];
               }
               list.append(tempStr);
               list.append(tempOp);
               tempOp.clear();
               tempStr.clear();
               pos=i+1;
            }
        }
    }
    if(temp==0)
        return str;

    for (int k=pos;k<str.length();k++)
        tempStr+=str[k];
    list.append(tempStr);

    QList<QString> num;
    for (int i=0;i<temp;i++)
    {
        switch (str[poslist[i].toUInt()].unicode())
        {
        case '*':
            num.append("2");
            break;
        case '/':
            num.append("2");
            break;
        case '+':
            num.append("1");
            break;
        case '-':
            num.append("1");
            break;
        default:
            break;
        }
    }
    num+="0";
    double Sum=0;
    for (int i=1;i<num.length()-1;i++)
    {
        if(num[i].toInt()>=num[i-1].toInt()&&num[i].toInt()>=num[i+1].toInt())
        {
            Sum=list[2*i-2].toDouble()*list[2*i].toDouble();

            list.removeAt(2*i);
            list.removeAt(2*i);
            list.removeAt(2*i);
            list.insert(2*i,QString::asprintf("%f",Sum));
            for (int j=0;j<list.size();j++)
            {
                  strReturn+=list[j];
            }
            return BasicCalculate(strReturn);
        }
    }

}
