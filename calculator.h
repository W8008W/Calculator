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

    void setOpMap();
    //判断是否是基本运算符
    bool isOperator(QString str);
    //判断是否是函数
    bool isMath(QString str);
    //判断是否是数字
    bool isOperend(QString str);

    //将算式转换成链表
    QList<QString> convertToList(QString str);

    double grtResult(QList<QString> list);
};

#endif // CALCULATOR_H
