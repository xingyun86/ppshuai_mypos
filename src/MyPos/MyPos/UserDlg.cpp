//Download by http://www.NewXing.com
// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog
extern CMyPosApp theApp;

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
	m_Listuser = _T("");
	m_datebirth = _T("");
	m_duty = _T("");
	m_jiguan = _T("");
	m_logname = _T("");
	m_username = _T("");
	m_number = _T("");
	m_upwd = _T("");
	m_sex = _T("");
	//}}AFX_DATA_INIT
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_CHECK1, m_oCheck1);
	DDX_Control(pDX, IDC_CHECK2, m_oCheck2);
	DDX_Control(pDX, IDC_CHECK3, m_oCheck3);
	DDX_Control(pDX, IDC_CHECK4, m_oCheck4);
	DDX_Control(pDX, IDC_CHECK5, m_oCheck5);
	DDX_Control(pDX, IDC_CHECK6, m_oCheck6);
	DDX_Control(pDX, IDC_CHECK7, m_oCheck7);
	DDX_Control(pDX, IDC_CHECK8, m_oCheck8);
	DDX_Control(pDX, IDC_CHECK9, m_oCheck9);
	DDX_Control(pDX, IDC_EDIT_USERID, m_oUserid);
	DDX_Control(pDX, IDC_EDIT_DISCOUNT, m_oDiscount);
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_oNumber);
	DDX_Control(pDX, IDC_EDIT_LOGNAME, m_oLogname);
	DDX_Control(pDX, IDC_EDIT_JIGUAN, m_oJiguan);
	DDX_Control(pDX, IDC_EDIT_DUTY, m_oDuty);
	DDX_Control(pDX, IDC_EDIT_DATEBIRTH, m_oDatebirth);
	DDX_Control(pDX, IDC_EDIT_PWD, m_oPwd);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_oUsername);
	DDX_Control(pDX, IDC_COMBO_SEX, m_oSex);
	DDX_Control(pDX, IDC_LIST_USER, m_oListuser);
	DDX_LBString(pDX, IDC_LIST_USER, m_Listuser);
	DDX_Text(pDX, IDC_EDIT_DATEBIRTH, m_datebirth);
	DDX_Text(pDX, IDC_EDIT_DUTY, m_duty);
	DDX_Text(pDX, IDC_EDIT_JIGUAN, m_jiguan);
	DDX_Text(pDX, IDC_EDIT_LOGNAME, m_logname);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_number);
	DDX_Text(pDX, IDC_EDIT_PWD, m_upwd);
	DDX_CBString(pDX, IDC_COMBO_SEX, m_sex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(IDC_BUTTON_UADD, OnButtonUadd)
	ON_BN_CLICKED(IDC_BUTTON_UDEL, OnButtonUdel)
	ON_BN_CLICKED(IDC_BUTTON_USAVE, OnButtonUsave)
	ON_LBN_SELCHANGE(IDC_LIST_USER, OnSelchangeListUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ReadToListbox();

	m_oListuser.SelectString(-1, theApp.name);//设置选中项
	OnSelchangeListUser();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDlg::OnButtonUadd() 
{
	//Clear the edit and combobox content.
	m_oDatebirth.SetWindowText("");
	m_oDuty.SetWindowText("");
	m_oJiguan.SetWindowText("");
	m_oLogname.SetWindowText("");
	m_oUsername.SetWindowText("");
	m_oNumber.SetWindowText("");
	m_oPwd.SetWindowText("");	
	m_oDiscount.SetWindowText("");
	m_oSex.SetCurSel(0);
	m_oCheck1.SetCheck(0);
	m_oCheck2.SetCheck(0);
	m_oCheck3.SetCheck(0);
	m_oCheck4.SetCheck(0);
	m_oCheck5.SetCheck(0);
	m_oCheck6.SetCheck(0);
	m_oCheck7.SetCheck(0);
	m_oCheck8.SetCheck(0);
	m_oCheck9.SetCheck(0);

	lNewID=GenNewID();
//	m_oListuser.SetCurSel(-1);
}

void CUserDlg::OnButtonUdel() 
{
	CString sql, stemp;
	int iOption;
	_RecordsetPtr m_pRecordset;

	iOption = m_oListuser.GetCurSel();
	if(iOption>=0)
	{
	m_oListuser.GetText(iOption, stemp);//得到选中项的文本

	sql="select * from USERS where NAME='"+stemp+"'";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		
		if(AfxMessageBox("要删除此用户吗？",MB_YESNO)==IDYES)
		{
			CString slogid=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("LOGINID");
			if(slogid=="Admin")
			{
				MessageBox("不能删除系统管理员！");
				return;
			}
			m_pRecordset->Delete(adAffectCurrent);///删除当前记录
			m_oListuser.DeleteString(iOption);
			OnButtonUadd();//Clear the edit text.
		}
		else
			return;				
		m_pRecordset->Update();   
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("删除用户出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
	}
}

void CUserDlg::OnButtonUsave() 
{
	CString sql="select * from USERS";
	CString temp,snewid,spower;
	CString name,sdiscount;
	_RecordsetPtr m_pRecordset;

	UpdateData();

	//检查数据完整性
	if(m_username.IsEmpty()||m_logname.IsEmpty()||m_upwd.IsEmpty())
	{
		AfxMessageBox("请输入姓名、登录名称和密码！");
		return;
	}
	m_oUsername.GetWindowText(name);//Get the current text in edit.

	if(AfxMessageBox("保存修改吗？",MB_YESNO)==IDYES)
	{
		int sex=m_oSex.GetCurSel();
		if(sex==0) m_sex="0";
		if(sex==1) m_sex="1";

		m_oDiscount.GetWindowText(sdiscount);

		if(m_oCheck1.GetCheck()==1)
			spower="[Basedoc]";
		if(m_oCheck2.GetCheck()==1)
			spower=spower+"[Stat]";
		if(m_oCheck3.GetCheck()==1)
			spower=spower+"[Sysmain]";
		if(m_oCheck4.GetCheck()==1)
			spower=spower+"[RF]";
		if(m_oCheck5.GetCheck()==1)
			spower=spower+"[DelBill]";
		if(m_oCheck6.GetCheck()==1)
			spower=spower+"[CallBill]";
		if(m_oCheck7.GetCheck()==1)
			spower=spower+"[Deldata]";
		if(m_oCheck8.GetCheck()==1)
			spower=spower+"[Hang]";
		if(m_oCheck9.GetCheck()==1)
			spower=spower+"[Recheck]";

		if(lNewID>atol(suserid))
		{
			snewid.Format("%d",lNewID);
			if(bRepeat(name)==TRUE)
			{
				AfxMessageBox("用户名重复，请重新输入!");
				return;
			}	
			try
			{ 
				m_pRecordset.CreateInstance("ADODB.Recordset");
				m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		  		m_pRecordset->AddNew();//insert the current into database.			
				m_pRecordset->PutCollect("ID",_variant_t(snewid));
				m_pRecordset->PutCollect("NAME",_variant_t(m_username));
				m_pRecordset->PutCollect("LOGINID",_variant_t(m_logname));
				m_pRecordset->PutCollect("PSD",_variant_t(m_upwd));
				m_pRecordset->PutCollect("TITLE",_variant_t(m_duty));
				m_pRecordset->PutCollect("SEX",_variant_t(m_sex));
				m_pRecordset->PutCollect("DATEBIRTH",_variant_t(m_datebirth));
				m_pRecordset->PutCollect("HOME",_variant_t(m_jiguan));
				m_pRecordset->PutCollect("EMPLOYNUMBER",_variant_t(m_number));
				m_pRecordset->PutCollect("DISCOUNT",_variant_t(sdiscount));
				m_pRecordset->PutCollect("POWER",_variant_t(spower));

				m_pRecordset->Update();//保存到库中    

				m_oListuser.AddString(m_username);
				m_oListuser.SelectString(-1,m_username);

				m_pRecordset->Close();
				UpdateData(FALSE);
			}
			catch(_com_error e)///捕捉异常
			{
				CString temp;
				temp.Format("保存用户资料出错:%s",e.ErrorMessage());
				AfxMessageBox(temp);
				return;
			}
		}
		else
		{
			_variant_t RecordsAffected;
			if(sdiscount=="")
				sdiscount="0";
			sql="Update USERS set NAME='"+m_username+
				"',LOGINID='"+m_logname+
				"',PSD='"+m_upwd+
				"',TITLE='"+m_duty+
				"',SEX='"+m_sex+
				"',DATEBIRTH='"+m_datebirth+
				"',HOME='"+m_jiguan+ 
				"',EMPLOYNUMBER='"+m_number+
				"',DISCOUNT="+sdiscount+
				",POWER='"+spower+"' where ID="+suserid+"";
			try
			{ 
				theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
				ReadToListbox();
				UpdateData(FALSE);
			}
			catch(_com_error e)///捕捉异常
			{
				CString temp;
				temp.Format("修改用户资料出错:%s",e.ErrorMessage());
				AfxMessageBox(temp);
				return;
			}
		}
	}
}




void CUserDlg::OnSelchangeListUser() //Read selected user info into controls.
{
	CString stemp,sql,sex,spower;
	int iOption; 
	_RecordsetPtr m_pRecordset;

	m_oCheck1.SetCheck(0);
	m_oCheck2.SetCheck(0);
	m_oCheck3.SetCheck(0);
	m_oCheck4.SetCheck(0);
	m_oCheck5.SetCheck(0);
	m_oCheck6.SetCheck(0);
	m_oCheck7.SetCheck(0);
	m_oCheck8.SetCheck(0);
	m_oCheck9.SetCheck(0);

	iOption = m_oListuser.GetCurSel();
	m_oListuser.GetText(iOption, stemp);//得到选中项的文本

	sql="select * from USERS where NAME='"+stemp+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			
		lNewID=0;
		//Read selected user info into controls.
		if(!m_pRecordset->adoEOF)
		{
			m_oUserid.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ID"));
			m_oUserid.GetWindowText(suserid);
			m_oPwd.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("PSD"));
			m_oUsername.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME"));
			m_oDuty.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("TITLE"));
			m_oDatebirth.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("DATEBIRTH"));
			m_oJiguan.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("HOME"));
			m_oNumber.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("EMPLOYNUMBER"));
			m_oDiscount.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("DISCOUNT"));
			CString slogid=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("LOGINID");
			if(slogid=="Admin")
				m_oLogname.SetReadOnly(TRUE);
			else
				m_oLogname.SetReadOnly(FALSE);
			m_oLogname.SetWindowText(slogid);

			sex=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("SEX");//Set sex combobox string.
			if(sex=="0")
				m_oSex.SetCurSel(0);
			if(sex=="1")
				m_oSex.SetCurSel(1);

			spower=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("POWER");
			if(spower.Find("Basedoc")>0)
				m_oCheck1.SetCheck(1);
			if(spower.Find("Stat")>0)
				m_oCheck2.SetCheck(1);
			if(spower.Find("Sysmain")>0)
				m_oCheck3.SetCheck(1);
			if(spower.Find("RF")>0)
				m_oCheck4.SetCheck(1);
			if(spower.Find("DelBill")>0)
				m_oCheck5.SetCheck(1);
			if(spower.Find("CallBill")>0)
				m_oCheck6.SetCheck(1);
			if(spower.Find("Deldata")>0)
				m_oCheck7.SetCheck(1);
			if(spower.Find("Hang")>0)
				m_oCheck8.SetCheck(1);
			if(spower.Find("Recheck")>0)
				m_oCheck9.SetCheck(1);
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("显示用户信息出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
}

long CUserDlg::GenNewID()
{
	CString sql;
	long NewID;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT Max(ID) FROM USERS";
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
		stemp.Format("获得ID最大值出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	return NewID;
}

BOOL CUserDlg::bRepeat(CString strFieldValue)
{
	CString sql;
	BOOL br;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT * FROM USERS WHERE NAME='";
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
		stemp.Format("查找用户名出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
		return br;
}


void CUserDlg::ReadToListbox()
{
	_RecordsetPtr m_pRecordset;

	//Read user name from database into listbox。
	m_oListuser.ResetContent();
	CString sql="select * from USERS";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			m_oListuser.AddString((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME"));
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("列表框读取用户名出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}	
}
