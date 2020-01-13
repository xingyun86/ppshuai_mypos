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
		AfxMessageBox("�������û��������룡");	
		return;
	}
	else//if user enter name and password.
	{
		//����sql���
//		m_pwd=theApp.addpwd(m_pwd,true);//Unencrypt the password.
		CString sql="SELECT * FROM USERS where LOGINID='"+m_logid+"' and PSD='"+m_pwd+"'";
		try
		{
			//��ѯ���ݿ⣬���Ƿ��д��û�������
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			//���û�д��û������룬�ٲ�ѯ�Ƿ��д��û�
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
						AfxMessageBox("�û������������");

//						if(AfxMessageBox("�û������������!�����½����û���",MB_YESNO)==IDYES)
//						{
//							m_pRecordset->Close();
//							sql="insert into USERS (ID,NAME,LOGINID,PSD) values('"+m_logid+"','"+m_logid+"','"+m_logid+"','"+m_pwd+"')";
//							_variant_t RecordsAffected;
//							theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
//							AfxMessageBox("���û��ɹ����������ס��\n\n�û�����"+m_logid+"\n��  �룺"+theApp.addpwd(m_pwd,false));
//							theApp.name=m_logid;
//							theApp.pwd=m_pwd;
//							CDialog::OnOK();						
//						}
//						else
//							return;										
//					}
					//����У���ʾ������Ϣ��
//					else
//					{
//						AfxMessageBox("�û������������");
//						return;
//					}
//				}
//				catch(_com_error e)///��׽�쳣
//				{
//					CString temp;
//					temp.Format("��ȡ�û������������:%s",e.ErrorMessage());
//					AfxMessageBox(temp);
//					return;
//				}
//			}
			//�û�����������ڣ���¼�ɹ�
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
		catch(_com_error e)///��׽�쳣
		{
			CString temp;
			temp.Format("��ȡ�û������������:%s",e.ErrorMessage());
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

  	//�������ݿ��е��û�������ʾ�ڿؼ��С�
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
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("��ȡ�û�������:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return false;
	}	
	m_BMButton1.AutoLoad(IDOK,this);
	m_BMButton2.AutoLoad(IDCANCEL,this);
	return TRUE;  // return TRUE unless you set the focus to a control
// EXCEPTION: OCX Property Pages should return FALSE

//	m_BMButton1.AutoLoad(IDOK,this);
}
