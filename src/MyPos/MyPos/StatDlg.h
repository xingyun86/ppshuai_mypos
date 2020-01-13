//Download by http://www.NewXing.com
#if !defined(AFX_STATDLG_H__0C051ED4_60E9_478A_9BFD_88BF649253E2__INCLUDED_)
#define AFX_STATDLG_H__0C051ED4_60E9_478A_9BFD_88BF649253E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatDlg dialog

class CStatDlg : public CDialog
{
// Construction
public:
	CString GetMaterielName(long materielid);
	void SumSingleItem(CString scondition);
	void SumBillTotal(CString scondition);
	CString Dateformat(CString sdate);
	CStatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatDlg)
	enum { IDD = IDD_DIALOG_STAT };
	CDateTimeCtrl	m_oSdate;
	CDateTimeCtrl	m_oOdate;
	CButton	m_oWeek;
	CEdit	m_oListtitle;
	CListBox	m_oListreport;
	CEdit	m_oSt;
	CEdit	m_oOt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatDlg)
	afx_msg void OnButtonStat();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPrintreport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATDLG_H__0C051ED4_60E9_478A_9BFD_88BF649253E2__INCLUDED_)
