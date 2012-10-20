// bj.h : main header file for the BJ application
//

#if !defined(AFX_BJ_H__2C6FD4E1_288C_418B_81FE_D72237D26925__INCLUDED_)
#define AFX_BJ_H__2C6FD4E1_288C_418B_81FE_D72237D26925__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBjApp:
// See bj.cpp for the implementation of this class
//

class CBjApp : public CWinApp
{
public:
	CBjApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBjApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBjApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BJ_H__2C6FD4E1_288C_418B_81FE_D72237D26925__INCLUDED_)
