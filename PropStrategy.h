#if !defined(AFX_PROPSTRATEGY_H__C57839E8_2549_43D5_9B38_AF909CFDD58E__INCLUDED_)
#define AFX_PROPSTRATEGY_H__C57839E8_2549_43D5_9B38_AF909CFDD58E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropStrategy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropStrategy dialog

class CPropStrategy : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropStrategy)

// Construction
public:
	CPropStrategy();
	~CPropStrategy();

// Dialog Data
	//{{AFX_DATA(CPropStrategy)
	enum { IDD = IDD_DIALOG_STANDARD_STRATEGY };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropStrategy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropStrategy)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPSTRATEGY_H__C57839E8_2549_43D5_9B38_AF909CFDD58E__INCLUDED_)
