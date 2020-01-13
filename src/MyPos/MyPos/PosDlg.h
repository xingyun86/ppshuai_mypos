//Download by http://www.NewXing.com
//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_POSDLG_H__A3C931E5_13ED_445A_AAFB_84A1B2FEE140__INCLUDED_)
#define AFX_POSDLG_H__A3C931E5_13ED_445A_AAFB_84A1B2FEE140__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PosDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPosDlg dialog
#define WM_APPLY WM_USER+1
#define WM_CHECKOUT WM_USER+2

class CPosDlg : public CDialog
{
// Construction
public:
	CBitmapButton m_BMButton3;
	CString GetCompanyFloor(BOOL bCompany);
	BOOL PrintListCtrl(CListCtrl &list);
	BOOL bGetBillStatus(CString sbillid);
	void ReadBillHead(CString sbillid);
	CString SumItemtotal(CString sbillid);
	long GetRecordCount(CString sql);
	void ReadToFormlist(CString billid);
	CString GetMaterielName(long materielid);
	long GetRowNo(CString sbillid);
	void AddItemToList();
	CPosDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPosDlg)
	enum { IDD = IDD_DIALOG_POS };
	CEdit	m_oActtotal;
	CEdit	m_oTotal;
	CButton	m_oButton;
	CListCtrl	m_oFormlist;
	CEdit	m_oBegintime;
	CEdit	m_oEndtime;
	CEdit	m_oCheck;
	CEdit	m_oStatus;
	CEdit	m_oPeasons;
	CEdit	m_oTableno;
	CListBox	m_oListbill;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPosDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPosDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddf();
	afx_msg void OnSelchangeListBill();
	afx_msg void OnButtonSelmateriel();
	afx_msg void OnDblclkListForm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonCallf();
	afx_msg void OnButtonDelf();
	afx_msg void OnButtonHidef();
	afx_msg void OnButtonCheckf();
	afx_msg void OnKillfocusEditTableno();
	afx_msg void OnKillfocusEditPeasons();
	afx_msg void OnButtonOff();
	afx_msg void OnButtonFindf();
	afx_msg void OnButtonLocalp();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);//Add a message map function OnMyMessage.
	afx_msg LRESULT OnMyCheckMessage(WPARAM wParam, LPARAM lParam);//Add a message map function OnMyMessage.
	DECLARE_MESSAGE_MAP()
private:
	CString GenNewBillID();
	CString send,spaymode;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSDLG_H__A3C931E5_13ED_445A_AAFB_84A1B2FEE140__INCLUDED_)
