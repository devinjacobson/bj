// BetMissThread.cpp : implementation file
//

#include "stdafx.h"
#include "bj.h"
#include "BetMissThread.h"
#include "bjDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CBetMissThread

UINT ThreadProc(LPVOID pParam){
	CBetMissParam* p = (CBetMissParam*)pParam;
   if (p == NULL)
    return 1;   // if pObject is not valid

   CBjDlg bjDlg;

	bjDlg.m_nThread = TRUE;
   
   if (p->m_plstBets == NULL || p->m_plstDecks == NULL){
		return 1;
   }
    // do something with 'pObject'

   while (1){
	   //lock something here.
		CSingleLock lock(&CBjDlg::m_Sect);

		lock.Lock();
		if (!lock.IsLocked()){
			Sleep(10);
			lock.Lock();
		}

	   if (p->m_plstBets->GetCount()){
		   int nMax = CBjDlg::m_nHighBet;
		   int nMin = CBjDlg::m_nLowBet;

			//set the real max and min here

			int nBet = (int)p->m_plstBets->RemoveHead();
			CDeck* pDeck = (CDeck*)p->m_plstDecks->RemoveHead();
			bjDlg.m_nWager = nBet;
			bjDlg.m_Deck = *pDeck;
		   lock.Unlock();
		   bjDlg.Calculate();
		   bjDlg.m_nHandsPlayed++;
			if (bjDlg.m_dMeW > bjDlg.m_dDealerW){
				bjDlg.m_nWon++;
				bjDlg.m_dTotal += nBet * (bjDlg.m_dMeW-bjDlg.m_dDealerW);
			}
			else{
				bjDlg.m_nLost++;
				bjDlg.m_dTotal += (bjDlg.m_dMeW-bjDlg.m_dDealerW);
			}

		   double dCount = 0;
		   int nA10 = pDeck->m_pCards[0].m_nNumAvailable-pDeck->m_pCards[0].m_nNumPlayed;
		   nA10 += pDeck->m_pCards[9].m_nNumAvailable-pDeck->m_pCards[9].m_nNumPlayed;
		   int n23456 = pDeck->m_pCards[1].m_nNumAvailable-pDeck->m_pCards[1].m_nNumPlayed;
		   n23456 += pDeck->m_pCards[2].m_nNumAvailable-pDeck->m_pCards[2].m_nNumPlayed;
		   n23456 += pDeck->m_pCards[3].m_nNumAvailable-pDeck->m_pCards[3].m_nNumPlayed;
		   n23456 += pDeck->m_pCards[4].m_nNumAvailable-pDeck->m_pCards[4].m_nNumPlayed;
		   n23456 += pDeck->m_pCards[5].m_nNumAvailable-pDeck->m_pCards[5].m_nNumPlayed;
		   dCount = (nA10-n23456);
			dCount *= 52;
			dCount /= (pDeck->m_nNumAvailable-pDeck->m_nNumPlayed);
			CBjDlg::m_dAvgStandardCount = CBjDlg::m_dAvgStandardCount*CBjDlg::m_nHandsPlayed;
			CBjDlg::m_dAvgStandardCount += dCount;
			CBjDlg::m_dAvgStandardCount /= CBjDlg::m_nHandsPlayed + 1;
			//check this!
			int nStandardBet = (dCount + 1)*((double)(nMax/nMin)/5);
		   if (nStandardBet < 1){
				nStandardBet = 1;
		   }
		   double dDiff = bjDlg.m_dMeW - bjDlg.m_dDealerW;
		   if (dDiff > 0){
				bjDlg.m_dTotalPossible += dDiff*nMax;
		   }
		   else{
				bjDlg.m_dTotalPossible += dDiff*nMin;
		   }
			CMistake* pMistake = NULL;

		   if (nBet >nMin && dDiff < 0){
				pMistake = bjDlg.GetMistake();
				pMistake->m_nMistake = MISTAKE_BET_HIGH;
				
				pMistake->m_dLoss = -dDiff*(nBet-nMin);
				lock.Lock();
				CBjDlg::m_lstMistakes.AddTail(pMistake);
				lock.Unlock();
				//mistake
			   //add to list
		   }
		   else if (nBet < nMax && dDiff > 0){
				pMistake = bjDlg.GetMistake();
				pMistake->m_nMistake = MISTAKE_BET_LOW;
				
				pMistake->m_dLoss = dDiff*(nMax-nBet);
				lock.Lock();
				CBjDlg::m_lstMistakes.AddTail(pMistake);
				lock.Unlock();
				//mistake
			   //add to list
		   }
		  
		   if (nStandardBet >nMin && dDiff < 0){
				pMistake = bjDlg.GetMistake();
				pMistake->m_nMistake = MISTAKE_BET_HIGH;
				
				pMistake->m_dLoss = -dDiff*(nStandardBet-1);
				lock.Lock();
				CBjDlg::m_lstStandardMistakes.AddTail(pMistake);
				lock.Unlock();
				//mistake
			   //add to list
		   }
		   else if (nStandardBet < nMax && dDiff > 0){
				pMistake = bjDlg.GetMistake();
				pMistake->m_nMistake = MISTAKE_BET_LOW;
				
				pMistake->m_dLoss = dDiff*(nMax-nStandardBet);
				lock.Lock();
				CBjDlg::m_lstStandardMistakes.AddTail(pMistake);
				lock.Unlock();
				//mistake
			   //add to list
		   }
		   //calculate the differences of the true win and what we bet.  
	   }
	   else{
			lock.Unlock();	
		   Sleep(1500);
	   }
   }
    return 0;   // thread completed successfully
}

IMPLEMENT_DYNCREATE(CBetMissThread, CWinThread)

CBetMissThread::CBetMissThread()
{
}

CBetMissThread::~CBetMissThread()
{
}

BOOL CBetMissThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CBetMissThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CBetMissThread, CWinThread)
	//{{AFX_MSG_MAP(CBetMissThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBetMissThread message handlers
