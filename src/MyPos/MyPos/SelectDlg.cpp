//Download by http://www.NewXing.com
// SelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "SelectDlg.h"
#include "ClassDlg.h"
#include "PosDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog
extern CMyPosApp theApp;


CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDlg)
	DDX_Control(pDX, IDC_LIST_SELECT, m_oListsmateriel);
	DDX_Control(pDX, IDC_TREE_SCLASS, m_oTreesclass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_SCLASS, OnSelchangedTreeSclass)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SELECT, OnClickListSelect)
	ON_BN_CLICKED(IDC_BUTTON_SADD, OnButtonSadd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg message handlers

BOOL CSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	AddTree();
	//设置list控件的文字和背景颜色
	m_oListsmateriel.SetBkColor(RGB(255,255,255));
	m_oListsmateriel.SetTextBkColor(RGB(161,223, 212));
	

	//清空list控件的数据
	for(int delcolumn=100;delcolumn>=0;delcolumn--)
		m_oListsmateriel.DeleteColumn(delcolumn);
	//设置list对话框的列
	DWORD dwStyle;
	RECT rect;
	LV_COLUMN lvc;

	dwStyle = m_oListsmateriel.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS ;

	m_oListsmateriel.SetExtendedStyle(dwStyle);
	m_oListsmateriel.GetClientRect(&rect);

	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH |LVCF_FMT;
	lvc.fmt=LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = _T("名称");
	lvc.cx = 140;
	m_oListsmateriel.InsertColumn(1,&lvc);

	lvc.iSubItem = 1;
	lvc.pszText = _T("价格");
	lvc.cx = 80;
	m_oListsmateriel.InsertColumn(2,&lvc);

	lvc.iSubItem = 2;
	lvc.pszText = _T("ID");
	lvc.cx = 0;
	m_oListsmateriel.InsertColumn(3,&lvc);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectDlg::AddTree()
{
	TVINSERTSTRUCT tvInsert;
	HTREEITEM hParent;
	_RecordsetPtr m_pTRecordset; //Must define it in function!!!Becourse this is a RECURSION function.
	CString sroot,sql;

	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;

//	tvInsert.item.pszText = _T("root");
	hParent = m_oTreesclass.InsertItem(&tvInsert);//HTREEITEM of root.

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
		errormessage.Format("[商品资料] Addtree Class error:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
//	tvInsert.item.pszText = _T("root");
	if(sroot!="")
	{
//		tvInsert.item.pszText =_T("");
		hParent = m_oTreesclass.InsertItem(&tvInsert);//HTREEITEM of root.

		AddSubTree("RootClass",hParent);//Here strChildTree just must not equal "root",can be anyother string.
	}
//	AddSubTree("1",hParent);//Here strChildTree just must not equal "root",can be anyother string.

	m_oTreesclass.Expand(hParent,TVE_EXPAND);
}

void CSelectDlg::AddSubTree(CString ParTree, HTREEITEM hPartItem)
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
				hCurrent = m_oTreesclass.InsertItem((LPCTSTR)(_bstr_t)(m_pTRecordset->GetCollect("NAME")), hPartItem, NULL);//Insert an item into current parent.
					
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
		temp.Format("[商品资料] Read sub tree error:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
}

void CSelectDlg::OnSelchangedTreeSclass(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CString sql,sql1;
	long lclassid;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!
	HTREEITEM hCurItem;

	hCurItem=m_oTreesclass.GetSelectedItem ();//Get Current item and its sub items.
	curtext=m_oTreesclass.GetItemText(hCurItem);//Read current item text into edit control.
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
		temp.Format("获取分类名称出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}

	sclassid.Format("%d",lclassid);
	sql1="Select * from MATERIEL where CLASSID="+sclassid+" and SUPPLY=1";
	ReadtoList(sql1);

	UpdateData(false);	
	*pResult = 0;
}

void CSelectDlg::ReadtoList(CString sql)
{
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	//删除所有list中的数据。
	m_oListsmateriel.DeleteAllItems();

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
				m_oListsmateriel.InsertItem(&lvitem);
				//读出数据写入到list中
				m_oListsmateriel.SetItemText(numline,0,(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("NAME"));
				float fprice=(float)m_pRecordset->GetCollect("PRICE");
				CString sprice;
				sprice.Format("%.2f",fprice);
				m_oListsmateriel.SetItemText(numline,1,sprice);
				long lmid=(long)m_pRecordset->GetCollect("ID");
				CString smid;
				smid.Format("%d",lmid);
				m_oListsmateriel.SetItemText(numline,2,smid);

				numline++;
				m_pRecordset->MoveNext();
			}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString temp;
		temp.Format("列表读入商品出错:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return;
	}
}

void CSelectDlg::OnClickListSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//得到当前选中的行
	POSITION pos = m_oListsmateriel.GetFirstSelectedItemPosition();
	//如果选中一行
	if(pos)
	{
		int nItem = m_oListsmateriel.GetNextSelectedItem(pos);
		theApp.smID=m_oListsmateriel.GetItemText(nItem,2);
		theApp.sprice=m_oListsmateriel.GetItemText(nItem,1);
		theApp.smname=m_oListsmateriel.GetItemText(nItem,0);
	}

	*pResult = 0;
}

void CSelectDlg::OnButtonSadd() 
{
	//When the OK button is click down,send a message(WM_APPLY) to the CMyDBgridDlgDlg.
	if(theApp.smname=="")
	{
		AfxMessageBox("请选择商品!");
		return;
	}
	else
		LRESULT Res=::SendMessage(theApp.pWnd, WM_APPLY, 0, 0);
	CDialog::OnOK();	
}
