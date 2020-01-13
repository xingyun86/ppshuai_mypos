// PosDlg.cpp : implementation file
// Download by http://www.NewXing.com

#include "stdafx.h"
#include "MyPos.h"
#include "PosDlg.h"
#include "SelectDlg.h"
#include "ModifyqaDlg.h"
#include "CallDlg.h"
#include "CheckDlg.h"
#include "OffdutyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPosDlg dialog
extern CMyPosApp theApp;


CPosDlg::CPosDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPosDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPosDlg)
	//}}AFX_DATA_INIT
}


void CPosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPosDlg)
	DDX_Control(pDX, IDC_EDIT_ACTTOTAL, m_oActtotal);
	DDX_Control(pDX, IDC_EDIT_TOTAL, m_oTotal);
	DDX_Control(pDX, IDC_BUTTON_SELMATERIEL, m_oButton);
	DDX_Control(pDX, IDC_LIST_FORM, m_oFormlist);
	DDX_Control(pDX, IDC_EDIT_BEGINTIME, m_oBegintime);
	DDX_Control(pDX, IDC_EDIT_ENDTIME, m_oEndtime);
	DDX_Control(pDX, IDC_EDIT_CKECK, m_oCheck);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_oStatus);
	DDX_Control(pDX, IDC_EDIT_PEASONS, m_oPeasons);
	DDX_Control(pDX, IDC_EDIT_TABLENO, m_oTableno);
	DDX_Control(pDX, IDC_LIST_BILL, m_oListbill);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPosDlg, CDialog)
	//{{AFX_MSG_MAP(CPosDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADDF, OnButtonAddf)
	ON_LBN_SELCHANGE(IDC_LIST_BILL, OnSelchangeListBill)
	ON_BN_CLICKED(IDC_BUTTON_SELMATERIEL, OnButtonSelmateriel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FORM, OnDblclkListForm)
	ON_BN_CLICKED(IDC_BUTTON_CALLF, OnButtonCallf)
	ON_BN_CLICKED(IDC_BUTTON_DELF, OnButtonDelf)
	ON_BN_CLICKED(IDC_BUTTON_HIDEF, OnButtonHidef)
	ON_BN_CLICKED(IDC_BUTTON_CHECKF, OnButtonCheckf)
	ON_EN_KILLFOCUS(IDC_EDIT_TABLENO, OnKillfocusEditTableno)
	ON_EN_KILLFOCUS(IDC_EDIT_PEASONS, OnKillfocusEditPeasons)
	ON_BN_CLICKED(IDC_BUTTON_OFF, OnButtonOff)
	ON_BN_CLICKED(IDC_BUTTON_FINDF, OnButtonFindf)
	ON_BN_CLICKED(IDC_BUTTON_LOCALP, OnButtonLocalp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_APPLY,OnMyMessage)//Map WM_APPLY message to OnMyMessage function.
	ON_MESSAGE(WM_CHECKOUT,OnMyCheckMessage)//Map WM_CHECKOUT message to OnMyMessage function.
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPosDlg message handlers

BOOL CPosDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//����list�ؼ������ֺͱ�����ɫ
	m_oFormlist.SetBkColor(RGB(255,255,255));
	m_oFormlist.SetTextBkColor(RGB(161,223,212));	

	//���list�ؼ�������
	for(int delcolumn=100;delcolumn>=0;delcolumn--)
		m_oFormlist.DeleteColumn(delcolumn);
	//����list�Ի������
	DWORD dwStyle;
	RECT rect;
	LV_COLUMN lvc;

	dwStyle = m_oFormlist.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT |LVS_SHOWSELALWAYS |LVS_EDITLABELS ;

	m_oFormlist.SetExtendedStyle(dwStyle);
	m_oFormlist.GetClientRect(&rect);

	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH |LVCF_FMT;
	lvc.fmt=LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("���");
	lvc.cx = 70;
	m_oFormlist.InsertColumn(1,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText = _T("����");
	lvc.cx = 220;
	m_oFormlist.InsertColumn(2,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText = _T("����");
	lvc.cx = 80;
	m_oFormlist.InsertColumn(3,&lvc);	

	lvc.iSubItem = 3;
	lvc.pszText = _T("���");
	lvc.cx = 120;
	m_oFormlist.InsertColumn(4,&lvc);	

	//Add all bill whos state is "�ȴ�" to listbill.
	CString sql="Select * from SALEBILL where STATUS<>'�ѽ���'";
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		while(!m_pRecordset->adoEOF)
		{
			m_oListbill.AddString((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ID"));
			m_pRecordset->MoveNext();
		}
			m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString stemp;
		stemp.Format("[��ʼ��]��ȡ '�ȴ�' ���ݳ���:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}

	//Select the last billid in listbox and read its items to listctrl and head to edit.
	int ncount=m_oListbill.GetCount();
	if(ncount>0)
	{
		CString sbillid;
		int nselect;
		nselect=m_oListbill.SetCurSel(ncount-1);
		m_oListbill.GetText(nselect,sbillid);
		ReadBillHead(sbillid);
		ReadToFormlist(sbillid);
	}
	else
	{
		//Put the button to the first list row.
		//��button�Ƶ����ʵ�λ�ò��������С
		m_oFormlist.GetWindowRect(&rect);
		m_oButton.MoveWindow(440,95, rect.right/33, rect.bottom/25);
		m_oButton.BringWindowToTop();
		m_oButton.ShowWindow(SW_SHOW);//�����ر�Ϊ��ʾ
	}
	theApp.pWnd=GetSafeHwnd();//Initialize pWnd;
	m_BMButton3.AutoLoad(IDC_BUTTON_ADDF,this);

























	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPosDlg::OnButtonAddf() 
{
	CString snowtime,sfloor,snewid,sbillno;
	CString sql;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	sfloor=GetCompanyFloor(FALSE);
	//Clear the edit ctrl.
	m_oTableno.SetWindowText("");
	m_oPeasons.SetWindowText("");

	//�õ�ϵͳʱ��
	CTime now=CTime::GetCurrentTime();
	snowtime=now.Format(_T("%Y-%m-%d %H:%M:%S"));

	sbillno=GenNewBillID();
	sql="Insert into SALEBILL (ID,BEGINDATE,STATUS,TOTAL,ACTTOTAL,PAYMODE,FLOOR) values ('"+sbillno+"','"+snowtime+"','�ȴ�',0,0,1,'"+sfloor+"')";
	try
	{ 	
		_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[����]���ɵ��ݳ���:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
	m_oStatus.SetWindowText("�ȴ�");
	m_oBegintime.SetWindowText(snowtime);	
	m_oTotal.SetWindowText("0.00");
	m_oActtotal.SetWindowText("0.00");

	m_oListbill.AddString(sbillno);
	m_oListbill.SelectString(-1,sbillno);
	theApp.scallid=sbillno;//Get current bill id.
	m_oFormlist.DeleteAllItems();

	RECT rect;
	m_oFormlist.GetWindowRect(&rect);
	m_oButton.MoveWindow(440,95, rect.right/40, rect.bottom/35);
	m_oButton.BringWindowToTop();
	m_oButton.ShowWindow(SW_SHOW);//�����ر�Ϊ��ʾ
}

CString CPosDlg::GenNewBillID()
{
	CString sql,snowtime;
	CString sNewID,scurid,snewid;
	long lnewid,lcount;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	//�õ�ϵͳʱ��
	CTime now=CTime::GetCurrentTime();
	snowtime=now.Format(_T("%Y%m%d"));
	sql="Select count(*) as XXX from SALEBILL where ID like '"+snowtime+"%""'";

	lcount=GetRecordCount(sql);
	if(lcount==0)
	{
		sNewID.Format("%s-00001",snowtime);
		return sNewID;
	}

	sql="Select Max(ID) as AAA from SALEBILL where ID like '"+snowtime+"%""'";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		scurid=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("AAA");
		lnewid=atol(scurid.Right(5))+1;
		snewid.Format("-%05d",lnewid);
		sNewID=snowtime+snewid;
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString stemp;
		stemp.Format("��ȡ��󵥾ݱ�ų���:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	return sNewID;
}

void CPosDlg::OnSelchangeListBill() 
{
	CString stemp,sql,sbillid;
	int iOption; 
	_RecordsetPtr m_pRecordset;

	iOption = m_oListbill.GetCurSel();
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�
	theApp.scallid=sbillid;//Get current bill id.
	//Clear the edit ctrl.
	m_oTableno.SetWindowText("");
	m_oPeasons.SetWindowText("");
	sql="select * from SALEBILL where ID='"+sbillid+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			
		if(!m_pRecordset->adoEOF)
		{
			m_oTableno.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("TABLENO"));
			m_oPeasons.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("PEOPLES"));
			m_oCheck.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("SALES"));
			m_oStatus.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("STATUS"));
			m_oBegintime.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("BEGINDATE"));
			m_oEndtime.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ENDDATE"));
			float ftotal=(float)m_pRecordset->GetCollect("TOTAL");
			CString stotal;
			stotal.Format("%.2f",ftotal);
			m_oTotal.SetWindowText(stotal);
			ftotal=(float)m_pRecordset->GetCollect("ACTTOTAL");
			stotal.Format("%.2f",ftotal);
			m_oActtotal.SetWindowText(stotal);
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("��ȡ����ͷ���༭�����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}	
	ReadToFormlist(sbillid);//Get bill items from database.

	int i=m_oFormlist.GetItemCount();
	RECT rect;
	m_oFormlist.GetWindowRect(&rect);
	m_oButton.MoveWindow(440,95+i*15, rect.right/40, rect.bottom/35);
	m_oButton.BringWindowToTop();
	m_oButton.ShowWindow(SW_SHOW);//�����ر�Ϊ��ʾ
}

BEGIN_EVENTSINK_MAP(CPosDlg, CDialog)
   //{{AFX_EVENTSINK_MAP(CPosDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

LRESULT CPosDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	//When CPosDlgDlg received the WM_APPLY message from CSelectDlg 
	//it call the AddItemToList() to fill list.
	AddItemToList();

	//-------------------------------------------------//
	CString smID,sqa,ssum,sno,sql,stotal,sbillid;
	CString sclassid;
	long lrowno;
	int iOption;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	iOption = m_oListbill.GetCurSel();
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�

	lrowno=GetRowNo(sbillid);
	sno.Format("%d",lrowno); //rowno.
	ssum=theApp.sprice;
	//Get class ID.
	sql="Select CLASSID from materiel where ID="+theApp.smID+"";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		long lclassid=(long)m_pRecordset->GetCollect("CLASSID");//How to get field value in only 1 record and 1 field condition.
		sclassid.Format("%d",lclassid);
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[ѡ����Ʒ]��ȡ��Ʒ���ID����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return (LRESULT)0;
	}

	sql="Insert into SALEDETAIL (BILLID,MATERIELID,ITEMCOUNT,ITEMTOTAL,CLASSID,ROWNO,ACTPRICE) values ('"+sbillid+"',"
		+theApp.smID+",1,"+ssum+","+sclassid+","+sno+","+ssum+")";
	try
	{ 	_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
		UpdateData(FALSE);
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[ѡ����Ʒ]������Ʒ�����ݿ����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return (LRESULT)0;
	}

	stotal=SumItemtotal(sbillid);
	sql="Update SALEBILL set TOTAL="+stotal+" where ID='"+sbillid+"'";
	try
	{ 	
		_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[����]���µ����ܽ�����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return (LRESULT)0;
	}
	m_oTotal.SetWindowText(stotal);
//	ReadToFormlist(sbillid);
	return (LRESULT)0;
}

void CPosDlg::AddItemToList()
{
	CString snumline;
	int numline=0,nmax;
	LV_ITEM lvitem;

	lvitem.pszText="";
	lvitem.mask=LVIF_TEXT;
	lvitem.iSubItem=0;

	numline=m_oFormlist.GetItemCount();
	lvitem.iItem=numline;

	snumline=m_oFormlist.GetItemText(numline-1,0);
	nmax=atoi(snumline)+1;
	snumline.Format("%d",nmax);

	m_oFormlist.InsertItem(&lvitem);

	//��������д�뵽list��
	m_oFormlist.SetItemText(numline,0,snumline);
	m_oFormlist.SetItemText(numline,1,theApp.smname);
	m_oFormlist.SetItemText(numline,2,"1");
	m_oFormlist.SetItemText(numline,3,theApp.sprice);		
	
	//Move the select button to next line.
	RECT rect;
	m_oFormlist.GetWindowRect(&rect);
	m_oButton.MoveWindow(440,110+numline*15, rect.right/40, rect.bottom/35);
	m_oButton.BringWindowToTop();
	m_oButton.ShowWindow(SW_SHOW);//�����ر�Ϊ��ʾ
}

long CPosDlg::GetRowNo(CString sbillid)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql,sname;
	long lrowno,lcount;

	sql="Select Count(*) AS XXX from SALEDETAIL where BILLID='"+sbillid+"'";
	lcount=GetRecordCount(sql);

	if(lcount==0)
	{
		lrowno=1;
		return lrowno;
	}

	sql="Select MAX(ROWNO) AS RRR from SALEDETAIL where BILLID='"+sbillid+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		lrowno=(long)m_pRecordset->GetCollect("RRR")+1;//How to get field value in only 1 record and 1 field condition.
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[����]��ȡ��Ʒ��ų���:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	return lrowno;
}

CString CPosDlg::GetMaterielName(long materielid)
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
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("��ȡ��Ʒ���Ƴ���:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	return sname;
}

void CPosDlg::OnButtonSelmateriel() 
{
	int iOption;
	CString sbillid;
	iOption = m_oListbill.GetCurSel();
	if(iOption<0)
		return;
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�

	if(bGetBillStatus(sbillid))
		return;

	CSelectDlg selectdlg;
	selectdlg.DoModal();	
}

void CPosDlg::ReadToFormlist(CString sbillid)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql,sname,sno,sqa,ssum;
	long rowcount=0;
	long lmid;
	float fsum;
	LV_ITEM lvitem;

	//���list�ؼ�������
	m_oFormlist.DeleteAllItems();

	int numline=0;
	lvitem.pszText="";
	lvitem.mask=LVIF_TEXT;
	lvitem.iSubItem=0;

	sql="Select * from SALEDETAIL where BILLID='"+sbillid+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		
		while(!m_pRecordset->adoEOF)
		{
			sno=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ROWNO");
			sqa=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ITEMCOUNT");
			lmid=(long)m_pRecordset->GetCollect("MATERIELID");
			sname=GetMaterielName(lmid);
			fsum=(float)m_pRecordset->GetCollect("ITEMTOTAL");
			ssum.Format("%.2f",fsum);

			lvitem.iItem=numline;
			m_oFormlist.InsertItem(&lvitem);
			//��������д�뵽list��
			m_oFormlist.SetItemText(numline,0,sno);
			m_oFormlist.SetItemText(numline,1,sname);
			m_oFormlist.SetItemText(numline,2,sqa);
			m_oFormlist.SetItemText(numline,3,ssum);					

			m_pRecordset->MoveNext();
			numline++;
		}
		RECT rect;
		m_oFormlist.GetWindowRect(&rect);
		m_oButton.MoveWindow(440,95+numline*15, rect.right/40, rect.bottom/35);
		m_oButton.BringWindowToTop();
		m_oButton.ShowWindow(SW_SHOW);//�����ر�Ϊ��ʾ
		m_pRecordset->Close();///�رռ�¼��rowcount
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("��ȡ������Ʒ���б��г���:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
}

void CPosDlg::OnDblclkListForm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString sno,ssum,sname,scount,sql;
	CString sbillid;
	float fprice,fsum;
	int ncount,nqa,iOption;

	iOption = m_oListbill.GetCurSel();
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�

	if(bGetBillStatus(sbillid))
		return;

	//�õ���ǰѡ�е���
	POSITION pos = m_oFormlist.GetFirstSelectedItemPosition();
	//���ѡ��һ��
	if(pos)
	{		
		int nItem = m_oFormlist.GetNextSelectedItem(pos);
		sno=m_oFormlist.GetItemText(nItem,0);
		scount=m_oFormlist.GetItemText(nItem,2);
		ncount=atoi(scount);
		theApp.sqa=scount;
		ssum=m_oFormlist.GetItemText(nItem,3);
		fsum=atof(ssum);
		fprice=fsum;
		if(ncount>0)
			fprice=fsum/ncount;
		//Open the modifyqa dlg. 
		CModifyqaDlg modifydlg;
		modifydlg.DoModal();

		nqa=atoi(theApp.sqa);
		fsum=nqa*fprice;
		ssum.Format("%.2f",fsum);

		m_oFormlist.SetItemText(nItem,2,theApp.sqa);
		m_oFormlist.SetItemText(nItem,3,ssum);
		//Update saledetail.
		sql="Update SALEDETAIL set ITEMCOUNT="+theApp.sqa+",ITEMTOTAL="+ssum+" where BILLID='"+sbillid+"' and ROWNO="+sno+"";
		try
		{ 	_variant_t RecordsAffected;
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
			UpdateData(FALSE);
		}
		catch(_com_error e)///��׽�쳣
		{
			CString temp;
			temp.Format("[�޸�����]������Ʒ����:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
		//Update salebill.
		_RecordsetPtr m_pRecordset; //Must define it in function!!!!
		float ftotal;
		CString stotal;
		sql="select Sum(ITEMTOTAL) as SSS from SALEDETAIL where BILLID='"+sbillid+"'";
		try
		{ 
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

			ftotal=(float)m_pRecordset->GetCollect("SSS");
			m_pRecordset->Close();
		}
		catch(_com_error e)///��׽�쳣
		{
			CString stemp;
			stemp.Format("[�޸�����]���㵥�ݽ�����:%s",e.ErrorMessage());
			AfxMessageBox(stemp);
			return;
		}
		stotal.Format("%.2f",ftotal);
		sql="Update SALEBILL set TOTAL="+stotal+" where ID='"+sbillid+"'";
		try
		{ 	_variant_t RecordsAffected;
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
		}
		catch(_com_error e)///��׽�쳣
		{
			CString temp;
			temp.Format("[�޸�����]�����ܽ�����:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
		m_oTotal.SetWindowText(stotal);

	}	
	*pResult = 0;
}

BOOL CPosDlg::PreTranslateMessage(MSG* pMsg) 
{
	int i,iState,iOption;
	RECT rect;
	CString sql,sno,sbillid,stotal;

	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F1:
			OnButtonAddf();
			break;
		case VK_F2:
			OnButtonDelf();
			break;
		case VK_F3:
			OnButtonCallf();
			break;
		case VK_F4:
			OnButtonHidef();
			break;
		case VK_F5:
			OnButtonCheckf();
			break;
		case VK_F6:
			
			break;
		case VK_F7:

			break;
		case VK_F8:

			break;
		case VK_F9:

			break;
		case VK_F10:
			OnButtonOff();
			break;
		}
	}
//	if(GetFocus()->GetDlgCtrlID()==IDC_LIST_FORM)//����ض��Ŀؼ���Ҳ���Բ����ж�  
//	{  
		if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_DELETE)  
        {  
			iOption = m_oListbill.GetCurSel();
			m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�

			if(bGetBillStatus(sbillid))
				return FALSE;

			int nItemSelected=m_oFormlist.GetSelectedCount();//��ѡ������
			int nItemCount=m_oFormlist.GetItemCount();//��������
			if(nItemSelected<1) 
				return FALSE;
			for(i=nItemCount-1;i>=0;i--)	
			{
				iState=m_oFormlist.GetItemState(i,LVIS_SELECTED);
				if(iState!=0) 
				{
					sno=m_oFormlist.GetItemText(i,0);
					m_oFormlist.DeleteItem(i);

					sql="delete * from SALEDETAIL where BILLID='"+sbillid+"' and ROWNO="+sno+"";
					try
					{ 	_variant_t RecordsAffected;
						theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
						UpdateData(FALSE);
					}
					catch(_com_error e)///��׽�쳣
					{
						CString temp;
						temp.Format("�����ݿ���ɾ�����ݳ���:%s",e.ErrorMessage());
						AfxMessageBox(temp);
						return FALSE;
					}
				}	
			}
			ReadToFormlist(sbillid);//Refresh formlist.
			m_oFormlist.GetWindowRect(&rect);
			m_oButton.MoveWindow(440,95+(nItemCount-1)*15, rect.right/40, rect.bottom/35);
			m_oButton.BringWindowToTop();
			m_oButton.ShowWindow(SW_SHOW);//�����ر�Ϊ��ʾ

			stotal=SumItemtotal(sbillid);
			m_oTotal.SetWindowText(stotal);
			sql="Update SALEBILL set TOTAL="+stotal+" where ID='"+sbillid+"'";
			try
			{ 	
				_variant_t RecordsAffected;
				theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
			}
			catch(_com_error e)///��׽�쳣
			{
				CString temp;
				temp.Format("[ɾ����Ʒ]������Ʒ�ܽ�����:%s",e.ErrorMessage());
				AfxMessageBox(temp);
				return FALSE;
			}
         }  
//	}		
	return CDialog::PreTranslateMessage(pMsg);
}

void CPosDlg::OnButtonCallf() 
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql;

	if(!theApp.VerifyPower("CallBill"))
	{
		AfxMessageBox("û��Ȩ�޵���!");
		return;
	}

	CCallDlg calldlg;//Create a dialog to enter billid to call.
	calldlg.dowhat="imhappy";
	calldlg.DoModal();

	if(!bGetBillStatus(theApp.scallid))
		return;

	sql="select * from SALEBILL where ID='"+theApp.scallid+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			
		if(!m_pRecordset->adoEOF)
		{
			m_oTableno.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("TABLENO"));
			m_oPeasons.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("PEOPLES"));
			m_oCheck.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("SALES"));
			m_oStatus.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("STATUS"));
			m_oBegintime.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("BEGINDATE"));
			m_oEndtime.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ENDDATE"));
			float ftotal=(float)m_pRecordset->GetCollect("TOTAL");
			CString stotal;
			stotal.Format("%.2f",ftotal);
			m_oTotal.SetWindowText(stotal);
			ftotal=(float)m_pRecordset->GetCollect("ACTTOTAL");
			stotal.Format("%.2f",ftotal);
			m_oActtotal.SetWindowText(stotal);
			ReadToFormlist(theApp.scallid);//Get bill items from database.

			m_oListbill.AddString(theApp.scallid);
			m_oListbill.SelectString(-1,theApp.scallid);
		}
		if(m_pRecordset->adoEOF)
		{
			CString temp="���� '"+theApp.scallid+"' �����ڣ�";
			AfxMessageBox(temp);
			theApp.scallid="";
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("���б��ȡ����ͷ���༭�����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}	
	m_oButton.ShowWindow(SW_HIDE);//����ʾ��Ϊ����	
}

long CPosDlg::GetRecordCount(CString sql)
{
	long lcount;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		lcount=(long)m_pRecordset->GetCollect("XXX");
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString stemp;
		stemp.Format("��ü�¼������:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	return lcount;
}

void CPosDlg::OnButtonDelf() 
{
	CString sql,sbillid;
	int iOption;
	_RecordsetPtr m_pRecordset;

	if(!theApp.VerifyPower("DelBill"))
	{
		AfxMessageBox("û��Ȩ��ɾ������!");
		return;
	}

	iOption = m_oListbill.GetCurSel();
	if(iOption==-1)
		return;
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�


	if(bGetBillStatus(sbillid))
	{
		AfxMessageBox("����ɾ���ѽ��ʵ���!");
		return;
	}

	if(AfxMessageBox("ȷ��ɾ���˵�����",MB_YESNO)==IDYES)
	{
		sql="Delete * from SALEBILL where ID='"+sbillid+"'";
		try
		{ 	
			_variant_t RecordsAffected;
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);		
		}
		catch(_com_error e)///��׽�쳣
		{
			CString temp;
			temp.Format("Delete bill id error:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}	
		sql="Delete * from SALEDETAIL where BILLID='"+sbillid+"'";
		try
		{ 
			_variant_t RecordsAffected;
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);		
		}
		catch(_com_error e)///��׽�쳣
		{
			CString temp;
			temp.Format("ɾ��������Ʒ����:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}	
		m_oListbill.DeleteString(iOption);
		if(m_oListbill.GetCount()>0)
		{
			if(m_oListbill.GetCount()>iOption)
				m_oListbill.SetCurSel(iOption);
			if(m_oListbill.GetCount()==iOption)
				m_oListbill.SetCurSel(iOption-1);

			iOption = m_oListbill.GetCurSel();
			m_oListbill.GetText(iOption, sbillid);//Again�õ�ѡ������ı�
			theApp.scallid=sbillid;//Get current bill id.
			ReadBillHead(sbillid);
			ReadToFormlist(sbillid);
		}
	}
	else
		return;			
}

void CPosDlg::OnButtonHidef() 
{
	int iOption;
	CString sbillid;

	iOption = m_oListbill.GetCurSel();
	if(iOption==-1)
		return;

	m_oListbill.GetText(iOption, sbillid);//Again�õ�ѡ������ı�

	if(!bGetBillStatus(sbillid))
	{
		AfxMessageBox("δ���ʵ��ݲ�������!");
		return;
	}

	m_oListbill.DeleteString(iOption);
	if(m_oListbill.GetCount()==0)
		m_oFormlist.DeleteAllItems();

	if(m_oListbill.GetCount()>0)
	{
		if(m_oListbill.GetCount()>iOption)
			m_oListbill.SetCurSel(iOption);
		if(m_oListbill.GetCount()==iOption)
			m_oListbill.SetCurSel(iOption-1);

		iOption = m_oListbill.GetCurSel();
		m_oListbill.GetText(iOption, sbillid);//Again�õ�ѡ������ı�
		theApp.scallid=sbillid;//Get current bill id.
		ReadBillHead(sbillid);
		ReadToFormlist(sbillid);//Refresh listctrl.	
	}
}


void CPosDlg::OnButtonCheckf() 
{
	int iOption;

	iOption = m_oListbill.GetCurSel();
	if(iOption==-1)
		return;

	m_oListbill.GetText(iOption, theApp.scallid);//�õ�ѡ������ı�

	if(bGetBillStatus(theApp.scallid))
	{
		AfxMessageBox("�ѽ��ʵ��ݲ����ٽ���!");
		return;
	}
	if(m_oFormlist.GetItemCount()==0)
	{
		AfxMessageBox("���ܽ��ʿյ���!");
		return;
	}
	else
	{
		CCheckDlg checkdlg;
		checkdlg.DoModal();
	}
}

LRESULT CPosDlg::OnMyCheckMessage(WPARAM wParam, LPARAM lParam)
{
	//When user click the button of checkdlg
	//it send a message to posdlg to do the following things.
	OnButtonLocalp();
	OnButtonHidef();
	return (LRESULT)(0);
}

CString CPosDlg::SumItemtotal(CString sbillid)
{
	//Sum bill Items money from database.
	CString stotal,sql;
	float ftotal;
	long lcount;
	_RecordsetPtr m_pRecordset;

	sql="Select count(*) as XXX from SALEDETAIL where BILLID ='"+sbillid+"'";
	lcount=GetRecordCount(sql);
	if(lcount==0)
	{
		stotal="0.00";
		return stotal;
	}

	sql="Select SUM(ITEMTOTAL) as SSS from SALEDETAIL where BILLID='"+sbillid+"'";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		ftotal=(float)m_pRecordset->GetCollect("SSS");
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[ǰ̨����]������Ʒ�ܽ�����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	stotal.Format("%.2f",ftotal);

	return stotal;
}

void CPosDlg::ReadBillHead(CString sbillid)
{
	CString sql,status;
	_RecordsetPtr m_pRecordset;

	sql="select * from SALEBILL where ID='"+sbillid+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			
		if(!m_pRecordset->adoEOF)
		{
			m_oTableno.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("TABLENO"));
			m_oPeasons.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("PEOPLES"));
			m_oCheck.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("SALES"));
			m_oStatus.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("STATUS"));
			m_oBegintime.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("BEGINDATE"));
			m_oEndtime.SetWindowText((LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ENDDATE"));
			float ftotal=(float)m_pRecordset->GetCollect("TOTAL");
			CString stotal;
			stotal.Format("%.2f",ftotal);
			m_oTotal.SetWindowText(stotal);
			ftotal=(float)m_pRecordset->GetCollect("ACTTOTAL");
			stotal.Format("%.2f",ftotal);
			m_oActtotal.SetWindowText(stotal);
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("��ȡ����ͷ���༭�����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
}

BOOL CPosDlg::bGetBillStatus(CString sbillid)
{
	CString sql,sstatus;
	BOOL bstatus;
	_RecordsetPtr m_pRecordset;

	sql="select STATUS from SALEBILL where ID='"+sbillid+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			
		if(!m_pRecordset->adoEOF)
		{
			sstatus=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("STATUS");
			if(sstatus=="�ȴ�"||sstatus=="����")
				bstatus=FALSE;
			else
				bstatus=TRUE;
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("��ȡ����״̬����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}
	return bstatus;
}

void CPosDlg::OnKillfocusEditTableno() 
{
	CString sql,stemp,sbillid;
	_RecordsetPtr m_pRecordset;
	int iOption;

	iOption = m_oListbill.GetCurSel();
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�
	if(bGetBillStatus(theApp.scallid))
		return;

	m_oTableno.GetWindowText(stemp);

	sql="Update SALEBILL set TABLENO='"+stemp+"' where ID='"+sbillid+"'";
	try
	{ 	_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("���µ���ͷ(����) ����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}	
}

void CPosDlg::OnKillfocusEditPeasons() 
{
	CString sql,stemp,sbillid;
	_RecordsetPtr m_pRecordset;
	int iOption;

	iOption = m_oListbill.GetCurSel();
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�

	if(bGetBillStatus(theApp.scallid))
		return;
	m_oPeasons.GetWindowText(stemp);

	sql="Update SALEBILL set PEOPLES='"+stemp+"' where ID='"+sbillid+"'";
	try
	{ 	_variant_t RecordsAffected;
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("���µ���ͷ(����)����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}		
}


void CPosDlg::OnButtonOff() 
{
	COffdutyDlg offdlg;
	offdlg.DoModal();
}


void CPosDlg::OnButtonFindf() 
{
	CString sql,sbillid;
	_RecordsetPtr m_pRecordset;

	CCallDlg calldlg;//Create a dialog to enter billid to call.
	calldlg.dowhat="pleased";
	calldlg.DoModal();	

	sql="select ID from SALEBILL where STATUS<>'�ѽ���' and TABLENO='"+calldlg.dowhat+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		if(!m_pRecordset->adoEOF)
		{
			sbillid=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ID");
			m_oListbill.SelectString(-1,sbillid);
			ReadToFormlist(sbillid);
		}
		if(m_pRecordset->adoEOF)
		{
			CString temp="����Ϊ '"+calldlg.dowhat+"' ���ݲ����ڣ�";
			AfxMessageBox(temp);
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("�������ų���:%s",e.ErrorMessage());
		AfxMessageBox(temp);
	}	
}

BOOL CPosDlg::PrintListCtrl(CListCtrl &list)
{
	CDC dc;
	//�Ѵ�ӡ�豸�������ӵ�DC����
	CPrintDialog pdlg(FALSE,PD_NOPAGENUMS|PD_NOSELECTION,this);
	BOOL bFindPrinter=pdlg.GetDefaults();
	if(!bFindPrinter)
		return FALSE;
	dc.Attach(pdlg.GetPrinterDC());

	//ȡ��ӡ���ĺ᷽����ݷ���ķֱ���
	//��ÿӢ�����
	short cxInch = dc.GetDeviceCaps(LOGPIXELSX);
	short cyInch = dc.GetDeviceCaps(LOGPIXELSY);
	//����
	CFont font;
	VERIFY(font.CreatePointFont(96, "����", &dc));//ΪDC��������
	CFont* def_font = dc.SelectObject(&font);//�������ڵ�����

	//���������ȡ��߶ȼ���ÿ�����������ÿҳ�������
	//ȡ��ӡֽ�Ÿ߶ȺͿ��
	int nPageHeight, nPageWidth;
	nPageHeight = dc.GetDeviceCaps(VERTRES);
	nPageWidth = dc.GetDeviceCaps(HORZRES);

	TEXTMETRIC TextM;
	dc.GetTextMetrics(&TextM);
	//����߶�	//����ƽ�����
	int nCharHeight = (unsigned short)TextM.tmHeight;
	int nCharWidth=(unsigned short)TextM.tmAveCharWidth;

	//ÿ���������	//ÿҳ�������
	int	m_MaxLineChar = nPageWidth / nCharWidth - 8; 
	int	m_LinesPerPage = nPageHeight/ nCharHeight; 
	//ҳ�߾�
	int nXMargin = 2;
	int nYMargin = 2;

	//�������
	int nLineCount = list.GetItemCount();
	int i;	

	//���������ӡֽ����Ŀ
	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = "Mypos printing"; 
	di.lpszOutput = (LPTSTR) NULL; 
	di.lpszDatatype = (LPTSTR) NULL; 
	di.fwType = 0; 
	dc.StartDoc(&di);
	dc.StartPage();

	//�����˾����
	CString stitle,sftitle,space="";
	stitle=GetCompanyFloor(TRUE);
	int n=(36-stitle.GetLength())/2;
	for(i=0;i<n;i++)
		space=space+" ";
	sftitle=space+stitle;
	dc.TextOut(2, nYMargin+nCharHeight,sftitle, strlen(sftitle));

	//�������
	CString sbillid;
	int iOption = m_oListbill.GetCurSel();
	m_oListbill.GetText(iOption, sbillid);//�õ�ѡ������ı�
	sbillid="����:"+sbillid;
	dc.TextOut( 2, nYMargin+nCharHeight*2, sbillid, strlen(sbillid));

	//������š���̨ʱ�䡢����������ʱ�䡢���������ʽ
	CString stable,speople,sbegin,ssale,stable1,speople1,send,spaymode;
	m_oTableno.GetWindowText(stable);
	stable1.Format("%-8s",stable);//Table No.
	m_oPeasons.GetWindowText(speople);
	speople1.Format("%-8s",speople);//People quantity.
	m_oBegintime.GetWindowText(sbegin);
	m_oCheck.GetWindowText(ssale);//Checkman.
	spaymode.Format("%-15s",theApp.spaymodep);
	if(ssale=="��")
	{
		ssale.Format("%-8s",theApp.name);
		spaymode="";
	}
	m_oEndtime.GetWindowText(send);//End time.
	if(send=="��")
		send=theApp.snowtimep;
	stable="��̨:"+sbegin+" ����:"+stable1;
	speople="����:"+send+" ����:"+speople1;
	ssale="���ʽ:"+spaymode+" ����:"+ssale;
	dc.TextOut( 2, nYMargin+nCharHeight*3, stable, strlen(stable));
	dc.TextOut( 2, nYMargin+nCharHeight*4, speople, strlen(speople));
	dc.TextOut( 2, nYMargin+nCharHeight*5, ssale, strlen(ssale));

	//����б�ؼ����б���
	CString slisttitle;
	slisttitle="����                  ����      ���";
	dc.TextOut( 2, nYMargin+nCharHeight*7,slisttitle, strlen(slisttitle));	

	int nMaxLinePerPage = nPageHeight/nCharHeight -3;//ÿҳ�������
	int nCurPage =1;
	//������е�����
	CString subitem,sfsub,sfsub1,sfsub2;
	for(i =0; i<nLineCount; i++)
	{
		if(nLineCount+7-(nCurPage-1)*nMaxLinePerPage > nMaxLinePerPage)
		{
			//�µ�һҳ
			dc.EndPage();
			dc.StartPage();
			nCurPage ++;
		}
		subitem= list.GetItemText(i, 1);
		sfsub.Format("%-20s",subitem);
		subitem= list.GetItemText(i, 2);
		sfsub1.Format("%6s",subitem);
		subitem= list.GetItemText(i, 3);
		sfsub2.Format("%10s",subitem);
		sfsub=sfsub+sfsub1+sfsub2;
		dc.TextOut( 2, nYMargin+(i+8-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
					sfsub, strlen(sfsub));
	}
	stitle="------------------------------------";
	dc.TextOut( 2, nYMargin+(nLineCount+8-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
		stitle, strlen(stitle));
	//����ܽ��
	CString stotal,sacttotal,sdiscount;
	float fdiscount;
	stotal.Format("%27s",theApp.sconsume);
	sacttotal.Format("%27s",theApp.sactsum);
	fdiscount=atof(stotal)-atof(sacttotal);
	sdiscount.Format("%31.2f",fdiscount);
	stotal="���ѽ��:"+stotal;
	sdiscount="�ۿ�:"+sdiscount;
	sacttotal="Ӧ�ս��:"+sacttotal;
	dc.TextOut( 2, nYMargin+(nLineCount+9-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
		stotal, strlen(stotal));
	dc.TextOut( 2, nYMargin+(nLineCount+10-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
		sdiscount, strlen(sdiscount));
	dc.TextOut( 2, nYMargin+(nLineCount+11-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
		sacttotal, strlen(sacttotal));
	stitle="------------------------------------";
	dc.TextOut( 2, nYMargin+(nLineCount+12-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
		stitle, strlen(stitle));
	sacttotal="лл�ݹˣ���ӭ�ٴι��٣�";
	dc.TextOut( 2, nYMargin+(nLineCount+13-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
		sacttotal, strlen(sacttotal));

	dc.EndPage();
	dc.EndDoc();
	//��ӡ����
	//���Ҫ���ǽ����廹ԭ����һ���Ǳ����
	dc.SelectObject(def_font); //�ָ�ԭ��������
	font.DeleteObject(); 

	DeleteDC(dc.Detach()); 

	return TRUE;
}

CString CPosDlg::GetCompanyFloor(BOOL bCompany)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	CString sql,scompany,sfloor;

	sql="Select * from COMPANY";	
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		if(!m_pRecordset->adoEOF)
		{
			 scompany=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("COMPANYNAME");
			 sfloor=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("FLOORNUMBER");
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///��׽�쳣
	{
		CString stemp;
		if(!bCompany)
			stemp.Format("[��ʼ��]��ȡ¥��ų���:%s",e.ErrorMessage());
		if(bCompany)
			stemp.Format("[��ӡ]��ȡ��˾������:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	if(!bCompany)
		return sfloor;
	if(bCompany)
		return scompany;
}

void CPosDlg::OnButtonLocalp() 
{
	PrintListCtrl(m_oFormlist);
}
