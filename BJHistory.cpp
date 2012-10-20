// BJHistory.cpp: implementation of the CBJHistory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bj.h"
#include "BJHistory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBJHistory::CBJHistory()
{
	m_dTotalPossible = 0;
	m_dTotalPossible2 = 0;
	m_plstMistakes = new CPtrList();	
	m_plstStandardMistakes = new CPtrList();	
}

CBJHistory::~CBJHistory()
{
//	delete m_plstMistakes;
//	delete m_plstStandardMistakes;
}

int CBJHistory::EmptyLists(){
	POSITION pos = m_plstMistakes->GetHeadPosition();
	CMistake* pMistake;
	while (pos != NULL){
		pMistake = (CMistake*)m_plstMistakes->GetNext(pos);
		delete pMistake;
	}
	pos = m_plstStandardMistakes->GetHeadPosition();
	while (pos != NULL){
		pMistake = (CMistake*)m_plstStandardMistakes->GetNext(pos);
		delete pMistake;
	}
	return TRUE;
}