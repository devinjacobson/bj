#if !defined(AFX_PROPBID_H__9BACB303_EFA1_4F12_ACD1_5FC618A53F0F__INCLUDED_)
#define AFX_PROPBID_H__9BACB303_EFA1_4F12_ACD1_5FC618A53F0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropBid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropBid dialog

class CPropBid : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropBid)

// Construction
public:
	CPropBid();
	~CPropBid();

// Dialog Data
	//{{AFX_DATA(CPropBid)
	enum { IDD = IDD_DIALOG_BID_SETTINGS };
	int		m_nHighBet;
	int		m_nLowBet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropBid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropBid)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPBID_H__9BACB303_EFA1_4F12_ACD1_5FC618A53F0F__INCLUDED_)
