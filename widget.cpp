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
	QString tempStr;
    int posL=str.lastIndexOf("(");
    int posR=-1;
    QString strTemp="";
    ui->lineEdit->setText(QString::asprintf("%d",str.length()));
    if(posL>=0)
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
	//tempStr = BasicCalculate(str);
	QRegExp rx;
	rx.setPattern("(\\.){0,1}0+$");
	tempStr = QString("%1").arg(BasicCalculate(str).toDouble(), 0, 'f', -1).replace(rx, "");
    ui->lineEdit->setText(tempStr);
    //ui->lineEdit->setText(QString::asprintf("%d----%d",posL,posR));
}

QString Widget::BasicCalculate(QString str)
{
    QList<QString> list;
    QString strOp="+-*/";
    QString tempStr="";
    QString strReturn="";
    int temp =0;
	int TEMP[100] = {};//运算符位置存放
    int pos=0;
    for (int i=0;i<str.length();i++)
    {
        for (int j=0;j<strOp.length();j++)
        {
            if(str[i]==strOp[j])
            {
			   QString tempOp = "";
               temp++;
			   TEMP[temp - 1] = i;
               for (int k=pos;k<i;k++)
               {
                    tempStr+=str[k];
               }
			   tempOp += strOp[j];
               list.append(tempStr);
               list.append(tempOp);
               tempOp.clear();
               tempStr.clear();
               pos=i+1;
            }
        }
    }
    if(temp==0||(temp==1&&str[0]=='-'))
        return str;

    for (int k=pos;k<str.length();k++)
        tempStr+=str[k];
    list.append(tempStr);

    QList<QString> num;
	num += "0";
    for (int i=0;i<temp;i++)
    {
        switch (str[TEMP[i]].unicode())
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
            list.removeAt(2*i-1);
            list.removeAt(2*i-2);
            list.insert(2*i-2,QString::asprintf("%f",Sum));
            for (int j=0;j<list.size();j++)
            {
                  strReturn+=list[j];
            }
			//去除后面的0
			
            return BasicCalculate(strReturn);
        }
    }

}
