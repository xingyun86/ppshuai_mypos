//Download by http://www.NewXing.com
#if !defined(AFX_OFFDUTYDLG_H__63B05568_3286_4A99_A417_583F7D893A94__INCLUDED_)
#define AFX_OFFDUTYDLG_H__63B05568_3286_4A99_A417_583F7D893A94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OffdutyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COffdutyDlg dialog

class COffdutyDlg : public CDialog
{
// Construction
public:
	CString YearMonthDay(CString y,CString m,CString d);
	COffdutyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COffdutyDlg)
	enum { IDD = IDD_DIALOG_OFFDUTY };
	CEdit	m_oOffrfmoney;
	CEdit	m_oOffrf;
	CListBox	m_oHanglist;
	CListBox	m_oNonchecklist;
	CListBox	m_oMoneylist;
	CEdit	m_oOffbills;
	CEdit	m_oOfftime;
	CEdit	m_oOffpeoples;
	CEdit	m_oCheckman;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COffdutyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COffdutyDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOffprint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OFFDUTYDLG_H__63B05568_3286_4A99_A417_583F7D893A94__INCLUDED_)
