// BJSettings.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "BJSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBJSettings

IMPLEMENT_DYNAMIC(CBJSettings, CPropertySheet)

CBJSettings::CBJSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CBJSettings::CBJSettings(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CBJSettings::~CBJSettings()
{
}


BEGIN_MESSAGE_MAP(CBJSettings, CPropertySheet)
	//{{AFX_MSG_MAP(CBJSettings)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBJSettings message handlers
