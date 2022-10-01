#pragma once
#include <map>
#include <sstream>


// CustomComboBox

class CustomComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CustomComboBox)
	PULONG64 m_pPid = NULL;
	std::map<ULONG64, CString> m_ProcessNames;
public:
	CustomComboBox();
	void SetProcessId(PULONG64 pid);
	virtual ~CustomComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchange();
	//��ȡ������Ϣ
	void GetProcessInfo();
	//���ݽ������ƻ�ȡPID
	ULONG64 GetPidFromProcessName(CString);
};


