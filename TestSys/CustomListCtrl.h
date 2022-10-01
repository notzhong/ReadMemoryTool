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
	LPLVHITTESTINFO m_plvhti;
public:
	void InitiativeCtrl();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void ChangedEdit();
};


