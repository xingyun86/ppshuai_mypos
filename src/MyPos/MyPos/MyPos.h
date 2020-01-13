//Download by http://www.NewXing.com
// MyPos.h : main header file for the MYPOS application
//

#if !defined(AFX_MYPOS_H__AF4613E9_F506_47E1_870C_DDDF4A4DA870__INCLUDED_)
#define AFX_MYPOS_H__AF4613E9_F506_47E1_870C_DDDF4A4DA870__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyPosApp:
// See MyPos.cpp for the implementation of this class
//

class CMyPosApp : public CWinApp
{
public:
	BOOL VerifyPower(CString power);
	CString addpwd(CString pwd,bool in);
	_ConnectionPtr m_pConnection;
	CString name;
	CString pwd;
	CString smname;
	CString sprice;
	CString smID;
	CString sqa;
	CString scallid;
	CString sconsume;
	CString sactsum;
	HWND pWnd;//Send message.
	HWND pWndoff;//Send message.
	CMyPosApp();
	CString spaymodep,snowtimep;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPosApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyPosApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPOS_H__AF4613E9_F506_47E1_870C_DDDF4A4DA870__INCLUDED_)
