//Download by http://www.NewXing.com
// ClassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "ClassDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassDlg dialog
extern CMyPosApp theApp;


CClassDlg::CClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClassDlg)
	m_classname = _T("");
	m_radiodiscount = -1;
	m_tempid = 0;
	//}}AFX_DATA_INIT
}


void CClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClassDlg)
	DDX_Control(pDX, IDC_RADIO1_DISCOUNT, m_oRadiodiscount);
	DDX_Control(pDX, IDC_EDIT_CLASSNAME, m_oClassname);
	DDX_Control(pDX, IDC_TREE_CLASS, m_oTreeclass);
	DDX_Text(pDX, IDC_EDIT_CLASSNAME, m_classname);
	DDX_Radio(pDX, IDC_RADIO1_DISCOUNT, m_radiodiscount);
	DDX_Text(pDX, IDC_TEMPID, m_tempid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClassDlg, CDialog)
	//{{AFX_MSG_MAP(CClassDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CLASS, OnSelchangedTreeClass)
	ON_BN_CLICKED(IDC_BUTTON_ADDSAME, OnButtonAddsame)
	ON_BN_CLICKED(IDC_BUTTON_ADDSUB, OnButtonAddsub)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassDlg message handlers

void CClassDlg::OnSelchangedTreeClass(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CString sql;
	CString curtext;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!
	HTREEITEM hCurItem;

	hCurItem=m_oTreeclass.GetSelectedItem ();//Get Current item and its sub items.
	curtext=m_oTreeclass.GetItemText(hCurItem);//Read current item text into edit control.
	m_classname=curtext;
	sql="SELECT * FROM MATERIELCLASS where NAME='"+curtext+"'";
	try
	{
		m_tempid=0;
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);
		if(!m_pRecordset->adoEOF)
		{
			m_tempid=(long)(m_pRecordset->GetCollect("ID"));
			Curpar=VariantToCString(m_pRecordset->GetCollect("PARENT"));

			if((float)(m_pRecordset->GetCollect("DISCOUNT"))==0)
				m_radiodiscount=0;
			if((float)(m_pRecordset->GetCollect("DISCOUNT"))==1)
				m_radiodiscount=1;
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		 CString errormessage;
		 MessageBox("读取单选按钮出错！",m_classname);
	}

	UpdateData(false);

	*pResult = 0;
}

void CClassDlg::AddSubTree(CString ParTree, HTREEITEM hPartItem)
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
				hCurrent = m_oTreeclass.InsertItem((LPCTSTR)(_bstr_t)(m_pTRecordset->GetCollect("NAME")), hPartItem, NULL);//Insert an item into current parent.
					
				curID=VariantToCString(m_pTRecordset->GetCollect("ID"));
				if (TreeSumRecordCount(curID)>0)
					AddSubTree(VariantToCString(m_pTRecordset->GetCollect("ID")),hCurrent);//Recursion.			
				
				if (!m_pTRecordset->adoEOF)
					m_pTRecordset->MoveNext();
			}
		}
		m_pTRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		 CString errormessage;
		 MessageBox("读取类别子树出错！",ParTree);
	}
}

void CClassDlg::AddTree()
{
	TVINSERTSTRUCT tvInsert;
	HTREEITEM hParent;
	_RecordsetPtr m_pTRecordset; //Must define it in function!!!Becourse this is a RECURSION function.
	CString sroot,sql;

	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;

	sql="SELECT * FROM MATERIELCLASS where ID=1";
	try
	{
		m_pTRecordset.CreateInstance("ADODB.Recordset");
		m_pTRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockOptimistic,adCmdText);

		if(!m_pTRecordset->adoEOF)
			sroot=(LPTSTR)(_bstr_t)m_pTRecordset->GetCollect("NAME");//Insert an item into current parent.
		m_pTRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("读取类别树出错:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
	tvInsert.item.pszText = _T("root");
	if(sroot!="")
	{
		//tvInsert.item.pszText =_T("");//User this line to give the tree a sum root.
		hParent = m_oTreeclass.InsertItem(&tvInsert);//HTREEITEM of root.

//		AddSubTree("1",hParent);//Here strChildTree just must not equal "root",can be anyother string.
		AddSubTree("RootClass",hParent);//Here strChildTree just must not equal "root",can be anyother string.
	}
	m_oTreeclass.Expand(hParent,TVE_EXPAND);
}

int CClassDlg::TreeSumRecordCount(CString strFieldValue)
{
	int Sum=0;
	CString sql;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	sql="SELECT * FROM MATERIELCLASS where PARENT ='";
	sql=sql+strFieldValue+"'";
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockPessimistic,adCmdText);

		if(!m_pRecordset->BOF)//If current record is not the first record.
		{
			m_pRecordset->MoveFirst ();		
			while(!m_pRecordset->adoEOF)
			{
				Sum+=1;
				m_pRecordset->MoveNext ();
			}	
		}
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("计算类别总数出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	return Sum;
}

CString CClassDlg::VariantToCString(VARIANT var)
{
	CString strValue;
	_variant_t var_t;
	_bstr_t bst_t;
	time_t cur_time;
	CTime time_value;
	COleCurrency var_currency;
	switch(var.vt)
	{
	case VT_EMPTY:strValue=_T("");break;
	case VT_UI1:strValue.Format ("%d",var.bVal);break;
	case VT_I2:strValue.Format ("%d",var.iVal );break;
	case VT_I4:strValue.Format ("%d",var.lVal);break;
	case VT_R4:strValue.Format ("%f",var.fltVal);break;
	case VT_R8:strValue.Format ("%f",var.dblVal);break;
	case VT_CY:
		var_currency=var;
		strValue=var_currency.Format(0);
		break;
	case VT_BSTR:
		var_t=var;
		bst_t=var_t;
		strValue.Format ("%s",(const char*)bst_t);
		break;
	case VT_NULL:strValue=_T("");break;
	case VT_DATE:
		cur_time=var.date;
		time_value=cur_time;
		strValue=time_value.Format("%A,%B%d,%Y");
		break;
	case VT_BOOL:strValue.Format ("%d",var.boolVal );break;
	default:strValue=_T("");break;
	}

	return strValue;
}

BOOL CClassDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	AddTree();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClassDlg::OnButtonAddsame() 
{
	CString sql;
	CString newclassname,Newpar,snewid;
	long lNewID;//Get new record id.
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	hParentItem=m_oTreeclass.GetParentItem(m_oTreeclass.GetSelectedItem ());//Get parent item handle.
	
	lNewID=GenNewID();//Call the "GenNewID" function to get a new ID.
	snewid.Format("%d",lNewID);
	Newpar=Curpar;
	newclassname.Format("新类别%d",lNewID);	

	try
	{
		_variant_t RecordsAffected;
		sql="Insert into MATERIELCLASS (ID,NAME,DISCOUNT,PARENT) VALUES ('"+snewid+"','"+newclassname+"','0','"+Newpar+"')";
		if(lNewID==1)
			sql="Insert into MATERIELCLASS (ID,NAME,DISCOUNT,PARENT) VALUES (1,'"+newclassname+"','0','RootClass')";
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("增加同级分类出错:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
	m_oClassname.SetWindowText(newclassname);
	m_oTreeclass.InsertItem((LPCTSTR)(_bstr_t)(newclassname), hParentItem, NULL);//Insert an item into current parent.
}

void CClassDlg::OnButtonAddsub() 
{
	CString sql;
	CString newclassname,Newpar,snewid;	
	long lNewID;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	hCurrentItem=m_oTreeclass.GetSelectedItem ();//Get current item handle as sub's parent.

	lNewID=GenNewID();
	snewid.Format("%d",lNewID);
	Newpar.Format("%d",m_tempid);
	newclassname.Format("新类别%d",lNewID);

	try
	{
		_variant_t RecordsAffected;
		sql="Insert into MATERIELCLASS (ID,NAME,DISCOUNT,PARENT) VALUES ('"+snewid+"','"+newclassname+"','0','"+Newpar+"')";
		if(lNewID==1)
			sql="Insert into MATERIELCLASS (ID,NAME,DISCOUNT,PARENT) VALUES (1,'"+newclassname+"','0','RootClass')";
		theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("增加下级分类出错:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
	m_oClassname.SetWindowText(newclassname);
	m_oTreeclass.InsertItem((LPCTSTR)(_bstr_t)(newclassname), hCurrentItem, NULL);//Insert an item into current parent.
}

void CClassDlg::OnButtonDel() 
{
	CString sql,curID;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	HTREEITEM hCurItem;

	hCurItem=m_oTreeclass.GetSelectedItem ();//Get Current item and its sub items.

	sql="SELECT * FROM MATERIELCLASS where NAME ='";
	sql=sql+m_classname+"'";

	if(AfxMessageBox("确定删除此类别吗？",MB_YESNO)==IDYES)
	{
		try
		{
			m_pRecordset.CreateInstance("ADODB.Recordset");
			m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenDynamic,adLockPessimistic,adCmdText);

			if(!m_pRecordset->BOF)//If current record is not the first record.
			{
				curID=VariantToCString(m_pRecordset->GetCollect("ID"));
				if(atol(curID)==1)
				{
					MessageBox("不能删除ID为1的类别！",m_classname);
					return;
				}
				if (TreeSumRecordCount(curID)==0)
				{
					if(CountMateriel(curID)>0)
						MessageBox("此类别下已有商品，不能删除！");
					else
					{
						m_pRecordset->Delete(adAffectCurrent);///删除当前记录
						m_oTreeclass.DeleteItem(hCurItem);
					}
				}
				if (TreeSumRecordCount(curID)>0)
					MessageBox("不能删除结点类别！",m_classname);
			}
			m_pRecordset->Update();
		m_pRecordset->Close();
		}
		catch(_com_error e)///捕捉异常
		{
			CString errormessage;
			MessageBox("删除类别出错！",m_classname);
		}
	}
}

void CClassDlg::OnButtonSave() 
{
	CString sql,parent,name,sdiscount;//,stempid
	long discount;

	UpdateData();
	//检查数据完整性
	if(m_classname.IsEmpty())
	{
		AfxMessageBox("类别名称不能为空！");
		return;
	}

	m_oClassname.GetWindowText(name);//Get the current text in edit.

	if(bRepeat(name)==TRUE)
	{
		AfxMessageBox("类别名称重复！请重新输入！");
		return;
	}

	if(AfxMessageBox("确定要保存修改吗？",MB_YESNO)==IDYES)
	{
		int nDiscount=GetCheckedRadioButton(IDC_RADIO1_DISCOUNT,IDC_RADIO2_DISCOUNT); 
		switch(nDiscount)//Get if it is discount.
		{
		case IDC_RADIO1_DISCOUNT:
			discount=0;
			break;
		case IDC_RADIO2_DISCOUNT:
			discount=1;
			break;
		default:
			break;
		}
		sdiscount.Format("%d",discount);
//		stempid.Format("%d",m_tempid);

		try
		{
			_variant_t RecordsAffected;
//			sql="Update MATERIELCLASS set NAME='"+name+"',DISCOUNT='"+sdiscount+"' where ID='"+stempid+"'";
			sql.Format("Update MATERIELCLASS set NAME='%s',DISCOUNT=%d where ID=%d",name,discount,m_tempid);//Must add''!!!
			theApp.m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
				
			hCurrentItem=m_oTreeclass.GetSelectedItem ();//Get current item handle as sub's parent.
			m_oTreeclass.SetItemText(hCurrentItem,(LPCTSTR)(_bstr_t)(name));
		}
		catch(_com_error e)///捕捉异常
		{
			CString stemp;
			stemp.Format("修改类别出错:%s",e.ErrorMessage());//
			AfxMessageBox(stemp);
			return;
		}
	}
}

BOOL CClassDlg::bRepeat(CString strFieldValue)
{
	CString sql;
	BOOL br;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT * FROM MATERIELCLASS WHERE NAME='";
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
		stemp.Format("查找类别名称出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
		return br;
}

int CClassDlg::GenNewID()
{
	CString sql;
	int NewID;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!
	
	sql="SELECT Max(ID) FROM MATERIELCLASS";
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

int CClassDlg::CountMateriel(CString sclassid)
{
	CString sql;
	int ncount;
	_RecordsetPtr m_pRecordset; //Must define it in function!!!!

	sql="SELECT count(*) as XXX FROM MATERIEL where classid="+sclassid+"";
	try
	{ 
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

		ncount =(long)m_pRecordset->GetCollect("XXX");
		m_pRecordset->Close();
	}
	catch(_com_error e)///捕捉异常
	{
		CString stemp;
		stemp.Format("计算类别下商品数量出错:%s",e.ErrorMessage());
		AfxMessageBox(stemp);
	}
	return ncount;
}
