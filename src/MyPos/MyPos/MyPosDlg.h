//Download by http://www.NewXing.com
// MyPosDlg.h : header file
//

#if !defined(AFX_MYPOSDLG_H__78028D48_EC88_4D30_879C_6FAF607BD0BC__INCLUDED_)
#define AFX_MYPOSDLG_H__78028D48_EC88_4D30_879C_6FAF607BD0BC__INCLUDED_

#include "TabSheet.h"
#include "BaseDlg.h"	// Added by ClassView
#include "PosDlg.h"
#include "StatDlg.h"
#include "SysmtDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyPosDlg dialog
#define WM_OFFDUTY WM_USER+3

class CMyPosDlg : public CDialog
{
// Construction
public:
	
	CMyPosDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyPosDlg)
	enum { IDD = IDD_MYPOS_DIALOG };
	CStatic	m_osUsername;
	CStatic	m_osCompany;
	CTabSheet	m_oTab1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPosDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyPosDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg LRESULT OnMyOffdutyMessage(WPARAM wParam, LPARAM lParam);//Add a message map function OnMyMessage.
	DECLARE_MESSAGE_MAP()
private:
	CBaseDlg m_oBasedlg;
	CPosDlg m_oPosdlg;
	CStatDlg m_oStatdlg;
	CSysmtDlg m_oSysmtdlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPOSDLG_H__78028D48_EC88_4D30_879C_6FAF607BD0BC__INCLUDED_)
