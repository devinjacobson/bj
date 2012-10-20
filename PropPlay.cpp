// PropPlay.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "PropPlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPlay property page

IMPLEMENT_DYNCREATE(CPropPlay, CPropertyPage)

CPropPlay::CPropPlay() : CPropertyPage(CPropPlay::IDD)
{
	//{{AFX_DATA_INIT(CPropPlay)
	m_nNumPlayers = 5;
	m_nPlaySpeed = 2;
	m_nPenetration = 80;
	//}}AFX_DATA_INIT
}

CPropPlay::~CPropPlay()
{
}

void CPropPlay::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPlay)
	DDX_Text(pDX, IDC_EDIT_NUM_PLAYERS, m_nNumPlayers);
	DDV_MinMaxInt(pDX, m_nNumPlayers, 1, 5);
	DDX_Text(pDX, IDC_EDIT_PLAY_SPEED, m_nPlaySpeed);
	DDV_MinMaxInt(pDX, m_nPlaySpeed, 1, 10);
	DDX_Text(pDX, IDC_EDIT_PENETRATION, m_nPenetration);
	DDV_MinMaxInt(pDX, m_nPenetration, 50, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPlay, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPlay)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPlay message handlers
