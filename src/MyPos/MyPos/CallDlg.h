//Download by http://www.NewXing.com
#if !defined(AFX_CALLDLG_H__C3BF65AB_83F1_4028_991B_05830CC5BD45__INCLUDED_)
#define AFX_CALLDLG_H__C3BF65AB_83F1_4028_991B_05830CC5BD45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CallDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCallDlg dialog

class CCallDlg : public CDialog
{
// Construction
public:
	CString dowhat;
	CCallDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCallDlg)
	enum { IDD = IDD_DIALOG_CALL };
	CStatic	m_oCallstatic;
	CEdit	m_oCallbillid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCallDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALLDLG_H__C3BF65AB_83F1_4028_991B_05830CC5BD45__INCLUDED_)
