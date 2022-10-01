
// TestSysDlg.h: 头文件
//

#pragma once
#include "CustomComboBox.h"
#include "CustomListCtrl.h"

// CTestSysDlg 对话框
class CTestSysDlg : public CDialogEx
{
// 构造
public:
	CTestSysDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	ULONG64 m_pid = NULL;
	CustomComboBox SysComboBox;
	CustomListCtrl m_ListCtrl;
	HANDLE m_pHandle = NULL;
protected:
	void InitCtrl();

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void CatMemoryData();
	afx_msg ULONG64 getAddress();
protected:
	CString m_pAddr;
	CString m_pOffSet1;
	CString m_pOffSet2;
	CString m_pOffSet3;
	CString m_pOffSet4;
	CString m_pOffSet5;

public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnIdok();
	void PrintForReadMemory();
	
	afx_msg void OnBnClickedRefresh();
};
