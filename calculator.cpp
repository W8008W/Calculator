#include "calculator.h"
#include<QList>
Calculator::Calculator()
{
    setOpMap();
    result="";
    isCorrect=true;
    errorMessage="";
}

void Calculator::setOpMap()
{
    /*
    *100至300之间为基本运算符
    * 301至400位函数运算符
    * 400以上为其他
    */
    oPMap.insert("+",100);
    oPMap.insert("-",100);
    oPMap.insert("*",200);
    oPMap.insert("/",200);
    oPMap.insert("^",300);
    oPMap.insert("%",300);
    oPMap.insert("!",301);
    oPMap.insert("sin",400);
    oPMap.insert("cos",400);
    oPMap.insert("tan",400);
    oPMap.insert("cot",400);
    oPMap.insert("log",400);
    oPMap.insert("lg",400);
    oPMap.insert("ln",400);
    oPMap.insert("(",500);
    oPMap.insert(")",500);
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

bool Calculator::isOperendS(QString str)
{
    if(str.length()==1)
    {
        if(str=="-")
            return false;
        else if (str=="e"||str=="π")
            return true;
    }
    if(str.length()==2)
    {
        if(str=="pi"||str=="PI")
            return true;
    }

	for (int i = 0; i < str.length(); i++)
	{
        if (!((str[i] >= '0'&&str[i] <= '9') || (str[i] == '.') || (str[i] == '-')))
        {
            return false;
        }
    }
    return true;
}

bool Calculator::isLineCorrect(QList<QString> list)
{
    QList<QString> tempK;
    tempK.clear();
	int tempL = 0;
	int tempR = 0;

	//判断括号是否输入正确
    for (int i = list.length()-1; i >=0; i--)
	{
        for (int j = 0; j<= i; j++)
        {
            if (list[j] == "(")
            {
                tempL++;
                tempK.append("(");
            }
            else if (list[j]==")")
            {
                tempR++;
                tempK.append(")");
            }
        }

        if(tempR>tempL)
        {
            errorMessage=QString::fromLocal8Bit("括号输入错误！！！");
            isCorrect=false;
            return isCorrect;
        }
        tempL=0;
        tempR=0;
	}

	for (int i=0;i<list.length();i++)
	{
		if (!isOperendS(list[i])&&!isOperator(list[i]))
		{
			errorMessage = QString::fromLocal8Bit("未知输入！！！");
			isCorrect = false;
			return isCorrect;
		}
	}

    for(int i=0;i<list.size();i++)
    {
        if(isOperator(list[i]))
        {
            switch (oPMap.value(list[i],0))
            {
            case 100:
                if(list[i]=="+")
                {
                    if(i==0||i==list.size()-1)
                    {
                        errorMessage=QString::fromLocal8Bit("加法输入错误,不能在头和尾！！！");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if(!((list[i-1]==")")||isOperendS(list[i-1])||list[i-1]=="!"))
                    {
                        errorMessage=QString::fromLocal8Bit("加法输入错误！！！，加法前面只能跟数字、）、!");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if (!((list[i+1]=="(")||isOperendS(list[i+1])||oPMap.value(list[i+1],0)==400))
                    {
                        errorMessage=QString::fromLocal8Bit("加法输入错误！！！，加法后面只能跟数字、函数、（");
                        isCorrect=false;
                        return isCorrect;
                    }
                }
                else if(list[i]=="-")
                {
                    if(i==list.length()-1)
                    {
                        errorMessage=QString::fromLocal8Bit("减法输入错误！！！，减法不能在尾部");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if (!(i==0||(isOperendS(list[i-1])&&list[i-1]!="-")||list[i-1]==")" ||list[i-1]=="(" || list[i - 1] == "!"))
                    {
                        errorMessage=QString::fromLocal8Bit("减法输入错误！！！，减法前面只能跟数字、）、（、!或空");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if (!((list[i+1]=="(")||isOperendS(list[i+1])||oPMap.value(list[i+1],0)==400))
                    {
                        errorMessage=QString::fromLocal8Bit("减法输入错误！！！，减法后面只能跟数字、函数、（");
                        isCorrect=false;
                        return isCorrect;
                    }
                }
                break;
            case 200:
                if(list[i]=="*")
                {
                    if(i==0||i==list.size()-1)
                    {
                        errorMessage=QString::fromLocal8Bit("乘法输入错误,不能在头和尾！！！");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if (!(isOperendS(list[i-1])||list[i-1]==")"))
                    {
                        errorMessage=QString::fromLocal8Bit("乘法输入错误！！！，乘法前面只能跟数字和）");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if (!((list[i+1]=="(")||isOperendS(list[i+1])||oPMap.value(list[i+1],0)==400))
                    {
                        errorMessage=QString::fromLocal8Bit("乘法输入错误！！！，乘法后面只能跟数字、函数、(");
                        isCorrect=false;
                        return isCorrect;
                    }
                }
                else if (list[i]=="/")
                {
                    if(i==0||i==list.size()-1)
                    {
                        errorMessage=QString::fromLocal8Bit("除法输入错误,不能在头和尾！！！");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if (!(isOperendS(list[i-1])||list[i-1]==")"))
                    {
                        errorMessage=QString::fromLocal8Bit("除法输入错误！！！，除法前面只能跟数字和）");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else if (!((list[i+1]=="(")||isOperendS(list[i+1])||oPMap.value(list[i+1],0)==400))
                    {
                        errorMessage=QString::fromLocal8Bit("除法输入错误！！！，除法后面只能跟数字、函数、(");
                        isCorrect=false;
                        return isCorrect;
                    }
                    else
                    {
                        if(isOperendS(list[i+1]))
                        {
                            if(!(list[i+1].toDouble()>0||list[i+1].toDouble()<0))
                            {
                                errorMessage=QString::fromLocal8Bit("被除数不能为0");
                                isCorrect=false;
                                return isCorrect;
                            }
                        }
                    }
                }
                break;
			case 300:
				if (list[i]=="^")
				{
					if (i == 0 || i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("指数输入错误,不能在头和尾！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (!(isOperendS(list[i - 1]) || list[i - 1] == ")"||list[i-1]=="!"))
					{
						errorMessage = QString::fromLocal8Bit("指数输入错误！！！，指数前面只能跟数字、）、!");
						isCorrect = false;
						return isCorrect;
					}
					else if (!((list[i + 1] == "(") || isOperendS(list[i + 1]) || oPMap.value(list[i + 1], 0) == 400))
					{
						errorMessage = QString::fromLocal8Bit("指数输入错误！！！，指数后面只能跟数字、函数、(");
						isCorrect = false;
						return isCorrect;
					}
				}
				else if(list[i]=="%")
				{
					if (i == 0)
					{
						errorMessage = QString::fromLocal8Bit("百分数输入错误,不能在头部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (!(isOperendS(list[i - 1]) || list[i - 1] == ")"||list[i-1]=="!"))
					{
						errorMessage = QString::fromLocal8Bit("百分数输入错误！！！，百分数前面只能跟数字、!、）");
						isCorrect = false;
						return isCorrect;
					}
					else if(i<list.size()-1)
					{
						if(!(isOperendS(list[i + 1]) || oPMap.value(list[i + 1], 0) == 100 || oPMap.value(list[i + 1], 0) == 200))
						{
							errorMessage = QString::fromLocal8Bit("百分数输入错误！！！，百分数后面只能跟数字和基本运算符");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				break;
			case 301:
				if (list[i] == "!")
				{
					if (i == 0)
					{
						errorMessage = QString::fromLocal8Bit("阶乘输入错误,不能在头部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (!(isOperendS(list[i - 1])))
					{
						errorMessage = QString::fromLocal8Bit("阶乘输入错误,前面只能是整数！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (isOperendS(list[i - 1]))
					{
						if (list[i - 1].toDouble() != list[i - 1].toInt())
						{
							errorMessage = QString::fromLocal8Bit("阶乘输入错误,前面只能是整数！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
					if (i<list.size()-1)
					{
						if (isOperator(list[i+1]))
						{
							if (!(oPMap.value(list[i+1])>=100&&oPMap.value(list[i+1],0)<=300))
							{
								errorMessage = QString::fromLocal8Bit("阶乘输入错误,后面只能是基本运算符！！！");
								isCorrect = false;
								return isCorrect;
							}
						}
						else if (isOperendS(list[i + 1]))
						{
							errorMessage = QString::fromLocal8Bit("阶乘输入错误,后面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				break;
			case 400:
				if (list[i]=="sin")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,sin不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if(list[i+1]!="(")
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,sin后面接左括号！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if(i>0)
					{
						if (isOperendS(list[i-1])&&list[i-1]!="-")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,sin前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if(list[i-1]==")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,sin前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				else if(list[i]=="cos")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,cos不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (list[i + 1] != "(")
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,cos后面接左括号！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (i > 0)
					{
						if (isOperendS(list[i - 1]) && list[i - 1] != "-")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,cos前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if (list[i - 1] == ")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,cos前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				else if(list[i]=="tan")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,tan不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (list[i + 1] != "(")
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,tan后面接左括号！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (i > 0)
					{
						if (isOperendS(list[i - 1]) && list[i - 1] != "-")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,tan前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if (list[i - 1] == ")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,tan前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				else if(list[i]=="cot")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,cot不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (list[i + 1] != "(")
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,cot后面接左括号！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (i > 0)
					{
						if (isOperendS(list[i - 1]) && list[i - 1] != "-")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,cot前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if (list[i - 1] == ")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,cot前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				else if (list[i] == "log")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,log不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (list[i + 1] != "(")
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,log后面接左括号！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (i > 0)
					{
						if (isOperendS(list[i - 1]) && list[i - 1] != "-")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,log前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if (list[i - 1] == ")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,log前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				else if (list[i] == "ln")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,ln不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (list[i + 1] != "(")
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,ln后面接左括号！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (i > 0)
					{
						if (isOperendS(list[i - 1]) && list[i - 1] != "-")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,ln前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if (list[i - 1] == ")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,ln前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				else if (list[i] == "lg")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,lg不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (list[i + 1] != "(")
					{
						errorMessage = QString::fromLocal8Bit("函数输入错误,lg后面接左括号！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (i > 0)
					{
						if (isOperendS(list[i - 1]) && list[i - 1] != "-")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,lg前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if (list[i - 1] == ")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,lg前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				break;
			case 500:
				if (list[i]=="(")
				{
					if (i == list.size() - 1)
					{
						errorMessage = QString::fromLocal8Bit("输入错误,(不能在尾部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (list[i+1]=="+"|| list[i + 1] == "-" || list[i + 1] == "*" || list[i + 1] == "/" || list[i + 1] == "^" || list[i + 1] == "%"|| list[i + 1] == "!"|| list[i + 1] == ")")
					{
						errorMessage = QString::fromLocal8Bit("(后面输入错误！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (i > 0)
					{
						if (isOperendS(list[i - 1]))
						{
							errorMessage = QString::fromLocal8Bit("输入错误,（前面不能接数字！！！");
							isCorrect = false;
							return isCorrect;
						}
						else if (list[i - 1] == ")")
						{
							errorMessage = QString::fromLocal8Bit("函数输入错误,(前面不能接右括号！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				if (list[i] == ")")
				{
					if (i == 0)
					{
						errorMessage = QString::fromLocal8Bit("输入错误,)不能在头部！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if (isOperator(list[i-1])&&list[i-1]!=")")
					{
						errorMessage = QString::fromLocal8Bit("输入错误,)前面输入错误！！！");
						isCorrect = false;
						return isCorrect;
					}
					else if(i<list.length()-1)
					{
						if (isOperendS(list[i+1])||list[i+1]=="tan"|| list[i + 1] == "cot"|| list[i + 1] == "sin"|| list[i + 1] == "cos"|| list[i + 1] == "(")
						{
							errorMessage = QString::fromLocal8Bit("输入错误,)后面输入错误！！！");
							isCorrect = false;
							return isCorrect;
						}
					}
				}
				break;
            }
        }
        else if (isOperendS(list[i]))
        {
            if(list[i]=="e"||list[i]=="PI"||list[i]=="pi"||list[i]=="π")
            {
                if(i==0&&list.length()>1)
                {
                    if(isOperendS(list[i+1]))
                    {
                        errorMessage=QString::fromLocal8Bit("输入错误！！！");
                        isCorrect=false;
                        return isCorrect;
                    }
                }
                else if(i>0)
                {
                    if(isOperendS(list[i-1]))
                    {
                        errorMessage=QString::fromLocal8Bit("输入错误！！！");
                        isCorrect=false;
                        return isCorrect;
                    }
                }
            }
        }
    }
    return true;
}

void Calculator::addList(QList<QString> tempList)
{
    int tempL=0;
    int tempR=0;
    QList<QString> temp;
    temp=tempList;
    for (int i=0;i<temp.length();i++)
    {
        if(temp[i]=="(")
            tempL++;
        else if (temp[i]==")")
        {
            tempR++;
        }
    }
    if(tempL>tempR)
    {
        for (int i=0;i<(tempL-tempR);i++)
        {
            list.append(")");
        }
    }
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
    int tempNum=0;
   // QList<QString> list;

    for (int i=0;i<str.size();i++)
    {
        judge+=str[i];
        if(isOperend(judge))
        {
            num=1;
        }
        else if(isOperator(judge))
        {
            num=2;
        }
        else if (isMath(judge))
        {
            num=3;
        }
        else
        {
            num=4;
        }

        if(num==1)
        {
            if(tempNum!=1&&(!temp.isEmpty()))
            {
                list.append(temp);
                temp.clear();
            }
            if(i==str.length()-1)
            {
                temp+=judge;
                list.append(temp);
                temp.clear();
            }
            temp+=judge;
            tempNum=1;
        }
        else if(num==2)
        {
            if(!temp.isEmpty())
            {
                list.append(temp);
                temp.clear();
            }
            temp+=str[i];
            list.append(temp);
            temp.clear();
            tempNum=2;
        }
        else if (num==3)
        {
            if(tempNum!=3&&(!temp.isEmpty()))
            {
                list.append(temp);
                temp.clear();
            }
            if (i==str.length()-1)
            {
				temp += judge;
                list.append(temp);
                temp.clear();
            }
            temp+=judge;
            tempNum=3;
        }
        else if(num==4)
        {
            if(tempNum!=4&&(!temp.isEmpty()))
            {
                list.append(temp);
                temp.clear();
            }
            if(i==str.length()-1)
            {
                temp+=str[i];
                list.append(temp);
                temp.clear();
            }
            temp+=judge;
            tempNum=4;
        }
        judge.clear();
    }
    return list;
}

QString Calculator::getResult(QString str)
{
    QString str1="";

    //是否是空
    if(str.isEmpty())
    {
        errorMessage=QString::fromLocal8Bit("请输入数据");
        isCorrect=false;
        return errorMessage;
    }
    //转换为Qlist<QString>方便计算
    list=convertToList(str);

    //算式错误，退出计算并输出错误信息
    if(!(isLineCorrect(list)))
    {
        return errorMessage;
    }
    //算式正确后，不全缺少的右括号
    else
    {
         addList(list);
    }
    for (int i=0;i<list.length();i++)
    {
         str1.append(list[i]);
    }
    return str1;

}

