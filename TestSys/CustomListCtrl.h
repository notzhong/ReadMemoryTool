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
	//��ȡ�༭���λ�úʹ�С
	LPLVHITTESTINFO m_plvhti;
public:
	//��ȡ�ؼ�CRect Info
	CRect GetCtrlRect();
	/*
	��ʼ���ؼ�
	*/
	void InitiativeCtrl();
	/*
	�ؼ���С�ı����
	*/
	afx_msg void OnSize(UINT nType, int cx, int cy);
	/*
	������˫�������༭��
	*/
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	/*
	�����������ؼ�
	*/
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/*
	�༭�����ݸı䣬ȷ���Ƿ�����б�ؼ���ֵ��
	*/
	afx_msg void ChangedEdit();
};


