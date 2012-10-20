#if !defined(AFX_DLGCASINORULES_H__81358F6C_5033_42DE_AAF9_A0B718E79ABB__INCLUDED_)
#define AFX_DLGCASINORULES_H__81358F6C_5033_42DE_AAF9_A0B718E79ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCasinoRules.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCasinoRules dialog

class CDlgCasinoRules : public CDialog
{
// Construction
public:
	CDlgCasinoRules(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCasinoRules)
	enum { IDD = IDD_DIALOG_CASINO_RULES };
	BOOL	m_nDASAllowed;
	BOOL	m_nHitSoft17;
	CString	m_strDouble;
	CString	m_strSplit;
	int		m_nNumDecks;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCasinoRules)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCasinoRules)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCASINORULES_H__81358F6C_5033_42DE_AAF9_A0B718E79ABB__INCLUDED_)
