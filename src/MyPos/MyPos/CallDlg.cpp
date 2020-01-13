// CallDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "MyPos.h"
#include "CallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCallDlg dialog
extern CMyPosApp theApp;


CCallDlg::CCallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCallDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCallDlg)
	DDX_Control(pDX, IDC_STATIC_CALL, m_oCallstatic);
	DDX_Control(pDX, IDC_EDIT_CALLBILLID, m_oCallbillid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCallDlg, CDialog)
	//{{AFX_MSG_MAP(CCallDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCallDlg message handlers

void CCallDlg::OnOK() 
{
	if(dowhat=="imhappy")
	{
		theApp.scallid="";
		m_oCallbillid.GetWindowText(theApp.scallid); 
	}
	if(dowhat=="pleased")
		m_oCallbillid.GetWindowText(dowhat); 

	CDialog::OnOK();
}


BOOL CCallDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(dowhat=="pleased")
		m_oCallstatic.SetWindowText("«Î ‰»Î◊¿∫≈£∫");
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
