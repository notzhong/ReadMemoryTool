#pragma once
#include <map>
#include <sstream>


// CustomComboBox

class CustomComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CustomComboBox)
	/*
	���ڽ��մ����process PID
	*/
	PULONG64 m_pPid = NULL;
	std::map<ULONG64, CString> m_ProcessNames;
public:
	CustomComboBox();
	/*
	����PID��ַ
	*/
	void SetProcessId(PULONG64 pid);
	virtual ~CustomComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	/*
	��Ͽ����ݷ����ı�󣬸��ݽ������Ƹı�PID
	*/
	afx_msg void OnCbnSelchange();
	//��ȡ������Ϣ
	void GetProcessInfo();
	//���ݽ������ƻ�ȡPID
	ULONG64 GetPidFromProcessName(CString);
};


