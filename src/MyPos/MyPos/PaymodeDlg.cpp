// PaymodeDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "MyPos.h"
#include "PaymodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaymodeDlg dialog
extern CMyPosApp theApp;

CPaymodeDlg::CPaymodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPaymodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaymodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPaymodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaymodeDlg)
	DDX_Control(pDX, IDC_BUTTON_PADD2, m_oPadd2);
	DDX_Control(pDX, IDC_STATIC_SHOWHINT, m_oShowhint);
	DDX_Control(pDX, IDC_LIST_PAYMODE, m_oListpaymode);
	DDX_Control(pDX, IDC_EDIT_PAYMODE, m_oPaymode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaymodeDlg, CDialog)
	//{{AFX_MSG_MAP(CPaymodeDlg)
	ON_BN_CLICKED(IDC_BUTTON_PADD, OnButtonPadd)
	ON_BN_CLICKED(IDC_BUTTON_PDEL, OnButtonPdel)
	ON_BN_CLICKED(IDC_BUTTON_PADD2, OnButtonPadd2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaymodeDlg message handlers

void CPaymodeDlg::OnButtonPadd() 
{
	m_oShowhint.ShowWindow(SW_SHOW);
	m_oPaymode.ShowWindow(SW_SHOW);
	m_oPadd2.ShowWindow(SW_SHOW);
}

void CPaymodeDlg::OnButtonPdel() 
{
	CString spaymode,sql;
	int iOption;
	_RecordsetPtr m_pRecordset;

	iOption = m_oListpaymode.GetCurSel();
	if(iOption>=0)
	{
		m_oListpaymode.GetText(iOption, spaymode);//得到选中项的文本
		if(spaymode=="人民币")
		{
			MessageBox("不能删除[人民币]付款方式!");
			return;
		}
		sql="Select * from PAYMODE where NAME='"+spaymode+"'";
		try
		{ 
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

			if(AfxMessageBox("确定要删除此付款方式吗？",MB_YESNO)==IDYES)
			{
				m_pRecordset->Delete(adAffectCurrent);///删除当前记录
				m_oListpaymode.DeleteString(iOption);
			}
			else
				return;	
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("删除付款方式出错:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}	
	}
}

long CPaymodeDlg::GenNewID()
{
	CString sql;
	long NewID;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT Max(ID) FROM PAYMODE";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		_variant_t vIndex = (long)0;//How to get field value in only 1 record and 1 field condition.
		_variant_t vtemp = m_pRecordset->GetCollect(vIndex);
		if(vtemp.lVal>0) 
			NewID =(long)(m_pRecordset->GetCollect(vIndex))+1;///取得第一个字段的值(MAX ID)加1后放入id变量.
		else	
			NewID=1;
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("获取付款方式ID最大值出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	if(NewID==88)
		NewID=89;

	return NewID;
}

void CPaymodeDlg::OnButtonPadd2() 
{
	CString spaymode,snewid,sql;
	long lnewid;
	_variant_t RecordsAffected;

	lnewid=GenNewID();
	snewid.Format("%d",lnewid);
	m_oPaymode.GetWindowText(spaymode);

	if(spaymode=="")
	{
		AfxMessageBox("请输入付款方式!");
		return;
	}

	if(bRepeat(spaymode))
	{
		AfxMessageBox("付款方式重复！请重新输入！");
		return;
	}

	sql="Insert into PAYMODE (ID,NAME) values("+snewid+",'"+spaymode+"')";
	try
	{ 
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
		m_oListpaymode.AddString(spaymode);
		UpdateData(FALSE);
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("增加付款方式出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
	m_oShowhint.ShowWindow(SW_HIDE);
	m_oPaymode.ShowWindow(SW_HIDE);	
	m_oPadd2.ShowWindow(SW_HIDE);
	m_oPaymode.SetWindowText("");
}

void CPaymodeDlg::ReadToListbox()
{
	int recordcount;
	_RecordsetPtr m_pRecordset;

	//Read paymode name from database into listbox.
	m_oListpaymode.ResetContent();
	CString sql="select * from PAYMODE";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		recordcount=m_pRecordset->GetRecordCount();//Get records total.		
		if(!m_pRecordset->adoEOF)
		{
			if(recordcount>0)
			{
			for (int i=0;i < recordcount;i++)//Read user name into listbox.
			{
				m_oListpaymode.AddString((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME"));
				sql=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME");
				m_pRecordset->MoveNext();
			}
			}
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("读取付款方式到列表框出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}	
}

BOOL CPaymodeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ReadToListbox();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPaymodeDlg::bRepeat(CString strFieldValue)
{
	CString sql;
	BOOL br;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT * FROM PAYMODE WHERE NAME='";
	sql=sql+strFieldValue+"'";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		if(m_pRecordset->adoEOF)
			br=FALSE;
		if(!m_pRecordset->adoEOF)
			br=TRUE;
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("查找付款方式名称出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
		return br;
}
