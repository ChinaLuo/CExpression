/********************************************************************************
* Copyright (C), 2012 鹤壁华盛 罗树鹏
*
* 【本例程采用Visual Studio 2010 SP1 并在Windows XP SP3上测试通过】
* 【作者联系方式：luoshupeng@gmail.com】
* 
* 本例程实现功能：
*		1.实现基本数学公式的计算
*		2.支持的运算符有：+(加或正数)，-(减或负数)，*(乘)，/(除)，%(求模)，()(括号)，
*				&(按位与)，|(按位或)，<<(左移)，>>(右移)
*		3.运算符优先级与C语言运算符优先级相同
* 
* 文件历史：
* 版本号		日期			作者			说明
* V1.0		2012-05-09	罗树鹏		创建并完成功能
*
*/
#pragma once

template<class M>
class CStack
{
public:
	CStack(int MaxStackSiz = 20)
	{
		MaxTop = MaxStackSiz - 1;
		stack = new M[MaxStackSiz];
		top = -1;
	}
	virtual ~CStack(void) { delete [] stack; }
	bool IsEmpty(void) { return top == -1; }
	bool IsFull(void) { return top == MaxTop; }
	void Push(const M& x) { stack[++top] = x; }
	void Pop(M& x) { x = stack[top--]; }
private:
	int top;
	int MaxTop;
	M* stack;
};

const CString FINDSTRING = _T("|&<>+-*/%()");
const CString FINDSTRING1 = FINDSTRING.Left(FINDSTRING.GetLength()-2);
const int FHBEGIN	= -7;
const int BITOR		= 1;
const int BITAND	= 2;
const int LSHIFT	= 3;
const int RSHIFT	= 4;
const int PLUS		= 5;
const int MINUS		= 6;
const int MULTIPLY	= 7;
const int DEVIDE	= 8;
const int LKH		= 9;
const int RKH		= 10;
const int MODULUS		= 11;
class CExpression
{
public:
	CExpression(void);
	virtual ~CExpression(void);
protected:
	// 运算符号栈
	CStack<int> m_Fh;
	// 运算数据栈
	CStack<double> m_Sz;
	// 上一次的数据（包括符号）
	int m_last;
	// 是否有左括号
	int m_Lkh;
	// 第一个数据
	int m_first;
public:
	// 添加符号
	void AddFh(int nFh);
	// 添加数据
	void AddNum(double dNum);
	// 向栈中压数字和符号
	int Ysf(int i);
	// 解析公式并返回结果
	double ParseString(const CString& szString);
	// 计算结果
	double GetResult(void);
};

