// UIEditorView.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "MainFrm.h"
#include "UIEditorDoc.h"
#include "UIEditorView.h"
#include "ImageHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CUIEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CUIEditorView, CScrollView)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

CUIEditorView::CUIEditorView()
{
	CSize	sizeTotal;

	sizeTotal.cx	= MAX_WIDTH;
	sizeTotal.cy	= MAX_HEIGHT;
	
	SetScrollSizes(MM_TEXT, sizeTotal);

	m_crView		= RGB(0x80, 0x80, 0x80);
	m_crCanvas		= RGB(0xF0, 0xF0, 0xF0);
	m_crCtrl		= RGB(0xA0, 0xA0, 0xA0);
	m_bShowBorder	= FALSE;
	m_bShowID		= FALSE;
	m_bShowText		= TRUE;
	m_bFillCtrl		= TRUE;
	m_bResize		= FALSE;
	m_bMove			= FALSE;
	m_nResizeEdge	= EDGE_NONE;
}

CUIEditorView::~CUIEditorView()
{
}

CUIEditorView* CUIEditorView::GetUIView()
{
	CFrameWnd*	pFrame	= (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	CView*		pView	= pFrame->GetActiveView();

	if (!pView)
	{
		return NULL;
	}

	if (!pView->IsKindOf(RUNTIME_CLASS(CUIEditorView)))
	{
		return NULL;
	}

	return (CUIEditorView*)pView;
}

BOOL CUIEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CUIEditorView::OnDraw(CDC* pDC)
{
	CUIEditorDoc*	pDoc = GetDocument();
	CDC				MemDC;
	CBitmap			MemBitmap;
	CBitmap*		MemOldBmp;
	CFont			NewFont;
	CFont*			pOldFont;
	CRect			rcWnd;
	COLORREF		crOld;
	int				nOldMode;
	CRect			rcID;
	int				lp1;
	int				lp2;
	int				lp3;
	int				lp4;
	DWORD			dwGroup;
	DWORD			dwCtrl;
	CString			strImageName;

	ASSERT_VALID(pDoc);

	GetClientRect(&rcWnd);
	MemDC.CreateCompatibleDC(pDC);
	MemBitmap.CreateCompatibleBitmap(pDC, rcWnd.Width(), rcWnd.Height());

	MemOldBmp	= MemDC.SelectObject(&MemBitmap);

	NewFont.CreatePointFont(60, _T("Arial"), &MemDC);
	
	pOldFont	= MemDC.SelectObject(&NewFont);
	crOld		= MemDC.SetTextColor(RGB(0xFF, 0xFF, 0x40));
	nOldMode	= MemDC.SetBkMode(TRANSPARENT);

	MemDC.FillSolidRect(0, 0, rcWnd.Width(), rcWnd.Height(), m_crView);

	dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);

	if (dwGroup != UI_INVALIDID)
	{
		MemDC.FillSolidRect(4, 4, pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth, pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight, RGB(0x60, 0x60, 0x60));
		MemDC.FillSolidRect(0, 0, pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth, pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight, m_crCanvas);

		for (lp1 = 0; lp1 < pDoc->m_arrUICtrlC.GetCount(); lp1++)
		{
			if (pDoc->m_arrUICtrlC.GetAt(lp1).dwPageID == pDoc->m_dwCPageID)
			{
				for (lp2 = 0; lp2 < pDoc->m_arrUICtrlS.GetCount(); lp2++)
				{
					if ((pDoc->m_arrUICtrlS.GetAt(lp2).dwCtrlID == pDoc->m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp2).dwGroupID == pDoc->m_dwCGroupID))
					{
						if (pDoc->m_arrUICtrlS.GetAt(lp2).bEnable)
						{
							BOOL	bImageShown		= FALSE;
							BOOL	bImageLinked	= FALSE;
							DWORD	dwImage			= pDoc->GetImageByID(pDoc->m_dwCImageID);

							if (pDoc->m_nCType == UI_ITEM_IMAGE)
							{
								if (pDoc->m_arrUIImageC.GetAt(dwImage).dwCtrlID == pDoc->m_arrUICtrlC.GetAt(lp1).dwCtrlID)
								{
									for (lp3 = 0; lp3 < pDoc->m_arrUIImageS.GetCount(); lp3++)
									{
										if ((pDoc->m_arrUIImageS.GetAt(lp3).dwImageID == pDoc->m_dwCImageID) && (pDoc->m_arrUIImageS.GetAt(lp3).dwGroupID == pDoc->m_dwCGroupID))
										{
											if (pDoc->GetImageFullPath(strImageName, pDoc->m_arrUIImageC.GetAt(dwImage), pDoc->m_arrUIImageS.GetAt(lp3), TRUE))
											{
												DrawBitmap(&MemDC, strImageName, pDoc->m_arrUIImageS.GetAt(lp3).nType, &pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow);

												bImageShown		= TRUE;
												bImageLinked	= TRUE;
											}
										}
									}
								}
							}

							if (bImageLinked == FALSE)
							{
								for (lp3 = 0; lp3 < pDoc->m_arrUIImageC.GetCount(); lp3++)
								{
									if (pDoc->m_arrUIImageC.GetAt(lp3).dwCtrlID == pDoc->m_arrUICtrlC.GetAt(lp1).dwCtrlID)
									{
										for (lp4 = 0; lp4 < pDoc->m_arrUIImageS.GetCount(); lp4++)
										{
											if ((pDoc->m_arrUIImageS.GetAt(lp4).dwImageID == pDoc->m_arrUIImageC.GetAt(lp3).dwImageID) && (pDoc->m_arrUIImageS.GetAt(lp4).dwGroupID == pDoc->m_dwCGroupID))
											{
												if (pDoc->GetImageFullPath(strImageName, pDoc->m_arrUIImageC.GetAt(lp3), pDoc->m_arrUIImageS.GetAt(lp4), TRUE))
												{
													DrawBitmap(&MemDC, strImageName, pDoc->m_arrUIImageS.GetAt(lp4).nType, &pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow);

													bImageShown	= TRUE;
													break;
												}
											}
										}

										break;
									}
								}
							}

							if ((bImageShown == FALSE) && (m_bFillCtrl == TRUE))
							{
								MemDC.FillSolidRect(&pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow, m_crCtrl);
							}

							if (m_bShowID)
							{
								rcID.CopyRect(&pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow);
								rcID.DeflateRect(4, 4);
								MemDC.DrawTextEx(pDoc->m_arrUICtrlC.GetAt(lp1).szName, &rcID, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_END_ELLIPSIS, NULL);
							}

							if ((_tcslen(pDoc->m_arrUICtrlC.GetAt(lp1).szText)) && (m_bShowText))
							{
								rcID.CopyRect(&pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow);
								MemDC.DrawTextEx(pDoc->m_arrUICtrlC.GetAt(lp1).szText, &rcID, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS, NULL);
							}

							if ((pDoc->m_nCType == UI_ITEM_CTRL) && (pDoc->GetCtrlByID(pDoc->m_dwCCtrlID) == lp1))
							{
								DrawSelector(&MemDC, &pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow, OBJSEL_CURRENT);
							}
							else
							{
								BOOL	bSelector	= FALSE;

								for (lp3 = 0; lp3 < pDoc->m_arrSLCtrlID.GetCount(); lp3++)
								{
									if (pDoc->m_arrSLCtrlID.GetAt(lp3) == pDoc->m_arrUICtrlS.GetAt(lp2).dwCtrlID)
									{
										DrawSelector(&MemDC, &pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow, OBJSEL_CURRENT);

										bSelector	= TRUE;
										break;
									}
								}

								if ((bSelector == TRUE) && (m_bShowBorder == TRUE))
								{
									DrawSelector(&MemDC, &pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow, OBJSEL_NORMAL);
								}
							}
						}
					}
				}
			}
		}

		if (pDoc->m_nCType == UI_ITEM_CTRL)
		{
			dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

			if (dwCtrl != UI_INVALIDID)
			{
				if (pDoc->m_arrUICtrlC.GetAt(dwCtrl).dwPageID == pDoc->m_dwCPageID)
				{
					for (lp1 = 0; lp1 < pDoc->m_arrUICtrlS.GetCount(); lp1++)
					{
						if ((pDoc->m_arrUICtrlS.GetAt(lp1).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp1).dwGroupID == pDoc->m_dwCGroupID) && (pDoc->m_arrUICtrlS.GetAt(lp1).bEnable == FALSE))
						{
							for (lp2 = 0; lp2 < pDoc->m_arrUIImageC.GetCount(); lp2++)
							{
								if (pDoc->m_arrUIImageC.GetAt(lp2).dwCtrlID == pDoc->m_dwCCtrlID)
								{
									for (lp3 = 0; lp3 < pDoc->m_arrUIImageS.GetCount(); lp3++)
									{
										if ((pDoc->m_arrUIImageS.GetAt(lp3).dwImageID == pDoc->m_arrUIImageC.GetAt(lp2).dwImageID) && (pDoc->m_arrUIImageS.GetAt(lp3).dwGroupID == pDoc->m_dwCGroupID))
										{
											if (pDoc->GetImageFullPath(strImageName, pDoc->m_arrUIImageC.GetAt(lp2), pDoc->m_arrUIImageS.GetAt(lp3), TRUE))
											{
												DrawBitmap(&MemDC, strImageName, pDoc->m_arrUIImageS.GetAt(lp3).nType, &pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow);
												break;
											}
										}
									}

									break;
								}
							}

							if (m_bShowID)
							{
								rcID.CopyRect(&pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow);
								rcID.DeflateRect(4, 4);
								MemDC.DrawTextEx(pDoc->m_arrUICtrlC.GetAt(dwCtrl).szName, &rcID, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_END_ELLIPSIS, NULL);
							}

							DrawSelector(&MemDC, &pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow, OBJSEL_HIDDEN);
							break;
						}
					}
				}
			}
		}
	}

	MemDC.SetBkMode(nOldMode);
	MemDC.SetTextColor(crOld);
	MemDC.SelectObject(pOldFont);
	NewFont.DeleteObject();

	pDC->BitBlt(0, 0, rcWnd.Width(), rcWnd.Height(), &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(&MemOldBmp);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CUIEditorView::OnInitialUpdate()
{
	CUIEditorDoc*	pDoc = GetDocument();

	CScrollView::OnInitialUpdate();

	DragAcceptFiles();
	
	pDoc->UpdateWorkspace(WSU_FULL);
	pDoc->UpdateProperties();
}

BOOL CUIEditorView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CUIEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CUIEditorDoc*	pDoc	= GetDocument();
	POINT			ptDelta	= { 0, 0 };
	DWORD			dwGroup;
	DWORD			dwCtrl;
	int				lp;

	ASSERT_VALID(pDoc);

	dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
	dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

	if ((pDoc->m_nCType == UI_ITEM_CTRL) && (dwCtrl != UI_INVALIDID))
	{
		switch (nChar)
		{
		case VK_LEFT:
			ptDelta.x--;
			break;
		case VK_UP:
			ptDelta.y--;
			break;
		case VK_RIGHT:
			ptDelta.x++;
			break;
		case VK_DOWN:
			ptDelta.y++;
			break;
		}
	}

	if ((ptDelta.x != 0) || (ptDelta.y != 0))
	{
		for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
		{
			if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
			{
				pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left			+= ptDelta.x;
				pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top			+= ptDelta.y;
				pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right			+= ptDelta.x;
				pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom		+= ptDelta.y;

				if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left < 0)
				{
					ptDelta.x										= 0 - pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left		+= ptDelta.x;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right		+= ptDelta.x;
				}

				if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right > pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth)
				{
					ptDelta.x										= pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth - pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left		+= ptDelta.x;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right		+= ptDelta.x;
				}

				if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top < 0)
				{
					ptDelta.y										= 0 - pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top		+= ptDelta.y;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom	+= ptDelta.y;
				}

				if (pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom > pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight)
				{
					ptDelta.y										= pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight - pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top		+= ptDelta.y;
					pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom	+= ptDelta.y;
				}

				Invalidate();
				pDoc->UpdateProperties();
				pDoc->SetModifiedFlag();
			}
		}
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CUIEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CUIEditorDoc*	pDoc	= GetDocument();

	ASSERT_VALID(pDoc);

	if (pDoc->m_dwCGroupID  == UI_INVALIDID)
	{
		return;
	}

	DWORD	dwCtrlID	= UI_INVALIDID;
	int		nType		= FindItemByPos(point.x, point.y, dwCtrlID);
	int		lp;

	switch (nType)
	{
	case UI_ITEM_NONE:
		{
			pDoc->m_nCType	= UI_ITEM_GROUP;
		}
		return;
	case UI_ITEM_PAGE:
		{
			pDoc->ClearSelection();

			pDoc->m_nCType		= UI_ITEM_PAGE;
			pDoc->m_nSLType		= UI_ITEM_PAGE;
			pDoc->m_dwSLPageID	= pDoc->m_dwCPageID;
		}
		break;
	case UI_ITEM_CTRL:
		{
			if ((pDoc->m_nCType == UI_ITEM_CTRL) && (dwCtrlID == pDoc->m_dwCCtrlID) && (dwCtrlID != UI_INVALIDID))
			{
				if (nFlags & MK_CONTROL)
				{
					// Do nothing
				}
				else
				{
					// Clear previous selection and set current selection
					pDoc->ClearSelection();

					if (m_nResizeEdge == EDGE_NONE)
					{
						m_hCursor	= SetCursor(LoadCursor(NULL, IDC_HAND));

						SetCapture();

						m_bMove		= TRUE;
						m_ptOldMove	= point;
					}
					else
					{
						HCURSOR	hCursor;

						switch (m_nResizeEdge)
						{
						case EDGE_LEFTTOP:
						case EDGE_RIGHTBOTTOM:
							{
								hCursor	= LoadCursor(NULL, IDC_SIZENWSE);
							}
							break;
						case EDGE_TOP:
						case EDGE_BOTTOM:
							{
								hCursor	= LoadCursor(NULL, IDC_SIZENS);
							}
							break;
						case EDGE_RIGHTTOP:
						case EDGE_LEFTBOTTOM:
							{
								hCursor	= LoadCursor(NULL, IDC_SIZENESW);
							}
							break;
						case EDGE_LEFT:
						case EDGE_RIGHT:
							{
								hCursor	= LoadCursor(NULL, IDC_SIZEWE);
							}
							break;
						}

						m_hCursor	= SetCursor(hCursor);

						SetCapture();

						m_bResize		= TRUE;
						m_ptOldResize	= point;
					}
				}
			}
			else
			{
				pDoc->m_nCType		= UI_ITEM_CTRL;
				pDoc->m_dwCCtrlID	= dwCtrlID;
				pDoc->m_nSLType		= UI_ITEM_CTRL;

				if ((nFlags & MK_CONTROL) == 0)
				{
					// Clear previous selection and set current selection
					pDoc->ClearSelection();
					pDoc->m_arrSLCtrlID.Add(dwCtrlID);
				}
				else
				{
					BOOL	bDuplicated	= FALSE;
					DWORD	dwCtrl;

					for (lp = 0; lp < pDoc->m_arrSLCtrlID.GetCount(); lp++)
					{
						if (pDoc->m_arrSLCtrlID.GetAt(lp) == dwCtrlID)
						{
							bDuplicated	= TRUE;
							break;
						}

						dwCtrl	= pDoc->GetCtrlByID(pDoc->m_arrSLCtrlID.GetAt(lp));

						if ((dwCtrl == UI_INVALIDID) || (pDoc->m_arrUICtrlC.GetAt(dwCtrl).dwPageID != pDoc->m_dwCPageID))
						{
							pDoc->ClearSelection();
							break;
						}
					}

					if (!bDuplicated)
					{
						pDoc->m_arrSLCtrlID.Add(dwCtrlID);
					}
				}
			}
		}
		break;
	}

	Invalidate();
	UpdateWindow();
	pDoc->UpdateWorkspace(WSU_SELECT);
	pDoc->UpdateProperties();

	CScrollView::OnLButtonDown(nFlags, point);
}

void CUIEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CUIEditorDoc*	pDoc	= GetDocument();

	ASSERT_VALID(pDoc);

	if (m_bMove)
	{
		m_bMove	= FALSE;

		ReleaseCapture();
		SetCursor(m_hCursor);
		pDoc->UpdateProperties();
		pDoc->SetModifiedFlag();
	}

	if (m_bResize)
	{
		m_bResize	= FALSE;
		
		ReleaseCapture();
		SetCursor(m_hCursor);
		pDoc->UpdateProperties();
		pDoc->SetModifiedFlag();
	}

	CScrollView::OnLButtonUp(nFlags, point);
}

void CUIEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CUIEditorDoc*	pDoc	= GetDocument();

	ASSERT_VALID(pDoc);

	POINT	ptDelta;
	int		lp;
	int		nCtrlS	= UI_INVALIDID;
	DWORD	dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
	DWORD	dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

	for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
	{
		if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
		{
			nCtrlS	= lp;
			break;
		}
	}

	if (m_bMove)
	{
		if (nFlags == MK_LBUTTON || nFlags == MK_MBUTTON)
		{
			ptDelta.x	= point.x - m_ptOldMove.x;
			ptDelta.y	= point.y - m_ptOldMove.y;
		
			pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left		+= ptDelta.x;
			pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top		+= ptDelta.y;
			pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right		+= ptDelta.x;
			pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom	+= ptDelta.y;

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left < 0)
			{
				ptDelta.x											= 0 - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left		+= ptDelta.x;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right		+= ptDelta.x;
			}

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right > pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth)
			{
				ptDelta.x											= pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left		+= ptDelta.x;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right		+= ptDelta.x;
			}

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top < 0)
			{
				ptDelta.y											= 0 - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top		+= ptDelta.y;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom	+= ptDelta.y;
			}

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom > pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight)
			{
				ptDelta.y											= pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top		+= ptDelta.y;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom	+= ptDelta.y;
			}

			Invalidate();
			UpdateWindow();
			pDoc->UpdateProperties();
			pDoc->SetModifiedFlag();

			m_ptOldMove	= point;
		}
	}
	else if (m_bResize)
	{
		if (nFlags == MK_LBUTTON || nFlags == MK_MBUTTON)
		{
			ptDelta.x	= point.x - m_ptOldResize.x;
			ptDelta.y	= point.y - m_ptOldResize.y;
		
			switch (m_nResizeEdge)
			{
			case EDGE_LEFTTOP:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left		+= ptDelta.x;
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top		+= ptDelta.y;
				}
				break;
			case EDGE_TOP:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top		+= ptDelta.y;
				}
				break;
			case EDGE_RIGHTTOP:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right		+= ptDelta.x;
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top		+= ptDelta.y;
				}
				break;
			case EDGE_RIGHT:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right		+= ptDelta.x;
				}
				break;
			case EDGE_RIGHTBOTTOM:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right		+= ptDelta.x;
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom	+= ptDelta.y;
				}
				break;
			case EDGE_BOTTOM:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom	+= ptDelta.y;
				}
				break;
			case EDGE_LEFTBOTTOM:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left		+= ptDelta.x;
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom	+= ptDelta.y;
				}
				break;
			case EDGE_LEFT:
				{
					pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left		+= ptDelta.x;
				}
				break;
			}

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left < 0)
			{
				ptDelta.x											= 0 - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left		+= ptDelta.x;
			}

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right > pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth)
			{
				ptDelta.x											= pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right		+= ptDelta.x;
			}

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top < 0)
			{
				ptDelta.y											= 0 - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top		+= ptDelta.y;
			}

			if (pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom > pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight)
			{
				ptDelta.y											= pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom;
				pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom	+= ptDelta.y;
			}

			pDoc->m_arrUICtrlS.GetAt(nCtrlS).uWidth		= static_cast<USHORT>(pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.right - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.left);
			pDoc->m_arrUICtrlS.GetAt(nCtrlS).uHeight	= static_cast<USHORT>(pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.bottom - pDoc->m_arrUICtrlS.GetAt(nCtrlS).rcWindow.top);

			Invalidate();
			UpdateWindow();
			pDoc->UpdateProperties();
			pDoc->SetModifiedFlag();

			m_ptOldResize	= point;
		}
	}
	else
	{
		HCURSOR	hCursor	= NULL;

		m_nResizeEdge	= IsOnEdge(point.x, point.y);

		switch (m_nResizeEdge)
		{
		case EDGE_LEFTTOP:
		case EDGE_RIGHTBOTTOM:
			{
				hCursor	= LoadCursor(NULL, IDC_SIZENWSE);
			}
			break;
		case EDGE_TOP:
		case EDGE_BOTTOM:
			{
				hCursor	= LoadCursor(NULL, IDC_SIZENS);
			}
			break;
		case EDGE_RIGHTTOP:
		case EDGE_LEFTBOTTOM:
			{
				hCursor	= LoadCursor(NULL, IDC_SIZENESW);
			}
			break;
		case EDGE_LEFT:
		case EDGE_RIGHT:
			{
				hCursor	= LoadCursor(NULL, IDC_SIZEWE);
			}
			break;
		}

		if (hCursor != NULL)
		{
			m_hCursor	= SetCursor(hCursor);
		}
		else
		{
			if (m_hCursor != NULL)
			{
				SetCursor(m_hCursor);
			}
		}
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CUIEditorView::OnDropFiles(HDROP hDropInfo)
{
	DECLARE_FRAME()

	CUIEditorDoc*	pDoc	= GetDocument();

	ASSERT_VALID(pDoc);

	TCHAR		szFileName[MAX_PATH];
	TCHAR		szDragName[MAX_PATH];
	POINT		pt;
	int			nType;
	DWORD		dwCtrl;
	UINT		uFiles;
	int			lp0;
	int			lp1;
	int			lp2;
	SYSTEMTIME	st;
	CString		strImageFolder;
	CString		strFullPath;
	CString		strPath;
	CString		strTitle;
	CString		strExt;
	int			nPos;
	BOOL		bFound;
	DWORD		dwFound	= UI_INVALIDID;

	DragQueryPoint(hDropInfo, &pt);

	nType	= FindItemByPos(pt.x, pt.y, dwCtrl);
	uFiles	= DragQueryFile(hDropInfo, 0xFFFFFFFF, szFileName, MAX_PATH);

	switch (nType)
	{
	case UI_ITEM_PAGE:
		{
			pDoc->m_nCType		= UI_ITEM_PAGE;
		}
		break;
	case UI_ITEM_CTRL:
		{
			pDoc->m_nCType		= UI_ITEM_CTRL;
			pDoc->m_dwCCtrlID	= dwCtrl;
		}
		break;
	case UI_ITEM_NONE:
		{
			pDoc->m_nCType		= UI_ITEM_GROUP;
		}
		break;
	}

	if (uFiles > 0)
	{
		BeginWaitCursor();

		if (pDoc->m_nCType != UI_ITEM_CTRL)
		{
			pDoc->AddCtrl();

			pDoc->m_nCType	= UI_ITEM_CTRL;
		}

		if (pDoc->m_nCType == UI_ITEM_CTRL)
		{
			for (lp0 = 0; lp0 < static_cast<int>(uFiles); lp0++)
			{
				DragQueryFile(hDropInfo, lp0, szDragName, MAX_PATH);

				strFullPath		= szDragName;
				nPos			= strFullPath.ReverseFind(_T('\\'));
				strImageFolder	= strFullPath.Left(nPos + 1);
				strPath			= strFullPath.Mid(nPos + 1);
				nPos			= strPath.ReverseFind(_T('.'));
				strTitle		= strPath.Left(nPos);
				strExt			= strPath.Mid(nPos + 1);
				dwFound			= UI_INVALIDID;

				for (lp1 = 0; lp1 < pDoc->m_arrUIImageC.GetCount(); lp1++)
				{
					if (!strTitle.CompareNoCase(pDoc->m_arrUIImageC.GetAt(lp1).szName))
					{
						for (lp2 = 0; lp2 < pDoc->m_arrUIImageS.GetCount(); lp2++)
						{
							if ((pDoc->m_arrUIImageS.GetAt(lp2).dwImageID == pDoc->m_arrUIImageC.GetAt(lp1).dwImageID) && (pDoc->m_arrUIImageS.GetAt(lp2).dwGroupID == pDoc->m_dwCGroupID))
							{
								dwFound	= lp2;
								break;
							}
						}

						if (dwFound != UI_INVALIDID)
						{
							bFound	= FALSE;

							if (!strExt.CompareNoCase(_T("bmp")))
							{
								if ((pDoc->m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_BMP) != UI_IMAGE_BMP)
								{
									bFound	= TRUE;
								}
							}
							else if (!strExt.CompareNoCase(_T("png")))
							{
								if ((pDoc->m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_PNG) != UI_IMAGE_PNG)
								{
									bFound	= TRUE;
								}
							}
#if FALSE
							else if ((!strExt.CompareNoCase(_T("jpg"))) || (!strExt.CompareNoCase(_T("jpeg"))))
							{
								if ((pDoc->m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_JPG) != UI_IMAGE_JPG)
								{
									bFound	= TRUE;
								}
							}
							else if (!strExt.CompareNoCase(_T("gif")))
							{
								if ((pDoc->m_arrUIImageS.GetAt(dwFound).nType & UI_IMAGE_GIF) != UI_IMAGE_GIF)
								{
									bFound	= TRUE;
								}
							}
#endif
							if (bFound)
							{
								bFound	= FALSE;

								GetLocalTime(&st);
								strImageFolder.Format(_T("%s%s_%04d%02d%02d%02d%02d%02d%03d.%s"), strImageFolder, strTitle, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, strExt);
								MoveFile(strFullPath, strImageFolder);
								
								strFullPath	= strImageFolder;

								OUTPUT_STR2(_T("Image %s was renamed to %s due to name confliction"), strFullPath, strImageFolder);
								break;
							}
						}
					}
				}

				if (!pDoc->AddImage(strFullPath))
				{
					continue;
				}

				bFound	= FALSE;

				for (lp1 = 0; lp1 < pDoc->m_arrUIImageC.GetCount(); lp1++)
				{
					if ((pDoc->m_arrUIImageC.GetAt(lp1).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUIImageC.GetAt(lp1).dwImageID != pDoc->m_dwCImageID))
					{
						bFound	= TRUE;
						break;
					}
				}

				dwFound	= UI_INVALIDID;

				for (lp1 = 0; lp1 < pDoc->m_arrUIImageS.GetCount(); lp1++)
				{
					if ((pDoc->m_arrUIImageS.GetAt(lp1).dwImageID == pDoc->m_dwCImageID) && (pDoc->m_arrUIImageS.GetAt(lp1).dwGroupID == pDoc->m_dwCGroupID))
					{
						dwFound	= lp1;
						break;
					}
				}

				if (bFound == FALSE)
				{
					for (lp1 = 0; lp1 < pDoc->m_arrUICtrlS.GetCount(); lp1++)
					{
						if (pDoc->m_arrUICtrlS.GetAt(lp1).dwCtrlID == pDoc->m_dwCCtrlID)
						{
							pDoc->m_arrUICtrlS.GetAt(lp1).uWidth			= pDoc->m_arrUIImageS.GetAt(dwFound).uWidth;
							pDoc->m_arrUICtrlS.GetAt(lp1).uHeight			= pDoc->m_arrUIImageS.GetAt(dwFound).uHeight;
							pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.right	= pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.left + pDoc->m_arrUICtrlS.GetAt(lp1).uWidth;
							pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.bottom	= pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.top + pDoc->m_arrUICtrlS.GetAt(lp1).uHeight;
						}
					}
				}

				for (lp1 = 0; lp1 < pDoc->m_arrUICtrlS.GetCount(); lp1++)
				{
					if (pDoc->m_arrUICtrlS.GetAt(lp1).dwCtrlID == pDoc->m_dwCCtrlID)
					{
						if (pDoc->m_arrUICtrlS.GetAt(lp1).uWidth < pDoc->m_arrUIImageS.GetAt(dwFound).uWidth)
						{
							pDoc->m_arrUICtrlS.GetAt(lp1).uWidth			= pDoc->m_arrUIImageS.GetAt(dwFound).uWidth;
							pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.right	= pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.left + pDoc->m_arrUICtrlS.GetAt(lp1).uWidth;
						}

						if (pDoc->m_arrUICtrlS.GetAt(lp1).uHeight < pDoc->m_arrUIImageS.GetAt(dwFound).uHeight)
						{
							pDoc->m_arrUICtrlS.GetAt(lp1).uHeight			= pDoc->m_arrUIImageS.GetAt(dwFound).uHeight;
							pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.bottom	= pDoc->m_arrUICtrlS.GetAt(lp1).rcWindow.top + pDoc->m_arrUICtrlS.GetAt(lp1).uHeight;
						}
					}
				}
			}
		}

		EndWaitCursor();

		pDoc->m_nCType	= UI_ITEM_IMAGE;

		Invalidate();
		pDoc->UpdateWorkspace(WSU_FULL);
		pDoc->UpdateWorkspace(WSU_SELECT);
		pDoc->UpdateProperties();
		pDoc->SetModifiedFlag();
	}

	pFrame->m_wndProperties.SetFocus();
	DragFinish(hDropInfo);

	CScrollView::OnDropFiles(hDropInfo);
}

#ifdef _DEBUG
void CUIEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CUIEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CUIEditorDoc* CUIEditorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUIEditorDoc)));

	return (CUIEditorDoc*)m_pDocument;
}
#endif //_DEBUG


void CUIEditorView::DrawSelector(CDC* pDC, LPRECT lprc, int nType)
{
	int			nWidth	= lprc->right - lprc->left;
	int			nHeight	= lprc->bottom - lprc->top;
	COLORREF	crLine;
	COLORREF	crPoint;

	switch (nType)
	{
	case OBJSEL_NORMAL:
		{
			crLine	= RGB(0x90, 0x90, 0xFF);
			crPoint	= RGB(0xFF, 0xFF, 0x80);
		}
		break;
	case OBJSEL_CURRENT:
		{
			crLine	= RGB(0xE0, 0xE0, 0xE0);
			crPoint	= RGB(0xFF, 0xFF, 0x80);
		}
		break;
	case OBJSEL_HIDDEN:
		{
			crLine	= RGB(0xE0, 0x60, 0xE0);
			crPoint	= RGB(0xFF, 0x80, 0xFF);
		}
		break;
	}

	pDC->FillSolidRect(lprc->left, lprc->top, nWidth, 2, crLine);
	pDC->FillSolidRect(lprc->left, lprc->top, 2, nHeight, crLine);
	pDC->FillSolidRect(lprc->left, lprc->bottom - 1, nWidth, 2, crLine);
	pDC->FillSolidRect(lprc->right - 1, lprc->top, 2, nHeight, crLine);

	if ((nWidth > 8) && (nHeight > 8) && (nType != OBJSEL_NORMAL))
	{
		pDC->FillSolidRect(lprc->left, lprc->top, 4, 4, crPoint);
		pDC->FillSolidRect(lprc->right - 4, lprc->top, 4, 4, crPoint);
		pDC->FillSolidRect(lprc->left, lprc->bottom - 4, 4, 4, crPoint);
		pDC->FillSolidRect(lprc->right - 4, lprc->bottom - 4, 4, 4, crPoint);
	}
}

int CUIEditorView::FindItemByPos(int x, int y, DWORD &dwCtrlID)
{
	CUIEditorDoc*	pDoc	= GetDocument();

	ASSERT_VALID(pDoc);

	int		lp1;
	int		lp2;
	int		ct;
	RECT	rc;
	POINT	pt		= { x, y };
	DWORD	dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);

	dwCtrlID	= UI_INVALIDID;
	ct			= static_cast<int>(pDoc->m_arrUICtrlC.GetCount());

	for (lp1 = ct - 1; lp1 >= 0; lp1--)
	{
		if (pDoc->m_arrUICtrlC.GetAt(lp1).dwPageID == pDoc->m_dwCPageID)
		{
			for (lp2 = 0; lp2 < pDoc->m_arrUICtrlS.GetCount(); lp2++)
			{
				if ((pDoc->m_arrUICtrlS.GetAt(lp2).dwCtrlID == pDoc->m_arrUICtrlC.GetAt(lp1).dwCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp2).dwGroupID == pDoc->m_dwCGroupID) && (pDoc->m_arrUICtrlS.GetAt(lp2).bEnable))
				{
					if (PtInRect(&pDoc->m_arrUICtrlS.GetAt(lp2).rcWindow, pt))
					{
						dwCtrlID	= pDoc->m_arrUICtrlC.GetAt(lp1).dwCtrlID;
		
						return UI_ITEM_CTRL;
					}
				}
			}
		}		
	}

	SetRect(&rc, 0, 0, pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth, pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight);

	if (PtInRect(&rc, pt))
	{
		return UI_ITEM_PAGE;
	}

	return UI_ITEM_NONE;
}

#define	EDGE_HALF_THICKNESS	3

int CUIEditorView::IsOnEdge(int x, int y)
{
	CUIEditorDoc*	pDoc	= GetDocument();

	ASSERT_VALID(pDoc);

	int		lp;
	RECT	rc;
	POINT	pt		= { x, y };
	DWORD	dwCtrl	= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);

	if ((pDoc->m_nCType != UI_ITEM_CTRL) || (dwCtrl == UI_INVALIDID) || (pDoc->m_arrUICtrlC.GetAt(dwCtrl).dwPageID != pDoc->m_dwCPageID))
	{
		return EDGE_NONE;
	}

	for (lp = 0; lp < pDoc->m_arrUICtrlS.GetCount(); lp++)
	{
		if ((pDoc->m_arrUICtrlS.GetAt(lp).dwCtrlID == pDoc->m_dwCCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp).dwGroupID == pDoc->m_dwCGroupID))
		{
			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left - EDGE_HALF_THICKNESS;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top - EDGE_HALF_THICKNESS;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + EDGE_HALF_THICKNESS + 1;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + EDGE_HALF_THICKNESS + 1;

			if (PtInRect(&rc, pt))
			{
				return EDGE_LEFTTOP;
			}

			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + EDGE_HALF_THICKNESS + 1;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top - EDGE_HALF_THICKNESS;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right - EDGE_HALF_THICKNESS;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + EDGE_HALF_THICKNESS + 1;

			if (PtInRect(&rc, pt))
			{
				return EDGE_TOP;
			}

			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right - EDGE_HALF_THICKNESS - 1;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top - EDGE_HALF_THICKNESS;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right + EDGE_HALF_THICKNESS;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + EDGE_HALF_THICKNESS + 1;

			if (PtInRect(&rc, pt))
			{
				return EDGE_RIGHTTOP;
			}

			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right - EDGE_HALF_THICKNESS - 1;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + EDGE_HALF_THICKNESS + 1;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right + EDGE_HALF_THICKNESS;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom - EDGE_HALF_THICKNESS;

			if (PtInRect(&rc, pt))
			{
				return EDGE_RIGHT;
			}

			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right - EDGE_HALF_THICKNESS - 1;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom - EDGE_HALF_THICKNESS;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right + EDGE_HALF_THICKNESS;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom + EDGE_HALF_THICKNESS + 1;

			if (PtInRect(&rc, pt))
			{
				return EDGE_RIGHTBOTTOM;
			}

			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + EDGE_HALF_THICKNESS + 1;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom - EDGE_HALF_THICKNESS;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.right - EDGE_HALF_THICKNESS;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom + EDGE_HALF_THICKNESS + 1;

			if (PtInRect(&rc, pt))
			{
				return EDGE_BOTTOM;
			}

			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left - EDGE_HALF_THICKNESS;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom - EDGE_HALF_THICKNESS;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + EDGE_HALF_THICKNESS + 1;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom + EDGE_HALF_THICKNESS + 1;

			if (PtInRect(&rc, pt))
			{
				return EDGE_LEFTBOTTOM;
			}

			rc.left		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left - EDGE_HALF_THICKNESS;
			rc.top		= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.top + EDGE_HALF_THICKNESS + 1;
			rc.right	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.left + EDGE_HALF_THICKNESS + 1;
			rc.bottom	= pDoc->m_arrUICtrlS.GetAt(lp).rcWindow.bottom - EDGE_HALF_THICKNESS;

			if (PtInRect(&rc, pt))
			{
				return EDGE_LEFT;
			}
		}
	}

	return EDGE_NONE;
}

void CUIEditorView::DrawBitmap(CDC* pDC, LPCTSTR lpszFileName, int nType, LPRECT lprc)
{
	if (nType & UI_IMAGE_BMP)
	{
		DrawBMP(pDC, lpszFileName, lprc);
	}
	
	if (nType & UI_IMAGE_PNG)
	{
		DrawPNG(pDC, lpszFileName, lprc);
	}

#if FALSE
	if (nType & UI_IMAGE_JPG)
	{
		DrawJPG(pDC, lpszFileName, lprc);
	}
	
	if (nType & UI_IMAGE_GIF)
	{
		DrawGIF(pDC, lpszFileName, lprc);
	}
#endif
}
