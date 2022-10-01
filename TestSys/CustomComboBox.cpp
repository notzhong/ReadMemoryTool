// CustomComboBox.cpp: 实现文件
//

#include "pch.h"
#include "TestSys.h"
#include "CustomComboBox.h"
#include <TlHelp32.h>

// CustomComboBox

IMPLEMENT_DYNAMIC(CustomComboBox, CComboBox)

CustomComboBox::CustomComboBox()
{
}

void CustomComboBox::SetProcessId(PULONG64 pPid)
{
	m_pPid = pPid;
}

CustomComboBox::~CustomComboBox()
{
}


BEGIN_MESSAGE_MAP(CustomComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CustomComboBox::OnCbnSelchange)
END_MESSAGE_MAP()



// CustomComboBox 消息处理程序


void CustomComboBox::OnCbnSelchange()
{
	// TODO: 在此添加控件通知处理程序代码
    CString sName;
    GetLBText(GetCurSel(), sName);
    *m_pPid = GetPidFromProcessName(sName);
    if (!*m_pPid)
		MessageBox(L"PID获取失败！！！", _T("提示："));
}

void CustomComboBox::GetProcessInfo()
{
    //此结构描述了列表中的条目，该条目枚举了拍摄快照时驻留在系统地址空间中的进程。
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    //创建系统进程快照
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    //获取第一个进程信息
    Process32First(hProcessSnap, &pe32);

    //创建用于接收系统进程的对象
    CString sProcessNames;

    //遍历进程名
    do
    {
<<<<<<< HEAD
=======

>>>>>>> 85f4d1832fbe654dcd1b1d041e1d4ea68d2b61e1
        //从进程快照中将进程名称传入接收的对象中
        sProcessNames = pe32.szExeFile;

        //将系统进程PID，名称存放入ProcessName中
        m_ProcessNames[pe32.th32ProcessID] = sProcessNames;

        AddString(sProcessNames);

    } while (Process32Next(hProcessSnap, &pe32));//获取下一个进程信息

    CloseHandle(hProcessSnap);
}

ULONG64 CustomComboBox::GetPidFromProcessName(CString sName)
{
<<<<<<< HEAD
    //根据进程文件名称遍历ProcessId
=======
>>>>>>> 85f4d1832fbe654dcd1b1d041e1d4ea68d2b61e1
    for (auto it = m_ProcessNames.begin(); it != m_ProcessNames.end(); it++) {
        if (it->second == sName)
            return it->first;
    }
    return 0;
}
