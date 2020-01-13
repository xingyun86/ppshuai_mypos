//Download by http://www.NewXing.com
#if !defined(AFX_CHECKDLG_H__308FEC04_0401_46B6_B7DB_78EB89ABB23A__INCLUDED_)
#define AFX_CHECKDLG_H__308FEC04_0401_46B6_B7DB_78EB89ABB23A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog

class CCheckDlg : public CDialog
{
// Construction
public:
	long GetPaymodeID(CString payname);
	CCheckDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckDlg)
	enum { IDD = IDD_DIALOG_CHECK };
	CEdit	m_oConsume;
	CEdit	m_oCdiscount;
	CEdit	m_oReceive;
	CEdit	m_oChange;
	CEdit	m_oTotalm;
	CComboBox	m_oCombopay;
	CListCtrl	m_oChecklist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCheckDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCheckok();
	afx_msg void OnChangeEditReceive();
	afx_msg void OnClickListChecklist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditCdiscount();
	afx_msg void OnButtonRf();
	afx_msg void OnButtonHang();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString GetClassName(long lclassid);
	long VerifyDicsount();
	void ReadtoList(CString sbillid);
	float fchange;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKDLG_H__308FEC04_0401_46B6_B7DB_78EB89ABB23A__INCLUDED_)
