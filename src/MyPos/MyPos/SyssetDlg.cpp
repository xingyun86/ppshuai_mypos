// SyssetDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "MyPos.h"
#include "SyssetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSyssetDlg dialog
extern CMyPosApp theApp;


CSyssetDlg::CSyssetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSyssetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSyssetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSyssetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSyssetDlg)
	DDX_Control(pDX, IDC_EDIT_FLOORNUMBER, m_oFloornumber);
	DDX_Control(pDX, IDC_EDIT_RESNAME, m_oResname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSyssetDlg, CDialog)
	//{{AFX_MSG_MAP(CSyssetDlg)
	ON_BN_CLICKED(IDC_BUTTON_SAVESET, OnButtonSaveset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyssetDlg message handlers

BOOL CSyssetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString sname,snumber,stemp;
	int nPosition,length;
	
	stemp=GetCompanyname();
	length=stemp.GetLength();
	nPosition=stemp.Find("&");
	
	sname=stemp.Left(nPosition);
	m_oResname.SetWindowText(sname);
	snumber=stemp.Right(length-nPosition-1);
	m_oFloornumber.SetWindowText(snumber);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSyssetDlg::OnButtonSaveset() 
{
	CString sname,snumber;
	CString sql;

	m_oFloornumber.GetWindowText(snumber);
	m_oResname.GetWindowText(sname);
	if(snumber==""||sname=="")
	{
		AfxMessageBox("Please materiel companyname,floornumber！");
		return;
	}

	sql="Insert into COMPANY (COMPANYNAME,FLOORNUMBER) values ('"+sname+"','"+snumber+"')";
	if(GetCompanyname()!="&")
		sql="Update COMPANY set COMPANYNAME='"+sname+"',FLOORNUMBER='"+snumber+"'";
	try
	{	_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("保存公司名称出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}	
}

CString CSyssetDlg::GetCompanyname()
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql="select * from COMPANY";
	CString sname,snumber;
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)
		{
			sname=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("COMPANYNAME");
			snumber=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("FLOORNUMBER");
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("读取公司名称出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	return sname+"&"+snumber;	
}
