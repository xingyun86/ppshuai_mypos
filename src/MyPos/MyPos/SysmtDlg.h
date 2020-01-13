//Download by http://www.NewXing.com
#if !defined(AFX_SYSMTDLG_H__70370091_6483_43B6_A631_660C741D4C0A__INCLUDED_)
#define AFX_SYSMTDLG_H__70370091_6483_43B6_A631_660C741D4C0A__INCLUDED_

#include "TabSheet.h"
#include "UserDlg.h"
#include "SyssetDlg.h"
#include "CleardataDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysmtDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysmtDlg dialog

class CSysmtDlg : public CDialog
{
// Construction
public:
	CSysmtDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysmtDlg)
	enum { IDD = IDD_DIALOG_SYSMT };
	CTabSheet	m_oTabSys;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysmtDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSysmtDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CUserDlg m_oUserdlg;
	CSyssetDlg m_oSyssetdlg;
	CCleardataDlg m_oCleardlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSMTDLG_H__70370091_6483_43B6_A631_660C741D4C0A__INCLUDED_)
