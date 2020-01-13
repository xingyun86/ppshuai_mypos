//Download by http://www.NewXing.com
// ModifyqaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "ModifyqaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyqaDlg dialog
extern CMyPosApp theApp;


CModifyqaDlg::CModifyqaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyqaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyqaDlg)
	//}}AFX_DATA_INIT
}


void CModifyqaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyqaDlg)
	DDX_Control(pDX, IDC_EDIT_MODIFYQA, m_oModifyqa);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyqaDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyqaDlg)
	ON_BN_CLICKED(ID_MOK, OnMok)
	ON_BN_CLICKED(ID_MCANCEL, OnMcancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyqaDlg message handlers

void CModifyqaDlg::OnMok() 
{
	m_oModifyqa.GetWindowText(theApp.sqa);
	CDialog::OnOK();	
}

void CModifyqaDlg::OnMcancel() 
{
	CDialog::OnCancel();	
}
