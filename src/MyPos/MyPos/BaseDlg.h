//Download by http://www.NewXing.com
#if !defined(AFX_BASEDLG_H__3BB3B513_1A8C_4AC8_B579_D486066977B7__INCLUDED_)
#define AFX_BASEDLG_H__3BB3B513_1A8C_4AC8_B579_D486066977B7__INCLUDED_

#include "ClassDlg.h"	// Added by ClassView
#include "TabSheet.h"
#include "MaterielDlg.h"
#include "PaymodeDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BaseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBaseDlg dialog
extern CMyPosApp theApp;

class CBaseDlg : public CDialog
{
// Construction
public:
	CBaseDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CBaseDlg)
	enum { IDD = IDD_DIALOG_BASE };
	CTabSheet	m_oTabBase;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBaseDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CClassDlg m_oClassdlg;
	CMaterielDlg m_oMaterieldlg;
	CPaymodeDlg m_oPaymodedlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEDLG_H__3BB3B513_1A8C_4AC8_B579_D486066977B7__INCLUDED_)
