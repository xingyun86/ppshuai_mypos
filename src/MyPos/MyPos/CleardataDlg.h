//Download by http://www.NewXing.com
#if !defined(AFX_CLEARDATADLG_H__081BB449_75A2_4092_98C0_EB64FB15508A__INCLUDED_)
#define AFX_CLEARDATADLG_H__081BB449_75A2_4092_98C0_EB64FB15508A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CleardataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCleardataDlg dialog

class CCleardataDlg : public CDialog
{
// Construction
public:
	CCleardataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCleardataDlg)
	enum { IDD = IDD_DIALOG_CLEAR };
	CDateTimeCtrl	m_oDateto;
	CDateTimeCtrl	m_oDatefrom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCleardataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString Dateformat(CString sdate);

	// Generated message map functions
	//{{AFX_MSG(CCleardataDlg)
	afx_msg void OnButtonClear();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEARDATADLG_H__081BB449_75A2_4092_98C0_EB64FB15508A__INCLUDED_)
