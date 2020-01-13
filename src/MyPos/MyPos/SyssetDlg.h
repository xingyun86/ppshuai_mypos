//Download by http://www.NewXing.com
#if !defined(AFX_SYSSETDLG_H__084B4C22_3977_4DF0_ACB4_B36F320ABF6E__INCLUDED_)
#define AFX_SYSSETDLG_H__084B4C22_3977_4DF0_ACB4_B36F320ABF6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SyssetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSyssetDlg dialog

class CSyssetDlg : public CDialog
{
// Construction
public:
	CSyssetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSyssetDlg)
	enum { IDD = IDD_DIALOG_SYSSET };
	CEdit	m_oFloornumber;
	CEdit	m_oResname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSyssetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSyssetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSaveset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString GetCompanyname();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSSETDLG_H__084B4C22_3977_4DF0_ACB4_B36F320ABF6E__INCLUDED_)
