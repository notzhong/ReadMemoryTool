
// TestSysDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TestSys.h"
#include "TestSysDlg.h"
#include "afxdialogex.h"
#include "libelevate.h"
#include <DbgHelp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FILE_MAX 44
#define FILE_NULL 0

// CTestSysDlg 对话框
static const int nType[6]{ 0,4,4,8,10,20 };
static char buff[FILE_MAX]{ 0 };


CTestSysDlg::CTestSysDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TESTSYS_DIALOG, pParent)
    , m_pAddr(L"")
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSysDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PROCESSCOMBO, SysComboBox);
    DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
    DDX_Text(pDX, IDC_ADDRESS, m_pAddr);
    DDX_Text(pDX, IDC_OFFSET1, m_pOffSet1);
    DDX_Text(pDX, IDC_OFFSET2, m_pOffSet2);
    DDX_Text(pDX, IDC_OFFSET3, m_pOffSet3);
    DDX_Text(pDX, IDC_OFFSET4, m_pOffSet4);
    DDX_Text(pDX, IDC_OFFSET5, m_pOffSet5);

}

BEGIN_MESSAGE_MAP(CTestSysDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()

    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_CATMEMORY, &CTestSysDlg::CatMemoryData)
    ON_WM_CLOSE()
    ON_WM_DESTROY()
    ON_COMMAND(IDOK, &CTestSysDlg::OnIdok)
    ON_BN_CLICKED(IDC_REFRESH, &CTestSysDlg::OnBnClickedRefresh)
END_MESSAGE_MAP()


// CTestSysDlg 消息处理程序

BOOL CTestSysDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码
    InitCtrl();
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestSysDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestSysDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CTestSysDlg::InitCtrl()
{
    SysComboBox.SetProcessId(&m_pid);
    SysComboBox.GetProcessInfo();

    m_ListCtrl.InitiativeCtrl();
    
}



void CTestSysDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);

    CRect listRc;
    if (m_ListCtrl.GetSafeHwnd())
    {
        m_ListCtrl.GetWindowRect(listRc);
        ScreenToClient(listRc);
        m_ListCtrl.SetWindowPos(NULL, listRc.left, listRc.top, cx - listRc.left, cy - listRc.top * 2, SWP_DRAWFRAME);
    }

}


void CTestSysDlg::CatMemoryData()
{
    // 判断列表是否为空，如果为否，则删除列表内容
    if (m_ListCtrl.GetItemCount())
        m_ListCtrl.DeleteAllItems();
    static ULONG64 g_nPID = NULL;
    if (!m_pHandle || m_pid != g_nPID)
    {
        g_nPID = m_pid;
        m_pHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, static_cast<DWORD>(m_pid));
        //进程打开提权
        if (!grant_access(m_pHandle, PROCESS_ALL_ACCESS))
        {
            MessageBox(L"提权失败", L"提示：");
            m_pHandle = NULL;
        }
    }
    if(m_pHandle)
        PrintForReadMemory();
}

ULONG64 CTestSysDlg::getAddress()
{
    UpdateData();
    auto pAddr = _wcstoi64(m_pAddr, NULL, 16) + \
        _wcstoi64(m_pOffSet1, NULL, 16) + \
        _wcstoi64(m_pOffSet2, NULL, 16) + \
        _wcstoi64(m_pOffSet3, NULL, 16) + \
        _wcstoi64(m_pOffSet4, NULL, 16) + \
        _wcstoi64(m_pOffSet5, NULL, 16);

    return pAddr;
}


void CTestSysDlg::OnClose()
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CDialogEx::OnClose();
}


void CTestSysDlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    // TODO: 在此处添加消息处理程序代码
}


BOOL CTestSysDlg::DestroyWindow()
{
    // TODO: 在此添加专用代码和/或调用基类

    return CDialogEx::DestroyWindow();
}


BOOL CTestSysDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CDialogEx::PreTranslateMessage(pMsg);
}


LRESULT CTestSysDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CDialogEx::WindowProc(message, wParam, lParam);
}


void CTestSysDlg::OnIdok()
{
    // TODO: 在此添加命令处理程序代码
    m_ListCtrl.ChangedEdit();
}

void CTestSysDlg::PrintForReadMemory()
{
    auto pAddress = getAddress();

    CString data;
    reinterpret_cast<CEdit*>(GetDlgItem(IDC_CATNUM))->GetWindowTextW(data);
    auto nCount = _wtoi(data);

    for (int i = 0; i < nCount; i++)
    {
        data.Format(L"0x%I64X", pAddress + i);
        m_ListCtrl.InsertItem(i, data);
        for (int n = 1; n < m_ListCtrl.GetHeaderCtrl()->GetItemCount(); n++)
        {
            memset(buff, FILE_NULL, FILE_MAX);
            if (!ReadProcessMemory(m_pHandle, reinterpret_cast<PVOID64>(pAddress + i),
                reinterpret_cast<PVOID64>(buff), nType[n], NULL))
            {
                data.Format(L"%u", GetLastError());
                MessageBox(data, L"提示：");
            };
            switch (n)
            {
            case 1:
            {
                data.Format(L"%u", *(int*)buff);
                break;
            }
            case 2:
            {
                data.Format(L"%f", *(float*)buff);
                break;
            }
            case 3:
            {

                data.Format(L"%lf", *(double*)buff);
                break;
            }
            case 4:
            {
                data.Format(L"%S", buff);
                break;
            }
            case 5:
            {
                data.Format(L"%s", (wchar_t*)buff);
                break;
            }
            }
            m_ListCtrl.SetItemText(i, n, data);
        }
    }
}



void CTestSysDlg::OnBnClickedRefresh()
{
    // TODO: 在此添加控件通知处理程序代码
    if (SysComboBox.GetCount())
        SysComboBox.ResetContent();
    SysComboBox.GetProcessInfo();
}
