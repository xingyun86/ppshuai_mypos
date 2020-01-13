//Download by http://www.NewXing.com
// SysmtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "SysmtDlg.h"
#include "SyssetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysmtDlg dialog
extern CMyPosApp theApp;


CSysmtDlg::CSysmtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysmtDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysmtDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSysmtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysmtDlg)
	DDX_Control(pDX, IDC_TAB_SYSMT, m_oTabSys);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysmtDlg, CDialog)
	//{{AFX_MSG_MAP(CSysmtDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysmtDlg message handlers

BOOL CSysmtDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_oTabSys.AddPage("用户资料", &m_oUserdlg, IDD_DIALOG_USER);
	m_oTabSys.AddPage("系统设置", &m_oSyssetdlg, IDD_DIALOG_SYSSET);
	if(theApp.VerifyPower("Deldata"))
		m_oTabSys.AddPage("清除数据", &m_oCleardlg, IDD_DIALOG_CLEAR);
	m_oTabSys.Show();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
