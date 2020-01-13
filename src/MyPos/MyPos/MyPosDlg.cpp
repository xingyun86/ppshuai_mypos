//Download by http://www.NewXing.com
// MyPosDlg.cpp : implementation file
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
// CAboutDlg dialog used for App About
extern CMyPosApp theApp;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPosDlg dialog

CMyPosDlg::CMyPosDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyPosDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyPosDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPosDlg)
	DDX_Control(pDX, IDC_STATIC_USERNAME, m_osUsername);
	DDX_Control(pDX, IDC_STATIC_COMPANY, m_osCompany);
	DDX_Control(pDX, IDC_TAB1, m_oTab1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyPosDlg, CDialog)
	//{{AFX_MSG_MAP(CMyPosDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_OFFDUTY,OnMyOffdutyMessage)//Map WM_OFFDUTY message to OnMyMessage function.
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPosDlg message handlers

BOOL CMyPosDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_oTab1.AddPage("前台销售", &m_oPosdlg, IDD_DIALOG_POS);
	if(theApp.VerifyPower("Stat"))
		m_oTab1.AddPage("统计报表", &m_oStatdlg, IDD_DIALOG_STAT);
	if(theApp.VerifyPower("Basedoc"))
		m_oTab1.AddPage("基础资料", &m_oBasedlg, IDD_DIALOG_BASE);
	if(theApp.VerifyPower("Sysmain"))
		m_oTab1.AddPage("系统维护", &m_oSysmtdlg, IDD_DIALOG_SYSMT);
	m_oTab1.Show();	

	//Add username and company name to static control.
	CString sql;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	sql="Select COMPANYNAME from COMPANY";	
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)		
			m_osCompany.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("COMPANYNAME"));
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[主窗口]获取公司名称出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	m_osUsername.SetWindowText(theApp.name);

	/////////////////////////
	theApp.pWndoff=m_hWnd;//Must initialize the HWND in OnInitDialog()!!!!
	//显示弹出的登录框。
	SetTimer(1,1,NULL);
    //m_BMButton2.AutoLoad(IDCANCEL,this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyPosDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyPosDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyPosDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



int CMyPosDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CSplashWnd::ShowSplashScreen(this);//Add splash screen.
	
	return 0;
}

void CMyPosDlg::OnClose() 
{
	if(AfxMessageBox("确定要退出吗？",MB_YESNO)==IDYES)	
		CDialog::OnClose();
}

LRESULT CMyPosDlg::OnMyOffdutyMessage(WPARAM wParam, LPARAM lParam)
{
	EndDialog(1);//Must use this function to close the dialog!!!!!!!!!!
	return (LRESULT)0;
}
