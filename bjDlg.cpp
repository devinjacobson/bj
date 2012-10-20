// bjDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "bjDlg.h"
#include "BetMissThread.h"
#include "PropPlay.h"
#include "PropBid.h"
#include "PropCasino.h"
#include "PropStrategy.h"
#include "CountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#include "HyperLink.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	CHyperLink	m_static1;
	CHyperLink m_static2;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
//	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	//}}AFX_DATA_MAP
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

//	m_static1.SetWindowText("<a href=http://www.sequinsoftware.com>www.sequinsoftware.com</a>");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBjDlg dialog
int CBjDlg::m_nCreated = 0;
CCriticalSection CBjDlg::m_Sect;
CPtrList CBjDlg::m_lstMistakes;
CPtrList CBjDlg::m_lstStandardMistakes;
int CBjDlg::m_nStandardBet;
//all stats just for thread to calculate.
int CBjDlg::m_nHandsPlayed;
int CBjDlg::m_nLost;
int CBjDlg::m_nWon;
CTimeSpan CBjDlg::m_TotalPlayTime;
double CBjDlg::m_dAvgStandardCount;
double CBjDlg::m_dTotal;
int CBjDlg::m_nLowBet;
int CBjDlg::m_nHighBet;

double CBjDlg::m_dTotalPossible = 0;

int CBjDlg::m_nAceDecisionMatrix[3][10][22];
int CBjDlg::m_nDecisionMatrix[3][10][22];
int CBjDlg::m_nDoubleDecisionMatrix[3][10][22];
int CBjDlg::m_nSplitDecisionMatrix[3][10][22];
CBJHistory CBjDlg::m_SessionHistory;
CBJHistory CBjDlg::m_DayHistory;
CBJHistory CBjDlg::m_WeekHistory;
CBJHistory CBjDlg::m_MonthHistory;
CBJHistory CBjDlg::m_YearHistory;

CListCtrl CBjDlg::m_listDecision;

#define AVG(A, B, C, D) (A*C+B*D)/(C+D)

CBjDlg::CBjDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBjDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBjDlg)
	m_nAutoplay = FALSE;
	m_nAllManual = FALSE;
	m_dDealerW = 0.0;
	m_dMeW = 0.0;
	m_dTotal = 0;
	m_dProbTotal = 0;
	m_strDealer = "";
	m_strMe = "";
	m_nDealer = -1;
	m_nHitStand = -1;
	m_dSplitAdvantage = 0;
	m_strCommand = "";
	m_nWon = 0;
	m_nLost = 0;
	m_dDDAdvantage = 0;
	m_nWager = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	
	for (int i = 0; i<32; i++){
		m_dDealerProb[i] = 0;
	}
	for (i = 0; i<32; i++){
		m_dDisplay[i] = 0;
	}
	for (i = 0; i<32; i++){
		m_dMeProb[i] = 0;
	}
	ResetArray(m_dDD);
	ResetArray(m_dNDD);
	ResetArray(m_dS);
	ResetArray(m_dNS);
	m_nIsSplit = FALSE;
	m_d32PayoutProb = 0;
	m_nIsDD = 0;
	m_nHandsPlayed = 0;
	if (!m_nCreated){
		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		m_DlgMistakes.Create(IDD_DIALOG_MISTAKES);
		m_DlgMistakes.m_pBjDlg = this;
		m_DlgMistakes.m_plstMistakes = &m_lstMistakes;
		m_DlgMistakes.m_plstStandardMistakes = &m_lstStandardMistakes;
		m_DlgPractice.Create(IDD_DIALOG_PRACTICE);
		m_DlgPractice.m_pBjDlg = this;
	
		m_pSettingsSheet = new CPropertySheet();
		m_pPropPlay = new CPropPlay();
		m_pPropBid = new CPropBid();
		m_pPropCasino = new CPropCasino();
		m_pPropStrategy = new CPropStrategy();
		m_pSettingsSheet->AddPage(m_pPropPlay);
		m_pSettingsSheet->AddPage(m_pPropBid);
		m_pSettingsSheet->AddPage(m_pPropCasino);
		m_pSettingsSheet->AddPage(m_pPropStrategy);
		m_nStandardBet = 1;
	}
	m_nIsPractice = FALSE;
	m_nIsPractice = TRUE;
	m_nIsMistake = FALSE;
	m_nThread = FALSE;
	m_nLowBet = 1;
	m_nHighBet = 5;
}

void CBjDlg::MakeAllVisible(){
	CWnd* pWnd;
	int i;
	for (i = 0; i < 10; i++){
		pWnd = GetDlgItem(IDC_BUTTON_D1+i);
	    pWnd->ShowWindow(SW_SHOWNORMAL);
		pWnd = GetDlgItem(IDC_BUTTON_M1+i);
	    pWnd->ShowWindow(SW_SHOWNORMAL);
		pWnd = GetDlgItem(IDC_BUTTON_O1+i);
	    pWnd->ShowWindow(SW_SHOWNORMAL);
	}
	pWnd = GetDlgItem(IDC_STATICPRO);
    pWnd->ShowWindow(SW_SHOWNORMAL);
	pWnd = GetDlgItem(IDC_STATICPRO2);
    pWnd->ShowWindow(SW_SHOWNORMAL);
	pWnd = GetDlgItem(IDC_STATICPRO3);
    pWnd->ShowWindow(SW_SHOWNORMAL);
	pWnd = GetDlgItem(IDC_CHECK_AUTOPLAY);
    pWnd->ShowWindow(SW_SHOWNORMAL);
	pWnd = GetDlgItem(IDC_CHECK_ALLMANUAL);
    pWnd->ShowWindow(SW_SHOWNORMAL);
	pWnd = GetDlgItem(IDC_BUTTON_NEW_HAND);
    pWnd->ShowWindow(SW_SHOWNORMAL);
	pWnd = GetDlgItem(IDC_BUTTON_RESHUFFLE);
    pWnd->ShowWindow(SW_SHOWNORMAL);
	
}

void CBjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBjDlg)
	DDX_Control(pDX, IDC_SPIN_WAGER, m_spinWager);
	DDX_Control(pDX, IDC_LIST_DECISION, m_listDecision);
	DDX_Control(pDX, IDC_EDIT_ME_CARDS, m_editMe);
	DDX_Control(pDX, IDC_EDIT_DEALER_CARDS, m_editDealer);
	DDX_Control(pDX, IDC_LIST_REMAINING, m_listRemaining);
	DDX_Check(pDX, IDC_CHECK_AUTOPLAY, m_nAutoplay);
	DDX_Check(pDX, IDC_CHECK_ALLMANUAL, m_nAllManual);
	DDX_Text(pDX, IDC_EDIT_DEALERW, m_dDealerW);
	DDX_Text(pDX, IDC_EDIT_MEW, m_dMeW);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_dTotal);
	DDX_Text(pDX, IDC_EDIT_WAGER, m_nWager);
//	DDX_Text(pDX, IDC_EDIT_PROBTOTAL, m_dProbTotal);
	DDX_Check(pDX, IDC_RADIO_DEALER2, m_nDealer);
	DDX_Check(pDX, IDC_RADIO_HIT, m_nHitStand);
	DDX_Text(pDX, IDC_EDIT_WON, m_nWon);
	DDX_Text(pDX, IDC_EDIT_LOST, m_nLost);
	DDX_Text(pDX, IDC_EDIT_DDADVANTAGE, m_dDDAdvantage);
	DDX_Text(pDX, IDC_EDIT_SPLITADVANTAGE, m_dSplitAdvantage);
	DDX_Text(pDX, IDC_EDIT_COMMAND, m_strCommand);
	DDX_Text(pDX, IDC_EDIT_HANDS_PLAYED, m_nHandsPlayed);
	DDX_Text(pDX, IDC_EDIT_BJ_ADVANTAGE, m_d32PayoutProb);
	DDX_Text(pDX, IDC_EDIT_WHIT, m_dWHit);
	DDX_Text(pDX, IDC_EDIT_WOHIT, m_dWOHit);
//	DDX_Text(pDX, IDC_EDIT22, m_dDisplay[22]);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBjDlg, CDialog)
	//{{AFX_MSG_MAP(CBjDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_DEALERFOCUS, OnDealerFocus)
	ON_COMMAND(ID_MEFOCUS, OnMeFocus)
	ON_COMMAND(IDC_BUTTON_RESHUFFLE, OnReshuffle)
	ON_COMMAND(ID_HANDOVER, OnHandOver)
	ON_BN_CLICKED(IDC_RADIO_DEALER2, OnRadioDealer2)
	ON_BN_CLICKED(IDC_RADIO_HIT, OnRadioHitStand)
	ON_BN_CLICKED(IDC_RADIO_SPLIT, OnRadioSplit)
	ON_BN_CLICKED(IDC_RADIO_DOUBLE, OnRadioDouble)
	ON_BN_CLICKED(IDC_RADIO_ACE, OnRadioAce)
	ON_COMMAND(ID_WON, OnWon)
	ON_COMMAND(ID_LOST, OnLost)
	ON_COMMAND(ID_NOBODY, OnNobody)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_AUTOPLAY, OnCheckAutoplay)
	ON_BN_CLICKED(IDC_CHECK_ALLMANUAL, OnCheckAllManual)
	ON_COMMAND(ID_MENUITEM_VIEW_MISTAKES, OnMenuitemViewMistakes)
	ON_COMMAND(ID_MENUITEM_VIEW_PRACTICE, OnMenuitemViewPractice)
	ON_COMMAND(ID_MENUITEM_VIEW_SETTINGS, OnMenuitemViewSettings)
	ON_COMMAND(ID_MENU_HELP_ABOUT, OnMenuitemHelpAbout)
	ON_COMMAND(IDC_BUTTON_NEW_HAND, OnNewHand)
	ON_BN_CLICKED(IDC_RADIO_ME2, OnRadioDealer2)
	ON_COMMAND(ID_CALCULATE, Calculate)
	ON_COMMAND_RANGE(IDC_BUTTON_M1, IDC_BUTTON_M10, OnMe)
	ON_COMMAND_RANGE(IDC_BUTTON_D1, IDC_BUTTON_D10, OnDealer)
	ON_COMMAND_RANGE(IDC_BUTTON_O1, IDC_BUTTON_O10, OnOther)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBjDlg message handlers

BOOL CBjDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//load the settings from the file here.
	// Add "About..." menu item to system menu.
	if (m_nThread){
		return TRUE;
	}
	if (!m_nCreated){
		m_nCreated++;
		m_SessionHistory.m_StartTime = CTime::GetCurrentTime();
		LoadHistory();  //get all month...stuff
//		CDeck* pDeck = new CDeck(m_Deck);
//		m_lstDecks.AddTail(pDeck);
		CBetMissParam* p = new CBetMissParam();
		p->m_plstBets = &m_DlgPractice.m_lstBets;
		p->m_plstDecks = &m_lstDecks;
		AfxBeginThread(ThreadProc, p);
	}
#ifdef PRO_VERSION
		//make everything visible.
		MakeAllVisible();
#endif
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_spinWager.SetBuddy(CWnd::GetDlgItem(IDC_EDIT_WAGER));
	m_spinWager.SetBase(10);
	m_spinWager.SetRange(1, 1000);
	CRect rect;
	m_listRemaining.GetClientRect(&rect);

	m_listRemaining.InsertColumn(0, "Card Value", LVCFMT_LEFT, rect.Width()*.1);
	m_listRemaining.InsertColumn(1, "Remaining", LVCFMT_RIGHT, rect.Width()*.2);
	m_listRemaining.InsertColumn(2, "Total", LVCFMT_LEFT, rect.Width()*.2);
	m_listRemaining.InsertColumn(3, "Probability", LVCFMT_LEFT, rect.Width()*.3);
	m_listRemaining.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	m_listDecision.GetClientRect(&rect);
	m_listDecision.InsertColumn(0, "Dealer", LVCFMT_LEFT, rect.Width()*.12);
	m_listDecision.InsertColumn(1, "1", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(2, "2", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(3, "3", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(4, "4", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(5, "5", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(6, "6", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(7, "7", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(8, "8", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(9, "9", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(10, "10", LVCFMT_LEFT, rect.Width()*.07);
	m_listDecision.InsertColumn(11, "Probability", LVCFMT_LEFT, rect.Width()*.18);
	m_listDecision.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	int i = 0;

	CString strTemp;
	for (i = 0; i< 22; i++){
		strTemp.Format("%d", i);
		m_listDecision.InsertItem(i, strTemp);
		m_listDecision.SetItemText(i, 1, "");
	}
	m_hAccel = LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	UpdateList();

	SetTimer(1, 3000, NULL); //autoplay timer.  
//	Calculate();
	CRect rectDesk;
	CRect rectWnd;
	CWnd::GetDesktopWindow()->GetClientRect(rectDesk);

	GetClientRect(rectWnd);
	// -50 make room for the start menu.
	rect.top = rectDesk.top + 50;
	rect.bottom = rect.top + rectWnd.Height() + 50;
	rect.left = rectDesk.left;
	rect.right = rectDesk.left + rectWnd.Width();
	MoveWindow(rect);


	m_DlgMistakes.ShowWindow(SW_SHOW);
	m_DlgMistakes.GetWindowRect(&rectWnd);
	rect.top = rectDesk.top;
	rect.bottom = rectDesk.top + rectWnd.Height();
	rect.right = rectDesk.right;
	rect.left = rectDesk.right - rectWnd.Width();
	m_DlgMistakes.MoveWindow(rect);
	m_DlgPractice.ShowWindow(SW_SHOW);
	m_DlgPractice.GetClientRect(&rectWnd);
	rect.top = rectDesk.bottom - rectWnd.Height() - 50;
	rect.bottom = rectDesk.bottom - 50;
	rect.left = rectDesk.right - rectWnd.Width();
	rect.right = rectDesk.right;
	m_DlgPractice.MoveWindow(rect);
	m_DlgPractice.Startup();
	m_DlgMistakes.BringWindowToTop();
	m_DlgPractice.GetDlgItem(IDC_EDIT_WAGER)->SetFocus();
	return TRUE;  // return TRUE  unless you set the focus to a control
}


BOOL CBjDlg::PreTranslateMessage(MSG* pMsg){
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		// finally, translate the message
		if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg)){
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CBjDlg::OnDealerFocus(){
	m_editDealer.SetFocus();
}

void CBjDlg::OnMeFocus(){
	m_editMe.SetFocus();
}

void CBjDlg::OnNobody(){
	m_listRemaining.SetFocus();
}

void CBjDlg::OnNewHand(){
	m_nIsPractice = FALSE;
	OnHandOver();
	m_nIsPractice = TRUE;
}

void CBjDlg::OnHandOver(){
	//clear hands.  
	CHand hand;
	m_handDealer = hand;
	m_handMe = hand;
	m_strMe = "";
	m_strDealer = "";
	m_editMe.SetWindowText("");
	m_editDealer.SetWindowText("");
	if (!m_nIsPractice || m_nAllManual){
		CWaitCursor wait;
		Calculate();
		wait.Restore();
		if (m_nIsMistake){
			m_dWOHit = 0;
			m_dWHit = 0;
		}
	}
	else{
		//calculate the actual winning
	}
	if (!m_nIsPractice && !m_nIsMistake){
		m_nHandsPlayed++;
		//this only works for non-practice mode.
		if (m_dMeW > m_dDealerW){
			m_nWon++;
			m_dTotal += m_nWager * (m_dMeW-m_dDealerW);
		}
		else{
			m_nLost++;
			m_dTotal += (m_dMeW-m_dDealerW);
		}
	}
	UpdateData(FALSE);
}

void CBjDlg::OnReshuffle(){
	m_Deck.Reshuffle();
	OnHandOver();
	UpdateList();
}

CMistake* CBjDlg::GetMistake(){
	CMistake* pMistake = new CMistake();
	pMistake->m_Dealer = m_handDealer;
	pMistake->m_Me = m_handMe;
	pMistake->m_Deck = m_Deck;
	pMistake->m_Date = CTime::GetCurrentTime();
	return pMistake;
}

int CBjDlg::PlayCard(int nValue, int nWho, int nDouble, int nSplit){
	//0 me, 1 dealer, 2 other, 12 standard
	CMistake* pMistake = NULL;
	if (nValue > 10){
		nValue = 10;
	}
	if (nWho == TURN_ME || nWho == TURN_STANDARD){
		//check status first, if mistake, add to list
		//if 0, then stand
		if (nValue){
			if (m_handMe.m_nNumCards <2){
				//no full hand yet
			}
			else if (nDouble){
				if (m_strCommand !="Double Down"){
					//mistake not yet
					pMistake = GetMistake();
					pMistake->m_nMistake = MISTAKE_DOUBLE;
					
					double dDDLoss=0;
					double dDDWin = 0;
					dDDWin = GetWinProb(m_dDD, dDDLoss, m_nIsDD);
					double dTemp = ((dDDWin-dDDLoss)*2) - (m_dMeW - m_dDealerW);
//					pMistake->m_dLoss = -dTemp;
					pMistake->m_dLoss = -m_dDDAdvantage;
					//still a mistake here.  The loss is not that much I dont think.  
					if (nWho==TURN_ME)
						m_lstMistakes.AddTail(pMistake);
					else
						m_lstStandardMistakes.AddTail(pMistake);
				}


			}
			else if (nSplit){
				if (m_strCommand !="Split"){
					//mistake not yet
					pMistake = GetMistake();
					pMistake->m_nMistake = MISTAKE_SPLIT;
					pMistake->m_dLoss = -m_dSplitAdvantage;
					if (nWho==TURN_ME)
						m_lstMistakes.AddTail(pMistake);
					else
						m_lstStandardMistakes.AddTail(pMistake);
				}
				if (nWho==TURN_ME){
					nValue = m_handMe.m_pnCards[0];
					m_handMe.m_nNumCards = 0;
					m_handMe.m_nTotalValue = 0;
					m_strMe = "";
					OnMe(IDC_BUTTON_M1 + nValue -1);
				}
				return TRUE;
			}	
			else if (m_strCommand == "Stand"){
				//mistake
				pMistake = GetMistake();
				pMistake->m_nMistake = MISTAKE_HIT;
				pMistake->m_dLoss = m_dWOHit - m_dWHit;
				if (nWho==TURN_ME)
					m_lstMistakes.AddTail(pMistake);
				else
					m_lstStandardMistakes.AddTail(pMistake);
			}
			else if (m_strCommand == "Split"){
				//mistake
				pMistake = GetMistake();
				if (!m_DlgPractice.m_nSplit){
					pMistake->m_nMistake = MISTAKE_NOSPLIT;
					pMistake->m_dLoss = m_dSplitAdvantage;
				}
				else{
					delete pMistake;
					return TRUE;
				}
				if (nWho==TURN_ME)
					m_lstMistakes.AddTail(pMistake);
				else
					m_lstStandardMistakes.AddTail(pMistake);
			}
			else if (m_strCommand == "Double Down"){
				pMistake = GetMistake();
				pMistake->m_nMistake = MISTAKE_NODOUBLE;
				pMistake->m_dLoss = m_dDDAdvantage;
				if (nWho==TURN_ME)
					m_lstMistakes.AddTail(pMistake);
				else
					m_lstStandardMistakes.AddTail(pMistake);
			}

			if (nDouble && m_DlgPractice.m_nSplit == 1){
				if (nWho==TURN_ME){
					nValue = m_handMe.m_pnCards[0];
					m_handMe.m_nNumCards = 0;
					m_handMe.m_nTotalValue = 0;
					m_strMe = "";
					OnMe(IDC_BUTTON_M1 + nValue -1);
				}				
			}
			else if (nWho==TURN_ME){
				OnMe(IDC_BUTTON_M1 + nValue -1);
			}
		}
		else{
			if (m_strCommand !="Stand"){
				//mistake
				pMistake = GetMistake();
				
				if (m_strCommand == "Split"){
					if (!m_DlgPractice.m_nSplit){
						pMistake->m_nMistake = MISTAKE_NOSPLIT;
						pMistake->m_dLoss = m_dSplitAdvantage;
					}
					else{
						delete pMistake;
						if (nWho==TURN_ME){
							nValue = m_handMe.m_pnCards[0];
							m_handMe.m_nNumCards = 0;
							m_handMe.m_nTotalValue = 0;
							m_strMe = "";
							OnMe(IDC_BUTTON_M1 + nValue -1);
						}				
						return TRUE;
					}
				}
				else if (m_strCommand == "Double Down"){
					pMistake->m_nMistake = MISTAKE_NODOUBLE;
					pMistake->m_dLoss = m_dDDAdvantage;
					pMistake->m_dLoss += m_dWHit - m_dWOHit;
				}
				else{
					pMistake->m_nMistake = MISTAKE_NOHIT;
					pMistake->m_dLoss = m_dWHit - m_dWOHit;
				}
/*
				if (m_dDDAdvantage>0){
					pMistake->m_dLoss += m_dDDAdvantage;
				}
				else if (m_dSplitAdvantage>0){
					pMistake->m_dLoss += m_dSplitAdvantage;
				}
*/
				if (nWho==TURN_ME){
					m_lstMistakes.AddTail(pMistake);
				}
				else{
					m_lstStandardMistakes.AddTail(pMistake);
				}
			}
			//standing
			//check for split
			//reset to the split hand
			if (m_DlgPractice.m_nSplit == 1){
				if (nWho==TURN_ME){
					nValue = m_handMe.m_pnCards[0];
					m_handMe.m_nNumCards = 0;
					m_handMe.m_nTotalValue = 0;
					m_strMe = "";
					OnMe(IDC_BUTTON_M1 + nValue -1);
				}				
			}
		}
		if (pMistake){
			if (nWho==TURN_ME){
				pMistake->m_nBet = m_DlgPractice.m_nBet;
			}
			else{
				pMistake->m_nBet = m_nStandardBet;
			}
		}
	}
	else if (nWho == TURN_DEAL){
		if (nValue){
			OnDealer(IDC_BUTTON_D1 + nValue -1);
		}
		else{
			//for calculation for bet mistakes later;
//			CDeck* pDeck = new CDeck(m_Deck);
			
			CSingleLock lock(&CBjDlg::m_Sect);

			lock.Lock();
			if (!lock.IsLocked()){
				Sleep(10);
				lock.Lock();
			}
			
//			m_lstDecks.AddTail(pDeck);
			lock.Unlock();

			OnHandOver();
		}
		
	}
	else{
		OnOther(IDC_BUTTON_O1 + nValue -1);
	}
	if (m_DlgMistakes.m_listMistakes.GetItemCount() !=m_lstMistakes.GetCount() || m_DlgMistakes.m_listStandardMistakes.GetItemCount() !=m_lstStandardMistakes.GetCount()){
		m_DlgMistakes.LoadMistakes();
	}
	else{
		m_DlgMistakes.UpdatePossible();
	}
	return TRUE;
}

void CBjDlg::OnMe(UINT nID){
	int i = nID - IDC_BUTTON_M1 + 1;
	CString strTemp;
	if (m_Deck.Play(i)){
		m_DlgPractice.OnMe(i);
		strTemp.Format("%s%d ", m_strMe, i);
		m_strMe = strTemp;
		m_editMe.SetWindowText(m_strMe);
		m_handMe.Hit(i);
		if (m_nIsPractice && m_handMe.m_nNumCards > 1){
			Calculate();
		}
		else if (!m_nIsPractice){
			Calculate();
		}
	}
	else{
		strTemp.Format("No %d's left", i);
//		AfxMessageBox(strTemp);
		m_Deck.Reshuffle();
	}
	UpdateList(i);

}

void CBjDlg::OnDealer(UINT nID){
	int i = nID - IDC_BUTTON_D1 + 1;
	CString strTemp;
	if (m_Deck.Play(i)){
		m_DlgPractice.OnDealer(i);
			strTemp.Format("%s%d ", m_strDealer, i);
			m_strDealer = strTemp;
			m_editDealer.SetWindowText(m_strDealer);
			m_handDealer.Hit(i);
	}
	else{
		strTemp.Format("No %d's left", i);
//		AfxMessageBox(strTemp);
		m_Deck.Reshuffle();
	}
	UpdateList(i);

}

void CBjDlg::OnOther(UINT nID){
	int i = nID - IDC_BUTTON_O1 + 1;
	CString strTemp;
	if (m_Deck.Play(i)){
		m_DlgPractice.OnOther(i);	
	}
	else{
		strTemp.Format("No %d's left", i);
//		AfxMessageBox(strTemp);
		m_Deck.Reshuffle();
	}
	UpdateList(i);

}

void CBjDlg::OnNumber(UINT nID){
	int i = nID - ID_1 + 1;
	CString strTemp;
	if (m_Deck.Play(i)){
		if (m_editMe.m_hWnd == ::GetFocus()){
			strTemp.Format("%s%d ", m_strMe, i);
			m_strMe = strTemp;
			m_editMe.SetWindowText(m_strMe);
			m_handMe.Hit(i);
			if (m_nIsPractice && m_handMe.m_nNumCards > 1){
				Calculate();
			}
			else if (!m_nIsPractice){
				Calculate();
			}
		}
		else if (m_editDealer.m_hWnd == ::GetFocus()){
			strTemp.Format("%s%d ", m_strDealer, i);
			m_strDealer = strTemp;
			m_editDealer.SetWindowText(m_strDealer);
			m_handDealer.Hit(i);
		}
	}
	else{
		strTemp.Format("No %d's left", i);
//		AfxMessageBox(strTemp);
		m_Deck.Reshuffle();
	}
	UpdateList(i);
}

void CBjDlg::UpdateMatrices(){
	CString strTemp;
	CString strOrig;
	int i = 0;

	int* pArray;
	switch (m_nHitStand){
	case 1:
		pArray = (int*)m_nDecisionMatrix;
		break;
	case 2:
		pArray = (int*)m_nDoubleDecisionMatrix;
		break;
	case 3:
		pArray = (int*)m_nSplitDecisionMatrix;
		break;
	case 4:
		pArray = (int*)m_nAceDecisionMatrix;
		break;
	default:
		pArray = (int*)m_nDecisionMatrix;
		break;
	}
	for (i = 0; i< 22; i++){
		for (int j=0; j<10; j++){

			switch(pArray[10*22+j*22+i]){
			case HIT:
				strTemp = "H";
				break;
			case STAND:
				strTemp = "S";
				break;
			case DOUBLE:
				strTemp = "D";
				break;
			case SPLIT:
				strTemp = "P";
				break;
			default:
				strTemp = "-";
				break;
			}
			if (pArray[j*22+i] != pArray[10*22+j*22+i]){
				strTemp += "c";
			}
//			if (!m_nThread){
				m_listDecision.SetItemText(i, j+1, strTemp);
//			}
		}
		strTemp.Format("%f", m_dDisplay[i]);
//		if (!m_nThread){
			m_listDecision.SetItemText(i, j+1, strTemp);
//		}
	}

	
}

void CBjDlg::UpdateList(int nValue){
	CString strTemp;
	int i = nValue -1;
	if (!nValue){
 		m_listRemaining.DeleteAllItems();
	}
	for (i = 0; i< m_Deck.m_nCards; i++){
		if (!nValue){
			strTemp.Format("%d", m_Deck.m_pCards[i].m_nValue);
			m_listRemaining.InsertItem(i, strTemp);
		}
		strTemp.Format("%d", m_Deck.m_pCards[i].m_nNumAvailable - m_Deck.m_pCards[i].m_nNumPlayed);
		m_listRemaining.SetItemText(i, 1, strTemp);
		strTemp.Format("%d", m_Deck.m_pCards[i].m_nNumAvailable);
		m_listRemaining.SetItemText(i, 2, strTemp);
		strTemp.Format("%f", (double)(m_Deck.m_pCards[i].m_nNumAvailable - m_Deck.m_pCards[i].m_nNumPlayed)/(double)(m_Deck.m_nNumAvailable-m_Deck.m_nNumPlayed));
		m_listRemaining.SetItemText(i, 3, strTemp);
	}
}

void CBjDlg::Calculate(){
	//get all probabilities and then update the interface.  
	if (!m_nCreated){
		m_nWager = m_spinWager.GetPos();
	}

	m_dMeW = 0;
	m_dDealerW = 0;
	m_nIsSplit = FALSE;
	m_nIsDD = FALSE;
	m_dDDAdvantage = 0;
	m_dSplitAdvantage = 0;
	m_dWS = 0;
	m_dWDD = 0;
	ResetArray(m_dMeProb);
	ResetArray(m_dDealerProb);
	ResetArray(m_dS);
	ResetArray(m_dNS);
	m_dDealerProb[0] = 1;
	m_dMeProb[0] = 1;

	//and dealer =0??
	if (m_handMe.m_nNumCards == 0 && m_handDealer.m_nNumCards==0){
		ResetMatrices();
	}
	GetDealerProb(m_handDealer, m_dDealerProb);
	GetMeProb(m_handMe, m_dMeProb);
	m_d32PayoutProb = Get32PayoutProb(m_handMe, m_Deck);
	m_dMeW += m_d32PayoutProb * .5;

	m_dMeW += m_dDDAdvantage;
	m_dMeW += m_dSplitAdvantage;
	UpdateProbabilities();
	if (m_dDDAdvantage == 0){
		m_dDDAdvantage = m_dWDD;
	}
	if (m_dSplitAdvantage == 0){
		m_dSplitAdvantage = m_dWS;
	}
	//only update if we have a clean slate here.
	if (m_handMe.m_nNumCards==0 && m_handDealer.m_nNumCards==0){
		UpdateMatrices();
	}
	if (!m_nThread){
		UpdateData(FALSE);
	}
	else{
		
	}
}
 

void CBjDlg::ResetArray(double * pD){
	for (int i = 0; i<32; i++){
		pD[i] = 0;
	}
}

void CBjDlg::ResetMatrices(){
	for (int i = 0; i<10; i++){
		for (int j=0; j<22; j++){
			m_nAceDecisionMatrix[0][i][j] = m_nAceDecisionMatrix[1][i][j];
			m_nDecisionMatrix[0][i][j] = m_nDecisionMatrix[1][i][j];
			m_nSplitDecisionMatrix[0][i][j] = m_nSplitDecisionMatrix[1][i][j];
			m_nDoubleDecisionMatrix[0][i][j] = m_nDoubleDecisionMatrix[1][i][j];

			if (m_nHandsPlayed == 1){
				//copy the standard decisions
				m_nAceDecisionMatrix[2][i][j] = m_nAceDecisionMatrix[1][i][j];
				m_nDecisionMatrix[2][i][j] = m_nDecisionMatrix[1][i][j];
				m_nSplitDecisionMatrix[2][i][j] = m_nSplitDecisionMatrix[1][i][j];
				m_nDoubleDecisionMatrix[2][i][j] = m_nDoubleDecisionMatrix[1][i][j];				
			}

			m_nAceDecisionMatrix[1][i][j] = 0;
			m_nDecisionMatrix[1][i][j] = 0;
			m_nSplitDecisionMatrix[1][i][j] = 0;
			m_nDoubleDecisionMatrix[1][i][j] = 0;
		}
	}
}

void CBjDlg::UpdateWinPct(){
	double dLoss = 0;
	double dWin = 0;
	dWin = GetWinProb(m_dMeProb, dLoss, TRUE);
	m_dMeW += dWin;
	m_dDealerW += dLoss;
}

double CBjDlg::Get32PayoutProb(CHand hand, CDeck deck){
	double dProb = 0;
	if (hand.m_nNumCards > 2){
		return 0;
	}
	else if (hand.m_nNumCards == 2){
		if (hand.m_pnCards[0] == 10 && hand.m_pnCards[1]==1){
			return 1;
		}
		else if (hand.m_pnCards[0]==1 && hand.m_pnCards[1]==10){
			return 1;
		}
		else{
			return 0;
		}
	}
	else if (hand.m_nNumCards == 1){
		if (hand.m_pnCards[0] == 10){
			dProb = deck.m_pCards[0].m_nNumAvailable - deck.m_pCards[0].m_nNumPlayed;
			dProb /= deck.m_nNumAvailable - deck.m_nNumPlayed;
		}
		else if(hand.m_pnCards[0] == 1){
			dProb = deck.m_pCards[9].m_nNumAvailable - deck.m_pCards[9].m_nNumPlayed;
			dProb /= deck.m_nNumAvailable - deck.m_nNumPlayed;			
		}
	}
	else{
		dProb = deck.m_pCards[0].m_nNumAvailable - deck.m_pCards[0].m_nNumPlayed;
		dProb /= deck.m_nNumAvailable - deck.m_nNumPlayed;
		dProb *= (deck.m_pCards[9].m_nNumAvailable - deck.m_pCards[9].m_nNumPlayed);
		dProb /= (deck.m_nNumAvailable - deck.m_nNumPlayed);
		dProb *= 2;
	}
	//dealer may get BJ too.  
	return dProb*(1-dProb);
}

void CBjDlg::UpdateProbabilities(){
	if (m_nDealer){
		memcpy(m_dDisplay, m_dDealerProb, sizeof(double)*32);
	}
	else{
		if (m_strCommand == "Double Down"){
			memcpy(m_dDisplay, m_dDD, sizeof(double)*32);
		}
//		else if (m_strCommand == "Split"){
//			memcpy(m_dDisplay, m_dS, sizeof(double)*32);
//		}
		else{
			memcpy(m_dDisplay, m_dMeProb, sizeof(double)*32);
		}
	}
	for (int i = 23; i<32; i++){
		m_dDisplay[22] += m_dDisplay[i];
	}
}

int CBjDlg::HitOnce(CHand& hand, CDeck& deck, double dProb){
	if (hand.m_nTotalValue >= 21){
		return FALSE;
	}
	if (hand.m_nHasAce){
		//split aces only take one hit.  
		if (hand.m_nNumCards == 2 && hand.m_nIsSplitAce){
			return FALSE;
		}
		if (hand.m_nTotalValue < 7){
//			return TRUE;
		}
		else if (hand.m_nTotalValue == 11){
			return FALSE;
		}
	}
	else{
		if (hand.m_nTotalValue < 12){
//			return TRUE;
		}
	}
	
	ResetArray(m_dMeProbWHit);
	double deckProb = 0;
	int nHandValue = 0;
	double handProb;
	double dLoss;
	double dWin = GetWinProb(hand, dLoss);
	double dTemp = (dWin - dLoss)*dProb;
	m_dWOHit = dTemp;	
	CHand tempHand;
	CDeck tempDeck;
	for (int i = 0; i<deck.m_nCards; i++){
		CHand tempHand = hand;
		CDeck tempDeck = deck;
		if (deck.m_pCards[i].m_nNumAvailable - deck.m_pCards[i].m_nNumPlayed > 0){
			deckProb = (double)(tempDeck.m_pCards[i].m_nNumAvailable - tempDeck.m_pCards[i].m_nNumPlayed);
			deckProb /= (double)(tempDeck.m_nNumAvailable - tempDeck.m_nNumPlayed);
			nHandValue = tempHand.m_nTotalValue;
			handProb = dProb*deckProb;
			tempHand.Hit(tempDeck.m_pCards[i].m_nValue);
			tempDeck.Play(tempDeck.m_pCards[i].m_nValue);
			nHandValue = tempHand.m_nTotalValue;
			m_dMeProbWHit[nHandValue] += handProb;
		}
		//this should only be for me.  
		//questionable here.  
//		if (tempHand.m_nHasAce && tempHand.m_nTotalValue < 12){
//			nHandValue += 10;
//		}

//		if (tempHand.m_nHasAce && tempHand.m_nTotalValue < 22){
//			if (HitOnce(tempHand, tempDeck, handProb)){
//			}
//			else{
//				m_dMeProbWHit[nHandValue] += handProb;
//			}
//		}
//		else{
//		}
	
	}
	//if it is better to hit
	
	
	
	double dLossWHit;
	double dWinWHit = GetWinProb(m_dMeProbWHit, dLossWHit);

	//not sure if this is what I want
//		if (dWinWHit > dLossWHit){
			//should I have the !m_nSplit here?

			if (hand.m_nNumCards == 2 && !m_nIsDD && !hand.m_nIsSplit){
				//should we double down or not??
				//if so what is the pct gain?
				if (hand.m_nTotalValue < 9 && !CPropCasino::m_nCanDouble8Below){
				}
				else if ((hand.m_nTotalValue==9) && !CPropCasino::m_nCanDouble9){
				}
				else if ((hand.m_nTotalValue==10 || hand.m_nTotalValue==11) && !CPropCasino::m_nCanDouble1011){
				}
				else if (hand.m_nHasAce && !CPropCasino::m_nCanDoubleAces){
				}
				else{
					memcpy(m_dDD, m_dMeProbWHit, sizeof(double)*32);
					m_nIsDD = hand.m_nTotalValue;
					if (hand.m_nHasAce){
						m_nIsDD += 100;
					}
				}

				//do splits here as well.  

			}
//		}

	CHand shand;
	if (hand.m_nNumCards == 2 && !m_nIsSplit){
		if (hand.m_pnCards[0] == hand.m_pnCards[1]){
			if (hand.m_nHasAce && !CPropCasino::m_nCanSplitAces){
			
			}
			else{
				shand.Hit(hand.m_pnCards[0]);
				CDeck sdeck = deck;
				shand.m_nIsSplit = TRUE;
				if (hand.m_nHasAce){
					shand.m_nIsSplitAce = TRUE;
				}
				ResetArray(m_dS);
				m_nIsSplit = hand.m_pnCards[0];
				Hit(shand, sdeck, dProb, FALSE, m_dS);
			}
		}
	}
	m_dWHit = dWinWHit - dLossWHit;
	if (dWinWHit - dLossWHit >= dTemp-.000000000000001){
		return TRUE;
	}
	else{
		if (hand.m_nTotalValue < 12 && !hand.m_nHasAce){
			int i = 0;
		}
		else if (hand.m_nTotalValue < 8){
			int j = 0;
		}
		if (m_nIsSplit && shand.m_nIsSplit){
			ResetArray(m_dNS);
//			m_dNS[hand.m_nTotalValue] = dProb;
		}
		return FALSE;	

	}

}

double CBjDlg::GetWinProb(CHand& hand, double& dLoss){
	double dWin = 0;
	dLoss = 0;
	int nHandValue = hand.m_nTotalValue;
	if (nHandValue < 12 && hand.m_nHasAce){
		nHandValue += 10;
	}
	int nDealerValue = 0;
	if (nHandValue > 21){
		dLoss = 1;
		return 0;
	}
	for (int i = 7; i<27; i++){
		if (i < 12){
			nDealerValue = i + 10;
		}
		else{
			nDealerValue = i;
		}

		if (nDealerValue > 21){
			dWin += m_dDealerProb[i];
		}
		else if (nHandValue > nDealerValue){
			dWin += m_dDealerProb[i];
		}
		else if (nHandValue < nDealerValue){
			dLoss += m_dDealerProb[i];
		}
	}
	return dWin;
}

//sometimes the 11s are not 21.  
//could just check the probability of pProb[9] is zero, we know that we doubled down on
//eight, if pProb[10] is zero, on nine and so forth.  
double CBjDlg::GetWinProb(double* pProb, double& dLoss, int nAddTen){
	double dWin = 0;
	dLoss = 0;
	int nDealerValue = 0;
	int nMeValue =0;
	double dTempWin = 0;
	double dTempLoss = 0;
	double dProbCheck = 0;
	int nHasAce = FALSE;
	if (nAddTen > 100){
		nAddTen -=100;
		nHasAce = TRUE;
	}
	for (int i = 7; i<27; i++){
		dTempWin = 0;
		dTempLoss =0;
		nDealerValue = i;
		if (i < 12 && i > 0){
			nDealerValue +=10;
		}
		if (m_dDealerProb[i] > 0){
			for (int j = 1; j<22; j++){
				if (nAddTen > 1){
					//double down stuff only.  
					if (j > nAddTen+1){
						if (nHasAce){
							if (j + 10 < 22){
								nMeValue = j + 10;
							}
							else {
								nMeValue = j;
							}
						}
						else{
							nMeValue = j;
						}
					}
					//with ace just dealt.  
					else if (j == nAddTen + 1){
						if (j + 10 < 22){
							nMeValue = j + 10;
						}
						else {
							nMeValue = j;
						}
					}
					else{
						if (pProb[j] > 0){
							int q = 0;
						}
						nMeValue = j;
					}
				}
				else{
					if (j<11){
						nMeValue = j+10;
					}
					else if (j == 11){
						if (nAddTen){
							nMeValue = j+10;
						}
						else{
							nMeValue = j;
						}
					}
					else{
						nMeValue = j;
					}
				}


				if (nDealerValue > 21){
					dTempWin += pProb[j];
				}
				else if (nMeValue > nDealerValue){
					dTempWin += pProb[j];
				}
				else if (nMeValue < nDealerValue){
					dTempLoss += pProb[j];
				}
			}
			dWin += dTempWin * m_dDealerProb[i];
			dLoss += dTempLoss * m_dDealerProb[i];
		}
	}

	for (int k = 22; k<31; k++){
		dLoss += pProb[k];
	}
	//blackjack here.  
	dWin += pProb[31]*(1-m_dDealerProb[31]);
	if (dProbCheck > 1.0001){
		int q = 0;
	}
	return dWin;
}


int CBjDlg::Hit(CHand hand, CDeck deck, double dProb, int nIsDealer, double* pProb){
	double deckProb = 0;
	int nHandValue = 0;
	double handProb;
	//for speed only.  cuts out about half the time without losing much accuracy.  
	//cuts out hands like 2 2 2 2 2 2, and 1 1 1 1 1 1 1.
	if (dProb < 0.00000001){
		return FALSE;
	}
	for (int i = 0; i<deck.m_nCards; i++){
		CHand tempHand = hand;
		CDeck tempDeck = deck;
		if (deck.m_pCards[i].m_nNumAvailable - deck.m_pCards[i].m_nNumPlayed > 0){
			deckProb = (double)(tempDeck.m_pCards[i].m_nNumAvailable - tempDeck.m_pCards[i].m_nNumPlayed);
			deckProb /= (double)(tempDeck.m_nNumAvailable - tempDeck.m_nNumPlayed);
			nHandValue = tempHand.m_nTotalValue;
			handProb = dProb*deckProb;
			tempHand.Hit(tempDeck.m_pCards[i].m_nValue);
			tempDeck.Play(tempDeck.m_pCards[i].m_nValue);
			nHandValue = tempHand.m_nTotalValue;
		}
		else{
			continue;
		}

		if (tempHand.ShouldHit(nIsDealer)){
			Hit(tempHand, tempDeck, handProb, nIsDealer);
		}
		else{
			if (nIsDealer){
				m_dDealerProb[nHandValue] += handProb;
				if (tempHand.m_nHasAce && tempHand.m_nTotalValue ==11 && tempHand.m_nNumCards==2){
					m_dDealerProb[31] += handProb;
				}
				m_dProbTotal += handProb;
			}
			else{
				//coming out of a double down possibility??
				

				if (HitOnce(tempHand, tempDeck, handProb)){
					if (!pProb){
						SetMatrix(tempHand.m_nTotalValue, HIT, tempHand.m_nHasAce);
					}
					Hit(tempHand, tempDeck, handProb, FALSE, pProb);
				}
				else{
					if (!pProb){
						if (tempHand.m_nHasAce && tempHand.m_nTotalValue ==11 && tempHand.m_nNumCards==2){
							m_dMeProb[31] += handProb; //blackjack;
						}
						else{
							m_dMeProb[nHandValue] += handProb;
						}
						SetMatrix(tempHand.m_nTotalValue, STAND, tempHand.m_nHasAce);
					}
					else{
						pProb[nHandValue] += handProb;
					}
					if (m_nIsDD && !pProb){// && hand.m_nNumCards > 1){
						m_dNDD[nHandValue] += handProb;
					}
					if (m_nIsSplit && !pProb){// && hand.m_nNumCards > 1){
						m_dNS[nHandValue] += handProb;
					}
					if (!pProb){
						m_dProbTotal += handProb;
					}
				}


				if (hand.m_nNumCards < 2){
					//if the (GetWinProb(m_dDD)-loss)*2 > GetWinProb(m_dNDD)
					//we want to double down.  and figure out the benifit from it.  
					if (m_nIsDD && !pProb){
						SetDD();
					}
					if (m_nIsSplit && !pProb){
						SetS();
					}
				}
			}
		}
	}
	return TRUE;
}

void CBjDlg::SetMatrix(int nHandValue, int nFunction, int nHasAce){
	if (nHandValue > 21 || nHandValue < 1){
		return;
	}
	if (m_handDealer.m_nTotalValue > 10 || m_handDealer.m_nTotalValue < 1){
		return;
	}
	if (nHasAce){
		m_nAceDecisionMatrix[1][m_handDealer.m_nTotalValue-1][nHandValue] = nFunction;
	}
	else if (nFunction==SPLIT){
		m_nSplitDecisionMatrix[1][m_handDealer.m_nTotalValue-1][nHandValue] = nFunction;
	}
	else if (nFunction==DOUBLE){
		m_nDoubleDecisionMatrix[1][m_handDealer.m_nTotalValue-1][nHandValue] = nFunction;		
	}
	else{
		m_nDecisionMatrix[1][m_handDealer.m_nTotalValue-1][nHandValue] = nFunction;		
	}

}

void CBjDlg::SetS(){
	double dSWin;
	double dSLoss;
	double dNSWin;
	double dNSLoss;
	double dTemp = 0;
	double dTempS = 0;
	double dTempNS = 0;
//	for (int i = 1; i<31; i++){
//		dTempS += m_dS[i];
//		dTempNS += m_dNS[i];
//	}
	if (m_nIsSplit == 2){
		int q = 0;
	}
	dSWin = GetWinProb(m_dS, dSLoss);
	dNSWin = GetWinProb(m_dNS, dNSLoss);
	dTemp = (dSWin-dSLoss)*2 - (dNSWin-dNSLoss);
	m_dWS = dTemp;
	if (dTemp > 0){
//		for (int k =1; k<29; k++){
//			m_dMeProb[k] -= m_dNS[k];
//			m_dMeProb[k] += m_dS[k];
//		}
//		m_dSplitAdvantage += dSWin - dSLoss;
		m_dSplitAdvantage += dTemp;
		if (m_nIsSplit == 1){
			SetMatrix(m_nIsSplit*2, SPLIT, TRUE);
		}
		SetMatrix(m_nIsSplit*2, SPLIT, FALSE);
		//might have to multiply this by some factor 
		//when we have 0 cards.  
	}
	else{
		int q = 0;
//		m_dSplitAdvantage += dTemp;
	}
	m_nIsSplit = FALSE;
	ResetArray(m_dNS);
	ResetArray(m_dS);
}

void CBjDlg::SetDD(){
	double dDDWin;
	double dDDLoss;
	double dNDDWin;
	double dNDDLoss;
	double dTemp;
	double dTempDD = 0;
	double dTempNDD = 0;
//	for (int i = 1; i<31; i++){
//		dTempDD += m_dDD[i];
//		dTempNDD += m_dNDD[i];
//	}

	int nHasAce = 0;
	dDDWin = GetWinProb(m_dDD, dDDLoss, m_nIsDD);
	dNDDWin = GetWinProb(m_dNDD, dNDDLoss);
	dTemp = (dDDWin-dDDLoss)*2 - (dNDDWin-dNDDLoss);
	m_dWDD = dTemp;
	if (dTemp > 0){
		if (m_nIsDD > 100){
			nHasAce = 1;
			m_nIsDD -= 100;
		}
//		for (int k =1; k<29; k++){
//			m_dMeProb[k] -= m_dNDD[k];
//			m_dMeProb[k] += m_dDD[k];
//		}
//		m_dDDAdvantage += dDDWin - dDDLoss;
		//should double down here.  
		//what do we win?
		m_dDDAdvantage += dTemp;
		SetMatrix(m_nIsDD, DOUBLE, nHasAce);
		//might have to multiply this by some factor 
		//when we have 0 cards.  
	}
	else{
//		m_dDDAdvantage += dTemp;
		int q = 0;
	}
	m_nIsDD = FALSE;
	ResetArray(m_dNDD);

}

int CBjDlg::GetDealerProb(CHand& DealerHand, double* pDealerProb){
	CHand hand = DealerHand;

	if (hand.ShouldHit(TRUE)){
		Hit(hand, m_Deck, pDealerProb[0]);
	}
	else{
		pDealerProb[hand.m_nTotalValue] = 1;
		m_dProbTotal = 1;
	}
	return TRUE;
}

int CBjDlg::GetMeProb(CHand& MeHand, double* pMeProb){
	
	if (m_handDealer.m_nNumCards == 0){
		m_strCommand = "Hit";
		double dMeTotal[32];
		for (int k = 0; k<32; k++){
			dMeTotal[k] = 0;
		}
		double deckProb;

		for (int i = 0; i<m_Deck.m_nCards; i++){
			CHand hand;
			CDeck deck = m_Deck;
			ResetArray(m_dDealerProb);
			ResetArray(m_dMeProb);
			if (deck.m_pCards[i].m_nNumAvailable - deck.m_pCards[i].m_nNumPlayed > 0){
				deckProb = (double)(deck.m_pCards[i].m_nNumAvailable - deck.m_pCards[i].m_nNumPlayed);
				deckProb /= (double)(deck.m_nNumAvailable - deck.m_nNumPlayed);
				hand.Hit(deck.m_pCards[i].m_nValue);
				deck.Play(deck.m_pCards[i].m_nValue);

				m_handDealer = hand;
				m_dDealerProb[0] = 1;//deckProb;
				GetDealerProb(hand, m_dDealerProb);
				
				if (HitOnce(MeHand, deck, deckProb)){
					Hit(MeHand, deck, deckProb, FALSE);
				}
				else {
					pMeProb[MeHand.m_nTotalValue] += deckProb;
					m_dProbTotal += deckProb;
				}

				for (k = 0; k<32; k++){
					dMeTotal[k] += m_dMeProb[k];
//					m_dMeProb[k]/=deckProb;
				}

				UpdateWinPct();
			}
		}
		CHand hand;
		m_handDealer = hand;
		for (k = 0; k<32; k++){
			m_dMeProb[k] = dMeTotal[k];
		}
	}

	else{
		if (HitOnce(MeHand, m_Deck, 1)){
			double dTemp = m_dWOHit;
			//fill me w/o hit
			Hit(MeHand, m_Deck, 1, FALSE);
			m_dWOHit = dTemp;
			m_dWHit = 0;
			if (MeHand.m_nNumCards == 2){
				m_strCommand = "";
				if (m_nIsDD){
					SetDD();
					if (m_dDDAdvantage > 0){
						m_strCommand = "Double Down";
					}
				}
				if (m_nIsSplit){
					SetS();
					if (m_nIsDD){
						if (m_dSplitAdvantage > m_dDDAdvantage){
							m_strCommand = "Split";
						}
					}
					else if (m_dSplitAdvantage > 0){
						m_strCommand = "Split";
					}
				}
				if (m_strCommand.IsEmpty()){
					m_strCommand = "Hit";
				}
			}
			else{
				m_strCommand = "Hit";
			}
		}
		else{
			//fill me whit
			m_dNS[MeHand.m_nTotalValue] = 1;
			if (m_nIsSplit){
				SetS();
			}
			if (m_dSplitAdvantage > 0){
				m_strCommand = "Split";
			}
			else{
				m_strCommand = "Stand";
			}
			pMeProb[MeHand.m_nTotalValue] = 1;
			m_dProbTotal = 1;
		}
		UpdateWinPct();
		if (m_dWHit == 0){
			m_dWHit = m_dMeW - m_dDealerW;
		}
	}
	return TRUE;
}


double CBjDlg::GetWProbability(CPtrList& lstMeCards, CPtrList& lstDealerCards, CDeck& deck){

	return 0;
}


int CBjDlg::LoadDlg(CDeck& deck, CHand& dealer, CHand& me){

	return TRUE;
}

void CBjDlg::ToggleMistake(){
	UpdateList();
	OnHandOver();
}

int CBjDlg::LoadDlg(CMistake* pMistake){
	m_nIsMistake = TRUE;
	CDeck deck = m_Deck;
	m_Deck = pMistake->m_Deck;
	int nCards =0;
	int i = 0;
	if (pMistake->m_nMistake >= 0){
		m_Deck.m_pCards[pMistake->m_Dealer.m_pnCards[0]-1].m_nNumPlayed--;
		nCards = pMistake->m_Me.m_nNumCards;
		for (i = 0; i< nCards; i++){
			m_Deck.m_pCards[pMistake->m_Me.m_pnCards[i]-1].m_nNumPlayed--;	
		}
		//this lets us change the decision matrix which I think is important.
		m_nIsPractice = 0;
	}
	else{
		//turn it into nonpractice mode
		m_nIsPractice = 0;
	}
	ToggleMistake();

	if (pMistake->m_nMistake >= 0){
		OnDealer(IDC_BUTTON_D1 - 1 + pMistake->m_Dealer.m_pnCards[0]);
		for (i = 0; i< nCards; i++){
			OnMe(IDC_BUTTON_M1 - 1 + pMistake->m_Me.m_pnCards[i]);
		}	
	}
	//turn it back to practice mode.
	m_nIsPractice = 1;
	m_Deck = deck;
	m_nIsMistake = FALSE;
	return TRUE;
}


void CBjDlg::OnMenuitemHelpAbout(){
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();	
}

void CBjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBjDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBjDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBjDlg::OnRadioDealer2() 
{
	Calculate();
}

void CBjDlg::OnRadioHitStand(){
	m_nHitStand = 1;
	UpdateMatrices();
//	Calculate();
}


void CBjDlg::OnRadioSplit(){
	m_nHitStand = 3;
	UpdateMatrices();
//	Calculate();
}

void CBjDlg::OnRadioDouble(){
	m_nHitStand = 2;
	UpdateMatrices();
//	Calculate();
}

void CBjDlg::OnRadioAce(){
	m_nHitStand = 4;
	UpdateMatrices();
//	Calculate();
}

void CBjDlg::OnWon(){
	m_nWon++;
}

void CBjDlg::OnLost(){
	m_nLost++;
}

void CBjDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1){
		//autoplay timer
		if (m_nAutoplay){
			//temp solution to watch lots of hands
			m_DlgPractice.m_nSpeed = 5;
			m_DlgPractice.OnButtonBet();
/*
			//simulate deal
			int nSimulate = TRUE;
			while (nSimulate){
				int nRand = rand()%13;
				if (nRand > 9)
					nRand = 9;
				CHand hand = m_handMe;
				if (m_handDealer.m_nNumCards == 0){
					//random 
					m_editDealer.SetFocus();
					OnNumber(ID_1+nRand);
				}
				else if (HitOnce(hand, m_Deck, 1)){
					m_editMe.SetFocus();
					OnNumber(ID_1+nRand);
				}
				else if (m_handMe.m_nTotalValue<22){
					m_editDealer.SetFocus();
					while (m_handDealer.ShouldHit(TRUE)){
						OnNumber(ID_1+nRand);
						nRand = rand()%13;
						if (nRand > 9)
							nRand = 9;
					}
					nSimulate = FALSE;
				}
				else{
					nSimulate = FALSE;
				}
			}
			OnHandOver();
*/
			
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CBjDlg::OnCheckAutoplay() 
{
	m_nAutoplay = !m_nAutoplay;
}

void CBjDlg::OnCheckAllManual() 
{
	m_nAllManual = !m_nAllManual;
}

void CBjDlg::OnMenuitemViewMistakes() 
{
	m_DlgMistakes.LoadMistakes();
	m_DlgMistakes.ShowWindow(SW_SHOW);
	
}

void CBjDlg::OnMenuitemViewPractice() 
{
	m_nIsPractice = TRUE;
	m_DlgPractice.ShowWindow(SW_SHOW);	
	
}

void CBjDlg::OnMenuitemViewSettings() 
{
	int nModal = m_pSettingsSheet->DoModal();	
	if (nModal==IDOK){
		if (m_pPropCasino->m_nNumDecks != m_Deck.m_nDecks){
			//reshuffle reset
			CDeck deck(m_pPropCasino->m_nNumDecks);
			m_Deck = deck;
			m_DlgPractice.Startup();
			OnReshuffle();
		}
		m_nLowBet = m_pPropBid->m_nLowBet;
		m_nHighBet = m_pPropBid->m_nHighBet;
		m_DlgPractice.m_nSpeed = m_pPropPlay->m_nPlaySpeed;
		m_DlgPractice.m_nNumPlayers = m_pPropPlay->m_nNumPlayers;
		CHand::m_DealerRules.m_nHitSoft17 = m_pPropCasino->m_nHitSoft17;

	}
	
}

int CBjDlg::AddMistakeToHistory(CMistake* pMistake, CBJHistory& bjHistory, int nWho){
	CTimeSpan span = CTime::GetCurrentTime() - bjHistory.m_StartTime;
	CMistake* pCopy;	//don't think I need
	if (span.GetDays() < 1){
		if (nWho ==0){
			m_DayHistory.m_plstMistakes->AddTail(pMistake);
		}
		else{
			m_DayHistory.m_plstStandardMistakes->AddTail(pMistake);
		}
	}
	if (span.GetDays() < 7){
		if (nWho ==0){
			m_WeekHistory.m_plstMistakes->AddTail(pMistake);
		}
		else{
			m_WeekHistory.m_plstStandardMistakes->AddTail(pMistake);
		}
	}
	if (span.GetDays() < 30){
		if (nWho ==0){
			m_MonthHistory.m_plstMistakes->AddTail(pMistake);
		}
		else{
			m_MonthHistory.m_plstStandardMistakes->AddTail(pMistake);
		}
		
	}
	if (span.GetDays() < 365){
		if (nWho ==0){
			m_YearHistory.m_plstMistakes->AddTail(pMistake);
		}
		else{
			m_YearHistory.m_plstStandardMistakes->AddTail(pMistake);
		}
	}
	//otherwise delete somehow
	return TRUE;
}

int CBjDlg::HistoryHelp(CBJHistory* pHistory, CBJHistory& bjHistory){
	double d1;
	double d2;
	int n1;
	int n2;
	d1 = pHistory->m_dAvgStandardCount;
	d2 = bjHistory.m_dAvgStandardCount;
	n1 = pHistory->m_nHandsPlayed;
	n2 = bjHistory.m_nHandsPlayed;
	pHistory->m_dAvgStandardCount = AVG(d1, d2, n1, n2);
	d1 = pHistory->m_dWinPerHand;
	d2 = bjHistory.m_dWinPerHand;
	pHistory->m_dWinPerHand = AVG(d1, d2, n1, n2);
	pHistory->m_dTotalPossible += bjHistory.m_dTotalPossible;
	pHistory->m_dTotalPossible2 += bjHistory.m_dTotalPossible2;
	pHistory->m_nHandsPlayed += bjHistory.m_nHandsPlayed;
	pHistory->m_TimePlayed += bjHistory.m_TimePlayed;	
	pHistory->m_nRealWin += bjHistory.m_nRealWin;
	return TRUE;
}

int CBjDlg::AddHistoryToHistory(CBJHistory& bjHistory){
	CTimeSpan span = CTime::GetCurrentTime() - bjHistory.m_StartTime;
	CMistake* pCopy;	//don't think I need
	CBJHistory* pHistory;
	if (span.GetDays() < 1){
		pHistory = &m_DayHistory;
		HistoryHelp(pHistory, bjHistory);
	}
	if (span.GetDays() < 7){
		pHistory = &m_WeekHistory;
		HistoryHelp(pHistory, bjHistory);
	}
	if (span.GetDays() < 30){
		pHistory = &m_MonthHistory;
		HistoryHelp(pHistory, bjHistory);
	}
	if (span.GetDays() < 365){
		pHistory = &m_YearHistory;
		HistoryHelp(pHistory, bjHistory);
	}
	return TRUE;
}

int CBjDlg::LoadHistory(){
	try{
		CFile file("History.dat", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
		CBJHistory bjHistory;
		int nLength = file.GetLength();
		char* buf = (char*)malloc(nLength);
		file.Read(buf, nLength);
		char* bufPtr = buf;
		int nPos = 0;
		CMistake* pMistake = NULL;
		//have to check for corrupt file
		int nLoop = 1;
		while (bufPtr < buf + nLength){
			memcpy((void*)&bjHistory, bufPtr, sizeof(bjHistory)-8);
			bufPtr += sizeof(bjHistory)-8;
			AddHistoryToHistory(bjHistory);
			nLoop = 1;
			while ((bufPtr < buf + nLength) && nLoop){
				pMistake = new CMistake();
				pMistake->Read(bufPtr);
				if (pMistake->m_nBet == -1){
					//finished with my mistakes
					nLoop = 0;
				}
				else{
					//add mistake
					AddMistakeToHistory(pMistake, bjHistory, 0);
				}
			}
			nLoop = 1;
			while ((bufPtr < buf + nLength) && nLoop){
				pMistake = new CMistake();
				pMistake->Read(bufPtr);
				if (pMistake->m_nBet == -1){
					//finished with standard
					nLoop = 0;
				}
				else {
					//add mistake
					AddMistakeToHistory(pMistake, bjHistory, 1);
				}
			}

		}		
	} catch (...){
	
	}
	return TRUE;	
}

int CBjDlg::CreateSessionHistory(CBJHistory& bjHistory){
	CTime now = CTime::GetCurrentTime();
	CTime start = now - m_TotalPlayTime;
	bjHistory.m_StartTime = start;
	bjHistory.m_EndTime = now;
	m_DlgMistakes.ResetMistakes(SESSION_MISTAKE);
	bjHistory.m_dAvgStandardCount = m_DlgMistakes.m_dAvgStandardCount;
	bjHistory.m_dTotalPossible = m_DlgMistakes.m_dTotalPossible;
	bjHistory.m_dTotalPossible2 = m_DlgMistakes.m_dTotalPossible2;
	bjHistory.m_dWinPerHand = m_DlgMistakes.m_dWinPerHand;
	bjHistory.m_nHandsPlayed = m_DlgMistakes.m_nHandsPlayed;
	bjHistory.m_TimePlayed = m_TotalPlayTime;
	bjHistory.m_nRealWin = m_DlgPractice.m_nSessionMoney;
	return TRUE;
}

void CBjDlg::OnClose() 
{
	//save the settings here.
	
	CreateSessionHistory(m_SessionHistory);
	CMistake* pMistake =NULL;
	try{
		CFile file("History.dat", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
		file.SeekToEnd();
		file.Write((void*)&m_SessionHistory, sizeof(m_SessionHistory)-8);
		POSITION pos = m_lstMistakes.GetHeadPosition();
		while (pos !=NULL){
			pMistake = (CMistake*)m_lstMistakes.GetNext(pos);
			pMistake->Write(&file);
//			delete pMistake;
		}
		CMistake mistake;
		mistake.m_nBet = -1;
		mistake.Write(&file);  //blank mistake to know the end
		pos = m_lstStandardMistakes.GetHeadPosition();
		while (pos !=NULL){
			pMistake = (CMistake*)m_lstStandardMistakes.GetNext(pos);
			pMistake->Write(&file);
//			delete pMistake;
		}
		mistake.m_nBet = -1;
		mistake.Write(&file);  //blank mistake to know the end
	} catch(...){
		
	}
	//this empties all lists here
	m_YearHistory.EmptyLists();

	CDialog::OnClose();
}

void CBjDlg::OnMenuShowCount() 
{
	int i = 0;
	CCountDlg dlg;
	dlg.m_nCount = 0;
	for (i = 2; i<7; i++){
		dlg.m_nCount += m_Deck.m_pCards[i-1].m_nNumPlayed;
	}
	i = 10;
	dlg.m_nCount -= m_Deck.m_pCards[i-1].m_nNumPlayed;
	i = 1;
	dlg.m_nCount -= m_Deck.m_pCards[i-1].m_nNumPlayed;
	dlg.DoModal();
	
}
