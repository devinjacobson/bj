// XHTMLStatic.h : header file
//

#ifndef XHTMLSTATIC_H
#define XHTMLSTATIC_H

/////////////////////////////////////////////////////////////////////////////
// CXHTMLStatic window

class CXHTMLStatic : public CStatic
{
// Construction
public:
	CXHTMLStatic();
	virtual ~CXHTMLStatic();

// Attributes
public:

// Operations
public:
	virtual COLORREF SetBkColor(COLORREF rgb) 
	{
		COLORREF oldrgb = m_crBackGround;
		m_crBackGround = rgb;
		return oldrgb;
	}
	COLORREF GetBkColor() const { return m_crBackGround; }

	virtual COLORREF SetTextColor(COLORREF rgb) 
	{
		COLORREF oldrgb = m_crText;
		m_crText = rgb;
		return oldrgb;
	}
	COLORREF GetTextColor() const { return m_crText; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXHTMLStatic)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int FormatText(HDC hdc, LPCTSTR lpszText, RECT * pRect, int nInitialXOffset);
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	HINSTANCE GotoURL(LPCTSTR url, int showcmd);
	BOOL IsBlank(LPCTSTR lpszText);

	COLORREF		m_crBackGround;
	COLORREF		m_crText;
	BOOL			m_bUnderline;
	BOOL			m_bBold;
	BOOL			m_bItalic;
	BOOL			m_bStrikeThrough;
	CFont			m_font;
	BOOL			m_bInAnchor;
	CPtrArray		m_AnchorRectPtrs;
	CStringArray	m_AnchorUrls;
	BOOL			m_bHyperlinkTimer;
	BOOL			m_bOnHyperlink;
	HCURSOR			m_hLinkCursor;
	HCURSOR			m_hPrevCursor;

	// Generated message map functions
protected:
	//{{AFX_MSG(CXHTMLStatic)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnClicked();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XHTMLSTATIC_H
