//Download by http://www.NewXing.com
#if !defined(AFX_LOGONDLG_H__F938E928_602B_49F3_80BF_84849EE05614__INCLUDED_)
#define AFX_LOGONDLG_H__F938E928_602B_49F3_80BF_84849EE05614__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogonDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogonDlg dialog

class CLogonDlg : public CDialog
{
// Construction
public:
	CBitmapButton m_BMButton2;
	CBitmapButton m_BMButton1;
//	CBitmapButton m_BMButton1;
	CLogonDlg(CWnd* pParent = NULL);   // standard constructor
	_RecordsetPtr m_pRecordset;
// Dialog Data
	//{{AFX_DATA(CLogonDlg)
	enum { IDD = IDD_DIALOG_LOGON };
	CComboBox	m_oLogon;
	CString	m_pwd;
	CString	m_logid;
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogonDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGONDLG_H__F938E928_602B_49F3_80BF_84849EE05614__INCLUDED_)
