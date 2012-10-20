// DlgPractice.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "DlgPractice.h"
#include "DialogMistakes.h"
#include "BjDlg.h"
#include "PropPlay.h"
#include "PropCasino.h"
#include "CountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPractice dialog
#define PRACTICE_TIMER 50
#define BASE_TIMER 200

CardWindow BjWnd;


CDlgPractice::CDlgPractice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPractice::IDD, pParent)
{
	for (int i = 0; i< 5; i++)
		m_dBJRemainder[i] = 0;
	m_nSessionMoney = 0;
	m_nSpeed = 1;
	m_nNumPlayers = 5;
	m_nNumDecks = 6;
	m_nBet = 0;
	m_nDoubled = 0;
	m_nSplit = 0;
	m_nTimer = 0;
	m_nCardsPlayed = 0;
	//{{AFX_DATA_INIT(CDlgPractice)
	m_nWager = 0;
	m_nMoney = 1000;
	//}}AFX_DATA_INIT
}


void CDlgPractice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPractice)
	DDX_Text(pDX, IDC_EDIT_WAGER, m_nWager);
	DDV_MinMaxInt(pDX, m_nWager, CBjDlg::m_nLowBet, CBjDlg::m_nHighBet);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_nMoney);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPractice, CDialog)
	//{{AFX_MSG_MAP(CDlgPractice)
	ON_COMMAND(ID_MENU_DECK_SETTINGS, OnMenuDeckSettings)
	ON_COMMAND(ID_MENU_DECK_RESHUFFLE, OnMenuDeckReshuffle)
	ON_COMMAND(ID_MENU_SHOW_COUNT, OnMenuShowCount)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_BET, OnButtonBet)
	ON_BN_CLICKED(IDC_BUTTON_DOUBLE, OnButtonDouble)
	ON_BN_CLICKED(IDC_BUTTON_HIT, OnButtonHit)
	ON_BN_CLICKED(IDC_BUTTON_SPLIT, OnButtonSplit)
	ON_BN_CLICKED(IDC_BUTTON_STAND, OnButtonStand)
	ON_COMMAND(ID_MENU_VIEWMISTAKES, OnMenuViewmistakes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPractice message handlers

BOOL CDlgPractice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;
	this->GetClientRect(&rect);
	BjWnd.Create(this->m_hWnd, WS_EX_CLIENTEDGE, WS_CHILD|WS_VISIBLE, 0, 0, rect.Width(), rect.Height());
	::MoveWindow(BjWnd, rect.left+100, rect.top, rect.Width()-100, rect.Height(), TRUE);
	
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_BACK);
//	bmp.SetBitmapDimension(rect.Width(), rect.Height());
	BjWnd.SetBackImage((HBITMAP)bmp);
	m_pDeck = BjWnd.CreateRegion(DECK_ID, true, 0, 0, 2, 0);
	m_pDeck->SetEmptyImage(CS_EI_SUNK);
//	m_pDeck->SetThreedCount(6);
	m_pDeck->SetDragRule(CS_DRAG_NONE, 0);
	m_pDeck->SetDropRule(CS_DROP_NONE, 0);
//	m_pDeck.SetClickProc(DeckClickProc);
//	m_pDeck.SetDblClickProc(DeckClickProc);
	m_pDeck->SetFaceDirection(CS_FACE_DOWN, 0);

	CString strLabel;
	for (int i=0; i<m_nNumPlayers; i++){
		int y = 200;
		int x = i*120+80;
		int v = (m_nNumPlayers/2)-i;
		if (v < 0){
			v = -v;
		}
		y -= v*20;
		m_pPlayers[i] = BjWnd.CreateRegion(i+2, true, x, y, 10, 10);
		
		m_pPlayers[i]->SetEmptyImage(CS_EI_SUNK);
		m_pPlayers[i]->SetPlacement(CS_XJUST_CENTER, 0, i * (__cardwidth + 30) , 0);
		m_pPlayers[i]->SetDragRule(CS_DRAG_NONE, 0);
		m_pPlayers[i]->SetDropRule(CS_DROP_NONE, 0);
		m_pPlayers[i]->SetFaceDirection(CS_FACE_UP, 0);

		if (i==0){
			strLabel = "Me";
		}
		else{
			strLabel.Format("Player%d", i);
		}
		m_pPlayerName[i] = BjWnd.CreateButton(i, (char*)(LPCTSTR)strLabel, CB_STATIC, true, x, y-40, 60, 20);
		strLabel = "Bet: $0";
		m_pPlayerBet[i] = BjWnd.CreateButton(i, (char*)(LPCTSTR)strLabel, CB_STATIC, true, x, y-20, 60, 20);
		strLabel = "Bank: $1000";
		m_pPlayerMoney[i] = BjWnd.CreateButton(i, (char*)(LPCTSTR)strLabel, CB_STATIC, true, x, y-60, 60, 20);
		m_nPlayerMoney[i] = 1000;

	}

	strLabel = "Hand1";
	m_pMyHand[0] = BjWnd.CreateButton(i, (char*)(LPCTSTR)strLabel, CB_STATIC, false, 20, 180, 60, 20);
	strLabel = "Hand2";
	m_pMyHand[1] = BjWnd.CreateButton(i, (char*)(LPCTSTR)strLabel, CB_STATIC, false, 10, 220, 60, 20);
	strLabel = "BET TO START";
	m_pInfo = BjWnd.CreateButton(i, (char*)(LPCTSTR)strLabel, CB_STATIC, true, 550, 20, 100, 20);


	m_pDealer = BjWnd.CreateRegion(i+2, true, 320, 0, 10, 10);
	m_pDealer->SetEmptyImage(CS_EI_SUNK);
	m_pDealer->SetPlacement(CS_XJUST_CENTER, 0, (__cardwidth + 30) , 0);
	m_pDealer->SetDragRule(CS_DRAG_NONE, 0);
	m_pDealer->SetDropRule(CS_DROP_NONE, 0);
	m_pDealer->SetFaceDirection(CS_FACE_UP, 0);


/*
	pPile = SolWnd.CreateRegion(PILE_ID, true, 110, yBorder, CS_DEFXOFF, 1);
	pPile->SetEmptyImage(CS_EI_NONE);
	pPile->SetDragRule(CS_DRAG_TOP, 0);
	pPile->SetDropRule(CS_DROP_NONE, 0);
	pPile->SetDblClickProc(PileDblClickProc);
	pPile->SetRemoveCardProc(PileRemoveProc);
*/	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPractice::OnMenuDeckSettings() 
{
	m_pBjDlg->OnMenuitemViewSettings();
}

void CDlgPractice::OnMenuDeckReshuffle() 
{
	m_nNumDecks = m_pBjDlg->m_pPropCasino->m_nNumDecks;
	m_nDeck = 0;
	m_Cards.Pop(m_Cards.NumCards());
	m_Cards1.Pop(m_Cards1.NumCards());
	m_Cards2.Pop(m_Cards2.NumCards());
	for (int i=0; i<m_nNumDecks; i++){
		CardStack deck;
		deck.NewDeck();
#ifdef TRAIN
		for (int j=0; j < deck.NumCards(); j++){
			if (deck[j].LoVal()>7 && deck[j].LoVal()<10 ){
				deck.RemoveCard(j);
				j--;
			}
		}
#endif
		deck.Shuffle();
		if (i<2){
			m_Cards += deck;
		}
		else if (i<4){
			m_Cards1 += deck;
		}
		else if (i<6){
			m_Cards2 += deck;
		}
	}
	CardStack temp;
	CardStack temp2;
	CardStack temp3;
	//shuffling
	for (i = 0; i< m_nNumDecks; i++){
		temp = m_Cards.Pop(52);
		temp2 = m_Cards1.Pop(52);
		temp3 = m_Cards2;
		m_Cards2 = temp + temp2;
		m_Cards2.Shuffle();
		m_Cards1 +=m_Cards;
		m_Cards1.Shuffle();
		m_Cards = temp3;
	}
	m_Cards.Shuffle();
	m_Cards1.Shuffle();
	m_Cards2.Shuffle();
	m_FullCards = m_Cards;
	m_pDeck->SetCardStack(m_FullCards);
	m_pDeck->Redraw();
	
	BjWnd.Redraw();
	m_nWhoseTurn = TURN_INITIAL;
	SetTimer(PRACTICE_TIMER, BASE_TIMER, NULL);	
}

void CDlgPractice::UpdateBet(int nPlayer){

}

void CDlgPractice::UpdateMoney(int nPlayer){
	if (nPlayer > m_nNumPlayers)
		return;
	CardRegion* pRegion = m_pPlayers[nPlayer];
	if (nPlayer == m_nNumPlayers)
		nPlayer=TURN_ME;
	int nWon = 0;
	int nDealer = GetValue(m_pDealer->GetCardStack());
	int nMe = GetValue(pRegion->GetCardStack());
	int nBet = m_nPlayerBet[nPlayer];

	//havent done blackjacks yet

	if (m_nDoubled){
		nBet*=2;
	}
	if (nMe < 22){
		if (nMe > nDealer){
			if (pRegion->GetCardStack().NumCards()==2){ 
				if (nMe == 21){
					double d = (double)nBet * 1.5;
					d += m_dBJRemainder[nPlayer];
					nBet = d;
					m_dBJRemainder[nPlayer] = d - (double)nBet;
				}
			}
			if (nPlayer==TURN_ME || nPlayer==m_nNumPlayers+TURN_ME){
				m_nMoney += nBet;
				m_nSessionMoney += nBet;
			}
			m_nPlayerMoney[nPlayer] += nBet;
		}
		else if (nMe==nDealer){
			//my blackjack vs 21
			if (nMe == 21){
				if (pRegion->GetCardStack().NumCards()==2 && m_pDealer->GetCardStack().NumCards()>2){ 
					double d = (double)nBet * 1.5;
					d += m_dBJRemainder[nPlayer];
					nBet = d;
					m_dBJRemainder[nPlayer] = d - (double)nBet;
					if (nPlayer==TURN_ME || nPlayer==m_nNumPlayers+TURN_ME){
						m_nMoney += nBet;
						m_nSessionMoney += nBet;
					}
					m_nPlayerMoney[nPlayer] += nBet;
				}
			}
		
		}
		else if (nDealer > 21){
			if (nPlayer==TURN_ME || nPlayer==m_nNumPlayers+TURN_ME){
				m_nMoney += nBet;
				m_nSessionMoney += nBet;
			}
			m_nPlayerMoney[nPlayer] += nBet;
		}
		else{
			if (nPlayer==TURN_ME || nPlayer==m_nNumPlayers+TURN_ME){
				m_nMoney -= nBet;
				m_nSessionMoney -= nBet;
			}
			m_nPlayerMoney[nPlayer] -= nBet;
		}
	}
	else{
		if (nPlayer==TURN_ME || nPlayer==m_nNumPlayers+TURN_ME){
			m_nMoney -= nBet;
			m_nSessionMoney -= nBet;
		}
		m_nPlayerMoney[nPlayer] -= nBet;
	}
	CString strMoney;
	strMoney.Format("Bank: $%d", m_nPlayerMoney[nPlayer]);
	m_pPlayerMoney[nPlayer]->SetText((char*)(LPCTSTR)strMoney);
	m_pPlayerBet[nPlayer]->SetText("Bet: $0");
	UpdateData(FALSE);
}

void CDlgPractice::StoreCounts(){
/*
	m_lstMe.AddTail((void*)m_pPlayers[0]->GetCardStack().NumCards());
	int nPlayers = 0;
	for (int i=1; i<m_nNumPlayers; i++){
		nPlayers += m_pPlayers[i]->GetCardStack().NumCards();
	}	
	m_lstPlayers.AddTail((void*)nPlayers);
	m_lstDealer.AddTail((void*)m_pDealer->GetCardStack().NumCards());
	m_lstDoubles.AddTail((void*)m_nDoubled);
*/
    m_nDoubled = 0;
	m_nSplit = 0;
	m_nBet =0;
}

int CDlgPractice::GetValue(CardStack cards){
	int nTotal = 0;
	int nCard = 0;
	int nHasAce = 0;
	for(int i = 0; i<cards.NumCards(); i++){
		nCard = cards[i].LoVal();
		if (nCard ==1){
			nHasAce = 1;
		}
		else if (nCard > 10){
			nCard = 10;
		}
		nTotal += nCard;
	}
	if (nHasAce){
		if (nTotal <= 11){
			nTotal +=10;
		}
	}
	return nTotal;

}

int CDlgPractice::Hit(CardStack cards){
	int nTotal = GetValue(cards);

	//check for soft 17 hits for dealer
	int i = rand()%4;
	if (nTotal+i > 16){
		return FALSE;
	}

	return TRUE;
}

Card CDlgPractice::GetCard(int nCardValue){
	Card card = m_Cards[0];
	int nCards = m_Cards.NumCards();
	int nValue = 0;
	for (int i = 0; i< nCards; i++){
		nValue = m_Cards[i].LoVal();
		if (nValue > 10){
			nValue = 10;
		}
		if (nValue == nCardValue){
			m_Cards[0] = m_Cards[i];
			m_Cards[i] = card;
			return m_Cards.Pop();
		}
	}	
	nCards = m_Cards1.NumCards();
	for ( i = 0; i< nCards; i++){
		nValue = m_Cards1[i].LoVal();
		if (nValue > 10){
			nValue = 10;
		}
		if (nValue == nCardValue){
			m_Cards[0] = m_Cards1[i];
			m_Cards1[i] = card;
			return m_Cards.Pop();
		}
	}	
	nCards = m_Cards2.NumCards();
	for (i = 0; i< nCards; i++){
		nValue = m_Cards2[i].LoVal();
		if (nValue > 10){
			nValue = 10;
		}
		if (nValue == nCardValue){
			m_Cards[0] = m_Cards2[i];
			m_Cards2[i] = card;
			return m_Cards.Pop();
		}
	}	
	return m_Cards.Pop();

}

void CDlgPractice::OnDealer(int nCardValue){
	Card card = GetCard(nCardValue);
}

void CDlgPractice::OnMe(int nCardValue){
	Card card = GetCard(nCardValue);
}

void CDlgPractice::OnOther(int nCardValue){
	Card card = GetCard(nCardValue);
}

void CDlgPractice::OnTimer(UINT nIDEvent) 
{
	Card card;
	if (nIDEvent == PRACTICE_TIMER){
		if (m_nTimer++ < m_nSpeed){
			return;
		}
		else {
			m_nTimer = 0;
		}
		if (m_pBjDlg->m_nAllManual){
			return;
		}
		if (m_nWhoseTurn ==TURN_ME){
			if (GetValue(m_pPlayers[TURN_ME]->GetCardStack())>=21){
				if (m_nSplit==1){
					OnButtonStand();
//					m_nSplit++;
				}
				else{
					if (!m_nSplit)
						m_nWhoseTurn = TURN_DEAL;
				}
			}
			else if (m_pBjDlg->m_nAutoplay){
				if (!Hit(m_pPlayers[TURN_ME]->GetCardStack())){
					OnButtonStand();
					m_nWhoseTurn = TURN_DEAL;
				}
				else{
					card = m_Cards.Pop();
					m_nCardsPlayed++;
					m_pBjDlg->PlayCard(card.LoVal(), TURN_ME);
					m_pPlayers[m_nWhoseTurn]->Push(card);
					m_pPlayers[m_nWhoseTurn]->Update();
				}
			}
		}
		else if (m_nWhoseTurn ==TURN_DEAL){

			if (!m_pBjDlg->m_handDealer.ShouldHit(TRUE)){
				//check for deck done.
				int nReshuffle = 0;
				int nPenetration = m_pBjDlg->m_pPropPlay->m_nPenetration;
				
				if (m_Cards.NumCards() < 24){
					if (m_nDeck == 0){
						m_Cards += m_Cards1;
						m_Cards1.Clear();
					}
					else if (m_nDeck == 1){
						m_Cards += m_Cards2;
						m_Cards2.Clear();
					}
					else {
						//this deck is done
						nReshuffle = 1;
					}
					m_nDeck++;
				}
				double dPenetration = m_pBjDlg->m_Deck.m_nNumPlayed;
				dPenetration /= m_pBjDlg->m_Deck.m_nNumAvailable;
				if (dPenetration*100 > nPenetration){
					nReshuffle = 1;
				}
				//check for penetration setting here

				for(int i = 0; i< m_nNumPlayers; i++){
					UpdateMoney(i);
				}
				if (m_nSplit){
					UpdateMoney(m_nNumPlayers+TURN_ME);
					BjWnd.DeleteRegion(m_pPlayers[m_nNumPlayers+TURN_ME]);
				}
				StoreCounts();
				m_pBjDlg->PlayCard(0, TURN_DEAL);
				m_nWhoseTurn = TURN_INITIAL;
				if (nReshuffle){
					OnMenuDeckReshuffle();	
					m_pBjDlg->OnReshuffle();
				}
			}
			else{
				card = m_Cards.Pop();
				m_nCardsPlayed++;
				m_pBjDlg->PlayCard(card.LoVal(), m_nWhoseTurn);
				m_pDealer->Push(card);
				m_pDealer->Update();
			}
		}
		else if (m_nWhoseTurn <= TURN_INITIAL){
			if (!m_nBet){
				int i=0;
				for (i = 0; i<m_nNumPlayers; i++){
					if (m_pPlayers[i]->NumCards()){
						m_pPlayers[i]->Pop(m_pPlayers[i]->GetCardStack().NumCards());
						m_pPlayers[i]->Update();
						i = m_nNumPlayers +1;
					}
				}
				if (i == m_nNumPlayers){
					m_pDealer->Pop(m_pDealer->GetCardStack().NumCards());
					m_pDealer->Update();
				}
				BjWnd.Redraw();				
			}
			else if (-m_nWhoseTurn < m_nNumPlayers){
				card = m_Cards.Pop();
				m_nCardsPlayed++;
				m_pBjDlg->PlayCard(card.LoVal(), TURN_COMP);
				m_pPlayers[m_nNumPlayers+m_nWhoseTurn]->Push(card);
				m_pPlayers[m_nNumPlayers+m_nWhoseTurn]->Update();
			
			}
			else if(-m_nWhoseTurn == m_nNumPlayers){
				//my turn
				card = m_Cards.Pop();
				m_nCardsPlayed++;
				m_pBjDlg->PlayCard(card.LoVal(), TURN_ME);
				m_pPlayers[m_nNumPlayers+m_nWhoseTurn]->Push(card);
				m_pPlayers[m_nNumPlayers+m_nWhoseTurn]->Update();
			}
			else if (-m_nWhoseTurn == m_nNumPlayers+1){
				//dealer
				card = m_Cards.Pop();
				m_nCardsPlayed++;
				m_pBjDlg->PlayCard(card.LoVal(), TURN_DEAL);
				m_pDealer->Push(card);
				m_pDealer->Update();
			}
			else if (-m_nWhoseTurn < m_nNumPlayers*2+2){
				//second round
				card = m_Cards.Pop();
				m_nCardsPlayed++;
				if (-m_nWhoseTurn == m_nNumPlayers*2+1){
					m_pBjDlg->PlayCard(card.LoVal(), TURN_ME);
				}
				else{
					m_pBjDlg->PlayCard(card.LoVal(), TURN_COMP);
				}
				m_pPlayers[m_nNumPlayers*2+1+m_nWhoseTurn]->Push(card);
				m_pPlayers[m_nNumPlayers*2+1+m_nWhoseTurn]->Update();
			}
			else {
				//initial deal over
				if (m_nWhoseTurn < 0){
					m_nWhoseTurn = m_nNumPlayers-1;
				}
				
			}
			if (m_nBet && m_nWhoseTurn < 0){
				m_nWhoseTurn--;
			}
		}
		else{ //players turn
			if (!Hit(m_pPlayers[m_nWhoseTurn]->GetCardStack())){
				m_nWhoseTurn--;
			}
			else{
				card = m_Cards.Pop();
				m_nCardsPlayed++;
				m_pBjDlg->PlayCard(card.LoVal(), TURN_COMP);
				m_pPlayers[m_nWhoseTurn]->Push(card);
				m_pPlayers[m_nWhoseTurn]->Update();
			}
						
		}
		if (m_nCardsPlayed >= m_nNumDecks/2){
			m_FullCards.Pop();
			m_pDeck->SetCardStack(m_FullCards);
			m_pDeck->Update();
			m_nCardsPlayed=0;

		}
		BjWnd.Redraw();
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgPractice::OnButtonBet() 
{
	if (!m_nBet){
		if (m_pBjDlg->m_nAutoplay){
			m_nWager = 1;			
		}
		else{
			UpdateData();
		}
		if (m_nWager > CBjDlg::m_nHighBet || m_nWager < CBjDlg::m_nLowBet){
			return;
		}
		//approximate 5 sec/hand + dealer
		CBjDlg::m_TotalPlayTime += CTimeSpan(5*m_nNumPlayers+5);
		for (int i=0; i<m_nNumPlayers; i++){
			m_pPlayers[i]->Pop(m_pPlayers[i]->GetCardStack().NumCards());
			m_pPlayers[i]->Update();
		}

		m_pDealer->Pop(m_pDealer->GetCardStack().NumCards());
		m_pDealer->Update();
		BjWnd.Redraw();
		
		CSingleLock lock(&CBjDlg::m_Sect);

		lock.Lock();
		if (!lock.IsLocked()){
			Sleep(10);
			lock.Lock();
		}
		
		m_nBet = m_nWager;  //allows the timer to deal cards
		
		CDeck* pDeck = new CDeck(m_pBjDlg->m_Deck);
		m_pBjDlg->m_lstDecks.AddTail(pDeck);		
		m_lstBets.AddTail((void*)m_nBet);
		
		lock.Unlock();
		

		m_pBjDlg->ToggleMistake(); //takes us out of looking at mistakes if we are
		SetBet(0, m_nBet);
		for (i = 1; i< m_nNumPlayers; i++){
			SetBet(i, rand()%5+1);
		}
	}
}

void CDlgPractice::SetBet(int nPlayer, int nBet){
	m_nPlayerBet[nPlayer] = nBet;
	CString strLabel;
	strLabel.Format("Bet: $%d", m_nPlayerBet[nPlayer]);
	m_pPlayerBet[nPlayer]->SetText((char*)(LPCTSTR)strLabel);
}

void CDlgPractice::PlayStandard(){
	//make the decision for the standard play and play that here.  
	if (m_pBjDlg->m_nHandsPlayed < 3){
		return;
	}
	else{
		int nDealerValue = GetValue(m_pDealer->GetCardStack());
		if (nDealerValue == 11){
			nDealerValue = 1;
		}
		int nMeValue = 0;
		int nCard = 0;
		int nHasAce = 0;
		int nTotal = 0;
		CardRegion* pRegion;
		GetCardRegion(pRegion);
		for(int i = 0; i<pRegion->GetCardStack().NumCards(); i++){
			nCard = pRegion->GetCardStack()[i].LoVal();
			if (nCard ==1){
				nHasAce = TRUE;
			}	
			else if (nCard > 10){
				nCard = 10;
			}
			nMeValue += nCard;
		}
		if (nDealerValue > 21 || nMeValue > 21 || nDealerValue < 1 || nMeValue < 1){
			return;
		}
		int nCommand = 0;
		int nDecision = m_pBjDlg->m_nDecisionMatrix[2][nDealerValue-1][nMeValue];
		int nAce = m_pBjDlg->m_nAceDecisionMatrix[2][nDealerValue-1][nMeValue];
		int nDouble = m_pBjDlg->m_nDoubleDecisionMatrix[2][nDealerValue-1][nMeValue];
		int nSplit = m_pBjDlg->m_nSplitDecisionMatrix[2][nDealerValue-1][nMeValue];
		
		if (nHasAce){
			nCommand = nAce;
		}
		else if (nDouble==DOUBLE){
			nCommand = nDouble;
		}
		else if (nSplit==SPLIT){
			nCommand = nSplit;
		}
		else{
			nCommand = nDecision;
		}
		if (nCommand==DOUBLE || nCommand==SPLIT){
			if (pRegion->GetCardStack().NumCards()==2){
				if (nCommand == SPLIT){
					if (pRegion->GetCardStack()[0].LoVal() != pRegion->GetCardStack()[1].LoVal()){
						nCommand = nDecision;
					}
				}
			}
			else{
				if (nHasAce && nMeValue < 11){
					nMeValue +=10;
					nCommand = m_pBjDlg->m_nDecisionMatrix[2][nDealerValue-1][nMeValue];
				}
				else{
					nCommand = nDecision;
				}
			}
		}
		switch(nCommand){
		case HIT:
			m_pBjDlg->PlayCard(1, TURN_STANDARD);
			break;
		case STAND:
			m_pBjDlg->PlayCard(0, TURN_STANDARD);
			break;
		case DOUBLE:
			m_pBjDlg->PlayCard(1, TURN_STANDARD, TRUE);
			break;
		case SPLIT:
			m_pBjDlg->PlayCard(1, TURN_STANDARD, FALSE, TRUE);
			break;
		default:
			m_pBjDlg->PlayCard(0, TURN_STANDARD);
			break;
		}

	}
}

void CDlgPractice::OnButtonDouble() 
{	
	if (m_nWhoseTurn !=TURN_ME){
		return;
	}
	else if (m_pPlayers[0]->GetCardStack().NumCards() > 2){
		return;
	}
	else{
		PlayStandard();
	}
	m_nDoubled += 1;
	Card card = m_Cards.Pop();
	m_pBjDlg->PlayCard(card.LoVal(), TURN_ME, TRUE);
	CardRegion* pRegion;
	GetCardRegion(pRegion);
	pRegion->Push(card);
	pRegion->Update();
	if (m_nSplit==1){
		m_nSplit++;
		m_pBjDlg->PlayCard(m_pPlayers[m_nNumPlayers+TURN_ME]->GetCardStack()[1].LoVal(), TURN_ME, TRUE);

		m_pMyHand[0]->SetText("Hand1");
		m_pMyHand[1]->SetText("Current");
		m_pMyHand[1]->Show(TRUE);
	}
	else{
		m_nWhoseTurn = TURN_DEAL;	
		
		m_pMyHand[0]->SetText("Hand1");
		m_pMyHand[1]->SetText("Hand2");
		m_pMyHand[0]->Show(FALSE);
		m_pMyHand[1]->Show(FALSE);
	}
}

void CDlgPractice::OnButtonHit() 
{
	if (m_nWhoseTurn !=TURN_ME){
		return;
	}
	else{
		PlayStandard();
	}
	Card card = m_Cards.Pop();
	m_pBjDlg->PlayCard(card.LoVal(), TURN_ME);
	CardRegion* pRegion;
	GetCardRegion(pRegion);

	pRegion->Push(card);
	pRegion->Update();
}

void CDlgPractice::OnButtonSplit() 
{
	int nValue;
	if (m_nWhoseTurn !=TURN_ME){
		return;
	}

	else if (m_pPlayers[0]->GetCardStack().NumCards() != 2){
		return;
	}
	else {
		nValue = m_pPlayers[0]->GetCardStack()[0].LoVal();
		int nValue2 = m_pPlayers[0]->GetCardStack()[1].LoVal();
		if (nValue > 10)
			nValue = 10;
		if (nValue2 > 10)
			nValue2 = 10;
		if (nValue != nValue2){
			return;
		}
		else{
			PlayStandard();
		}
	}
	//check to make sure we can
	
	if (!m_nSplit){
		m_nSplit += 1;
	//	m_pBjDlg->PlayCard(1, TURN_ME, FALSE, TRUE);
		
		int i = m_nNumPlayers+TURN_ME;
		m_pPlayers[i] = BjWnd.CreateRegion(i+2, true, TURN_ME*120, 240, 10, 10);
		m_pPlayers[i]->SetEmptyImage(CS_EI_SUNK);
		m_pPlayers[i]->SetPlacement(CS_XJUST_CENTER, 0, i * (__cardwidth + 30) , 0);
		m_pPlayers[i]->SetDragRule(CS_DRAG_NONE, 0);
		m_pPlayers[i]->SetDropRule(CS_DROP_NONE, 0);
		m_pPlayers[i]->SetFaceDirection(CS_FACE_UP, 0);

		m_pBjDlg->PlayCard(1, TURN_ME, FALSE, TRUE);
		m_pPlayers[i]->Push(m_pPlayers[0]->Pop());
		
		Card card = m_Cards.Pop();
		m_pBjDlg->PlayCard(card.LoVal(), TURN_ME);
		m_pPlayers[0]->Push(card);	
		
		card = m_Cards.Pop();
		m_pPlayers[i]->Push(card);
		m_pPlayers[i]->Update();
		m_pPlayers[0]->Update();

		m_pMyHand[0]->SetText("Current");
		m_pMyHand[0]->Show(TRUE);
		m_pMyHand[1]->Show(TRUE);
	}
	
}

void CDlgPractice::GetCardRegion(CardRegion*& pRegion){
	if (m_nSplit==2){
		pRegion=m_pPlayers[m_nNumPlayers+TURN_ME];
	}
	else{
		pRegion=m_pPlayers[0];
	}
}

void CDlgPractice::OnButtonStand() 
{
	if (m_nWhoseTurn !=TURN_ME){
		return;
	}
	CardRegion* pRegion;
	GetCardRegion(pRegion);
	if (GetValue(pRegion->GetCardStack()) < 12){
		AfxMessageBox("Huh");
		return;
	}
	else{
		PlayStandard();
	}
	m_pBjDlg->PlayCard(0, TURN_ME);
	if (m_nSplit==1){
		m_nSplit++;
		//0 is the last played card i guess
		int nValue = m_pPlayers[m_nNumPlayers+TURN_ME]->GetCardStack()[0].LoVal();
		m_pBjDlg->PlayCard(nValue, TURN_ME);
		nValue = m_pPlayers[m_nNumPlayers+TURN_ME]->GetCardStack()[1].LoVal();

		m_pMyHand[0]->SetText("Hand1");
		m_pMyHand[1]->SetText("Current");
		m_pMyHand[1]->Show(TRUE);
	}
	else{
		m_nWhoseTurn = TURN_DEAL;
		m_pMyHand[0]->SetText("Hand1");
		m_pMyHand[1]->SetText("Hand2");
		m_pMyHand[0]->Show(FALSE);
		m_pMyHand[1]->Show(FALSE);
	}
}

void CDlgPractice::OnMenuViewmistakes() 
{
	
	m_pBjDlg->m_DlgMistakes.ShowWindow(SW_SHOW);
	
}

void CDlgPractice::OnMenuShowCount() 
{
	m_pBjDlg->OnMenuShowCount();	
}

void CDlgPractice::Startup() 
{	
	OnMenuDeckReshuffle();
	
}
