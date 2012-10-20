// DlgCasinoRules.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "DlgCasinoRules.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCasinoRules dialog


CDlgCasinoRules::CDlgCasinoRules(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCasinoRules::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCasinoRules)
	m_nDASAllowed = FALSE;
	m_nHitSoft17 = FALSE;
	m_strDouble = _T("");
	m_strSplit = _T("");
	m_nNumDecks = 0;
	//}}AFX_DATA_INIT
}


void CDlgCasinoRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCasinoRules)
	DDX_Check(pDX, IDC_CHECK_DAS_ALLOWED, m_nDASAllowed);
	DDX_Check(pDX, IDC_CHECK_HIT_SOFT17, m_nHitSoft17);
	DDX_CBString(pDX, IDC_COMBO_DOUBLING, m_strDouble);
	DDX_CBString(pDX, IDC_COMBO_SPLITTING, m_strSplit);
	DDX_Text(pDX, IDC_EDIT_NUM_DECKS, m_nNumDecks);
	DDV_MinMaxInt(pDX, m_nNumDecks, 1, 24);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCasinoRules, CDialog)
	//{{AFX_MSG_MAP(CDlgCasinoRules)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCasinoRules message handlers
