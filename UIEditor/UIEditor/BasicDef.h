// BasicDef.h

#pragma once

#ifndef	DECLARE_FRAME
#define	DECLARE_FRAME()		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
#endif

#ifndef	WND_MAIN
#define	WND_MAIN			pFrame
#define	WND_WORKSPACE		pFrame->m_wndWorkspace
#define	WND_PROPERTIES		pFrame->m_wndProperties
#define	WND_OUTPUT			pFrame->m_wndOutput
#endif

#ifndef	OUTPUT_STR
#define	OUTPUT_STR							pFrame->m_wndOutput.AddString
#define	OUTPUT_STR0(m)						pFrame->m_wndOutput.AddString(__FUNCTION__, m)
#define	OUTPUT_STR1(m, a1)					pFrame->m_wndOutput.AddString(__FUNCTION__, m, a1)
#define	OUTPUT_STR2(m, a1, a2)				pFrame->m_wndOutput.AddString(__FUNCTION__, m, a1, a2)
#define	OUTPUT_STR3(m, a1, a2, a3)			pFrame->m_wndOutput.AddString(__FUNCTION__, m, a1, a2, a3)
#define	OUTPUT_STR4(m, a1, a2, a3, a4)		pFrame->m_wndOutput.AddString(__FUNCTION__, m, a1, a2, a3, a4)
#define	OUTPUT_STR5(m, a1, a2, a3, a4, a5)	pFrame->m_wndOutput.AddString(__FUNCTION__, m, a1, a2, a3, a4, a5)
#endif
