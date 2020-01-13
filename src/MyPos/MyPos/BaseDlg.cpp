//Download by http://www.NewXing.com
// BaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "BaseDlg.h"
#include "MaterielDlg.h"
#include "ClassDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDlg dialog


CBaseDlg::CBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBaseDlg)
	DDX_Control(pDX, IDC_TAB_BASE, m_oTabBase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBaseDlg, CDialog)
	//{{AFX_MSG_MAP(CBaseDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseDlg message handlers

BOOL CBaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_oTabBase.AddPage("商品类别", &m_oClassdlg, IDD_DIALOG_CLASS);
	m_oTabBase.AddPage("商品资料", &m_oMaterieldlg, IDD_DIALOG_MATERIEL);
	m_oTabBase.AddPage("付款方式", &m_oPaymodedlg, IDD_DIALOG_PAYMODE);
	m_oTabBase.Show();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

