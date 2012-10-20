// Deck.h: interface for the CDeck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECK_H__7DEC1849_B4CB_45C8_9E07_E2BB4272B4D6__INCLUDED_)
#define AFX_DECK_H__7DEC1849_B4CB_45C8_9E07_E2BB4272B4D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCard{ 
public:
	CCard(int nValue = 0){
		m_nValue = nValue;
		m_nNumPlayed = 0;
		m_nNumAvailable = 0;
	};
	~CCard(){};
	int m_nValue;
	int m_nNumPlayed;
	int m_nNumAvailable;
};


class CDealerRules{
public:

	CDealerRules(){
		m_nHitSoft17 = FALSE;
		m_nHitMax = 17;
	};
	~CDealerRules(){};
	int m_nHitSoft17;
	int m_nHitMax;


};

class CHitRules{
	CHitRules(){
		
	}
	~CHitRules(){};
};

class CHand{
public:
	CHand(){
		m_nNumCards = 0;
		m_nTotalValue = 0;
		m_nHasAce = 0;
		m_pHitRules = NULL;
		m_nIsDoubleDown = 0;
		m_nIsSplit = 0;
		m_nIsSplitAce = 0;
	}
	CHand(CHand& hand);
	operator=(CHand hand);
	~CHand(){
	};
	int m_pnCards[32];	
	
	static CDealerRules m_DealerRules;
	CHitRules* m_pHitRules;
	int ShouldHit(int nIsDealer);
	void Hit(int nValue);
	int m_nNumCards;
	int m_nTotalValue;
	int m_nHasAce;
	int m_nIsDoubleDown;
	int m_nIsSplit;
	int m_nIsSplitAce;
};


class CDeck  
{
public:
	CDeck(int nNumDecks = 6, int nType = 1);
	CDeck(CDeck& deck);
	operator=(CDeck deck);
	void Reshuffle();
	int Play(int nValue);
	virtual ~CDeck();
	void Write(CFile* pFile){
		pFile->Write(m_pCards, m_nCards*sizeof(CCard));
		pFile->Write((void*)&m_nDecks, (UINT)&m_nNumPlayed + sizeof(m_nNumPlayed)-(UINT)&m_nDecks);	
	};
	void Read(char*& buf){
		memcpy(m_pCards, buf, m_nCards*sizeof(CCard));
		buf += m_nCards*sizeof(CCard);
		int nSize = (UINT)&m_nNumPlayed + sizeof(m_nNumPlayed)-(UINT)&m_nDecks;
		memcpy((void*)&m_nDecks, buf, nSize);
		buf += nSize;
	};
	CCard* m_pCards;
	int m_nCards;
	int m_nDecks;
	int m_nNumAvailable;
	int m_nNumPlayed;
	
};

#define MISTAKE_BET_LOW -2
#define MISTAKE_BET_HIGH -1
#define MISTAKE_PLAY 0
#define MISTAKE_HIT 1
#define MISTAKE_NOHIT 2
#define MISTAKE_SPLIT 3
#define MISTAKE_NOSPLIT 4
#define MISTAKE_DOUBLE 5
#define MISTAKE_NODOUBLE 6

class CMistake{
public:
	CMistake(int nThisSession = TRUE){
		m_nMistakeType = MISTAKE_PLAY;
		m_nMistake = 0;
		m_dLoss = 0;
		m_nBet = 1;
		m_nThisSession = nThisSession;
	};
	~CMistake(){
	};
	Write(CFile* pFile){
	m_Deck.Write(pFile);
	pFile->Write((void*)&m_Dealer, (UINT)&m_nThisSession + sizeof(m_nThisSession)-(UINT)&m_Dealer);
	};
	Read(char*& buf){
	m_Deck.Read(buf);
	int nSize = (UINT)&m_nThisSession + sizeof(m_nThisSession)-(UINT)&m_Dealer;
	memcpy((void*)&m_Dealer, buf, nSize);
	buf += nSize;
	};
	CDeck m_Deck;
	CHand m_Dealer;
	CHand m_Me;
	int m_nMistakeType;
	int m_nMistake;
	double m_dLoss;
	int m_nBet;
	CTime m_Date; //YYYYMMDD
	int m_nThisSession;
};

#endif // !defined(AFX_DECK_H__7DEC1849_B4CB_45C8_9E07_E2BB4272B4D6__INCLUDED_)
