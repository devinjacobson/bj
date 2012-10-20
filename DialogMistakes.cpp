// DialogMistakes.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "DialogMistakes.h"
#include "BjDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMistakes dialog



CDialogMistakes::CDialogMistakes(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMistakes::IDD, pParent)
{
	m_plstMistakes = NULL;
	m_pCurrentHistory = NULL;
	//{{AFX_DATA_INIT(CDialogMistakes)
	m_dBetMistakes = 0.0;
	m_dPlayMistakes = 0.0;
	m_dTotalActual = 0.0;
	m_dTotalMistakes = 0.0;
	m_dTotalPossible = 0.0;
	m_dBetMistakes2 = 0.0;
	m_dPlayMistakes2 = 0.0;
	m_dTotalActual2 = 0.0;
	m_dTotalMistakes2 = 0.0;
	m_dTotalPossible2 = 0.0;
	m_dAvgStandardCount = 0.0;
	m_nHandsPlayed = 0;
	m_dWinPerHand = 0.0;
	m_strTimePlayed = _T("");
	m_nActualWin = 0;
	m_dTheoreticalWin = 0.0;
	//}}AFX_DATA_INIT
}


void CDialogMistakes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogMistakes)
	DDX_Control(pDX, IDC_LIST_MISTAKES_STANDARD, m_listStandardMistakes);
	DDX_Control(pDX, IDC_LIST_MISTAKES, m_listMistakes);
	DDX_Text(pDX, IDC_EDIT_BET_MISTAKES, m_dBetMistakes);
	DDX_Text(pDX, IDC_EDIT_PLAY_MISTAKES, m_dPlayMistakes);
	DDX_Text(pDX, IDC_EDIT_TOTAL_ACTUAL, m_dTotalActual);
	DDX_Text(pDX, IDC_EDIT_TOTAL_MISTAKES, m_dTotalMistakes);
	DDX_Text(pDX, IDC_EDIT_TOTAL_POSSIBLE, m_dTotalPossible);
	DDX_Text(pDX, IDC_EDIT_BET_MISTAKES2, m_dBetMistakes2);
	DDX_Text(pDX, IDC_EDIT_PLAY_MISTAKES2, m_dPlayMistakes2);
	DDX_Text(pDX, IDC_EDIT_TOTAL_ACTUAL2, m_dTotalActual2);
	DDX_Text(pDX, IDC_EDIT_TOTAL_MISTAKES2, m_dTotalMistakes2);
	DDX_Text(pDX, IDC_EDIT_TOTAL_POSSIBLE2, m_dTotalPossible2);
	DDX_Text(pDX, IDC_EDIT_AVG_STANDARD_COUNT, m_dAvgStandardCount);
	DDX_Text(pDX, IDC_EDIT_HANDS_PLAYED, m_nHandsPlayed);
	DDX_Text(pDX, IDC_EDIT_WIN_HAND, m_dWinPerHand);
	DDX_Text(pDX, IDC_EDIT_TIME_PLAYED, m_strTimePlayed);
	DDX_Text(pDX, IDC_EDIT_ACTUAL_WIN, m_nActualWin);
	DDX_Text(pDX, IDC_EDIT_THEORETICAL_WIN, m_dTheoreticalWin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogMistakes, CDialog)
	//{{AFX_MSG_MAP(CDialogMistakes)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_MISTAKES, OnColumnclickListMistakes)
	ON_WM_CANCELMODE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MISTAKES, OnDblclkListMistakes)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MISTAKES_STANDARD, OnDblclkListMistakesStandard)
	ON_COMMAND(ID_MENUITEM_MISTAKES_VIEW_SESSION, OnMenuitemMistakesViewSession)
	ON_COMMAND(ID_MENUITEM_MISTAKES_VIEW_DAY, OnMenuitemMistakesViewDay)
	ON_COMMAND(ID_MENUITEM_MISTAKES_VIEW_MONTH, OnMenuitemMistakesViewMonth)
	ON_COMMAND(ID_MENUITEM_MISTAKES_VIEW_WEEK, OnMenuitemMistakesViewWeek)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_MISTAKES_VIEW_DAY, OnUpdateMenuitemMistakesViewDay)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_MISTAKES_VIEW_MONTH, OnUpdateMenuitemMistakesViewMonth)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_MISTAKES_VIEW_SESSION, OnUpdateMenuitemMistakesViewSession)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_MISTAKES_VIEW_WEEK, OnUpdateMenuitemMistakesViewWeek)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogMistakes message handlers

void CDialogMistakes::OnColumnclickListMistakes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	
	*pResult = 0;
}

BOOL CDialogMistakes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rect;
	m_listMistakes.GetClientRect(&rect);

	m_listMistakes.InsertColumn(0, "Cards Played", LVCFMT_LEFT, rect.Width()*.2);
	m_listMistakes.InsertColumn(1, "Type", LVCFMT_RIGHT, rect.Width()*.2);
	m_listMistakes.InsertColumn(2, "Cost", LVCFMT_LEFT, rect.Width()*.25);
	m_listMistakes.InsertColumn(3, "Date", LVCFMT_LEFT, rect.Width()*.3);
	m_listMistakes.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	m_listStandardMistakes.GetClientRect(&rect);

	m_listStandardMistakes.InsertColumn(0, "Cards Played", LVCFMT_LEFT, rect.Width()*.2);
	m_listStandardMistakes.InsertColumn(1, "Type", LVCFMT_RIGHT, rect.Width()*.2);
	m_listStandardMistakes.InsertColumn(2, "Cost", LVCFMT_LEFT, rect.Width()*.25);
	m_listStandardMistakes.InsertColumn(3, "Date", LVCFMT_LEFT, rect.Width()*.3);
	m_listStandardMistakes.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogMistakes::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}


int CDialogMistakes::MistakeInList(CMistake* pMistake, int nWho){

	int nCount;
	CListCtrl* pListControl;
	if (nWho==0){
		pListControl = &m_listMistakes;
	}
	else{
		pListControl = &m_listStandardMistakes;
	}
	nCount = pListControl->GetItemCount();

	CMistake* p;
	for (int i = 0; i<nCount; i++){
		p = (CMistake*)pListControl->GetItemData(i);
		if (p == pMistake){
			return TRUE;
		}
	}
	return FALSE;
}

void CDialogMistakes::ResetMistakes(int nType){
	m_listMistakes.DeleteAllItems();
	m_listStandardMistakes.DeleteAllItems();
	switch (nType){
	case DAY_MISTAKE:
		m_pCurrentHistory = &CBjDlg::m_DayHistory;
		break;
	case WEEK_MISTAKE:
		m_pCurrentHistory = &CBjDlg::m_WeekHistory;
		break;
	case MONTH_MISTAKE:
		m_pCurrentHistory = &CBjDlg::m_MonthHistory;
		break;
	case YEAR_MISTAKE:
		m_pCurrentHistory = &CBjDlg::m_YearHistory;
		break;
	case SESSION_MISTAKE:
	default:
		m_pCurrentHistory = NULL;//&CBjDlg::m_SessionHistory;
		break;

	}
	//load all of the shit from everything here.
	//dont mess with the pointer list of mistakes in BjDlg
	//load all of the mistakes from the year/month here
	m_dTotalMistakes = 0;
	m_dTotalMistakes2 = 0;
	m_dPlayMistakes = 0;
	m_dPlayMistakes2 = 0;
	LoadHistory();
	LoadMistakes();
}

void CDialogMistakes::LoadHistory(){
	if (m_pCurrentHistory == NULL){
		return;
	}
	CPtrList* pTemp;
	CPtrList* pTemp2;
	pTemp = m_plstMistakes;
	pTemp2 = m_plstStandardMistakes;
	m_plstMistakes = m_pCurrentHistory->m_plstMistakes;
	m_plstStandardMistakes = m_pCurrentHistory->m_plstStandardMistakes;
	LoadMistakes();
	m_plstMistakes = pTemp;
	m_plstStandardMistakes = pTemp2;
}

void CDialogMistakes::LoadMistakes(){
	POSITION pos = m_plstMistakes->GetHeadPosition();
	CMistake* pMistake = NULL;
	char* buf = new char[16];
	int nItem = 0;
	CString strMistake;
		
	while (pos !=NULL){
		pMistake = (CMistake*)m_plstMistakes->GetNext(pos);
		if (MistakeInList(pMistake, 0)){
			continue;
		}
		buf = itoa(pMistake->m_Deck.m_nNumPlayed, buf, 10);
		m_listMistakes.InsertItem(nItem = 0, buf);
		GetMistakeType(pMistake, strMistake);
		if (pMistake->m_nMistake < 0){
			m_dBetMistakes += pMistake->m_dLoss;
			m_dTotalMistakes += pMistake->m_dLoss;
			//bet
		}
		else{
			m_dPlayMistakes += pMistake->m_dLoss*pMistake->m_nBet;
			m_dTotalMistakes += pMistake->m_dLoss*pMistake->m_nBet;
			//mistake play
		}
		m_listMistakes.SetItemText(nItem, 1, strMistake);
		strMistake.Format("%.4f", pMistake->m_dLoss);
		m_listMistakes.SetItemText(nItem, 2, strMistake);
		m_listMistakes.SetItemText(nItem, 3, pMistake->m_Date.Format("%m/%d %H:%M"));
		m_listMistakes.SetItemData(nItem, (DWORD)pMistake);
	}
	pos = m_plstStandardMistakes->GetHeadPosition();
	while (pos !=NULL){
		pMistake = (CMistake*)m_plstStandardMistakes->GetNext(pos);
		if (MistakeInList(pMistake, 1)){
			continue;
		}
		buf = itoa(pMistake->m_Deck.m_nNumPlayed, buf, 10);
		m_listStandardMistakes.InsertItem(nItem = 0, buf);
		GetMistakeType(pMistake, strMistake);
		if (pMistake->m_nMistake < 0){
			m_dBetMistakes2 += pMistake->m_dLoss;
			m_dTotalMistakes2 += pMistake->m_dLoss;
			//bet
		}
		else{
			m_dPlayMistakes2 += pMistake->m_dLoss*pMistake->m_nBet;
			m_dTotalMistakes2 += pMistake->m_dLoss*pMistake->m_nBet;
			//mistake play
		}
		m_listStandardMistakes.SetItemText(nItem, 1, strMistake);
		strMistake.Format("%.4f", pMistake->m_dLoss);
		m_listStandardMistakes.SetItemText(nItem, 2, strMistake);
		m_listStandardMistakes.SetItemText(nItem, 3, pMistake->m_Date.Format("%m/%d %H:%M"));
		m_listStandardMistakes.SetItemData(nItem, (DWORD)pMistake);
	}

	UpdatePossible();
	delete buf;

	//update the total mistakes, look at betting mistakes and others seperately.
}

void CDialogMistakes::UpdatePossible(){
	m_dTotalPossible = CBjDlg::m_dTotalPossible;
	m_dTotalPossible2 = CBjDlg::m_dTotalPossible;
	//add history
	if (m_pCurrentHistory){
		m_dTotalPossible += m_pCurrentHistory->m_dTotalPossible;
		m_dTotalPossible2 += m_pCurrentHistory->m_dTotalPossible2;
	}

	m_dTotalActual = m_dTotalPossible - m_dTotalMistakes;
	m_dTotalActual2 = m_dTotalPossible2 - m_dTotalMistakes2;
	//update the other stats as well
	m_nHandsPlayed = CBjDlg::m_nHandsPlayed;	
	//add history
	if (m_pCurrentHistory){
		m_nHandsPlayed += m_pCurrentHistory->m_nHandsPlayed;
	}

	m_dWinPerHand = m_dTotalActual/m_nHandsPlayed;
	m_dAvgStandardCount = CBjDlg::m_dAvgStandardCount;	
	m_nActualWin = m_pBjDlg->m_DlgPractice.m_nSessionMoney;
	m_dTheoreticalWin = m_dWinPerHand*m_nHandsPlayed*m_pBjDlg->m_nLowBet;
	//add history
	CTimeSpan total = CBjDlg::m_TotalPlayTime;
	if (m_pCurrentHistory){
		m_dAvgStandardCount = (m_dAvgStandardCount*CBjDlg::m_nHandsPlayed + m_pCurrentHistory->m_dAvgStandardCount*m_pCurrentHistory->m_nHandsPlayed);
		m_dAvgStandardCount /= m_nHandsPlayed;
		total += m_pCurrentHistory->m_TimePlayed;
		m_nActualWin += m_pCurrentHistory->m_nRealWin;
	}
	m_strTimePlayed = total.Format("%D days %H:%M");
	//add history
	UpdateData(FALSE);	
}

void CDialogMistakes::GetMistakeType(CMistake* pMistake, CString& strMistake){
	if (pMistake->m_nMistakeType == MISTAKE_PLAY){
		switch(pMistake->m_nMistake){
			case MISTAKE_BET_HIGH:
				strMistake = "Bet High";
				break;
			case MISTAKE_BET_LOW:
				strMistake = "Bet Low";
				break;
			case MISTAKE_HIT:
				strMistake = "Hit";
				break;
			case MISTAKE_NOHIT:
				strMistake = "No Hit";
				break;
			case MISTAKE_SPLIT:
				strMistake = "Split";
				break;
			case MISTAKE_NOSPLIT:
				strMistake = "No Split";
				break;
			case MISTAKE_DOUBLE:
				strMistake = "Double";
				break;
			case MISTAKE_NODOUBLE:
				strMistake = "No Double";
				break;
			default:
				strMistake = " ";
				break;
		}
	}
	else{
		strMistake = "Bet";
	}
}

void CDialogMistakes::OnDblclkListMistakes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nSelection = 0;
	if ((nSelection = m_listMistakes.GetSelectionMark()) > -1){
		CMistake* pMistake = (CMistake*)m_listMistakes.GetItemData(nSelection);
		CWaitCursor wait;
		m_pBjDlg->LoadDlg(pMistake);
		m_pBjDlg->BringWindowToTop();
		wait.Restore();
	}	
	*pResult = 0;
}

void CDialogMistakes::OnDblclkListMistakesStandard(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nSelection = 0;
	if ((nSelection = m_listStandardMistakes.GetSelectionMark()) > -1){
		CMistake* pMistake = (CMistake*)m_listStandardMistakes.GetItemData(nSelection);
		CWaitCursor wait;
		m_pBjDlg->LoadDlg(pMistake);
		m_pBjDlg->BringWindowToTop();
		wait.Restore();
	}		
	*pResult = 0;
}

void CDialogMistakes::OnMenuitemMistakesViewSession() 
{
	ResetMistakes(SESSION_MISTAKE);	
}

void CDialogMistakes::OnMenuitemMistakesViewDay() 
{
	ResetMistakes(DAY_MISTAKE);	
	
}

void CDialogMistakes::OnMenuitemMistakesViewMonth() 
{
	ResetMistakes(MONTH_MISTAKE);	
	
}

void CDialogMistakes::OnMenuitemMistakesViewWeek() 
{
	ResetMistakes(WEEK_MISTAKE);	
	
}


//not working why???
void CDialogMistakes::OnUpdateMenuitemMistakesViewDay(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck();	
}

void CDialogMistakes::OnUpdateMenuitemMistakesViewMonth(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck();	
	
}

void CDialogMistakes::OnUpdateMenuitemMistakesViewSession(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck();	
	
}

void CDialogMistakes::OnUpdateMenuitemMistakesViewWeek(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck();	
}
