// WorkspaceBar.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "UIEditorDoc.h"
#include "WorkspaceBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const	int	nBorderSize	= 1;

#ifndef	ITEM_MAP
#define	ITEM_MAP
#define	ITEM_GROUP(nID)		((UI_ITEM_GROUP << 24) + nID)
#define	ITEM_PAGE(nID)		((UI_ITEM_PAGE << 24) + nID)
#define	ITEM_CTRL(nID)		((UI_ITEM_CTRL << 24) + nID)
#define	ITEM_IMAGE(nID)		((UI_ITEM_IMAGE << 24) + nID)
#define	ITEM_TYPE(nItem)	((nItem >> 24) & 0x000000FF)
#define	ITEM_ID(nItem)		(nItem & 0x00FFFFFF)
#endif

BEGIN_MESSAGE_MAP(CWorkspaceBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(TVN_SELCHANGED, 1, OnTvnSelChanged)
END_MESSAGE_MAP()

CWorkspaceBar::CWorkspaceBar()
{
}

CWorkspaceBar::~CWorkspaceBar()
{
}

int CWorkspaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	CRect	rectDummy;

	rectDummy.SetRectEmpty();

	const	DWORD	dwViewStyle	= WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

	if (!m_wndTree.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Workspace View\n");
		return -1;
	}

	m_lstTree.Create(IDB_ITEMS, 16, 1, RGB(0x80, 0x00, 0x80));
	m_wndTree.SetImageList(&m_lstTree, TVSIL_NORMAL);

	return 0;
}

void CWorkspaceBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	m_wndTree.SetWindowPos(NULL, nBorderSize, nBorderSize, cx - 2 * nBorderSize, cy - 2 * nBorderSize, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CWorkspaceBar::OnPaint() 
{
	CPaintDC	dc(this);
	CRect		rectTree;

	m_wndTree.GetWindowRect(rectTree);
	ScreenToClient(rectTree);
	rectTree.InflateRect(nBorderSize, nBorderSize);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CWorkspaceBar::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CUIEditorDoc*	pDoc		= CUIEditorDoc::GetUIDocument();
	UINT			uiFlags;
	HTREEITEM		hItem;
	CMenu			Menu;
	CPoint			TreePoint	= point;

	UNREFERENCED_PARAMETER(pWnd);

	m_wndTree.ScreenToClient(&TreePoint);

	hItem	= m_wndTree.HitTest(TreePoint, &uiFlags);

	if (hItem && (uiFlags & TVHT_ONITEM))
	{
		m_wndTree.SetFocus();
		m_wndTree.SelectItem(hItem);
		
		DWORD_PTR dwIndex	= m_wndTree.GetItemData(hItem);

		Select(static_cast<DWORD>(dwIndex));

		Menu.CreatePopupMenu();

		switch (pDoc->m_nCType)
		{
		case UI_ITEM_GROUP:
			{
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_PAGE_ADD, _T("페이지 추가"));
			}
			break;
		case UI_ITEM_PAGE:
			{
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_PAGE_GENERATE, _T("코드 생성"));
				Menu.AppendMenu(MF_SEPARATOR);
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_CTRL_ADD, _T("컨트롤 추가"));
				Menu.AppendMenu(MF_SEPARATOR);
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_PAGE_MOVE_TOP, _T("제일 위로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_PAGE_MOVE_UP, _T("위로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_PAGE_MOVE_DOWN, _T("아래로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_PAGE_MOVE_BOTTOM, _T("제일 아래로 이동"));
				Menu.AppendMenu(MF_SEPARATOR);
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_PAGE_DELETE, _T("삭제"));
			}
			break;
		case UI_ITEM_CTRL:
			{
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_IMAGE_ADD, _T("이미지 추가"));
				Menu.AppendMenu(MF_SEPARATOR);
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_CTRL_MOVE_TOP, _T("제일 위로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_CTRL_MOVE_UP, _T("위로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_CTRL_MOVE_DOWN, _T("아래로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_CTRL_MOVE_BOTTOM, _T("제일 아래로 이동"));
				Menu.AppendMenu(MF_SEPARATOR);
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_CTRL_DELETE, _T("삭제"));
			}
			break;
		case UI_ITEM_IMAGE:
			{
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_IMAGE_MOVE_TOP, _T("제일 위로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_IMAGE_MOVE_UP, _T("위로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_IMAGE_MOVE_DOWN, _T("아래로 이동"));
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_IMAGE_MOVE_BOTTOM, _T("제일 아래로 이동"));
				Menu.AppendMenu(MF_SEPARATOR);
				Menu.AppendMenu(MF_ENABLED, ID_ACTION_IMAGE_DELETE, _T("삭제"));
			}
			break;
		}

		Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN, point.x, point.y, AfxGetMainWnd());
	}
}

void CWorkspaceBar::OnTvnSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	CUIEditorDoc*	pDoc		= CUIEditorDoc::GetUIDocument();
	LPNMTREEVIEW	pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM		hItem		= pNMTreeView->itemNew.hItem;

	if (pDoc == NULL)
	{
		return;
	}

	if ((pNMTreeView->action != 0) && (hItem != NULL))
	{
		DWORD_PTR	dwItem	= m_wndTree.GetItemData(hItem);

		Select(static_cast<DWORD>(dwItem));
		pDoc->ClearSelection();
	}

	pDoc->UpdateAllViews(NULL);
	pDoc->UpdateProperties();

	*pResult = 0;
}

void CWorkspaceBar::BuildTree()
{
	CUIEditorDoc*	pDoc	= CUIEditorDoc::GetUIDocument();
	DWORD			dwGroup	= pDoc->GetGroupByID(pDoc->m_dwCGroupID);
	CString			strName;
	HTREEITEM		hItemG, hItemP, hItemC, hItemI;
	int				lp1, lp2, lp3;
	BOOL			bEnable;

	m_wndTree.DeleteAllItems();

	// Group

	strName.Format(_T("%s [%dx%d]"), pDoc->m_arrUIGroup.GetAt(dwGroup).szName, pDoc->m_arrUIGroup.GetAt(dwGroup).uWidth, pDoc->m_arrUIGroup.GetAt(dwGroup).uHeight);

	hItemG	= m_wndTree.InsertItem(strName, WSI_GROUP, WSI_GROUP);

	m_wndTree.SetItemData(hItemG, ITEM_GROUP(pDoc->m_dwCGroupID));

	for (lp1 = 0; lp1 < pDoc->m_arrUIPageC.GetCount(); lp1++)
	{
		hItemP	= m_wndTree.InsertItem(pDoc->m_arrUIPageC.GetAt(lp1).szName, WSI_PAGE, WSI_PAGE, hItemG);

		m_wndTree.SetItemData(hItemP, ITEM_PAGE(pDoc->m_arrUIPageC.GetAt(lp1).dwPageID));

		for (lp2 = 0; lp2 < pDoc->m_arrUICtrlC.GetCount(); lp2++)
		{
			if (pDoc->m_arrUICtrlC.GetAt(lp2).dwPageID == pDoc->m_arrUIPageC.GetAt(lp1).dwPageID)
			{
				bEnable	= FALSE;

				for (lp3 = 0; lp3 < pDoc->m_arrUICtrlS.GetCount(); lp3++)
				{
					if ((pDoc->m_arrUICtrlS.GetAt(lp3).dwCtrlID == pDoc->m_arrUICtrlC.GetAt(lp2).dwCtrlID) && (pDoc->m_arrUICtrlS.GetAt(lp3).dwGroupID == pDoc->m_dwCGroupID))
					{
						bEnable	= pDoc->m_arrUICtrlS.GetAt(lp3).bEnable;
					}
				}

				if (bEnable)
				{
					hItemC	= m_wndTree.InsertItem(pDoc->m_arrUICtrlC.GetAt(lp2).szName, WSI_CTRL_ENABLE, WSI_CTRL_ENABLE, hItemP);
				}
				else
				{
					hItemC	= m_wndTree.InsertItem(pDoc->m_arrUICtrlC.GetAt(lp2).szName, WSI_CTRL_DISABLE, WSI_CTRL_DISABLE, hItemP);
				}

				m_wndTree.SetItemData(hItemC, ITEM_CTRL(pDoc->m_arrUICtrlC.GetAt(lp2).dwCtrlID));

				for (lp3 = 0; lp3 < pDoc->m_arrUIImageC.GetCount(); lp3++)
				{
					if (pDoc->m_arrUIImageC.GetAt(lp3).dwCtrlID == pDoc->m_arrUICtrlC.GetAt(lp2).dwCtrlID)
					{
						hItemI	= m_wndTree.InsertItem(pDoc->m_arrUIImageC.GetAt(lp3).szName, WSI_IMAGE, WSI_IMAGE, hItemC);

						m_wndTree.SetItemData(hItemI, ITEM_IMAGE(pDoc->m_arrUIImageC.GetAt(lp3).dwImageID));
					}
				}
			}
		}
	}

	hItemG	= FindCurrentItem();

	m_wndTree.EnsureVisible(hItemG);
	m_wndTree.SelectItem(hItemG);
	m_wndTree.SetItemState(hItemG, TVIS_SELECTED, TVIS_SELECTED);

}

void CWorkspaceBar::FindItem(DWORD dwData, HTREEITEM &hFound, HTREEITEM hRoot)
{
	if (hRoot == NULL)
	{
		FindItem(dwData, hFound, m_wndTree.GetRootItem());
		return;
	}

	if (dwData == m_wndTree.GetItemData(hRoot))
	{
		hFound	= hRoot;
	}

	HTREEITEM	hChild	= m_wndTree.GetNextItem(hRoot, TVGN_CHILD);

	for ( ; hChild != NULL && hFound == NULL ; )
	{
		FindItem(dwData, hFound, hChild);

		hChild	= m_wndTree.GetNextSiblingItem(hChild);
	}
}

void CWorkspaceBar::FindItem(LPCTSTR lpszItem, HTREEITEM &hFound, HTREEITEM hRoot)
{
	if (hRoot == NULL)
	{
		FindItem(lpszItem, hFound, m_wndTree.GetRootItem());
		return;
	}

	if (m_wndTree.GetItemText(hRoot).Compare(lpszItem) == 0)
	{
		hFound	= hRoot;
	}

	HTREEITEM	hChild	= m_wndTree.GetNextItem(hRoot, TVGN_CHILD);

	for ( ; hChild != NULL && hFound == NULL ; )
	{
		FindItem(lpszItem, hFound, hChild);

		hChild	= m_wndTree.GetNextSiblingItem(hChild);
	}
}

HTREEITEM CWorkspaceBar::FindCurrentItem()
{
	CUIEditorDoc*	pDoc	= CUIEditorDoc::GetUIDocument();
	HTREEITEM		hItem	= NULL;
	DWORD			dwData;

	switch (pDoc->m_nCType)
	{
	case UI_ITEM_GROUP:
		{
			dwData	= ITEM_GROUP(pDoc->m_dwCGroupID);
		}
		break;
	case UI_ITEM_PAGE:
		{
			dwData	= ITEM_PAGE(pDoc->m_dwCPageID);
		}
		break;
	case UI_ITEM_CTRL:
		{
			dwData	= ITEM_CTRL(pDoc->m_dwCCtrlID);
		}
		break;
	case UI_ITEM_IMAGE:
		{
			dwData	= ITEM_IMAGE(pDoc->m_dwCImageID);
		}
		break;
	default:
		return NULL;
	}

	FindItem(dwData, hItem);

	return hItem;
}

BOOL CWorkspaceBar::Select(DWORD dwItem)
{
	CUIEditorDoc*	pDoc	= CUIEditorDoc::GetUIDocument();
	int				lp1;
	int				lp2;

	if (pDoc == NULL)
	{
		return FALSE;
	}

	pDoc->m_nCType	= ITEM_TYPE(dwItem);
	
	switch (pDoc->m_nCType)
	{
	case UI_ITEM_GROUP:
		{
			pDoc->m_dwCGroupID	= ITEM_ID(dwItem);
		}
		break;
	case UI_ITEM_PAGE:
		{
			pDoc->m_dwCPageID	= ITEM_ID(dwItem);
			pDoc->m_dwCCtrlID	= UI_INVALIDID;
			pDoc->m_dwCImageID	= UI_INVALIDID;

			for (lp1 = 0; lp1 < pDoc->m_arrUICtrlC.GetCount(); lp1++)
			{
				if (pDoc->m_arrUICtrlC.GetAt(lp1).dwPageID == pDoc->m_dwCPageID)
				{
					pDoc->m_dwCCtrlID	= pDoc->m_arrUICtrlC.GetAt(lp1).dwCtrlID;

					for (lp2 = 0; lp2 < pDoc->m_arrUIImageC.GetCount(); lp2++)
					{
						if (pDoc->m_arrUIImageC.GetAt(lp2).dwCtrlID == pDoc->m_dwCCtrlID)
						{
							pDoc->m_dwCImageID	= pDoc->m_arrUIImageC.GetAt(lp2).dwImageID;
							break;
						}
					}

					break;
				}
			}
		}
		break;
	case UI_ITEM_CTRL:
		{
			DWORD	dwCtrl;

			pDoc->m_dwCCtrlID	= ITEM_ID(dwItem);
			dwCtrl				= pDoc->GetCtrlByID(pDoc->m_dwCCtrlID);
			pDoc->m_dwCPageID	= pDoc->m_arrUICtrlC.GetAt(dwCtrl).dwPageID;
			pDoc->m_dwCImageID	= UI_INVALIDID;

			for (lp1 = 0; lp1 < pDoc->m_arrUIImageC.GetCount(); lp1++)
			{
				if (pDoc->m_arrUIImageC.GetAt(lp1).dwCtrlID == pDoc->m_dwCCtrlID)
				{
					pDoc->m_dwCImageID	= pDoc->m_arrUIImageC.GetAt(lp1).dwImageID;
					break;
				}
			}
		}
		break;
	case UI_ITEM_IMAGE:
		{
			DWORD	dwImage;

			pDoc->m_dwCImageID	= ITEM_ID(dwItem);
			dwImage				= pDoc->GetImageByID(pDoc->m_dwCImageID);
			pDoc->m_dwCPageID	= pDoc->m_arrUIImageC.GetAt(dwImage).dwPageID;
			pDoc->m_dwCCtrlID	= pDoc->m_arrUIImageC.GetAt(dwImage).dwCtrlID;
		}
		break;
	}

	return TRUE;
}

void CWorkspaceBar::SelectItem()
{
	CUIEditorDoc*	pDoc	= CUIEditorDoc::GetUIDocument();
	DWORD			dwIndex	= 0xFF000000;

	switch (pDoc->m_nCType)
	{
	case UI_ITEM_GROUP:
		{
			dwIndex	= ITEM_GROUP(pDoc->m_dwCGroupID);
		}
		break;
	case UI_ITEM_PAGE:
		{
			dwIndex	= ITEM_PAGE(pDoc->m_dwCPageID);
		}
		break;
	case UI_ITEM_CTRL:
		{
			dwIndex	= ITEM_CTRL(pDoc->m_dwCCtrlID);
		}
		break;
	case UI_ITEM_IMAGE:
		{
			dwIndex	= ITEM_IMAGE(pDoc->m_dwCImageID);
		}
		break;
	default:
		return;
	}

	Select(dwIndex);
	m_wndTree.SelectItem(FindCurrentItem());
}

void CWorkspaceBar::UpdateItem(LPCTSTR lpszItem, int nImage)
{
	HTREEITEM	hItem	= m_wndTree.GetSelectedItem();

	if (hItem != NULL)
	{
		m_wndTree.SetItemText(hItem, lpszItem);

		if (nImage != WSI_INVALID)
		{
			m_wndTree.SetItemImage(hItem, nImage, nImage);
		}
	}
}

void CWorkspaceBar::DeleteItem()
{
	HTREEITEM	hItem;

	hItem	= m_wndTree.GetSelectedItem();

	if (hItem != NULL)
	{
		m_wndTree.DeleteItem(hItem);
	}

	hItem	= m_wndTree.GetSelectedItem();

	if (hItem != NULL)
	{
		Select(static_cast<DWORD>(m_wndTree.GetItemData(hItem)));
	}
}
