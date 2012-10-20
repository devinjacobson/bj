// PropStrategy.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "PropStrategy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropStrategy property page

IMPLEMENT_DYNCREATE(CPropStrategy, CPropertyPage)

CPropStrategy::CPropStrategy() : CPropertyPage(CPropStrategy::IDD)
{
	//{{AFX_DATA_INIT(CPropStrategy)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropStrategy::~CPropStrategy()
{
}

void CPropStrategy::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropStrategy)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropStrategy, CPropertyPage)
	//{{AFX_MSG_MAP(CPropStrategy)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropStrategy message handlers
