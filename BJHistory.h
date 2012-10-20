// BJHistory.h: interface for the CBJHistory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BJHISTORY_H__112CEA4E_6781_4A48_A887_8C33332A9CAD__INCLUDED_)
#define AFX_BJHISTORY_H__112CEA4E_6781_4A48_A887_8C33332A9CAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBJHistory  
{
public:
	CBJHistory();
	~CBJHistory();
	int EmptyLists();
	CTime m_StartTime;
	CTime m_EndTime;
	int m_nDate; //YYYYMMDD
	//all the dialog mistakes data
	double	m_dTotalPossible;
	double	m_dTotalPossible2;
	double	m_dAvgStandardCount;
	int		m_nHandsPlayed;
	double	m_dWinPerHand;
	CTimeSpan	m_TimePlayed;
	int		m_nRealWin;
	//end of dialog data
	CPtrList* m_plstMistakes;	
	CPtrList* m_plstStandardMistakes;
	
};

#endif // !defined(AFX_BJHISTORY_H__112CEA4E_6781_4A48_A887_8C33332A9CAD__INCLUDED_)
