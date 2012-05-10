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
	// �������ջ
	CStack<int> m_Fh;
	// ��������ջ
	CStack<double> m_Sz;
	// ��һ�ε����ݣ��������ţ�
	int m_last;
	// �Ƿ���������
	int m_Lkh;
	// ��һ������
	int m_first;
public:
	// ��ӷ���
	void AddFh(int nFh);
	// �������
	void AddNum(double dNum);
	// ��ջ��ѹ���ֺͷ���
	int Ysf(int i);
	// ������ʽ�����ؽ��
	double ParseString(const CString& szString);
	// ������
	double GetResult(void);
};

