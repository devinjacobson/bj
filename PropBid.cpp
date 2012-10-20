// PropBid.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "PropBid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropBid property page

IMPLEMENT_DYNCREATE(CPropBid, CPropertyPage)

CPropBid::CPropBid() : CPropertyPage(CPropBid::IDD)
{
	//{{AFX_DATA_INIT(CPropBid)
	m_nHighBet= 5;
	m_nLowBet = 1;
	//}}AFX_DATA_INIT
}

CPropBid::~CPropBid()
{
}

void CPropBid::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropBid)
	DDX_Text(pDX, IDC_EDIT_HIGH_BID, m_nHighBet);
	DDV_MinMaxInt(pDX, m_nHighBet, 1, 100);
	DDX_Text(pDX, IDC_EDIT_LOW_BID, m_nLowBet);
	DDV_MinMaxInt(pDX, m_nLowBet, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropBid, CPropertyPage)
	//{{AFX_MSG_MAP(CPropBid)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropBid message handlers
