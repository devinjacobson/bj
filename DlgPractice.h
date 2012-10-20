#if !defined(AFX_DLGPRACTICE_H__3315DF7F_2011_42D1_A03D_BC4DE0A13954__INCLUDED_)
#define AFX_DLGPRACTICE_H__3315DF7F_2011_42D1_A03D_BC4DE0A13954__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPractice.h : header file
//

#include "..\CardLib\CardLib.h"

#define DECK_ID 1

#define TURN_INITIAL -1
#define TURN_ME 0
#define TURN_COMP 1//through 10
#define TURN_DEAL 11
#define TURN_STANDARD 12
/////////////////////////////////////////////////////////////////////////////
// CDlgPractice dialog
class CBjDlg;
class CDlgPractice : public CDialog
{
// Construction
public:
	CDlgPractice(CWnd* pParent = NULL);   // standard constructor
	CBjDlg* m_pBjDlg;
	CardStack m_Cards;
	CardStack m_Cards1;
	CardStack m_Cards2;
	CardStack m_FullCards;
	
	int m_nTimer;
	int m_nDeck;
	int m_nBet;
	int m_nNumDecks;
	int m_nSpeed;
	int m_nWhoseTurn;
	int m_nRemove;
	CardRegion* m_pDeck;
	CardRegion* m_pDealer;
	CardRegion* m_pPlayers[10];
	
	CardButton* m_pPlayerName[5];
	CardButton* m_pPlayerBet[5];
	CardButton* m_pPlayerMoney[5];
	CardButton* m_pMyHand[2];
	CardButton* m_pInfo;
	int m_nPlayerMoney[5];
	int m_nPlayerBet[5];
	int m_nNumPlayers;

	int m_nCardsPlayed;
	int m_nSessionMoney;
	double m_dBJRemainder[5];
	int m_nDoubled;
	int m_nSplit;
	CPtrList m_lstDealer;
	CPtrList m_lstMe;
	CPtrList m_lstPlayers;
	CPtrList m_lstBets;
	CPtrList m_lstDoubles;
	void StoreCounts();
	void UpdateMoney(int nPlayer = 0);
	void UpdateBet(int nPlayer = 0);
	void SetBet(int nPlayer, int nBet);
	int GetValue(CardStack cards);
	int Hit(CardStack cards);
	void GetCardRegion(CardRegion*& pRegion);	//this is for splits
	void PlayStandard();
	void Startup();
	void OnDealer(int nCardValue);
	void OnMe(int nCardValue);
	void OnOther(int nCardValue);
	Card GetCard(int nCardValue);
	//int m_nMyControl;
// Dialog Data
	//{{AFX_DATA(CDlgPractice)
	enum { IDD = IDD_DIALOG_PRACTICE };
	int		m_nWager;
	int		m_nMoney;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPractice)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CDlgPractice)
	virtual BOOL OnInitDialog();
	afx_msg void OnMenuDeckSettings();
	afx_msg void OnMenuDeckReshuffle();
	afx_msg void OnMenuShowCount();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonBet();
	afx_msg void OnButtonDouble();
	afx_msg void OnButtonHit();
	afx_msg void OnButtonSplit();
	afx_msg void OnButtonStand();
	afx_msg void OnMenuViewmistakes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRACTICE_H__3315DF7F_2011_42D1_A03D_BC4DE0A13954__INCLUDED_)
