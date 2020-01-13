//Download by http://www.NewXing.com
#if !defined(AFX_MODIFYQADLG_H__C70DA795_B42C_4503_BCD7_34120BF48608__INCLUDED_)
#define AFX_MODIFYQADLG_H__C70DA795_B42C_4503_BCD7_34120BF48608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyqaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyqaDlg dialog

class CModifyqaDlg : public CDialog
{
// Construction
public:
	CModifyqaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyqaDlg)
	enum { IDD = IDD_DIALOG_MODIFYQA };
	CEdit	m_oModifyqa;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyqaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyqaDlg)
	afx_msg void OnMok();
	afx_msg void OnMcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYQADLG_H__C70DA795_B42C_4503_BCD7_34120BF48608__INCLUDED_)
