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
#include "StdAfx.h"
#include "Expression.h"


CExpression::CExpression(void)
	: m_last(PLUS)
	, m_Lkh(0)
	, m_first(0)
{
}


CExpression::~CExpression(void)
{
}


// 添加符号
void CExpression::AddFh(int nFh)
{
	int t;
	if (m_last==0 || m_last==RKH)
	{
		if (nFh == PLUS)
		{
			m_last = PLUS;
			t = Ysf(PLUS);
		}
		else if (nFh == MINUS)
		{
			m_last = MINUS;
			t = Ysf(MINUS);
		}
		else if (nFh == MULTIPLY)
		{
			m_last = MULTIPLY;
			t = Ysf(MULTIPLY);
		}
		else if (nFh == DEVIDE)
		{
			m_last = DEVIDE;
			t = Ysf(DEVIDE);
		}
		else if (nFh == MODULUS)
		{
			m_last = MODULUS;
			t = Ysf(MODULUS);
		}
		else if (nFh==RKH && m_Lkh>0)
		{
			m_last = RKH;
			m_Lkh --;
			t = Ysf(-1);
		}
		else if (nFh == BITOR)
		{
			m_last = BITOR;
			t = Ysf(BITOR);
		}
		else if (nFh == BITAND)
		{
			m_last = BITAND;
			t = Ysf(BITAND);
		}
		else if (nFh == LSHIFT)
		{
			m_last = LSHIFT;
			t = Ysf(LSHIFT);
		}
		else if (nFh == RSHIFT)
		{
			m_last = RSHIFT;
			t = Ysf(RSHIFT);
		}
		else AfxMessageBox(_T("错误！！！运算符匹配有误！！"));
	} 
	else if (m_last==PLUS || m_last==MINUS || m_last==MULTIPLY || m_last==DEVIDE || m_last==LKH)
	{
		if (nFh == LKH)
		{
			if (m_first == 0) { m_Fh.Push(FHBEGIN); m_first++; }
			m_last = LKH;
			m_Lkh ++;
			t = Ysf(LKH);
		}
		else AfxMessageBox(_T("错误！！！运算符匹配有误！！"));
	}
	else AfxMessageBox(_T("错误！！！运算符匹配有误！！"));
}


// 添加数据
void CExpression::AddNum(double dNum)
{
	if (m_first == 0) { m_Fh.Push(FHBEGIN); }	//第一个数据，压入符号开始标识
	if (m_last!=0 && m_last!=RKH)
	{
		m_first ++;
		m_Sz.Push(dNum);
	}
	m_last = 0;
}


// 向栈中压数字和符号
int CExpression::Ysf(int i)
{
	double g, h;
	int n, t;
	m_Fh.Pop(n);
	while (n != FHBEGIN)		//top 不是开始符
	{
		if (n-i < 0)	//当前优先级高，则入栈
		{
			m_Fh.Push(n);
			m_Fh.Push(i);
			return 1;
		}
		else if (n==LKH && i==-1){return 1;}	//脱括号
		else if (n==LKH)	//左括号在前，后面是普通运算符
		{
			m_Fh.Push(n);
			m_Fh.Push(i);
			return 1;
		}
		else if (n-i >= 0)		//当前优先级低,则运算
		{
			m_Sz.Pop(h); m_Sz.Pop(g);
			if (n==PLUS)		h = g + h;
			else if (n==MINUS)	h = g - h;
			else if (n==MULTIPLY) h = g * h;
			else if (n==DEVIDE)	h = g / h;
			else if (n==MODULUS)	h = (int)g % (int)h;
			else if (n==BITOR)		h = (int)g | (int)h;
			else if (n==BITAND)		h = (int)g & (int)h;
			else if (n==LSHIFT)		h = (int)g << (int)h;
			else if (n==RSHIFT)		h = (int)g >> (int)h;
			m_Sz.Push(h);
			t = Ysf(i);
		}
		return 1;
	}
	if(i==-3)return 0;			//开始与结束相遇
	else						//开始时第一个符号压入
	{
		m_Fh.Push(n);
		m_Fh.Push(i);
		return 1;
	}
}


// 解析公式并返回结果
double CExpression::ParseString(const CString& szString)
{
	if ( szString.IsEmpty())
		return 0;
	CString szLine = szString;
	CString szTmp;
	//第一个是否是左括号
	szLine.Trim();
	szTmp = szLine.Left(1);	
	if (szTmp.CompareNoCase(_T("(")) == 0)	//是左括号
	{
		AddFh(LKH);
		szLine = szLine.Mid(1,szLine.GetLength()-1);
	} 
	//第一个是否是正号或者负号
	if ( ! szLine.IsEmpty())
	{
		szLine.Trim();
		szTmp = szLine.Left(1);
		if ( szTmp.CompareNoCase(_T("-"))==0 || szTmp.CompareNoCase(_T("+"))==0 )
		{
			szLine = szLine.Mid(1,szLine.GetLength()-1);
			if ( ! szLine.IsEmpty() )
			{
				int pos = -1;
				pos = szLine.FindOneOf(FINDSTRING1/*_T("+-* /")*/);
				if (pos != -1)
					szTmp += szLine.Left(pos);
				else 
					szTmp += szLine;
				AddNum(_ttof(szTmp.Trim()));
				szLine = szLine.Mid(pos,szLine.GetLength()-pos);
				szLine.Trim();
			}
		}
	}
	while ( ! szLine.IsEmpty() )
	{
		int pos = -1;
		pos = szLine.FindOneOf(FINDSTRING);
		if (pos == 0)
		{
			szTmp = szLine.Left(1);
			szLine = szLine.Mid(1,szLine.GetLength()-1);
		}
		else if (pos > 0)
		{
			szTmp = szLine.Left(pos);
			szLine = szLine.Mid(pos,szLine.GetLength()-pos);
		}
		else 
		{
			szTmp = szLine;
			szLine = szLine.Mid(szLine.GetLength(),0);
		}
		szLine.Trim();
		if (szTmp.CompareNoCase(_T("+")) == 0)	//+
			AddFh(PLUS);
		else if (szTmp.CompareNoCase(_T("-")) == 0)	//-
			AddFh(MINUS);
		else if (szTmp.CompareNoCase(_T("*")) == 0)	//*
			AddFh(MULTIPLY);
		else if (szTmp.CompareNoCase(_T("/")) == 0)	// /
			AddFh(DEVIDE);
		else if (szTmp.CompareNoCase(_T("%")) == 0)	// %
			AddFh(MODULUS);
		else if (szTmp.CompareNoCase(_T("(")) == 0)	//(
			AddFh(LKH);
		else if (szTmp.CompareNoCase(_T(")")) == 0)	//)
			AddFh(RKH);
		else if (szTmp.CompareNoCase(_T("|")) == 0)	// |
			AddFh(BITOR);
		else if (szTmp.CompareNoCase(_T("&")) == 0)	// &
			AddFh(BITAND);
		else if (szTmp.CompareNoCase(_T("<")) == 0)	// <<
		{
			szLine = szLine.Mid(1,szLine.GetLength()-1);
			AddFh(LSHIFT);
		}
		else if (szTmp.CompareNoCase(_T(">")) == 0)	// >>
		{
			szLine = szLine.Mid(1,szLine.GetLength()-1);
			AddFh(RSHIFT);
		}
		else
			AddNum(_ttof(szTmp.Trim()));
	}
	return GetResult();
}


// 计算结果
double CExpression::GetResult(void)
{
	/*if(m_last!=6)AddNum();*/
	int t;
	double x;
	if(m_Lkh==0&&(m_last==0||m_last==RKH))
	{
		t=Ysf(-3);
		m_Sz.Pop(x);

		m_last = PLUS;
		m_Lkh	= 0;
		m_first	= 0;

		return x;
	}
	else 
	{
		AfxMessageBox(_T("错误！！！表达式有误！！"));
		return 0;
	}
}
