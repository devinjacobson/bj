// bjDlg.h : header file
//

#if !defined(AFX_BJDLG_H__6D6B59B0_253C_448A_AE04_34A11CD5A632__INCLUDED_)
#define AFX_BJDLG_H__6D6B59B0_253C_448A_AE04_34A11CD5A632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBjDlg dialog

#include "DialogMistakes.h"
#include "DlgPractice.h"

#define HIT 1
#define STAND 2
#define DOUBLE 3
#define SPLIT 4

class CPropCasino;
class CPropBid;
class CPropPlay;
class CPropStrategy;
class CBjDlg : public CDialog
{
// Construction
public:
	CBjDlg(CWnd* pParent = NULL);	// standard constructor
	void MakeAllVisible();
	CDeck m_Deck;

	CPropertySheet* m_pSettingsSheet;
	CPropCasino* m_pPropCasino;
	CPropBid* m_pPropBid;
	CPropPlay* m_pPropPlay;
	CPropStrategy* m_pPropStrategy;

	static CCriticalSection m_Sect;
	static int m_nCreated;
	static double m_dTotalPossible;
	int m_nThread;
// Dialog Data
	//{{AFX_DATA(CBjDlg)
	enum { IDD = IDD_BJ_DIALOG };
	CSpinButtonCtrl	m_spinWager;
	static CListCtrl	m_listDecision;
	CEdit	m_editMe;
	CEdit	m_editDealer;
	CListCtrl	m_listRemaining;
	BOOL	m_nAutoplay;
	BOOL	m_nAllManual;
	double	m_dDealerW;
	double	m_dMeW;
	int		m_nWager;
	int		m_nMe;
	double	m_dProbTotal;
	CString m_strDealer;
	CString m_strMe;
	int		m_nDealer;
	int		m_nHitStand;
	//}}AFX_DATA
	static double	m_dTotal;
	static int		m_nWon;
	static int		m_nLost;
	static CTimeSpan m_TotalPlayTime;
	static double m_dAvgStandardCount;

	int m_nIsPractice;
	int m_nIsMistake;
	HACCEL m_hAccel;
	void UpdateList(int nValue = 0);

	//temporary decision percentages.
	double m_dWHit;
	double m_dWOHit;
	double m_dWDD;
	double m_dWS;


	CDialogMistakes m_DlgMistakes;
	CDlgPractice m_DlgPractice;
	//possibilities functions
	CMistake* GetMistake();
	void ToggleMistake();
	
	CPtrList m_lstDecks;
	static CPtrList m_lstMistakes;
	static CPtrList m_lstStandardMistakes;
	static int m_nStandardBet;
	static int m_nHighBet;
	static int m_nLowBet;

	//I may want to play through the whole deck and then calculate later
	int LoadDlg(CDeck& deck, CHand& dealer, CHand& me);
	int LoadDlg(CMistake* pMistake);

	void ResetMatrices();
	void UpdateMatrices();
	void SetMatrix(int nHandValue, int nFunction, int nHasAce = FALSE);
	//decision matrices are [dealer card][2 card sum]

	//watch for double thread access to this
	//3 is the standard
	static int m_nAceDecisionMatrix[3][10][22];
	static int m_nDecisionMatrix[3][10][22];
	static int m_nDoubleDecisionMatrix[3][10][22];
	static int m_nSplitDecisionMatrix[3][10][22];
	
	static int m_nHandsPlayed;
	double m_dAvgProbW;
	CHand m_handDealer;
	CHand m_handMe;
	double m_dDealerProb[32];	//probabilities array indexed
	double m_dMeProb[32];		//probabilities array indexed
	double m_dMeProbWHit[32];
	double m_dDisplay[32];

	double m_dDD[32];		//double down probability
	double m_dNDD[32];		//no double down temp probability.  
	double m_dS[32];		//with split
	double m_dNS[32];		//without split.  
	int m_nIsSplit;
	double m_dDDAdvantage;
	double m_dSplitAdvantage;
	CString m_strCommand;
	int m_nIsDD;
	double m_dLastMeW;
	double m_dLastDealerW;
	double m_d32PayoutProb;
	double Get32PayoutProb(CHand hand, CDeck deck);
	void Calculate();
	void ResetArray(double* pD);
	double GetWinProb(CHand& hand, double& dLoss);
	double GetWinProb(double* pProb, double& dLoss, int nAddTen =TRUE);

	void UpdateProbabilities();
	void UpdateWinPct();
	void SetDD();
	void SetS();
	int HitOnce(CHand& hand, CDeck& deck, double dProb);
	int Hit(CHand hand, CDeck deck, double dProb, int nIsDealer = TRUE, double* pProb = NULL);
	int GetDealerProb(CHand& DealerHand, double* pDealerProb);
	int GetMeProb(CHand& MeHand, double* pMeProb);
	double GetWProbability(CPtrList& lstMeCards, CPtrList& lstDealerCards, CDeck& deck);
	int PlayCard(int nValue, int nWho, int nDouble = FALSE, int nIsSplit = FALSE);

	int CreateSessionHistory(CBJHistory& bjHistory);
	int AddMistakeToHistory(CMistake* pMistake, CBJHistory& bjHistory, int nWho = 0);
	int AddHistoryToHistory(CBJHistory& bjHistory);
	int HistoryHelp(CBJHistory* pHistory, CBJHistory& bjHistory);
	
	int LoadHistory();
	
	static CBJHistory m_SessionHistory;
	static CBJHistory m_DayHistory;
	static CBJHistory m_WeekHistory;
	static CBJHistory m_MonthHistory;
	static CBJHistory m_YearHistory;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBjDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:	
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBjDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDealerFocus();
	afx_msg void OnMenuShowCount();
	afx_msg void OnMeFocus();
	afx_msg void OnReshuffle();
	afx_msg void OnHandOver();
	afx_msg void OnNewHand();
	afx_msg void OnRadioDealer2();
	afx_msg void OnRadioHitStand();
	afx_msg void OnRadioSplit();
	afx_msg void OnRadioDouble();
	afx_msg void OnRadioAce();
	afx_msg void OnWon();
	afx_msg void OnLost();
	afx_msg void OnNobody();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNumber(UINT nId);
	afx_msg void OnMe(UINT nId);
	afx_msg void OnOther(UINT nId);
	afx_msg void OnDealer(UINT nId);
	afx_msg void OnCheckAutoplay();
	afx_msg void OnCheckAllManual();
	afx_msg void OnMenuitemViewMistakes();
	afx_msg void OnMenuitemViewPractice();
	afx_msg void OnMenuitemViewSettings();
	afx_msg void OnMenuitemHelpAbout();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BJDLG_H__6D6B59B0_253C_448A_AE04_34A11CD5A632__INCLUDED_)
