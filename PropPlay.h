#if !defined(AFX_PROPPLAY_H__656C278E_66D8_4552_8731_291615512C4F__INCLUDED_)
#define AFX_PROPPLAY_H__656C278E_66D8_4552_8731_291615512C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropPlay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPlay dialog

class CPropPlay : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPlay)

// Construction
public:
	CPropPlay();
	~CPropPlay();

// Dialog Data
	//{{AFX_DATA(CPropPlay)
	enum { IDD = IDD_DIALOG_PLAY_SETTINGS };
	int		m_nNumPlayers;
	int		m_nPlaySpeed;
	int		m_nPenetration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPlay)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPLAY_H__656C278E_66D8_4552_8731_291615512C4F__INCLUDED_)
