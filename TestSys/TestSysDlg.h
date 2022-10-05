
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
	/*
	*窗口初始化时调用的函数
	*/
	virtual BOOL OnInitDialog();
	/*
	*MFC初始化绘画窗口调用函数
	*/
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	/*
	*获取Process的PID
	*/
	ULONG64 m_pid = NULL;
	/*
	*下拉框控件
	*/
	CustomComboBox SysComboBox;
	/*
	* 列表控件
	*/
	CustomListCtrl m_ListCtrl;
	/*
	* 用于接受打开Process的句柄
	*/
	HANDLE m_pHandle = NULL;
protected:
	/*
	* 初始化控件信息
	*/
	void InitCtrl();

public:
	/*
	*窗口改变大小时调用产生WM_SIZE信号，调用该函数
	*/
	afx_msg void OnSize(UINT nType, int cx, int cy);
	/*
	遍历按钮所绑定的函数，点击遍历按钮后开始遍历指定地址
	*/
	afx_msg void CatMemoryData();
	/*
	获取偏移地址
	*/
	afx_msg ULONG64 getAddress();
protected:
	/*
	记录读取的内存地址
	*/
	CString m_pAddr;
	/*
	记录偏移大小
	*/
	CString m_pOffSet1;
	CString m_pOffSet2;
	CString m_pOffSet3;
	CString m_pOffSet4;
	CString m_pOffSet5;

public:
	/*
	OnClose();
	OnDestroy();
	DestroyWindow();
	都是销毁窗口所调用的。
	*/
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnIdok();
	/*
	打印读到内存数据
	*/
	void PrintForReadMemory();
	/*
	刷新应用程序列表
	*/
	afx_msg void OnBnClickedRefresh();
};
