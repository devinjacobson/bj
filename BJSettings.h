#if !defined(AFX_BJSETTINGS_H__289D9306_22AC_4EE9_B216_3A17A0F2CFD7__INCLUDED_)
#define AFX_BJSETTINGS_H__289D9306_22AC_4EE9_B216_3A17A0F2CFD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BJSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBJSettings

class CBJSettings : public CPropertySheet
{
	DECLARE_DYNAMIC(CBJSettings)

// Construction
public:
	CBJSettings(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CBJSettings(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBJSettings)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBJSettings();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBJSettings)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BJSETTINGS_H__289D9306_22AC_4EE9_B216_3A17A0F2CFD7__INCLUDED_)
