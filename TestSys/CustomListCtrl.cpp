// CustomListCtrl.cpp: 实现文件
//

#include "pch.h"
#include "TestSys.h"
#include "CustomListCtrl.h"


// CustomListCtrl

IMPLEMENT_DYNAMIC(CustomListCtrl, CListCtrl)

CustomListCtrl::CustomListCtrl():m_plvhti(new LVHITTESTINFO)
{
	
}

CustomListCtrl::~CustomListCtrl()
{
	delete m_plvhti;
}


BEGIN_MESSAGE_MAP(CustomListCtrl, CListCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CustomListCtrl 消息处理程序
void TestDemo(CustomListCtrl* This)
{
	This->InsertItem(0, L"111");
	This->SetItemText(0, 1, L"222");
	This->SetItemText(0, 2, L"222");
}



void CustomListCtrl::InitiativeCtrl()
{
	InsertColumn(0, L"地址", 0, 100);
	InsertColumn(1, L"4字节数据", 0, 100);
	InsertColumn(2, L"单浮点数", 0, 100);
	InsertColumn(3, L"双浮点数", 0, 100);
	InsertColumn(4, L"ANSI", 0, 100);
	InsertColumn(5, L"UNICODE", 0, 100);

	TestDemo(this);
	SetExtendedStyle(LVS_EX_BORDERSELECT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

}


void CustomListCtrl::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);
	auto nCount = GetHeaderCtrl()->GetItemCount();
	int nWidth = cx / nCount;
	for (int i = 0; i < nCount; i++)
	{
		SetColumnWidth(i, nWidth);
	}
	// TODO: 在此处添加消息处理程序代码
}


void CustomListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rc;
	
	if (int nRow = HitTest(point) != -1)
	{
		//填入双击位置坐标
		m_plvhti->pt = point;
		//该位置位于列表视图项的文本之上。
		m_plvhti->flags = LVHT_ONITEMLABEL;
		//获取双击位置的信息
		SubItemHitTest(m_plvhti);
		GetSubItemRect(m_plvhti->iItem, m_plvhti->iSubItem, LVIR_LABEL, rc);
        m_Edit.Create(WS_CHILD | WS_VISIBLE | ES_LEFT | WS_BORDER, rc, this, IDC_EDITCHANG);
		m_Edit.SetWindowTextW(m_Text = GetItemText(m_plvhti->iItem, m_plvhti->iSubItem));
		m_Edit.SetFocus();
		m_Edit.SetSel(0, -1);
	}
	CListCtrl::OnLButtonDblClk(nFlags, point);
}


void CustomListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_Edit.GetSafeHwnd())
	{
		m_Edit.DestroyWindow();
	}
	CListCtrl::OnLButtonDown(nFlags, point);
}

void CustomListCtrl::ChangedEdit()
{
	if (!m_Edit.GetSafeHwnd())
		return;
	CString Title;
	m_Edit.GetWindowTextW(Title);
	if (m_Text.Compare(Title))
	{
        if (IDCANCEL != MessageBox(L"确定修改？", L"提示：", MB_OKCANCEL | MB_ICONWARNING))
            SetItemText(m_plvhti->iItem, m_plvhti->iSubItem, Title);
	}
	m_Edit.DestroyWindow();
}


