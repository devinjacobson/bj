// Deck.cpp: implementation of the CDeck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bj.h"
#include "Deck.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDealerRules CHand::m_DealerRules;

CHand::CHand(CHand& hand){
	m_nNumCards = hand.m_nNumCards;
	m_nTotalValue = hand.m_nTotalValue;
	m_nHasAce = hand.m_nHasAce;
	m_nIsSplit = hand.m_nIsSplit;
	m_nIsSplitAce = hand.m_nIsSplitAce;
	memcpy(m_pnCards, hand.m_pnCards, sizeof(int)*32);
}

CHand::operator=(CHand hand){
	m_nNumCards = hand.m_nNumCards;
	m_nTotalValue = hand.m_nTotalValue;
	m_nHasAce = hand.m_nHasAce;
	m_nIsSplit = hand.m_nIsSplit;
	m_nIsSplitAce = hand.m_nIsSplitAce;
	memcpy(m_pnCards, hand.m_pnCards, sizeof(int)*32);
	return TRUE;
}

int CHand::ShouldHit(int nIsDealer){
	if (nIsDealer){
		if (m_DealerRules.m_nHitSoft17){
			if (m_nTotalValue ==7 && m_nHasAce){
				return TRUE;
			}
		}
		if ((m_nTotalValue > 6 && m_nTotalValue < 12 && m_nHasAce)){
			return FALSE;
		}
		else if (m_nTotalValue < m_DealerRules.m_nHitMax){
			return TRUE;
		}
		else{
			return FALSE;
		}
	}
	else{
		return FALSE;
	}
}

void CHand::Hit(int nValue){
	m_pnCards[m_nNumCards++] = nValue;
	m_nTotalValue += nValue;
	if (nValue == 1){
		m_nHasAce = TRUE;
	}
}

CDeck::CDeck(int nNumDecks, int nType)
{
	m_nCards = 10;
	m_pCards = (CCard*)malloc(m_nCards*sizeof(CCard));
	memset((void*)m_pCards, 0, m_nCards*sizeof(CCard));
	m_nDecks = nNumDecks;
	m_nNumAvailable = 0;

	int j = 0;
	int nTemp = 0;
	for (int i = 1; i< 14; i++){
		if (i > 10){
			nTemp = 10;
		}
		else {
			nTemp = i;
		}
#ifdef TRAIN
		if(i < 8 || i > 9){
#endif
			m_pCards[nTemp-1].m_nValue = nTemp;
			m_pCards[nTemp-1].m_nNumAvailable += m_nDecks*4;
			m_nNumAvailable += m_nDecks* 4;
#ifdef TRAIN
		}
#endif
	}
	m_nNumPlayed = 0;
}

CDeck::CDeck(CDeck& deck){
	m_nCards = deck.m_nCards;
	m_pCards = (CCard*)malloc(m_nCards*sizeof(CCard));
	memset((void*)m_pCards, 0, m_nCards*sizeof(CCard));
	m_nDecks = deck.m_nDecks;

	for (int i = 0; i< m_nCards; i++){
		m_pCards[i].m_nValue = deck.m_pCards[i].m_nValue;
		m_pCards[i].m_nNumPlayed = deck.m_pCards[i].m_nNumPlayed;
		m_pCards[i].m_nNumAvailable = deck.m_pCards[i].m_nNumAvailable;
	}
	m_nNumAvailable = deck.m_nNumAvailable;
	m_nNumPlayed = deck.m_nNumPlayed;

}

CDeck::operator=(CDeck deck){
	m_nCards = deck.m_nCards;
	m_nDecks = deck.m_nDecks;
	for (int i = 0; i< m_nCards; i++){
		m_pCards[i].m_nValue = deck.m_pCards[i].m_nValue;
		m_pCards[i].m_nNumPlayed = deck.m_pCards[i].m_nNumPlayed;
		m_pCards[i].m_nNumAvailable = deck.m_pCards[i].m_nNumAvailable;
	}
	m_nNumAvailable = deck.m_nNumAvailable;
	m_nNumPlayed = deck.m_nNumPlayed;
	return TRUE;
}

void CDeck::Reshuffle(){
	for (int i = 0; i< m_nCards; i++){
		m_pCards[i].m_nNumPlayed = 0;
	}
	m_nNumPlayed = 0;
}

int CDeck::Play(int nValue){
	if (nValue <= m_nCards && nValue > 0){
		if (m_pCards[nValue-1].m_nNumPlayed >= m_pCards[nValue-1].m_nNumAvailable){
			return FALSE;
		}
		m_pCards[nValue-1].m_nNumPlayed++;
		m_nNumPlayed++;
	}
	return TRUE;	
}

CDeck::~CDeck()
{
	if (m_pCards){
		free(m_pCards);
	}
}
