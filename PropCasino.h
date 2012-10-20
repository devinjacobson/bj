#if !defined(AFX_PROPCASINO_H__B4B50741_E6FE_4182_8F07_9F00DB6C6C78__INCLUDED_)
#define AFX_PROPCASINO_H__B4B50741_E6FE_4182_8F07_9F00DB6C6C78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropCasino.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropCasino dialog

class CPropCasino : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropCasino)

// Construction
public:
	CPropCasino();
	~CPropCasino();

// Dialog Data
	//{{AFX_DATA(CPropCasino)
	enum { IDD = IDD_DIALOG_CASINO_SETTINGS };
	static BOOL	m_nDAS;
	BOOL	m_nHitSoft17;
	int		m_nNumDecks;
	static BOOL	m_nCanDoubleAces;
	static BOOL	m_nCanDouble1011;
	static BOOL	m_nCanDouble9;
	static BOOL	m_nCanDouble8Below;
	static BOOL	m_nCanSplitAces;
	static int m_nNumSplits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropCasino)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropCasino)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPCASINO_H__B4B50741_E6FE_4182_8F07_9F00DB6C6C78__INCLUDED_)
