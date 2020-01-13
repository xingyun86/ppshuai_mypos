//Download by http://www.NewXing.com
#if !defined(AFX_SELECTDLG_H__2D048A8E_4A3D_4D9D_8843_8A11023A425B__INCLUDED_)
#define AFX_SELECTDLG_H__2D048A8E_4A3D_4D9D_8843_8A11023A425B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog

class CSelectDlg : public CDialog
{
// Construction
public:
	CSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectDlg)
	enum { IDD = IDD_DIALOG_SELECT };
	CListCtrl	m_oListsmateriel;
	CTreeCtrl	m_oTreesclass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeSclass(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListSelect(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSadd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ReadtoList(CString sql);
	void AddSubTree(CString ParTree, HTREEITEM hPartItem);
	void AddTree();
	CString sclassid;
	CString curtext;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDLG_H__2D048A8E_4A3D_4D9D_8843_8A11023A425B__INCLUDED_)
