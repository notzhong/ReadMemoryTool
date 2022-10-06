#pragma once
#include <map>
#include <sstream>


// CustomComboBox

class CustomComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CustomComboBox)
	/*
	用于接收传入的process PID
	*/
	PULONG64 m_pPid = NULL;
	std::map<ULONG64, CString> m_ProcessNames;
public:
	CustomComboBox();
	/*
	设置PID地址
	*/
	void SetProcessId(PULONG64 pid);
	virtual ~CustomComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	/*
	组合框内容发生改变后，根据进程名称改变PID
	*/
	afx_msg void OnCbnSelchange();
	//获取进程信息
	void GetProcessInfo();
	//根据进程名称获取PID
	ULONG64 GetPidFromProcessName(CString);
};


