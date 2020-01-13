//Download by http://www.NewXing.com
// CleardataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "CleardataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCleardataDlg dialog
extern CMyPosApp theApp;


CCleardataDlg::CCleardataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCleardataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCleardataDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCleardataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCleardataDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER_TO, m_oDateto);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FROM, m_oDatefrom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCleardataDlg, CDialog)
	//{{AFX_MSG_MAP(CCleardataDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCleardataDlg message handlers

void CCleardataDlg::OnButtonClear() 
{
	CString sfrom,sto,sdate1,sdate2,sbeginid,sendid,sql;
	_RecordsetPtr m_pRecordset;

	m_oDatefrom.GetWindowText(sfrom);
	sdate1=Dateformat(sfrom);
	sfrom.Format("%s 00:00:00",sdate1);
	m_oDateto.GetWindowText(sto);	
	sdate2=Dateformat(sto);
	sto.Format("%s 00:00:00",sdate2);

	sql="Select ID from SALEBILL where ENDDATE>='"+sfrom+"' and ENDDATE<='"+sto+"' and STATUS='已结帐'";
	if(AfxMessageBox("确定清除数据吗？",MB_YESNO)==IDYES)
	{
		try
		{ 	
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			if(!m_pRecordset->adoEOF)
			{
				m_pRecordset->MoveFirst();
				sbeginid=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ID");
				m_pRecordset->MoveLast();
				sendid=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ID");
			}
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("[清除数据]获得单据编号出错:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
		sql="Delete * from SALEBILL where ENDDATE>='"+sfrom+"' and ENDDATE<='"+sto+"' and STATUS='已结帐'";
		try
		{ 
			_variant_t RecordsAffected;
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);		
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("[清除数据]删除单据头:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}	

		if(sbeginid=="" || sendid=="")
			return;

		sql="Delete * from SALEDETAIL where BILLID>='"+sbeginid+"' and BILLID<='"+sendid+"'";
		try
		{ 
			_variant_t RecordsAffected;
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);		
			sql="Delete * from PAYDETAIL where BILLID>='"+sbeginid+"' and BILLID<='"+sendid+"'";
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);		
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("[清除数据]删除单据商品或付款明细出错:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}	
	}	

}

CString CCleardataDlg::Dateformat(CString sdate)
{
	if(sdate.GetLength()==8)
	{
		sdate.Insert(7,'0');
		sdate.Insert(5,'0');
	}
	if(sdate.GetLength()==9)
	{
		if(sdate.GetAt(6)=='-')
			sdate.Insert(5,'0');
		else
			sdate.Insert(8,'0');
	}
	return sdate;
}

BOOL CCleardataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
