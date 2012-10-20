// PropCasino.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "PropCasino.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropCasino property page

BOOL CPropCasino::m_nDAS;
BOOL	CPropCasino::m_nCanDoubleAces;
BOOL	CPropCasino::m_nCanDouble1011;
BOOL	CPropCasino::m_nCanDouble9;
BOOL	CPropCasino::m_nCanDouble8Below;
BOOL	CPropCasino::m_nCanSplitAces;
int CPropCasino::m_nNumSplits;

IMPLEMENT_DYNCREATE(CPropCasino, CPropertyPage)

CPropCasino::CPropCasino() : CPropertyPage(CPropCasino::IDD)
{
	//{{AFX_DATA_INIT(CPropCasino)
	m_nDAS = FALSE;
	m_nHitSoft17 = FALSE;
	m_nNumDecks = 6;
	m_nCanDoubleAces = TRUE;
	m_nCanDouble1011 = TRUE;
	m_nCanDouble9 = TRUE;
	m_nCanDouble8Below = TRUE;
	m_nCanSplitAces = TRUE;
	m_nNumSplits = 2;
	//}}AFX_DATA_INIT
}

CPropCasino::~CPropCasino()
{
}

void CPropCasino::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropCasino)
	DDX_Check(pDX, IDC_CHECK_DAS_ALLOWED, m_nDAS);
	DDX_Check(pDX, IDC_CHECK_HIT_SOFT17, m_nHitSoft17);
	DDX_Text(pDX, IDC_EDIT_NUM_DECKS, m_nNumDecks);
	DDV_MinMaxInt(pDX, m_nNumDecks, 1, 12);
	DDX_Text(pDX, IDC_EDIT_NUM_SPLITS, m_nNumSplits);
	DDV_MinMaxInt(pDX, m_nNumSplits, 2, 2);
	DDX_Check(pDX, IDC_CHECK_CAN_DOUBLE_ACES, m_nCanDoubleAces);
	DDX_Check(pDX, IDC_CHECK_CAN_DOUBLE_1011, m_nCanDouble1011);
	DDX_Check(pDX, IDC_CHECK_CAN_DOUBLE_9, m_nCanDouble9);
	DDX_Check(pDX, IDC_CHECK_CAN_DOUBLE_ACES4, m_nCanDouble8Below);
	DDX_Check(pDX, IDC_CHECK_CAN_SPLIT_ACES, m_nCanSplitAces);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropCasino, CPropertyPage)
	//{{AFX_MSG_MAP(CPropCasino)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropCasino message handlers
