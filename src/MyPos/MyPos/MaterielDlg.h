//Download by http://www.NewXing.com
#if !defined(AFX_MATERIELDLG_H__0472BC22_5CB9_4B83_8D46_BA22D0BEDD68__INCLUDED_)
#define AFX_MATERIELDLG_H__0472BC22_5CB9_4B83_8D46_BA22D0BEDD68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MaterielDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaterielDlg dialog

class CMaterielDlg : public CDialog
{
// Construction
public:
	CMaterielDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMaterielDlg)
	enum { IDD = IDD_DIALOG_MATERIEL };
	CListCtrl	m_oListmateriel;
	CTreeCtrl	m_oMclass;
	CButton	m_oSupply;
	CEdit	m_oMshopcode;
	CEdit	m_oMprice;
	CEdit	m_oMname;
	CEdit	m_oMbarcode;
	CComboBox	m_oMdiscount;
	CString	m_mname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaterielDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMaterielDlg)
	afx_msg void OnButtonMsave();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonMadd();
	afx_msg void OnButtonMdel();
	afx_msg void OnSelchangedTreeMclass(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListMateriel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL bRepeat(CString strFieldValue);
	void ReadtoList(CString sql);
	long GenNewID();
	void AddSubTree(CString ParTree, HTREEITEM hPartItem);
	void AddTree();
	CString curtext;
	CString sclassid;
	long lclassid;
	long lNewID;
	long lMID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATERIELDLG_H__0472BC22_5CB9_4B83_8D46_BA22D0BEDD68__INCLUDED_)
