// CheckDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "MyPos.h"
#include "CheckDlg.h"
#include "PosDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog
extern CMyPosApp theApp;


CCheckDlg::CCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckDlg)
	//}}AFX_DATA_INIT
}


void CCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckDlg)
	DDX_Control(pDX, IDC_EDIT_CONSUME, m_oConsume);
	DDX_Control(pDX, IDC_EDIT_CDISCOUNT, m_oCdiscount);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_oReceive);
	DDX_Control(pDX, IDC_EDIT_CHANGE, m_oChange);
	DDX_Control(pDX, IDC_EDIT_TOTALM, m_oTotalm);
	DDX_Control(pDX, IDC_COMBO_PAYMODE, m_oCombopay);
	DDX_Control(pDX, IDC_LIST_CHECKLIST, m_oChecklist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckDlg)
	ON_BN_CLICKED(IDC_BUTTON_CHECKOK, OnButtonCheckok)
	ON_EN_CHANGE(IDC_EDIT_RECEIVE, OnChangeEditReceive)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CHECKLIST, OnClickListChecklist)
	ON_EN_CHANGE(IDC_EDIT_CDISCOUNT, OnChangeEditCdiscount)
	ON_BN_CLICKED(IDC_BUTTON_RF, OnButtonRf)
	ON_BN_CLICKED(IDC_BUTTON_HANG, OnButtonHang)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg message handlers

BOOL CCheckDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置list控件的文字和背景颜色
	m_oChecklist.SetBkColor(RGB(255,255,255));
	m_oChecklist.SetTextBkColor(RGB(161,223,212));
	//清空list控件的数据
	for(int delcolumn=100;delcolumn>=0;delcolumn--)
		m_oChecklist.DeleteColumn(delcolumn);
	//设置list对话框的列
	DWORD dwStyle;
	RECT rect;
	LV_COLUMN lvc;

	dwStyle = m_oChecklist.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS ;

	m_oChecklist.SetExtendedStyle(dwStyle);
	m_oChecklist.GetClientRect(&rect);

	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH |LVCF_FMT;
	lvc.fmt=LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("商品类别");
	lvc.cx = 110;
	m_oChecklist.InsertColumn(1,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText = _T("消费金额");
	lvc.cx = 90;
	m_oChecklist.InsertColumn(2,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText = _T("可折扣金额");
	lvc.cx = 90;
	m_oChecklist.InsertColumn(3,&lvc);	
	
	lvc.iSubItem = 3;
	lvc.pszText = _T("折扣%");
	lvc.cx = 60;
	m_oChecklist.InsertColumn(4,&lvc);	

	lvc.iSubItem = 4;
	lvc.pszText = _T("结帐金额");
	lvc.cx = 90;
	m_oChecklist.InsertColumn(5,&lvc);	

	//Add paymode to combobox.
	_RecordsetPtr m_pRecordset;
	CString sql="select * from PAYMODE";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			m_oCombopay.AddString((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME"));
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		m_oCombopay.SetCurSel(0);//Select the 1st string of combobox.
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]读取付款方式到组合框出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}	
	//Read class consume to list.
	ReadtoList(theApp.scallid);

	//Sum bill Items money from database.
	CString stotal;
	float ftotal=0;
	sql="Select SUM(ITEMTOTAL) as SSS from SALEDETAIL where BILLID='"+theApp.scallid+"'";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		_variant_t vtemp = m_pRecordset->GetCollect("SSS");
		if(vtemp.dblVal>0) 
			ftotal=(float)m_pRecordset->GetCollect("SSS");
		else
			ftotal=0;
		stotal.Format("%.2f",ftotal);
		m_oTotalm.SetWindowText(stotal);
		m_oConsume.SetWindowText(stotal);
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]计算单据商品金额出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCheckDlg::OnButtonCheckok() 
{
	CString stotal,sbilltotal,spayID,sql,spaymode,snowtime;
	long lpayID;
	_RecordsetPtr m_pRecordset;

	m_oConsume.GetWindowText(stotal);
	m_oTotalm.GetWindowText(sbilltotal);
	int nselect=m_oCombopay.GetCurSel();
	m_oCombopay.GetLBText(nselect,spaymode);
	lpayID=GetPaymodeID(spaymode);
	spayID.Format("%d",lpayID);

	if(fchange<0)
		return;

	//得到系统时间
	CTime now=CTime::GetCurrentTime();
	snowtime=now.Format(_T("%Y-%m-%d %H:%M:%S"));
	sql="Update SALEBILL set ENDDATE='"+snowtime+"',SALES='"+theApp.name+"',TOTAL="
		+stotal+",ACTTOTAL="+sbilltotal+",STATUS='已结帐',PAYMODE="+spayID+" where ID='"+theApp.scallid+"'";
	try
	{ 	
		_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]单据头更新数据库出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
	//output the checkout time and paymode to the print.
	theApp.snowtimep=snowtime;
	theApp.spaymodep=spaymode;
	theApp.sconsume=stotal;
	theApp.sactsum=sbilltotal;
	//Insert data into PAYDETAIL.
	CString sclass,scontotal,sdiscount,sacttotal,svaltotal;
	int nItemCount=m_oChecklist.GetItemCount();//表项总数
	for(int i=0;i<nItemCount;i++)	
	{
		sclass=m_oChecklist.GetItemText(i,0);
		scontotal=m_oChecklist.GetItemText(i,1);
		sdiscount=m_oChecklist.GetItemText(i,3);
		sacttotal=m_oChecklist.GetItemText(i,4);
		float fvaltotal=atof(scontotal)-atof(sacttotal);
		svaltotal.Format("%.2f",fvaltotal);
		sql="Insert into PAYDETAIL(BILLID,CLASS,TOTAL,DISCOUNT,ACTTOTAL,VALTOTAL) values('"+theApp.scallid+
			"','"+sclass+"',"+scontotal+",'"+sdiscount+"',"+sacttotal+","+svaltotal+")";
		try
		{ 	
			_variant_t RecordsAffected;
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("[结帐]付款明细（PAYDETAIL）插入数据出错:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
	}	
		
	//When the check button is click down,send a message(WM_CHECKOUT) to the CPosDlg.
	LRESULT Res=::SendMessage(theApp.pWnd, WM_CHECKOUT, 0, 0);

	CDialog::OnOK();
}

long CCheckDlg::GetPaymodeID(CString payname)
{
	long paymodeID;
	_RecordsetPtr m_pRecordset;
	
	CString sql="Select * from PAYMODE where NAME='"+payname+"'";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		paymodeID=(long)m_pRecordset->GetCollect("ID");
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]获取付款方式ID出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	return paymodeID;
}

void CCheckDlg::OnChangeEditReceive() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	CString sreceive,schange,stotal;

	m_oChange.SetWindowText("");
	m_oReceive.GetWindowText(sreceive);
	m_oTotalm.GetWindowText(stotal);
	fchange=atof(sreceive)-atof(stotal);
	if(fchange>=0)
	{
		schange.Format("%.2f",fchange);
		m_oChange.SetWindowText(schange);
	}
}

void CCheckDlg::ReadtoList(CString sbillid)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql,sclassname,sclassname1,sctotal;
	long lclassid;
	float fctotal=0;

	sql="Select Sum(ITEMTOTAL) as XXX,CLASSID from SALEDETAIL where BILLID='"+sbillid+"' group by CLASSID ";
	//删除所有list中的数据。
	m_oChecklist.DeleteAllItems();

	int numline=0;
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		LV_ITEM lvitem;
		lvitem.pszText="";
		lvitem.mask=LVIF_TEXT;
		lvitem.iSubItem=0;
		while(!m_pRecordset->adoEOF)
		{
			lvitem.iItem=numline;
			m_oChecklist.InsertItem(&lvitem);
			//读出数据写入到list中
			lclassid= (long)m_pRecordset->GetCollect("CLASSID");
			sclassname=GetClassName(lclassid);
			sclassname1=sclassname.Left(sclassname.GetLength()-4);
			m_oChecklist.SetItemText(numline,0,sclassname1);//Read class name to 0 column.
			fctotal=(float)m_pRecordset->GetCollect("XXX");
			sctotal.Format("%.2f",fctotal);
			m_oChecklist.SetItemText(numline,1,sctotal);//Read class consume total to 1st column.
			if(sclassname.Right(1)=="0")
				m_oChecklist.SetItemText(numline,2,"0.00");//Read class consume discount total to 2nd column.
			else
				m_oChecklist.SetItemText(numline,2,sctotal);
			m_oChecklist.SetItemText(numline,3,"100");
			m_oChecklist.SetItemText(numline,4,sctotal);//Read class consume act total to 4th column.

			numline++;
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]列表读入商品出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
}

CString CCheckDlg::GetClassName(long lclassid)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql,sclassid,sname,sdiscount;

	sclassid.Format("%d",lclassid);
	sql="Select NAME,DISCOUNT from MATERIELCLASS where ID="+sclassid+"";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)
		{
			sname=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME");
			sdiscount=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("DISCOUNT");
			sname=sname+"xxx"+sdiscount;
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]获取类别名称出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	return sname;
}

void CCheckDlg::OnClickListChecklist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//得到当前选中的行
	POSITION pos = m_oChecklist.GetFirstSelectedItemPosition();
	//如果选中一行
	if(pos)
	{
		int nItem = m_oChecklist.GetNextSelectedItem(pos);
		CString	sdiscount=m_oChecklist.GetItemText(nItem,3);
		m_oCdiscount.SetWindowText(sdiscount);
	}

	*pResult = 0;
}

void CCheckDlg::OnChangeEditCdiscount() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString sdiscountsum,sdiscount,ssum;
	float fdiscountsum,fsum;
	long ldiscount;
	LV_ITEM lvitem;
	lvitem.pszText="";
	lvitem.mask=LVIF_TEXT;
	
	//得到当前选中的行
	POSITION pos = m_oChecklist.GetFirstSelectedItemPosition();
	//如果选中一行
	if(pos)
	{
		int nItem = m_oChecklist.GetNextSelectedItem(pos);
		sdiscountsum=m_oChecklist.GetItemText(nItem,2);
		fdiscountsum=atof(sdiscountsum);
		m_oCdiscount.GetWindowText(sdiscount);
		ldiscount=atol(sdiscount);
		if(ldiscount>100||ldiscount<0)
		{
			MessageBox("请确定折扣大于0并且小于100！");
			return;
		}
		if(ldiscount<VerifyDicsount())
		{
			CString temp;
			temp.Format("折扣不能小于%d！",VerifyDicsount());
			AfxMessageBox(temp);
			return;
		}
		fsum=ldiscount*fdiscountsum/100;
		ssum.Format("%.2f",fsum);
		if(fdiscountsum==0)//If the class could not be discount.
		{
			sdiscountsum=m_oChecklist.GetItemText(nItem,1);	
			ssum=sdiscountsum;
		}
		lvitem.iItem=nItem;
		m_oChecklist.InsertItem(&lvitem);
		m_oChecklist.SetItemText(nItem,3,sdiscount);
		m_oChecklist.SetItemText(nItem,4,ssum);
	}	

	float ftotal=0;
	int nItemCount=m_oChecklist.GetItemCount();//表项总数
	for(int i=0;i<nItemCount;i++)	
	{
		sdiscountsum=m_oChecklist.GetItemText(i,4);
		fdiscountsum=atof(sdiscountsum);
		ftotal=ftotal+fdiscountsum;
	}
	CString stotal;
	stotal.Format("%.2f",ftotal);
	m_oTotalm.SetWindowText(stotal);
}

void CCheckDlg::OnButtonRf() 
{
	CString sql;

	if(!theApp.VerifyPower("RF"))
	{
		AfxMessageBox("没有权限RF单据!");
		return;
	}

	//得到系统时间
	CTime now=CTime::GetCurrentTime();
	CString	snowtime=now.Format(_T("%Y-%m-%d %H:%M:%S"));
	sql="Update SALEBILL set SALES='"+theApp.name+"',ENDDATE='"+snowtime+"',STATUS='已结帐', ACTTOTAL=0, PAYMODE=88 where ID='"+theApp.scallid+"'";
	try
	{ 	
		_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]RF更新数据库出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}	

	//When the check button is click down,send a message(WM_CHECKOUT) to the CPosDlg.
	LRESULT Res=::SendMessage(theApp.pWnd, WM_CHECKOUT, 0, 0);

	EndDialog(1);//Close the dialog.
}

void CCheckDlg::OnButtonHang() 
{
	if(!theApp.VerifyPower("Hang"))
	{
		AfxMessageBox("没有权限挂帐!");
		return;
	}

	CString sql;
	sql="Update SALEBILL set STATUS='挂帐' where ID='"+theApp.scallid+"'";
	try
	{ 	
		_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[结帐]挂帐更新数据库出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}	

	EndDialog(1);//Close the dialog.
}

long CCheckDlg::VerifyDicsount()
{
	CString sql;
	_RecordsetPtr m_pRecordset;
	long ldiscount;

	sql="Select DISCOUNT from USERS where NAME='"+theApp.name+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		if(!m_pRecordset->adoEOF)
			ldiscount=(long)m_pRecordset->GetCollect("DISCOUNT");
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("读取用户权限出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return -1;
	}
	return ldiscount;
}
