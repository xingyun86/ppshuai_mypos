//Download by http://www.NewXing.com
// LogonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "LogonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogonDlg dialog
extern CMyPosApp theApp;


CLogonDlg::CLogonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogonDlg)
	m_pwd = _T("");
	m_logid = _T("");
	//}}AFX_DATA_INIT
}


void CLogonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogonDlg)
	DDX_Control(pDX, IDC_COMBO_LOGON, m_oLogon);
	DDX_Text(pDX, IDC_EDIT_LOGPWD, m_pwd);
	DDX_CBString(pDX, IDC_COMBO_LOGON, m_logid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogonDlg, CDialog)
	//{{AFX_MSG_MAP(CLogonDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogonDlg message handlers

void CLogonDlg::OnOK() 
{  
	// TODO: Add extra validation here
	UpdateData();
	if(m_logid.IsEmpty()||m_pwd.IsEmpty())
	{	
		AfxMessageBox("请输入用户名和密码！");	
		return;
	}
	else//if user enter name and password.
	{
		//成生sql语句
//		m_pwd=theApp.addpwd(m_pwd,true);//Unencrypt the password.
		CString sql="SELECT * FROM USERS where LOGINID='"+m_logid+"' and PSD='"+m_pwd+"'";
		try
		{
			//查询数据库，看是否有此用户和密码
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			//如果没有此用户和密码，再查询是否有此用户
			if(m_pRecordset->adoEOF)
//			{
//				m_pRecordset->Close();
//				sql="select LOGINID from USERS where LOGINID='"+m_logid+"'";
//				try
//				{
//					m_pRecordset.CreateInstance("ADODB.Recordset");
//					m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

//					if(m_pRecordset->adoEOF)
//					{
						AfxMessageBox("用户名或密码错误！");

//						if(AfxMessageBox("用户名或密码错误!你想新建此用户吗？",MB_YESNO)==IDYES)
//						{
//							m_pRecordset->Close();
//							sql="insert into USERS (ID,NAME,LOGINID,PSD) values('"+m_logid+"','"+m_logid+"','"+m_logid+"','"+m_pwd+"')";
//							_variant_t RecordsAffected;
//							theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
//							AfxMessageBox("新用户成功建立！请记住：\n\n用户名："+m_logid+"\n密  码："+theApp.addpwd(m_pwd,false));
//							theApp.name=m_logid;
//							theApp.pwd=m_pwd;
//							CDialog::OnOK();						
//						}
//						else
//							return;										
//					}
					//如果有，提示错误信息。
//					else
//					{
//						AfxMessageBox("用户名或密码错误！");
//						return;
//					}
//				}
//				catch(_com_error e)///捕捉异常
//				{
//					CString temp;
//					temp.Format("读取用户名和密码错误:%s",e.ErrorMessage());
//					AfxMessageBox(temp);
//					return;
//				}
//			}
			//用户名和密码存在，登录成功
			else
			{
//				theApp.name=m_logid;
				theApp.name=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME");
				theApp.pwd=m_pwd;
				CDialog::OnOK();
				return;
			}
			m_pRecordset->Close();
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("读取用户名和密码错误:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
	}
}

void CLogonDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

BOOL CLogonDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

  	//读出数据库中的用户名，显示在控件中。
	int i,recordcount;
	CString sql="select LOGINID from USERS order by LOGINID";

	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		recordcount=m_pRecordset->GetRecordCount();//Get records total.	

		if(!m_pRecordset->adoEOF)
		{
			for(i=0;i<recordcount;i++)
			{
			m_oLogon.AddString((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("LOGINID"));
			sql=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("LOGINID");
			m_pRecordset->MoveNext();
			}
		}

		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("读取用户名错误:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return false;
	}	
	m_BMButton1.AutoLoad(IDOK,this);
	m_BMButton2.AutoLoad(IDCANCEL,this);
	return TRUE;  // return TRUE unless you set the focus to a control
// EXCEPTION: OCX Property Pages should return FALSE

//	m_BMButton1.AutoLoad(IDOK,this);
}
