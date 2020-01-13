//Download by http://www.NewXing.com
// OffdutyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPos.h"
#include "OffdutyDlg.h"
#include "MyPosDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COffdutyDlg dialog
extern CMyPosApp theApp;


COffdutyDlg::COffdutyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COffdutyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COffdutyDlg)
	//}}AFX_DATA_INIT
}


void COffdutyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COffdutyDlg)
	DDX_Control(pDX, IDC_EDIT_OFFRFMONEY, m_oOffrfmoney);
	DDX_Control(pDX, IDC_EDIT_OFFRF, m_oOffrf);
	DDX_Control(pDX, IDC_LIST3, m_oHanglist);
	DDX_Control(pDX, IDC_LIST2, m_oNonchecklist);
	DDX_Control(pDX, IDC_LIST1, m_oMoneylist);
	DDX_Control(pDX, IDC_EDIT_OFFBILLS, m_oOffbills);
	DDX_Control(pDX, IDC_EDIT_OFFTIME, m_oOfftime);
	DDX_Control(pDX, IDC_EDIT_OFFPEOPLES, m_oOffpeoples);
	DDX_Control(pDX, IDC_EDIT_CHECKMAN, m_oCheckman);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COffdutyDlg, CDialog)
	//{{AFX_MSG_MAP(COffdutyDlg)
	ON_BN_CLICKED(IDC_BUTTON_OFFPRINT, OnButtonOffprint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COffdutyDlg message handlers

void COffdutyDlg::OnOK() 
{
	//When the offduty button is click down,send a message(WM_OFFDUTY) to the CPosDlg.
	LRESULT Res=::SendMessage(theApp.pWndoff, WM_OFFDUTY, 0, 0);
	
	CDialog::OnOK();
}

BOOL COffdutyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	_RecordsetPtr m_pRecordset;
	//�õ�ϵͳʱ��
	CTime now=CTime::GetCurrentTime();
	CString snowtime=now.Format(_T("%Y-%m-%d %H:%M:%S"));
	m_oCheckman.SetWindowText(theApp.name);
	m_oOfftime.SetWindowText(snowtime);
	CString starttime,stime;
	starttime=snowtime.Left(10);
	stime=snowtime.Mid(11,2);

	if(atoi(stime)>8)
		starttime=starttime+" 08:00:00";
	else
	{
		CString smonth=starttime.Mid(5,2);
		int imonth=atoi(smonth);
		CString sday=starttime.Right(2);

		starttime=YearMonthDay("2003",smonth,sday);
		starttime=starttime+" 08:00:00";
	}

	_variant_t vtemp;
	//RMB Checkout bills stat.
	CString soffsum="0.00",speoplesum="0",sbillsum="0",space=" ";
	long lbillsum=0,lpeoplesum=0;
	float foffsum=0,fttl=0;
	int i,n;
	CString sql;
	sql="Select sum(ACTTOTAL) as XXX, sum(PEOPLES) as PPP, count(*) as NNN from (Select * from SALEBILL where ENDDATE>'"+starttime+
		"' and ENDDATE<'"+snowtime+"') where SALES='"+theApp.name+"' and STATUS='�ѽ���' and PAYMODE<>88";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		vtemp=m_pRecordset->GetCollect("XXX");
		if(vtemp.dblVal>0)
			foffsum=vtemp.dblVal;
		vtemp=m_pRecordset->GetCollect("NNN");
		if(vtemp.lVal>0)
			lbillsum=vtemp.lVal;
		vtemp=m_pRecordset->GetCollect("PPP");
		if(vtemp.iVal>0)
			lpeoplesum=vtemp.iVal;
//		lpeoplesum=(long)m_pRecordset->GetCollect("PPP");
		soffsum.Format("%.2f",foffsum);
		if(lpeoplesum>0)
			speoplesum.Format("%d",lpeoplesum);
		sbillsum.Format("%d",lbillsum);
		fttl=foffsum;
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[�°�]��������ܽ�����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return FALSE;
	}
	m_oOffbills.SetWindowText(sbillsum);
	m_oOffpeoples.SetWindowText(speoplesum);
	n=17-soffsum.GetLength();
	for(i=0;i<n-1;i++)
		space=space+" ";
	m_oMoneylist.AddString("�����:"+space+soffsum);
	//Non-RMB Checkout bills stat.
	sql="Select sum(ACTTOTAL) as XXX from (Select * from SALEBILL where ENDDATE>'"+starttime+
		"' and ENDDATE<'"+snowtime+"') where SALES='"+theApp.name+"' and STATUS='�ѽ���' and PAYMODE<>1 and PAYMODE<>88";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		vtemp=m_pRecordset->GetCollect("XXX");
		foffsum=vtemp.dblVal;
		soffsum="0.00";
		if(foffsum>0)
		{
			soffsum.Format("%.2f",foffsum);
			fttl=fttl+foffsum;
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[�°�]���������ҽ����ܽ�����:%s",e.ErrorMessage());
		AfxMessageBox(temp);
		return FALSE;
	}
	n=17-soffsum.GetLength();
	space=" ";
	for(i=0;i<n-1;i++)
		space=space+" ";
	m_oMoneylist.AddString("�䡡��:"+space+soffsum);
	soffsum.Format("%.2f",fttl);
	n=17-soffsum.GetLength();
	space=" ";
	for(i=0;i<n-1;i++)
		space=space+" ";
	m_oMoneylist.AddString("�ϡ���:"+space+soffsum);	
	//Noncheck bills and hang bills.
	sql="Select ID,TOTAL,STATUS from (Select * from SALEBILL where BEGINDATE>'"+starttime+
		"' and BEGINDATE<'"+snowtime+"') where STATUS<>'�ѽ���'";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		float ftotal=0,ftotal1=0;
		while(!m_pRecordset->adoEOF)
		{
			CString sbillid,sbilltotal,status;
			sbillid=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("ID");
			float fbilltotal=(float)m_pRecordset->GetCollect("TOTAL");
			sbilltotal.Format("%.2f",fbilltotal);
			status=(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("STATUS");
			n=10-sbilltotal.GetLength();
			space=" ";
			for(i=0;i<n-1;i++)
				space=space+" ";
			if(status=="�ȴ�")
			{
				m_oNonchecklist.AddString(sbillid+space+sbilltotal);
				ftotal=ftotal+fbilltotal;
			}
			if(status=="����")
			{
				m_oHanglist.AddString(sbillid+space+sbilltotal);
				ftotal1=ftotal1+fbilltotal;
			}
			m_pRecordset->MoveNext();
		}
		CString stotal;
		stotal.Format("%.2f",ftotal);
		n=17-stotal.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";
		m_oNonchecklist.AddString("�ϡ���:"+space+stotal);
		stotal.Format("%.2f",ftotal1);
		n=17-stotal.GetLength();
		space=" ";
		for(i=0;i<n-1;i++)
			space=space+" ";
		m_oHanglist.AddString("�ϡ���:"+space+stotal);
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[�°�]����δ���ʵ��ݺ͹��ʳ���:%s",e.ErrorMessage());
		return FALSE;
		AfxMessageBox(temp);
	}	
	//RF bills stat.
	CString srfsum="0.00";
	float frfsum;
	sql="Select sum(TOTAL) as XXX, count(*) as NNN from (Select * from SALEBILL where ENDDATE>'"+starttime+
		"' and ENDDATE<'"+snowtime+"') where SALES='"+theApp.name+"' and STATUS='�ѽ���' and PAYMODE=88";
	try
	{ 	
		m_pRecordset.CreateInstance("ADODB.Recordset");
		m_pRecordset->Open((_variant_t)sql,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
		vtemp=m_pRecordset->GetCollect("XXX");
		lbillsum=(long)m_pRecordset->GetCollect("NNN");
		sbillsum.Format("%d",lbillsum);
		if(vtemp.dblVal>0)
		{
			frfsum=vtemp.dblVal;
			srfsum.Format("%.2f",frfsum);
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		CString temp;
		temp.Format("[�°�]����RF������:%s",e.ErrorMessage());
		return FALSE;
		AfxMessageBox(temp);
	}
	m_oOffrf.SetWindowText(sbillsum);
	m_oOffrfmoney.SetWindowText(srfsum);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString COffdutyDlg::YearMonthDay(CString y, CString m, CString d)
{
	CString sday,smonth,sy,sdate;
	int ny=atoi(y);
	sy=y;
	int imonth=atoi(m);
	smonth=m;
	int nday=0;
	nday=atoi(d)-1;
	sday.Format("%02d",nday);
	//If it is 1st,Janurary.
	if(nday==0 && imonth==1)
	{
		ny=ny-1;
		sy.Format("%d",ny);
		imonth=12;
		sday="31";
	}
	//If it is 1st of the month.
	if(nday==0)
	{
		switch(imonth)
		{
		case 2:
			sday="31";
			break;
		case 3:
			if(ny%4>0)
				sday="28";
			else
				sday="29";
			break;
		case 4:
			sday="31";
			break;
		case 5:
			sday="30";
			break;
		case 6:
			sday="31";
			break;
		case 7:
			sday="30";
			break;
		case 8:
			sday="31";
			break;
		case 9:
			sday="31";
			break;
		case 10:
			sday="30";
			break;
		case 11:
			sday="31";
			break;
		case 12:
			sday="30";
			break;
		default:
			break;
		}
		imonth=imonth-1;
		smonth.Format("%2d",imonth);
	}
	sdate=sy+"-"+smonth+"-"+sday;

	return sdate;
}

void COffdutyDlg::OnButtonOffprint() 
{
	int i,ncount;	
	CDC dc;
	//�Ѵ�ӡ�豸�������ӵ�DC����
	CPrintDialog pdlg(FALSE,PD_NOPAGENUMS|PD_NOSELECTION,this);
	BOOL bFindPrinter=pdlg.GetDefaults();
	if(!bFindPrinter)
		return;
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
	//ÿҳ�������
	int nMaxLinePerPage = nPageHeight/nCharHeight -3;
	int nCurPage =1;
	//ҳ�߾�
	int nXMargin = 2;
	int nYMargin = 2;

	//���������ӡֽ����Ŀ
	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = "Report printing"; 
	di.lpszOutput = (LPTSTR) NULL; 
	di.lpszDatatype = (LPTSTR) NULL; 
	di.fwType = 0; 
	dc.StartDoc(&di);
	dc.StartPage();

	//�����������
	CString stitle,sftitle;
	stitle="�����ձ���";
	sftitle.Format("%23s",stitle);
	dc.TextOut(2, nYMargin+nCharHeight,sftitle, strlen(sftitle));
	stitle="==============";
	sftitle.Format("%25s",stitle);
	dc.TextOut(2, nYMargin+nCharHeight*2,sftitle, strlen(sftitle));

	//�����������
	//���������ڡ�������������RF�����
	CString ssale,sdate,speople,sbills,sRF,sRFtotal,stemp;
	m_oCheckman.GetWindowText(ssale);
	m_oOfftime.GetWindowText(sdate);
	m_oOffpeoples.GetWindowText(speople);
	m_oOffbills.GetWindowText(sbills);
	m_oOffrf.GetWindowText(sRF);
	m_oOffrfmoney.GetWindowText(sRFtotal);
	stemp.Format("%-7s",ssale);//use stemp save ssale's value.
	ssale="����:"+stemp+"����:"+sdate;
	dc.TextOut(2, nYMargin+nCharHeight*3,ssale, strlen(ssale));//Out put the first line.
	stemp.Format("%-7s",speople);//use stemp save ssale's value.
	speople="����:"+stemp+"����:"+sbills;
	dc.TextOut(2, nYMargin+nCharHeight*4,speople, strlen(speople));//Out put the first line.
	stemp.Format("%-7s",sRF);//use stemp save ssale's value.
	sRF="R  F:"+stemp+"RF���:"+sRFtotal;
	dc.TextOut(2, nYMargin+nCharHeight*5,sRF, strlen(sRF));//Out put the first line.
	//��������������
	stitle="-------------�������-------------";
	dc.TextOut(2, nYMargin+nCharHeight*7,stitle, strlen(stitle));
	ncount=m_oMoneylist.GetCount();
	CString sline;
	for(i=0; i<ncount; i++)
	{
		if(ncount+7-(nCurPage-1)*nMaxLinePerPage > nMaxLinePerPage)
		{
			//�µ�һҳ
			dc.EndPage();
			dc.StartPage();
			nCurPage ++;
		}
		m_oMoneylist.GetText(i, sline);//�õ�ѡ������ı�
		dc.TextOut( 2, nYMargin+(i+8-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
					sline, strlen(sline));
	}
	//���δ�ᵥ������
	stitle="-------------δ�ᵥ��-------------";
	dc.TextOut(2, nYMargin+nCharHeight*(ncount+8),stitle, strlen(stitle));
	int ncount1=m_oNonchecklist.GetCount();
	for(i=0; i<ncount1; i++)
	{
		if(ncount+ncount1+7-(nCurPage-1)*nMaxLinePerPage > nMaxLinePerPage)
		{
			//�µ�һҳ
			dc.EndPage();
			dc.StartPage();
			nCurPage ++;
		}
		m_oNonchecklist.GetText(i, sline);//�õ�ѡ������ı�
		dc.TextOut( 2, nYMargin+(i+ncount+9-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
					sline, strlen(sline));
	}
	//������ʵ�������
	stitle="-------------���ʵ���-------------";
	dc.TextOut(2, nYMargin+nCharHeight*(ncount1+ncount+9),stitle, strlen(stitle));
	int ncount2=m_oHanglist.GetCount();
	for(i=0; i<ncount2; i++)
	{
		if(ncount+7-(nCurPage-1)*nMaxLinePerPage > nMaxLinePerPage)
		{
			//�µ�һҳ
			dc.EndPage();
			dc.StartPage();
			nCurPage ++;
		}
		m_oHanglist.GetText(i, sline);//�õ�ѡ������ı�
		dc.TextOut( 2, nYMargin+(i+ncount1+ncount+10-(nCurPage-1)*nMaxLinePerPage)*nCharHeight, 
					sline, strlen(sline));
	}

	dc.EndPage();
	dc.EndDoc();
	//��ӡ����
	//���Ҫ���ǽ����廹ԭ����һ���Ǳ����
	dc.SelectObject(def_font); //�ָ�ԭ��������
	font.DeleteObject(); 

	DeleteDC(dc.Detach()); 		
}
