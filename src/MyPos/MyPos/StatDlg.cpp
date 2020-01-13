//Download by http://www.NewXing.com
// StatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "StatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatDlg dialog
extern CMyPosApp theApp;


CStatDlg::CStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatDlg)
	//}}AFX_DATA_INIT
}


void CStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER_SD, m_oSdate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_OD, m_oOdate);
	DDX_Control(pDX, IDC_RADIO_WEEK, m_oWeek);
	DDX_Control(pDX, IDC_EDIT_LISTTITLE, m_oListtitle);
	DDX_Control(pDX, IDC_LIST_REPORT, m_oListreport);
	DDX_Control(pDX, IDC_EDIT_ST, m_oSt);
	DDX_Control(pDX, IDC_EDIT_OT, m_oOt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatDlg, CDialog)
	//{{AFX_MSG_MAP(CStatDlg)
	ON_BN_CLICKED(IDC_BUTTON_STAT, OnButtonStat)
	ON_BN_CLICKED(IDC_BUTTON_PRINTREPORT, OnButtonPrintreport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatDlg message handlers

BOOL CStatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_oWeek.SetCheck(1);
	m_oSt.SetWindowText("00:00:00");
	m_oOt.SetWindowText("23:59:59");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStatDlg::OnButtonStat() 
{
	int n;
	CString sql,sfloor,scompany,ssdate,sodate,sstime,sotime;
	CString sbegin,send,stotal;
	_RecordsetPtr m_pRecordset;

	int nselect=GetCheckedRadioButton(IDC_RADIO_SINGLE,IDC_RADIO_WEEK); 
	switch(nselect)//Get if it is discount.
	{
	case IDC_RADIO_WEEK:
		n=0;
		m_oListtitle.SetWindowText("           ** 销售汇总报表 **");
		break;
	case IDC_RADIO_SINGLE:
		n=1;
		m_oListtitle.SetWindowText("             ** 单品报表 **");
		break;
	default:
		break;
	}

	int ncount=m_oListreport.GetCount()-1;
	for(int i=ncount;i>=0;i--)//Clear report listbox.
		m_oListreport.DeleteString(i);

	sql="Select * from COMPANY";	
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)	
		{
			 sfloor=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("FLOORNUMBER");
			 scompany=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("COMPANYNAME");
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString sdate;
		sdate.Format("读取楼层号出错:%s",e.ErrorMessage());
		AfxMessageBox(sdate);
	}
	m_oListreport.AddString("                                      ");
	int ns=32-scompany.GetLength()-sfloor.GetLength();
	CString space=" ";
	for(int j=0;j<ns-1;j++)
		space=space+" ";
	m_oListreport.AddString(scompany+space+"楼层号 "+sfloor);
	m_oListreport.AddString("---------------------------------------");

	m_oSdate.GetWindowText(ssdate);
	ssdate=Dateformat(ssdate);
	m_oSt.GetWindowText(sstime);
	sbegin=ssdate+" "+sstime;
	m_oListreport.AddString("开始时间:           "+sbegin);

	m_oOdate.GetWindowText(sodate);
	sodate=Dateformat(sodate);
	m_oOt.GetWindowText(sotime);
	send=sodate+" "+sotime;
	m_oListreport.AddString("结束时间:           "+send);
	m_oListreport.AddString("---------------------------------------");

	sql="where ENDDATE>='"+sbegin+"' and ENDDATE<='"+send+"' and STATUS='已结帐'";
	if(n==0)
		SumBillTotal(sql);
	if(n==1)
	{
		m_oListreport.AddString("商品名称                           数量");
		SumSingleItem(sql);
	}

}

CString CStatDlg::Dateformat(CString sdate)
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

void CStatDlg::SumBillTotal(CString scondition)
{
	float fsum,fttl;
	long lcount,lpersonqa,lbillqa;
	CString sql,ssum,scount,spersonqa,sbillqa;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString space,space1;
	int i,n;
	//count bills quantity.
	sql="Select COUNT(*) as XXX from SALEBILL "+scondition+"";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		lcount=(long)m_pRecordset->GetCollect("XXX");
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[报表]读取记录数出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	if(lcount==0)
	{
		m_oListreport.AddString("人民币:                           0.00");
		return;
	}
	//Calculate sum acttotal , people's quantity and bill's quantity.
	sql="Select SUM(ACTTOTAL) as AAA,SUM(PEOPLES) as BBB,COUNT(*) as CCC from SALEBILL "+scondition+"";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)
		{
			fsum =m_pRecordset->GetCollect("AAA");
			fttl=fsum;
			lpersonqa=m_pRecordset->GetCollect("BBB");
			lbillqa=m_pRecordset->GetCollect("CCC");
		}
		ssum.Format("%.2f",fsum);
		spersonqa.Format("%d",lpersonqa);
		sbillqa.Format("%d",lbillqa);

		n=31-ssum.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";
		m_oListreport.AddString("人民币:"+space+ssum);

		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[报表]计算单据金额出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	//Sum hang bills total.
	_variant_t vtemp;
	sql="Select SUM(TOTAL) as XXX from SALEBILL "+scondition+"";
	sql.Replace("已结帐","挂帐");
	sql.Replace("ENDDATE","BEGINDATE");
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		vtemp=m_pRecordset->GetCollect("XXX");
		fsum=vtemp.dblVal;
		if(fsum>0)
		{
			fttl=fttl+fsum;
			ssum.Format("%.2f",fsum);
		}
		else
			ssum="0.00";

		n=33-ssum.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";
		m_oListreport.AddString("挂帐:"+space+ssum);

		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[报表]计算单据挂帐金额出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	//Sum RF bills total.
	sql="Select SUM(TOTAL) as XXX from SALEBILL "+scondition+" and PAYMODE=88";
//	sql="Select SUM(TOTAL) as XXX from (Select * from SALEBILL "+scondition+") where PAYMODE=88";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		vtemp=m_pRecordset->GetCollect("XXX");
		fsum=vtemp.dblVal;
		if(fsum>0)
		{
			fttl=fttl+fsum;
			ssum.Format("%.2f",fsum);
		}
		else
			ssum="0.00";

		n=35-ssum.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";
		m_oListreport.AddString("RF:"+space+ssum);
		m_oListreport.AddString("                       ----------------");

		CString sttl;
		sttl.Format("%.2f",fttl);
		n=38-sttl.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";
		m_oListreport.AddString(space+sttl);
		m_oListreport.AddString("                                       ");
		m_oListreport.AddString("类别                 汇总          折扣");

		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[报表]计算单据RF金额出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	//Calculate class's acttotal and valtotal.
//	sql="Select CLASS,Sum(ACTTOTAL) as XXX,Sum(VALTOTAL) as VVV from PAYDETAIL where BILLID in (Select ID from SALEBILL "+scondition+") group by CLASS ";
	sql="Select CLASS,Sum(ACTTOTAL) as XXX,Sum(VALTOTAL) as VVV, count(*) from PAYDETAIL where BILLID in (Select ID from SALEBILL "+scondition+") group by CLASS having count(*)>=1";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		float fat=0;
		float fvt=0;
		while(!m_pRecordset->adoEOF)
		{
			CString sclassname =(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("CLASS");
			float facttotal=m_pRecordset->GetCollect("XXX");
			float fvaltotal=m_pRecordset->GetCollect("VVV");
			fat=fat+facttotal;
			fvt=fvt+fvaltotal;
			CString sacttotal,svaltotal;
			sacttotal.Format("%.2f",facttotal);
			svaltotal.Format("%.2f",fvaltotal);

			n=25-sclassname.GetLength()-sacttotal.GetLength();
			space=" ";
			for(i=0;i<n-1;i++)
				space=space+" ";
			CString space1=" ";
			n=14-svaltotal.GetLength();
			for(i=0;i<n-1;i++)
				space1=space1+" ";
			m_oListreport.AddString(sclassname+space+sacttotal+space1+svaltotal);

			m_pRecordset->MoveNext();
		}
		m_oListreport.AddString("                                       ");
		CString sat,svt;
		sat.Format("%.2f",fat);
		svt.Format("%.2f",fvt);
		n=20-sat.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";
		space1=" ";
		n=14-svt.GetLength();
		for(i=0;i<n-1;i++)
			space1=space1+" ";
		m_oListreport.AddString("总计:"+space+sat+space1+svt);
		m_oListreport.AddString("                                       ");

		n=28-spersonqa.GetLength()-sbillqa.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";		
		m_oListreport.AddString("人数:"+spersonqa+space+"单数:"+sbillqa);
		m_oListreport.AddString("                                       ");
		m_oListreport.AddString("-----------------未结单----------------");

		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[报表]计算类别金额出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	//Get non-check bill.
	float fnonttl=0;
	CString snontotal;
	sql="Select ID,TOTAL from SALEBILL where STATUS<>'已结帐'";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			CString snoncheck=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ID");
			float fnontotal=(float)m_pRecordset->GetCollect("TOTAL");
			snontotal.Format("%.2f",fnontotal);
			n=38-snoncheck.GetLength()-snontotal.GetLength();
			space=" ";
			for(i=0;i<n-1;i++)
				space=space+" ";
			m_oListreport.AddString(snoncheck+space+snontotal);

			fnonttl=fnonttl+fnontotal;
			m_pRecordset->MoveNext();
		}
		if(fnonttl!=0)
		{
			snontotal.Format("%.2f",fnonttl);
			n=38-snontotal.GetLength();
			space=" ";
			for(i=0;i<n-1;i++)
				space=space+" ";
			m_oListreport.AddString("                       ----------------");
			m_oListreport.AddString(space+snontotal);
		}

		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[报表]读取未结单出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}

}

void CStatDlg::SumSingleItem(CString scondition)
{
	CString sql,sitemsum,smname;
	long litemsum,lmid;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	//Select suit records and insert them into SINGLEREPORT.
	sql="Delete * from SINGLEREPORT";
	try
	{ 
		_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
		sql="Insert into SINGLEREPORT (ITEMCOUNT,MATERIELID) Select ITEMCOUNT,MATERIELID from SALEDETAIL Where BILLID in (Select ID from SALEBILL "+scondition+")";
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[单品]插入单品项目出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
		return;
	}	

	//Get records and insert them into report listbox.
	sql="Select MATERIELID,Sum(ITEMCOUNT) as XXX,count(*) from SINGLEREPORT group by MATERIELID having count(*)>=1";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		while(!m_pRecordset->adoEOF)
		{
			litemsum =(long)m_pRecordset->GetCollect("XXX");
			sitemsum.Format("%6d",litemsum);
			lmid=(long)m_pRecordset->GetCollect("MATERIELID");
			smname=GetMaterielName(lmid);
			CString soutname;
			soutname.Format("%-32s",smname);
//			int n=38-sitemsum.GetLength()-smname.GetLength();
//			CString space=" ";
//			for(int i=0;i<n-1;i++)
//				space=space+" ";
//			m_oListreport.AddString(smname+space+sitemsum);
			m_oListreport.AddString(soutname+sitemsum);

			m_pRecordset->MoveNext();//Don't forget this function!!
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("[单品]计算单品数量出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}

}

CString CStatDlg::GetMaterielName(long materielid)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql,smaterielid,sname;

	smaterielid.Format("%d",materielid);
	sql="Select NAME from MATERIEL where ID="+smaterielid+"";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)
			sname=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME");	
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("获取商品名称出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	return sname;
}

void CStatDlg::OnButtonPrintreport() 
{
	//获得行数
	int ncount = m_oListreport.GetCount();
	if(ncount==0)
	{
		MessageBox("无打印内容!");
		return;
	}
	int i;	

	CDC dc;
	//把打印设备环境附加到DC对象
	CPrintDialog pdlg(FALSE,PD_NOPAGENUMS|PD_NOSELECTION,this);
	BOOL bFindPrinter=pdlg.GetDefaults();
	if(!bFindPrinter)
		return;
	dc.Attach(pdlg.GetPrinterDC());

	//取打印机的横方向和纵方向的分辨率
	//即每英寸点数
	short cxInch = dc.GetDeviceCaps(LOGPIXELSX);
	short cyInch = dc.GetDeviceCaps(LOGPIXELSY);
	//字体
	CFont font;
	VERIFY(font.CreatePointFont(96, "宋体", &dc));//为DC创建字体
	CFont* def_font = dc.SelectObject(&font);//保存现在的字体

	//根据字体宽度、高度计算每行最大字数及每页最大行数
	//取打印纸张高度和宽度
	int nPageHeight, nPageWidth;
	nPageHeight = dc.GetDeviceCaps(VERTRES);
	nPageWidth = dc.GetDeviceCaps(HORZRES);

	TEXTMETRIC TextM;
	dc.GetTextMetrics(&TextM);
	//字体高度	//字体平均宽度
	int nCharHeight = (unsigned short)TextM.tmHeight;
	int nCharWidth=(unsigned short)TextM.tmAveCharWidth;

	//每行最大字数	//每页最大行数
	int	m_MaxLineChar = nPageWidth / nCharWidth - 8; 
	//每页最大行数
	int nMaxLinePerPage = nPageHeight/nCharHeight -3;
	int nCurPage =1;
	//页边距
	int nXMargin = 2;
	int nYMargin = 2;

	//设置所需打印纸张数目
	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = "Report printing"; 
	di.lpszOutput = (LPTSTR) NULL; 
	di.lpszDatatype = (LPTSTR) NULL; 
	di.fwType = 0; 
	dc.StartDoc(&di);
	dc.StartPage();

	//输出报表名称
	CString stitle,sftitle,space="";
	m_oListreport.GetWindowText(stitle);
	int n=(36-stitle.GetLength())/2;
	for(i=0;i<n;i++)
		space=space+" ";
	sftitle=space+stitle;
	dc.TextOut(2, nYMargin+nCharHeight,sftitle, strlen(sftitle));

	//输出报表内容
	CString sline;
	for(i=0; i<ncount; i++)
	{
		if(ncount+7-(nCurPage-1)*nMaxLinePerPage > nMaxLinePerPage)
		{
			//新的一页
			dc.EndPage();
			dc.StartPage();
			nCurPage ++;
		}
		m_oListreport.GetText(i, sline);//得到选中项的文本
		dc.TextOut( 2, nYMargin+(i+1-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
					sline, strlen(sline));
	}

	dc.EndPage();
	dc.EndDoc();
	//打印结束
	//最后不要忘记将字体还原，这一句是必需的
	dc.SelectObject(def_font); //恢复原来的字体
	font.DeleteObject(); 

	DeleteDC(dc.Detach()); 	
}
