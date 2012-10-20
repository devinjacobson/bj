// CountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "CountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCountDlg dialog


CCountDlg::CCountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCountDlg)
	m_nCount = 0;
	//}}AFX_DATA_INIT
}


void CCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCountDlg)
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCountDlg, CDialog)
	//{{AFX_MSG_MAP(CCountDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCountDlg message handlers
