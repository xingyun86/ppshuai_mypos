//Download by http://www.NewXing.com
#if !defined(AFX_CLASSDLG_H__B6736001_C0BF_47D8_8A7A_A2540CC35379__INCLUDED_)
#define AFX_CLASSDLG_H__B6736001_C0BF_47D8_8A7A_A2540CC35379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClassDlg dialog

class CClassDlg : public CDialog
{
// Construction
public:
	int CountMateriel(CString sclassid);
	CClassDlg(CWnd* pParent = NULL);   // standard constructor
	static CString VariantToCString(VARIANT var);
	static int TreeSumRecordCount(CString strFieldValue);

// Dialog Data
	//{{AFX_DATA(CClassDlg)
	enum { IDD = IDD_DIALOG_CLASS };
	CButton	m_oRadiodiscount;
	CEdit	m_oClassname;
	CTreeCtrl	m_oTreeclass;
	CString	m_classname;
	int		m_radiodiscount;
	long	m_tempid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClassDlg)
	afx_msg void OnSelchangedTreeClass(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddsame();
	afx_msg void OnButtonAddsub();
	afx_msg void OnButtonDel();
	afx_msg void OnButtonSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GenNewID();//Generate a new record ID.
	void AddSubTree(CString ParTree, HTREEITEM hPartItem);
	void AddTree();
	BOOL bRepeat(CString strFieldValue);
	HTREEITEM hCurrentItem,hParentItem;
	CString Curpar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASSDLG_H__B6736001_C0BF_47D8_8A7A_A2540CC35379__INCLUDED_)
