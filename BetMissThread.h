#if !defined(AFX_BETMISSTHREAD_H__1FDE95F9_4E11_4422_AB59_FB6F87E2420E__INCLUDED_)
#define AFX_BETMISSTHREAD_H__1FDE95F9_4E11_4422_AB59_FB6F87E2420E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BetMissThread.h : header file
//


UINT ThreadProc(LPVOID pParam);
class CBetMissParam{
public:
	CPtrList* m_plstBets;
	CPtrList* m_plstDecks;
};

/////////////////////////////////////////////////////////////////////////////
// CBetMissThread thread

class CBetMissThread : public CWinThread
{
	DECLARE_DYNCREATE(CBetMissThread)
protected:
	CBetMissThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBetMissThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBetMissThread();

	// Generated message map functions
	//{{AFX_MSG(CBetMissThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BETMISSTHREAD_H__1FDE95F9_4E11_4422_AB59_FB6F87E2420E__INCLUDED_)
