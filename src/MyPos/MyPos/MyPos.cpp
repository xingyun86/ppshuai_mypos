//Download by http://www.NewXing.com
// MyPos.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyPos.h"
#include "MyPosDlg.h"
#include "LogonDlg.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPosApp

BEGIN_MESSAGE_MAP(CMyPosApp, CWinApp)
	//{{AFX_MSG_MAP(CMyPosApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
//	ON_COMMAND(ID_HELP, CWinApp::OnHelp)//Deuse the F1-Help.
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPosApp construction

CMyPosApp::CMyPosApp()
{
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyPosApp object

CMyPosApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyPosApp initialization

BOOL CMyPosApp::InitInstance()
{
	//Add splash image to the application.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	AfxOleInit();//初始化COM库
	AfxEnableControlContainer();

	// 此程序只能运行一次，用互斥量来判断程序是否已运行
    HANDLE m_hMutex=CreateMutex(NULL,TRUE, m_pszAppName); 
    if(GetLastError()==ERROR_ALREADY_EXISTS) 
		return FALSE; 

	//以下是连接access2000数据库。。。
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象

		if(SUCCEEDED(hr))
		{
			m_pConnection->ConnectionTimeout=3;///设置超时时间为3秒
//			hr = m_pConnection->Open(Filepath,"","",adModeUnknown);
			if (sizeof(void*) == sizeof(long))
			{
				hr = m_pConnection->Open((LPCWSTR)CStringW("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=cypos.mdb;"), (LPCWSTR)CStringW(""), (LPCWSTR)CStringW(""), adModeUnknown);
			}
			else
			{
				hr = m_pConnection->Open((LPCWSTR)CStringW("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=cypos.mdb;"), (LPCWSTR)CStringW(""), (LPCWSTR)CStringW(""), adModeUnknown);
			}
			///连接数据库
			///上面一句中连接字串中的Provider是针对ACCESS2000环境的，对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51;  }
		}
	}
	catch (_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format(_T("连接数据库错误信息:%s,%s"), e.ErrorMessage(), (LPCTSTR)CString((LPWSTR)e.Description()));
		::MessageBox(NULL, temp, _T("提示信息"), NULL);
		return false;
	}
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

    SetDialogBkColor (RGB (130,194, 220), RGB ( 16,20, 255 ) );

	CLogonDlg logdlg;
	if(logdlg.DoModal()==IDOK)
		CString sql="SELECT * FROM USERS where LOGID='"+theApp.name+"'";
	else
		return FALSE;

	pWnd=NULL;//Initialize pointer!!!!
	theApp.pWndoff=NULL;//Initialize pointer!!!!
	scallid="";

	CMyPosDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}

CString CMyPosApp::addpwd(CString pwd, bool in)
{
	char temp[1000];
	int i = 0;
	if(in)
	{
		for(i=0;i<pwd.GetLength();i++)
			temp[i]=pwd[i]-2-i;
		temp[i]='\0';
	}
	else
	{
		for(i=0;i<pwd.GetLength();i++)
			temp[i]=pwd[i]+2+i;
		temp[i]='\0';
	}
	CString str;
	str.Format("%s",temp);
	return str;
}

int CMyPosApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_pConnection->State)
		m_pConnection->Close(); ///如果已经打开了连接则关闭它
	return CWinApp::ExitInstance();
}


BOOL CMyPosApp::VerifyPower(CString power)
{
	CString sql,spower;
	_RecordsetPtr m_pRecordset;

	sql="Select POWER from USERS where NAME='"+theApp.name+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)
			spower=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("POWER");
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("读取用户权限出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return FALSE;
	}

	if(spower.Find(power)>=0)
		return TRUE;
	else
		return FALSE;
}

