#if !defined(AFX_DIALOGMISTAKES_H__3E8869A9_34B0_48D4_BD86_F17CCC78CCF2__INCLUDED_)
#define AFX_DIALOGMISTAKES_H__3E8869A9_34B0_48D4_BD86_F17CCC78CCF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogMistakes.h : header file
//
#define SESSION_MISTAKE 1
#define DAY_MISTAKE 2
#define WEEK_MISTAKE 3
#define MONTH_MISTAKE 4
#define YEAR_MISTAKE 5

/////////////////////////////////////////////////////////////////////////////
// CDialogMistakes dialog
class CBjDlg;
class CDialogMistakes : public CDialog
{
// Construction
public:
	CDialogMistakes(CWnd* pParent = NULL);   // standard constructor
	void LoadHistory();
	void LoadMistakes();
	void UpdatePossible();
	void GetMistakeType(CMistake* pMistake, CString& strMistake);
	int MistakeInList(CMistake* pMistake, int nWho);
	CBJHistory* m_pCurrentHistory;

// Dialog Data
	//{{AFX_DATA(CDialogMistakes)
	enum { IDD = IDD_DIALOG_MISTAKES };
	CListCtrl	m_listStandardMistakes;
	CListCtrl	m_listMistakes;
	double	m_dBetMistakes;
	double	m_dPlayMistakes;
	double	m_dTotalActual;
	double	m_dTotalMistakes;
	double	m_dTotalPossible;
	double	m_dBetMistakes2;
	double	m_dPlayMistakes2;
	double	m_dTotalActual2;
	double	m_dTotalMistakes2;
	double	m_dTotalPossible2;
	double	m_dAvgStandardCount;
	int		m_nHandsPlayed;
	double	m_dWinPerHand;
	CString	m_strTimePlayed;
	int		m_nActualWin;
	double	m_dTheoreticalWin;
	//}}AFX_DATA
	CBjDlg* m_pBjDlg;
	CPtrList* m_plstMistakes; //might want to be able to sort by num cards or other things
	CPtrList* m_plstStandardMistakes;

	void ResetMistakes(int nType);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMistakes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogMistakes)
	afx_msg void OnColumnclickListMistakes(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnDblclkListMistakes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListMistakesStandard(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitemMistakesViewSession();
	afx_msg void OnMenuitemMistakesViewDay();
	afx_msg void OnMenuitemMistakesViewMonth();
	afx_msg void OnMenuitemMistakesViewWeek();
	afx_msg void OnUpdateMenuitemMistakesViewDay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuitemMistakesViewMonth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuitemMistakesViewSession(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMenuitemMistakesViewWeek(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMISTAKES_H__3E8869A9_34B0_48D4_BD86_F17CCC78CCF2__INCLUDED_)
