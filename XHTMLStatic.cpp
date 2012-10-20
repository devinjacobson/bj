// XHTMLStatic.cpp  Version 1.0
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// Thanks to Charles Petzold for explaining how GetTextExtentPoint32() works,
// in his excellent "Programming Windows", Fifth Edition:
//     http://www.bookpool.com/.x/6o8gzz6xw6/sm/157231995X
//
// Thanks to Chris Maunder for showing how to set the cursor and receive mouse
// clicks for static controls, and for all the code that I used from his 
// CHyperLink class:
//     http://www.codeproject.com/miscctrl/hyperlink.asp
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XHTMLStatic.h"
#include "XNamedColors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CXHTMLStatic

BEGIN_MESSAGE_MAP(CXHTMLStatic, CStatic)
	//{{AFX_MSG_MAP(CXHTMLStatic)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_CONTROL_REFLECT(STN_CLICKED, OnClicked)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ctor
CXHTMLStatic::CXHTMLStatic()
{
	m_crBackGround		= ::GetSysColor(COLOR_WINDOW);
	m_crText			= ::GetSysColor(COLOR_WINDOWTEXT);
	m_bUnderline		= FALSE;
	m_bBold				= FALSE;
	m_bItalic			= FALSE;
	m_bStrikeThrough	= FALSE;
	m_bHyperlinkTimer	= FALSE;
	m_bOnHyperlink		= FALSE;
	m_hLinkCursor		= NULL;
	m_hPrevCursor		= NULL;
	m_bInAnchor			= FALSE;
	m_AnchorRectPtrs.RemoveAll();
	m_AnchorUrls.RemoveAll();

    CString strWndDir;
    GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
    strWndDir.ReleaseBuffer();

    strWndDir += _T("\\winhlp32.exe");
    // This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
    HMODULE hModule = ::LoadLibrary(strWndDir);
    if (hModule) 
	{
        HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
        if (hHandCursor)
            m_hLinkCursor = CopyCursor(hHandCursor);
    }
    ::FreeLibrary(hModule);
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CXHTMLStatic::~CXHTMLStatic()
{
	int n = m_AnchorRectPtrs.GetSize();

	for (int i = 0; i < n; i++)
	{
		CRect *pRect = (CRect *) m_AnchorRectPtrs[i];
		if (pRect)
			delete pRect;
	}

	m_AnchorRectPtrs.RemoveAll();
	m_AnchorUrls.RemoveAll();
}

///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CXHTMLStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// get text from control
	CString strText;
	GetWindowText(strText);

	CString str1;
	int index;

	// set text and background colors
	COLORREF crText = m_crText;
	COLORREF prev_crText = crText;

	COLORREF crBackground = m_crBackGround;
	COLORREF prev_crBackground = crBackground;

	CFont *pOldFont = dc.SelectObject(&m_font);
	int n = strText.GetLength();

	CRect rect;
	GetClientRect(&rect);

	dc.FillSolidRect(&rect, m_crBackGround);

	int nInitialXOffset = 0;

	LOGFONT lf, prev_lf;
	CFont* cf = GetFont();
	if (cf)
		cf->GetObject(sizeof(lf), &lf);
	else
		GetObject(GetStockObject(SYSTEM_FONT), sizeof(lf), &lf);
	memcpy(&prev_lf, &lf, sizeof(lf));

	CString strAnchorText = _T("");

	while (n > 0)
	{
		///////////////////////////////////////////////////////////////////////
		if (strText.Left(3) == _T("<b>") ||			// check for <b>
			strText.Left(3) == _T("<B>"))			// check for <B>
		{
			n -= 3;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			m_bBold++;// = TRUE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(4) == _T("</b>") ||	// check for </b>
				 strText.Left(4) == _T("</B>"))		// check for </B>
		{
			n -= 4;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			if (m_bBold)
				m_bBold--;// = FALSE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(3) == _T("<i>") ||	// check for <i>
				 strText.Left(3) == _T("<I>"))		// check for <I>
		{
			n -= 3;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			m_bItalic++;// = TRUE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(4) == _T("</i>") ||	// check for </i>
				 strText.Left(4) == _T("</I>"))		// check for </I>
		{
			n -= 4;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			if (m_bItalic)
				m_bItalic--;// = FALSE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(3) == _T("<u>") ||	// check for <u>
				 strText.Left(3) == _T("<U>"))		// check for <U>
		{
			n -= 3;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			m_bUnderline++;// = TRUE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(4) == _T("</u>") ||	// check for </u>
				 strText.Left(4) == _T("</U>"))		// check for </U>
		{
			n -= 4;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			if (m_bUnderline)
				m_bUnderline--;// = FALSE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(8) == _T("<strike>") ||	// check for <strike>
				 strText.Left(8) == _T("<STRIKE>"))		// check for <STRIKE>
		{
			n -= 8;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			m_bStrikeThrough++;// = TRUE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(9) == _T("</strike>") ||	// check for </strike>
				 strText.Left(9) == _T("</STRIKE>"))	// check for </STRIKE>
		{
			n -= 9;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			if (m_bStrikeThrough)
				m_bStrikeThrough--;// = FALSE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(5) == _T("<font") ||		// check for <font
				 strText.Left(5) == _T("<FONT"))		// check for <FONT
		{
			index = strText.Find(_T('>'));
			if (index != -1)
			{
				CString strFont = strText.Mid(5, index-5);
				int m = strFont.GetLength();
				strText = strText.Mid(index+1);

				// loop to parse FONT attributes
				while (m > 0)
				{
					// trim left whitespace
					if ((strFont.GetLength() > 0) && (strFont[0] == _T(' ')))
					{
						m--;
						strFont = strFont.Mid(1);
						continue;
					}

					///////////////////////////////////////////////////////////
					if (strFont.Left(5) == _T("color") ||
						strFont.Left(5) == _T("COLOR"))
					{
						int index2 = strFont.Find(_T('"'));
						if (index2 != -1)
						{
							m -= index2 + 1;
							strFont = strFont.Mid(index2+1);

							index2 = strFont.Find(_T('"'));
							if (index2 != -1)
							{
								CString strColor = strFont.Left(index2);
								CXNamedColors nc(strColor);
								crText = nc.GetRGB();
								strFont = strFont.Mid(index2+1);
								m = strFont.GetLength();
							}
						}
						else
							break;
					}
					///////////////////////////////////////////////////////////
					else if (strFont.Left(7) == _T("bgcolor") ||
							 strFont.Left(7) == _T("BGCOLOR"))
					{
						int index2 = strFont.Find(_T('"'));
						if (index2 != -1)
						{
							m -= index2 + 1;
							strFont = strFont.Mid(index2+1);

							index2 = strFont.Find(_T('"'));
							if (index2 != -1)
							{
								CString strBgColor = strFont.Left(index2);
								CXNamedColors nc(strBgColor);
								crBackground = nc.GetRGB();
								strFont = strFont.Mid(index2+1);
								m = strFont.GetLength();
							}
						}
						else
							break;
					}
					///////////////////////////////////////////////////////////
					else if (strFont.Left(4) == _T("face") ||
							 strFont.Left(4) == _T("FACE"))
					{
						int index2 = strFont.Find(_T('"'));
						if (index2 != -1)
						{
							m -= index2 + 1;
							strFont = strFont.Mid(index2+1);
							index2 = strFont.Find(_T('"'));
							if (index2 != -1)
							{
								memset(lf.lfFaceName, 0, sizeof(lf.lfFaceName));
								_tcsncpy(lf.lfFaceName, strFont, index2);

								m -= index2 + 1;
								if (m > 0)
									strFont = strFont.Mid(index2+1);
								else
									strFont = _T("");
								m = strFont.GetLength();
							}
						}
						else
							break;
					}
					///////////////////////////////////////////////////////////
					else if (strFont.Left(4) == _T("size") ||
							 strFont.Left(4) == _T("SIZE"))
					{
						int index2 = strFont.Find(_T('"'));
						if (index2 != -1)
						{
							m -= index2 + 1;
							strFont = strFont.Mid(index2+1);
							index2 = strFont.Find(_T('"'));
							if (index2 != -1)
							{
								int nSize = 0;
								nSize = _ttoi(strFont);
								lf.lfHeight -= nSize;

								m -= index2 + 1;
								if (m > 0)
									strFont = strFont.Mid(index2+1);
								else
									strFont = _T("");
								m = strFont.GetLength();
							}
						}
						else
							break;
					}
					else
					{
						while ((strFont.GetLength() > 0) && 
							   (strFont[0] != _T(' ')))
						{
							m--;
							strFont = strFont.Mid(1);
						}
					}
				}
				n -= index + 1;
			}
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(7) == _T("</font>") ||	// check for </font>
				 strText.Left(7) == _T("</FONT>"))		// check for </FONT>
		{
			n -= 7;
			index = strText.Find(_T('>'));
			if (index != -1)
				strText = strText.Mid(index+1);
			crText = prev_crText;
			crBackground = prev_crBackground;
			memcpy(&lf, &prev_lf, sizeof(lf));
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		// <a href=www.xyz.com>XYZ Web Site</a>
		else if (strText.Left(8) == _T("<a href=") ||	// check for <a href=
				 strText.Left(8) == _T("<A HREF="))		// check for <A HREF=
		{
			index = strText.Find(_T('>'));
			if (index != -1)
			{
				strAnchorText = strText.Mid(8, index-8);
				strText = strText.Mid(index+1);
				n = strText.GetLength();
				m_bInAnchor = TRUE;
				continue;
			}
		}
		///////////////////////////////////////////////////////////////////////
		else if (strText.Left(4) == _T("</a>") ||	// check for </a>
				 strText.Left(4) == _T("</A>"))		// check for </A>
		{
			strText = strText.Mid(4);
			n -= 4;
			m_bInAnchor = FALSE;
			continue;
		}
		///////////////////////////////////////////////////////////////////////
		// <br> or \r\n or plain text
		else
		{
			str1 = strText;
			index = str1.Find(_T('<'));
			if (index != -1)
			{
				if (strText.Left(4) == _T("<br>") ||	// check for <br>
					strText.Left(4) == _T("<BR>"))		// check for <BR>
				{
					n -= 4;
					str1 = _T("\r\n ");
					strText = strText.Mid(4);
				}
				else
				{
					str1 = strText.Left(index);
					if (str1.GetLength() <= 0)
					{
						if (strText.GetLength() != 0)
						{
							str1 = strText[0];
							index = 1;
							n -= 1;
						}
					}
					strText = strText.Mid(index);
				}
			}
			else
			{
				str1 = strText;
				strText = _T("");
			}
		}

		lf.lfWeight    = m_bBold ? FW_BOLD : FW_NORMAL;
		lf.lfUnderline = (BYTE) m_bUnderline;
		lf.lfItalic    = (BYTE) m_bItalic;
		lf.lfStrikeOut = (BYTE) m_bStrikeThrough;

		m_font.DeleteObject();
		VERIFY(m_font.CreateFontIndirect(&lf));

		dc.SetTextColor(crText);
		dc.SetBkColor(crBackground);
		dc.SelectObject(&m_font);

		CRect rectDraw;
		rectDraw = rect;

		nInitialXOffset = FormatText(dc.m_hDC, str1, &rect, nInitialXOffset);

		if (m_bInAnchor)
		{
			SIZE size;
			GetTextExtentPoint32(dc.m_hDC, str1, str1.GetLength(), &size);
			rectDraw.bottom = rectDraw.top + size.cy;
			rectDraw.right = rectDraw.left + size.cx;

			// save rect for this text - save in window coordinates
			CRect *pRect = new CRect(rectDraw);

			m_AnchorRectPtrs.Add(pRect);
			m_AnchorUrls.Add(strAnchorText);

			if (!m_bHyperlinkTimer)
			{
				m_bHyperlinkTimer = TRUE;
				SetTimer(1, 80, NULL);
			}
		}

		n -= str1.GetLength();
	}

	// Restore DC's State
	dc.SelectObject(pOldFont);

	// Do not call CStatic::OnPaint() for painting messages
}

///////////////////////////////////////////////////////////////////////////////
// IsBlank
BOOL CXHTMLStatic::IsBlank(LPCTSTR lpszText)
{
	TCHAR c;
	while ((c = *lpszText++) != _T('\0'))
		if (c != _T(' ') && c != _T('\t'))
			return FALSE;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// FormatText
int CXHTMLStatic::FormatText(HDC hdc, 
							 LPCTSTR lpszText, 
							 RECT * pRect, 
							 int nInitialXOffset)
{
	int		xStart, yStart, nWord, xNext, xLast;
	TCHAR	*pText = (TCHAR *) lpszText;
	TCHAR	*pBegin, *pEnd;
	SIZE	size;

	yStart = pRect->top;
	xNext = nInitialXOffset;
	xLast = 0;

	if (pRect->top >= (pRect->bottom-1))
		return 0;

	// set initial size
	TCHAR * szTest = _T("abcdefgABCDEFG");
	GetTextExtentPoint32(hdc, szTest, _tcslen(szTest), &size);

	// prepare for next line - clear out the error term
	SetTextJustification(hdc, 0, 0);

	CString strOut = _T("");

	BOOL bReturnSeen = FALSE;

	do									// for each text line
	{
		nWord = 0;						// initialize number of spaces in line

		pBegin = pText;					// set pointer to char at beginning of line

		// skip to first non-space in line
		while (*pText != _T('\0') && *pText == _T(' '))
		{
			if (xNext)
				strOut += *pText;
			pText++;
		}

		for(;;)							// until the line is known
		{
			pEnd = pText;				// set pointer to char at end of line

			// skip to next word
			while (*pText != _T('\0') && *pText == _T(' '))
				strOut += *pText++;

			// skip \r
			if (*pText == _T('\r'))
				pText++;
			// \n = new line
			if (*pText == _T('\n'))
			{
				strOut += _T(' ');
				pText++;
				bReturnSeen = TRUE;
			}

			if (!bReturnSeen)
			{
				// skip to next space 
				while (*pText != _T('\0') && *pText != _T(' '))
					strOut += *pText++;
			}

			// after each word, calculate extents

			nWord++;
			GetTextExtentPoint32(hdc, strOut, strOut.GetLength(), &size);

			if (size.cx >= (pRect->right - xNext - 5))	// don't get too close to margin,
														// in case of italic text
			{
				if ((pEnd - pBegin) != 0)
				{
					strOut = strOut.Left(pEnd - pBegin);
					break;
				}
				pText = pBegin;
				xNext = 0;
				yStart += size.cy;
			}
			if (*pText == _T('\0'))
			{
				pEnd = pText;
				strOut = strOut.Left(pEnd - pBegin);
				break;
			}
			if (bReturnSeen)
			{
				pEnd = pText;
				strOut = strOut.Left(pEnd - pBegin);
				break;
			}
		}

		nWord--;               // discount last space at end of line

		// if end of text and no space characters, set pEnd to end

		GetTextExtentPoint32(hdc, strOut, strOut.GetLength(), &size);

		xStart = pRect->left;

		xStart += xNext;
		xNext = 0;
		xLast = xStart + size.cx;

		// display the text

		if ((yStart <= (pRect->bottom-size.cy)) && (!IsBlank(strOut)))
			TextOut(hdc, xStart, yStart, strOut, strOut.GetLength());

		// prepare for next line - clear out the error term
		SetTextJustification(hdc, 0, 0);

		strOut.Empty();

		pText = pEnd;
		if (*pText)
		{
			yStart += size.cy;
		}

		bReturnSeen = FALSE;

	} while (*pText && (yStart < pRect->bottom));

	if (yStart > (pRect->bottom-size.cy))
		pRect->top = pRect->bottom;
	else
		pRect->top = yStart;

	return xLast;
}

///////////////////////////////////////////////////////////////////////////////
// PreSubclassWindow
void CXHTMLStatic::PreSubclassWindow() 
{
    // We want to get mouse clicks via STN_CLICKED
    DWORD dwStyle = GetStyle();
    ::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	CStatic::PreSubclassWindow();

	CFont* cf = GetFont();
	LOGFONT lf;

	if (cf != NULL)
	{
		cf->GetObject(sizeof(lf), &lf);
	}
	else
	{
		GetObject(GetStockObject(SYSTEM_FONT), sizeof(lf), &lf);
	}

	m_font.DeleteObject();
	VERIFY(m_font.CreateFontIndirect(&lf));
}

///////////////////////////////////////////////////////////////////////////////
// OnTimer
void CXHTMLStatic::OnTimer(UINT /*nIDEvent*/) 
{
	int n = m_AnchorRectPtrs.GetSize();

	if (n == 0)
		return;

	CPoint point;
	::GetCursorPos(&point);

	m_bOnHyperlink = FALSE;

	for (int i = 0; i < n; i++)
	{
		CRect *pRect = (CRect *) m_AnchorRectPtrs[i];
		CRect rect = *pRect;
		ClientToScreen(&rect);

		if (rect.PtInRect(point))		 // Cursor is currently over control
		{
			if (m_hLinkCursor)
			{
				HCURSOR hPrevCursor = ::SetCursor(m_hLinkCursor);
				if (m_hPrevCursor == NULL)
					m_hPrevCursor = hPrevCursor;
				m_bOnHyperlink = TRUE;
				break;
			}
		}
	}

	if (!m_bOnHyperlink && m_hPrevCursor)
	{
		::SetCursor(m_hPrevCursor);
		m_hPrevCursor = NULL;
		RedrawWindow();
	}
}

///////////////////////////////////////////////////////////////////////////////
// OnSetCursor
BOOL CXHTMLStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (!m_bOnHyperlink)	
		return CStatic::OnSetCursor(pWnd, nHitTest, message);
	else
		return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// OnClicked
void CXHTMLStatic::OnClicked()
{
	CPoint point;
	::GetCursorPos(&point);

	BOOL bOnHyperlink = FALSE;

	int n = m_AnchorRectPtrs.GetSize();

	if (n == 0)
		return;

	int i;
	for (i = 0; i < n; i++)
	{
		CRect *pRect = (CRect *) m_AnchorRectPtrs[i];
		CRect rect = *pRect;
		ClientToScreen(&rect);

		if (rect.PtInRect(point))		 // Cursor is currently over control
		{
			bOnHyperlink = TRUE;
			break;
		}
	}

	if (bOnHyperlink)
		GotoURL(m_AnchorUrls[i], SW_SHOW);
}

///////////////////////////////////////////////////////////////////////////////
// GoToURL
HINSTANCE CXHTMLStatic::GotoURL(LPCTSTR url, int showcmd)
{
	ASSERT(url);
	ASSERT(url[0] != _T('\0'));

	TCHAR key[MAX_PATH + MAX_PATH];

	// First try ShellExecute()
	HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

	// If it failed, get the .htm regkey and lookup the program
	if ((UINT)result <= HINSTANCE_ERROR) 
	{
		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) 
		{
			_tcscat(key, _T("\\shell\\open\\command"));

			if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) 
			{
				TCHAR *pos;
				pos = _tcsstr(key, _T("\"%1\""));
				if (pos == NULL) {					   // No quotes found
					pos = _tcsstr(key, _T("%1"));	   // Check for %1, without quotes 
					if (pos == NULL)				   // No parameter at all...
						pos = key+lstrlen(key)-1;
					else
						*pos = _T('\0');			   // Remove the parameter
				}
				else
					*pos = _T('\0');				   // Remove the parameter

				_tcscat(pos, _T(" "));
				_tcscat(pos, url);
				result = (HINSTANCE) WinExec((LPSTR)key,showcmd);
			}
		}
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////
// GetRegKey
LONG CXHTMLStatic::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hkey;
	LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);
	
	*retdata = 0;

	if (retval == ERROR_SUCCESS) 
	{
		long datasize = MAX_PATH;
		TCHAR data[MAX_PATH];
		retval = RegQueryValue(hkey, NULL, data, &datasize);
		if (retval == ERROR_SUCCESS) 
		{
			lstrcpy(retdata, data);
			RegCloseKey(hkey);
		}
	}
	
	return retval;
}

///////////////////////////////////////////////////////////////////////////////
// OnDestroy
void CXHTMLStatic::OnDestroy() 
{
	if (m_bHyperlinkTimer)
		KillTimer(1);
	m_bHyperlinkTimer = FALSE;

	CStatic::OnDestroy();
}
