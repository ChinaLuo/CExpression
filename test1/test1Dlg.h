
// test1Dlg.h : 头文件
//

#pragma once
#include "Expression.h"

// Ctest1Dlg 对话框
class Ctest1Dlg : public CDialogEx
{
// 构造
public:
	Ctest1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
