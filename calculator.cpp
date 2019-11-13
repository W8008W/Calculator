#include "calculator.h"
#include<QList>
Calculator::Calculator()
{
    setOpMap();
}

void Calculator::setOpMap()
{
    oPMap.insert("+",100);
    oPMap.insert("-",100);
    oPMap.insert("*",200);
    oPMap.insert("/",200);
    oPMap.insert("^",300);
    oPMap.insert("%",300);
    oPMap.insert("sin",400);
    oPMap.insert("cos",400);
    oPMap.insert("tan",400);
    oPMap.insert("cot",400);
    oPMap.insert("log",400);
    oPMap.insert("lg",400);
    oPMap.insert("ln",400);
}

bool Calculator::isOperator(QString str)
{
    for (int i=0;i<oPMap.size();i++)
    {
        if(oPMap.value(str,0))
        {
            return true;
        }
    }
    return false;
}

bool Calculator::isMath(QString str)
{
    if((str[0]>='a'&&str[0]<='z')||(str[0]>='A'&&str[0]<='Z'))
    {
        return true;
    }
    return false;
}

bool Calculator::isOperend(QString str)
{
    if((str[0]>='0'&&str[0]<='9')||(str[0]=='.'))
    {
        return true;
    }
    else
        return false;
}

QList<QString> Calculator::convertToList(QString str)
{
    QString judge,middle,temp;
    judge="";
    temp="";
    int num=0;
    QList<QString> list;

    for (int i=0;i<str.length();i++)
    {
        judge+=str[i];
        //把数字入链
        if(isOperend(judge))
        {
            if(num==0)
            {
                temp+=str[i];
            }
            else if(num==1)
            {
                temp+=str[i];
                if(i==str.length()-1)
                {
                    list.append(temp);
                    temp.clear();
                }
            }
            else
            {
				if (num == 3)
				{
					list.append(temp);
					temp.clear();
				}
				temp += str[i];
				if (i == str.length() - 1)
				{
					list.append(temp);
					temp.clear();
				}
            }
            num=1;
            judge.clear();
        }
        //把操作符入链
        else if (isOperator(judge))
        {
			if (i>0)
			{
				list.append(temp);
				temp.clear();
			}
            list.append(judge);
            num=2;
            judge.clear();
        }
        else if(isMath(judge))
        {
			if (num != 3&&(!temp.isEmpty()))
			{
				list.append(temp);
				temp.clear();
			}
            temp+=str[i];
            if(i==str.length()-1)
            {
                list.append(temp);
                temp.clear();
            }
            num=3;
            judge.clear();
        }
        else
        {
			if (!temp.isEmpty())
			{
				list.append(temp);
				temp.clear();
			}
            list.append(judge);
            num=4;
            judge.clear();
        }
    }
    return list;
}

double Calculator::grtResult(QList<QString> list)
{
    Q_UNUSED(list)
    for (int i=0;i<list.size();i++)
    {

    }
    return 0;
}
