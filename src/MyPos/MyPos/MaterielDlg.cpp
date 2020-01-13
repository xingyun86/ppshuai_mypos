//Download by http://www.NewXing.com
// MaterielDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "MaterielDlg.h"
#include "ClassDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaterielDlg dialog
extern CMyPosApp theApp;

CMaterielDlg::CMaterielDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterielDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMaterielDlg)
	m_mname = _T("");
	//}}AFX_DATA_INIT
}


void CMaterielDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterielDlg)
	DDX_Control(pDX, IDC_LIST_MATERIEL, m_oListmateriel);
	DDX_Control(pDX, IDC_TREE_MCLASS, m_oMclass);
	DDX_Control(pDX, IDC_CHECK_SUPPLY, m_oSupply);
	DDX_Control(pDX, IDC_EDIT_MSHOPCODE, m_oMshopcode);
	DDX_Control(pDX, IDC_EDIT_MPRICE, m_oMprice);
	DDX_Control(pDX, IDC_EDIT_MNAME, m_oMname);
	DDX_Control(pDX, IDC_EDIT_MBARCODE, m_oMbarcode);
	DDX_Control(pDX, IDC_COMBO_MDISCOUNT, m_oMdiscount);
	DDX_Text(pDX, IDC_EDIT_MNAME, m_mname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterielDlg, CDialog)
	//{{AFX_MSG_MAP(CMaterielDlg)
	ON_BN_CLICKED(IDC_BUTTON_MSAVE, OnButtonMsave)
	ON_BN_CLICKED(IDC_BUTTON_MADD, OnButtonMadd)
	ON_BN_CLICKED(IDC_BUTTON_MDEL, OnButtonMdel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MCLASS, OnSelchangedTreeMclass)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MATERIEL, OnClickListMateriel)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaterielDlg message handlers

void CMaterielDlg::OnButtonMsave() 
{
	CString sql="select * from Materiel";
	CString snewid,sname,sdiscount,sprice,ssupply,sshopcode,sbarcode;
	CString sMID;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	UpdateData();

	//检查数据完整性
	m_oMname.GetWindowText(sname);//Get the current text in edit.
	m_oMprice.GetWindowText(sprice);
	if(sname==""||sprice=="")
	{
		AfxMessageBox("请输入商品名称、价格！");
		return;
	}
	m_oMname.GetWindowText(sname);//Get the current text in edit.

	int discount=m_oMdiscount.GetCurSel();
	sdiscount.Format("%d",discount);

	if(m_oSupply.GetCheck()==0) ssupply="0";
	if(m_oSupply.GetCheck()==1) ssupply="1";

	m_oMprice.GetWindowText(sprice);
	m_oMshopcode.GetWindowText(sshopcode);
	m_oMbarcode.GetWindowText(sbarcode);

	if(lNewID>lMID)
	{
		if(bRepeat(sname)==TRUE)
		{
			AfxMessageBox("商品名称重复，请重新输入！");
			return;
		}	
		snewid.Format("%d",lNewID);
		try
		{ 
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

	  		m_pRecordset->AddNew();//insert the current into database.			
			m_pRecordset->PutCollect("ID",_variant_t(snewid));
			m_pRecordset->PutCollect("NAME",_variant_t(sname));
			m_pRecordset->PutCollect("DISCOUNT",_variant_t(sdiscount));//Here m_discount must be a float.
			m_pRecordset->PutCollect("SUPPLY",_variant_t(ssupply));
			m_pRecordset->PutCollect("PRICE",_variant_t(sprice));
			m_pRecordset->PutCollect("SHOPCODE",_variant_t(sshopcode));
			m_pRecordset->PutCollect("BARCODE",_variant_t(sbarcode));
			m_pRecordset->PutCollect("CLASSID",_variant_t(sclassid));

			m_pRecordset->Update();//保存到库中    
			m_pRecordset->Close();
			UpdateData(FALSE);
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("增加商品出错:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
	}
	else if(AfxMessageBox("确定修改商品资料吗？",MB_YESNO)==IDYES)
	{
		_variant_t RecordsAffected;
		sMID.Format("%d",lMID);
		sql="Update MATERIEL set NAME='"+sname+
			"',PRICE="+sprice+
			",DISCOUNT="+sdiscount+
			",SHOPCODE='"+sshopcode+
			"',BARCODE='"+sbarcode+
			"',SUPPLY="+ssupply+" where ID="+sMID+"";
		try
		{ 
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
			UpdateData(FALSE);
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("修改商品资料出错:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
	}
	CString sql1="Select * from MATERIEL where CLASSID="+sclassid+"";
	ReadtoList(sql1);
}

long CMaterielDlg::GenNewID()
{
	CString sql;
	long NewID;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT Max(ID) FROM MATERIEL";
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
		stemp.Format("获取类别ID最大值出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	return NewID;
}

void CMaterielDlg::AddSubTree(CString ParTree, HTREEITEM hPartItem)
{
	HTREEITEM hCurrent;
	CString sql;
	CString curID;
	_RecordsetPtr m_pTRecordset; //Must define it in function!!!Becourse this is a RECURSION function.

	sql="SELECT * FROM MATERIELCLASS where PARENT='";
	sql=sql+ParTree+"'";//The 1st time Partree="1".
	try
	{
		m_pTRecordset.CreateInstance("ADODB.Recordset");
		m_pTRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);

		m_pTRecordset->MoveFirst();
		if(!m_pTRecordset->adoEOF)
		{
			while(!m_pTRecordset->adoEOF)
			{
				hCurrent = m_oMclass.InsertItem((LPCTSTR)(_bstr_t)(m_pTRecordset->GetCollect("NAME")), hPartItem, NULL);//Insert an item into current parent.
					
				curID=CClassDlg::VariantToCString(m_pTRecordset->GetCollect("ID"));
				if (CClassDlg::TreeSumRecordCount(curID)>0)
					AddSubTree(CClassDlg::VariantToCString(m_pTRecordset->GetCollect("ID")),hCurrent);//Recursion.			
				
				if (!m_pTRecordset->adoEOF)
					m_pTRecordset->MoveNext();
			}
		}
		m_pTRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("[商品资料]读取子树出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
}

void CMaterielDlg::AddTree()
{
	TVINSERTSTRUCT tvInsert;
	HTREEITEM hParent;
	_RecordsetPtr m_pTRecordset; //Must define it in function!!!Becourse this is a RECURSION function.
	CString sroot,sql;

	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;

	tvInsert.item.pszText = _T("root");
	hParent = m_oMclass.InsertItem(&tvInsert);//HTREEITEM of root.

	sql="SELECT * FROM MATERIELCLASS where ID=1";
	try
	{
		m_pTRecordset.CreateInstance("ADODB.Recordset");
		m_pTRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);

		if(!m_pTRecordset->adoEOF)
		{
			sroot=(LPTSTR)(_bstr_t)m_pTRecordset->GetCollect("NAME");//Insert an item into current parent.
		}
		m_pTRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("[商品资料] 读取树出错:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
//	tvInsert.item.pszText = _T("root");
	if(sroot!="")
	{
//		tvInsert.item.pszText =_T("");
		hParent = m_oMclass.InsertItem(&tvInsert);//HTREEITEM of root.

		AddSubTree("RootClass",hParent);//Here strChildTree just must not equal "root",can be anyother string.
	}
//	AddSubTree("1",hParent);//Here strChildTree just must not equal "root",can be anyother string.

	m_oMclass.Expand(hParent,TVE_EXPAND);
}

BOOL CMaterielDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//设置list控件的文字和背景颜色
	m_oListmateriel.SetBkColor(RGB(255,255,255));
	m_oListmateriel.SetTextBkColor(RGB(161,223,212));	

	//清空list控件的数据
	for(int delcolumn=100;delcolumn>=0;delcolumn--)
		m_oListmateriel.DeleteColumn(delcolumn);
	//设置list对话框的列
	DWORD dwStyle;
	RECT rect;
	LV_COLUMN lvc;

	dwStyle = m_oListmateriel.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS ;

	m_oListmateriel.SetExtendedStyle(dwStyle);
	m_oListmateriel.GetClientRect(&rect);

	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH |LVCF_FMT;
	lvc.fmt=LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("类别");
	lvc.cx = 80;
	m_oListmateriel.InsertColumn(1,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText = _T("名称");
	lvc.cx = 150;
	m_oListmateriel.InsertColumn(2,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText = _T("价格");
	lvc.cx = 65;
	m_oListmateriel.InsertColumn(3,&lvc);

	//Read the 1st class's materiels to list.
//	CString sql="Select * from MATERIEL where CLASSID=1";
//	ReadtoList(sql);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMaterielDlg::OnButtonMadd() 
{
	m_oMname.SetWindowText("");
	m_oMprice.SetWindowText("");
	m_oMshopcode.SetWindowText("");
	m_oMbarcode.SetWindowText("");
	lNewID=GenNewID();
}

void CMaterielDlg::OnButtonMdel() 
{
	CString sql, stemp,ssclassid;
	_RecordsetPtr m_pRecordset;
	long lclassid;

	m_oMname.GetWindowText(stemp);//得到选中项的文本
	if(stemp=="")
		return;

	sql="select * from MATERIEL where NAME='"+stemp+"'";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		
		lclassid=(long)(m_pRecordset->GetCollect("CLASSID"));
		if(AfxMessageBox("确定删除此商品吗？",MB_YESNO)==IDYES)
		{
			m_pRecordset->Delete(adAffectCurrent);///删除当前记录
		}
		else
			return;				
		m_pRecordset->Update();   
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("删除商品出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
	ssclassid.Format("%d",lclassid);
	CString sql1="Select * from MATERIEL Where CLASSID="+ssclassid+"";
	ReadtoList(sql1);
}

void CMaterielDlg::ReadtoList(CString sql)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	//删除所有list中的数据。
	m_oListmateriel.DeleteAllItems();

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
				m_oListmateriel.InsertItem(&lvitem);
				//读出数据写入到list中
//				m_oListmateriel.SetItemText(numline,0,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("CLASSID"));
				m_oListmateriel.SetItemText(numline,0,curtext);
				m_oListmateriel.SetItemText(numline,1,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME"));
				float fprice=(float)m_pRecordset->GetCollect("PRICE");
				CString sprice;
				sprice.Format("%.2f",fprice);
				m_oListmateriel.SetItemText(numline,2,sprice);
				numline++;
				m_pRecordset->MoveNext();
			}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("读取商品到列表出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
	//设置标题
	CString temp;
	temp.Format("共有%d条记录",numline);
	SetWindowText(temp);
}

void CMaterielDlg::OnSelchangedTreeMclass(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CString sql,sql1;
	long lclassid;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!
	HTREEITEM hCurItem;

	//Clear text in edit.
	m_oMname.SetWindowText("");
	m_oMprice.SetWindowText("");
	m_oMshopcode.SetWindowText("");
	m_oMbarcode.SetWindowText("");
	lNewID=0;//Refresh lNewID's value.

	hCurItem=m_oMclass.GetSelectedItem ();//Get Current item and its sub items.
	curtext=m_oMclass.GetItemText(hCurItem);//Read current item text into edit control.
	sql="SELECT * FROM MATERIELCLASS where NAME='"+curtext+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		if(!m_pRecordset->adoEOF)
		{
			lclassid=(long)(m_pRecordset->GetCollect("ID"));
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("获取类别名称出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}

	sclassid.Format("%d",lclassid);
	sql1="Select * from MATERIEL where CLASSID="+sclassid+"";
	ReadtoList(sql1);

	UpdateData(false);

	*pResult = 0;
}

void CMaterielDlg::OnClickListMateriel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString smname,sshopcode,sbarcode,sprice;
	CString sql;
	float fprice;
	int ndiscount,nsupply;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!

	m_oMname.SetWindowText("");
	m_oMprice.SetWindowText("");
	m_oMshopcode.SetWindowText("");
	m_oMbarcode.SetWindowText("");

	//得到当前选中的行
	POSITION pos = m_oListmateriel.GetFirstSelectedItemPosition();
	//如果选中一行
	if(pos)
	{
		int nItem = m_oListmateriel.GetNextSelectedItem(pos);
		smname=m_oListmateriel.GetItemText(nItem,1);
		m_oMname.SetWindowText(smname);

		lNewID=0;//Refresh lNewID's value.
		sql="Select * from MATERIEL where NAME='"+smname+"'";
		try
		{
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
			if(!m_pRecordset->adoEOF)
			{
				lMID=(long)(m_pRecordset->GetCollect("ID"));
				fprice=(float)(m_pRecordset->GetCollect("PRICE"));
				ndiscount=(long)m_pRecordset->GetCollect("DISCOUNT");
				nsupply=(long)m_pRecordset->GetCollect("SUPPLY");
				sshopcode=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("SHOPCODE");
				sbarcode=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("BARCODE");
				sprice.Format("%.2f",fprice);
				m_oMprice.SetWindowText(sprice);
				m_oMshopcode.SetWindowText(sshopcode);
				m_oMbarcode.SetWindowText(sbarcode);
				m_oMdiscount.SetCurSel(ndiscount);
				m_oSupply.SetCheck(nsupply);
			}
			m_pRecordset->Close();
		}
		catch(_com_error e)///捕捉异常
		{
			CString temp;
			temp.Format("读取商品资料到控件出错:%s",e.ErrorMessage());
			AfxMessageBox(temp);
			return;
		}
	}
	
	*pResult = 0;
}

BOOL CMaterielDlg::bRepeat(CString strFieldValue)
{
	CString sql;
	BOOL br;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT * FROM MATERIEL WHERE NAME='";
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
		stemp.Format("查找商品名称出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
		return br;
}

void CMaterielDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	m_oMclass.DeleteAllItems();
	AddTree();	
}
