//Download by http://www.NewXing.com
#if !defined(AFX_PAYMODEDLG_H__464504CB_0045_4D4C_8A62_1E5F1718D4EC__INCLUDED_)
#define AFX_PAYMODEDLG_H__464504CB_0045_4D4C_8A62_1E5F1718D4EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaymodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaymodeDlg dialog

class CPaymodeDlg : public CDialog
{
// Construction
public:
	CPaymodeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPaymodeDlg)
	enum { IDD = IDD_DIALOG_PAYMODE };
	CButton	m_oPadd2;
	CStatic	m_oShowhint;
	CListBox	m_oListpaymode;
	CEdit	m_oPaymode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaymodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPaymodeDlg)
	afx_msg void OnButtonPadd();
	afx_msg void OnButtonPdel();
	afx_msg void OnButtonPadd2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL bRepeat(CString strFieldValue);
	void ReadToListbox();
	long GenNewID();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAYMODEDLG_H__464504CB_0045_4D4C_8A62_1E5F1718D4EC__INCLUDED_)
