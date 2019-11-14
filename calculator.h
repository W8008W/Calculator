#ifndef CALCULATOR_H
#define CALCULATOR_H
#include<QString>
#include<QList>

class Calculator
{
public:
    Calculator();

    //运算符
    QMap<QString,int> oPMap;
    QList<QString> list;
    //basicCal运算结果
    QString result;
    QString errorMessage;

    //算式是否正确
    bool isCorrect;


    void setOpMap();

    //判断是否是基本运算符
	bool isOperator(QString str);
    //判断是否是函数
    bool isMath(QString str);
    //判断是否是数字,针对输入转换成列表
    bool isOperend(QString str);
	//判断是否是数字,字符串，包含“-”
	bool isOperendS(QString str);
    //判断算式括号是否正确
    bool isLineCorrect(QList<QString> list);
    //将算式转换成链表
    QList<QString> convertToList(QString str);
};

#endif // CALCULATOR_H
