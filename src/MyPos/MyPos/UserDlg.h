//Download by http://www.NewXing.com
#if !defined(AFX_USERDLG_H__09A5B039_763B_49C4_87D8_64A8EF94CC5A__INCLUDED_)
#define AFX_USERDLG_H__09A5B039_763B_49C4_87D8_64A8EF94CC5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	CUserDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_DIALOG_USER };
	CButton	m_oCheck1;
	CButton	m_oCheck2;
	CButton	m_oCheck3;
	CButton	m_oCheck4;
	CButton	m_oCheck5;
	CButton	m_oCheck6;
	CButton	m_oCheck7;
	CButton	m_oCheck8;
	CButton	m_oCheck9;
	CEdit	m_oUserid;
	CEdit	m_oDiscount;
	CEdit	m_oNumber;
	CEdit	m_oLogname;
	CEdit	m_oJiguan;
	CEdit	m_oDuty;
	CEdit	m_oDatebirth;
	CEdit	m_oPwd;
	CEdit	m_oUsername;
	CComboBox	m_oSex;
	CListBox	m_oListuser;
	CString	m_Listuser;
	CString	m_datebirth;
	CString	m_duty;
	CString	m_jiguan;
	CString	m_logname;
	CString	m_username;
	CString	m_number;
	CString	m_upwd;
	CString	m_sex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUadd();
	afx_msg void OnButtonUdel();
	afx_msg void OnButtonUsave();
	afx_msg void OnSelchangeListUser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ReadToListbox();
	BOOL bRepeat(CString strFieldValue);
	long GenNewID();
	long lNewID;
	CString suserid;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__09A5B039_763B_49C4_87D8_64A8EF94CC5A__INCLUDED_)
