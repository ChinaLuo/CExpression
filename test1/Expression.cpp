/********************************************************************************
* Copyright (C), 2012 �ױڻ�ʢ ������
*
* �������̲���Visual Studio 2010 SP1 ����Windows XP SP3�ϲ���ͨ����
* ��������ϵ��ʽ��luoshupeng@gmail.com��
* 
* ������ʵ�ֹ��ܣ�
*		1.ʵ�ֻ�����ѧ��ʽ�ļ���
*		2.֧�ֵ�������У�+(�ӻ�����)��-(������)��*(��)��/(��)��%(��ģ)��()(����)��
*				&(��λ��)��|(��λ��)��<<(����)��>>(����)
*		3.��������ȼ���C������������ȼ���ͬ
* 
* �ļ���ʷ��
* �汾��		����			����			˵��
* V1.0		2012-05-09	������		��������ɹ���
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


// ��ӷ���
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
		else AfxMessageBox(_T("���󣡣��������ƥ�����󣡣�"));
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
		else AfxMessageBox(_T("���󣡣��������ƥ�����󣡣�"));
	}
	else AfxMessageBox(_T("���󣡣��������ƥ�����󣡣�"));
}


// �������
void CExpression::AddNum(double dNum)
{
	if (m_first == 0) { m_Fh.Push(FHBEGIN); }	//��һ�����ݣ�ѹ����ſ�ʼ��ʶ
	if (m_last!=0 && m_last!=RKH)
	{
		m_first ++;
		m_Sz.Push(dNum);
	}
	m_last = 0;
}


// ��ջ��ѹ���ֺͷ���
int CExpression::Ysf(int i)
{
	double g, h;
	int n, t;
	m_Fh.Pop(n);
	while (n != FHBEGIN)		//top ���ǿ�ʼ��
	{
		if (n-i < 0)	//��ǰ���ȼ��ߣ�����ջ
		{
			m_Fh.Push(n);
			m_Fh.Push(i);
			return 1;
		}
		else if (n==LKH && i==-1){return 1;}	//������
		else if (n==LKH)	//��������ǰ����������ͨ�����
		{
			m_Fh.Push(n);
			m_Fh.Push(i);
			return 1;
		}
		else if (n-i >= 0)		//��ǰ���ȼ���,������
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
	if(i==-3)return 0;			//��ʼ���������
	else						//��ʼʱ��һ������ѹ��
	{
		m_Fh.Push(n);
		m_Fh.Push(i);
		return 1;
	}
}


// ������ʽ�����ؽ��
double CExpression::ParseString(const CString& szString)
{
	if ( szString.IsEmpty())
		return 0;
	CString szLine = szString;
	CString szTmp;
	//��һ���Ƿ���������
	szLine.Trim();
	szTmp = szLine.Left(1);	
	if (szTmp.CompareNoCase(_T("(")) == 0)	//��������
	{
		AddFh(LKH);
		szLine = szLine.Mid(1,szLine.GetLength()-1);
	} 
	//��һ���Ƿ������Ż��߸���
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


// ������
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
		AfxMessageBox(_T("���󣡣������ʽ���󣡣�"));
		return 0;
	}
}
