#pragma once


// CustomListCtrl

class CustomListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CustomListCtrl)

public:
	CustomListCtrl();
	virtual ~CustomListCtrl();

protected:
	DECLARE_MESSAGE_MAP()

	CEdit m_Edit;
	CString m_Text;
	//获取编辑框的位置和大小
	LPLVHITTESTINFO m_plvhti;
public:
	//获取控件CRect Info
	CRect GetCtrlRect();
	/*
	初始化控件
	*/
	void InitiativeCtrl();
	/*
	控件大小改变调用
	*/
	afx_msg void OnSize(UINT nType, int cx, int cy);
	/*
	鼠标左键双击产生编辑框
	*/
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	/*
	鼠标左键单击控件
	*/
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/*
	编辑框内容改变，确定是否更改列表控件数值。
	*/
	afx_msg void ChangedEdit();
};


