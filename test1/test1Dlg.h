
// test1Dlg.h : ͷ�ļ�
//

#pragma once
#include "Expression.h"

// Ctest1Dlg �Ի���
class Ctest1Dlg : public CDialogEx
{
// ����
public:
	Ctest1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_str;
	CString m_szResult;
	afx_msg void OnBnClickedButton1();
	CExpression m_expression;
};
