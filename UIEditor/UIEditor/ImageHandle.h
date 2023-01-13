// ImageHandle.h

#pragma once

#ifndef UDB_DEST_BPP
#define UDB_DEST_BPP	16
#endif

#ifndef BMP_EXTRA_BYTES
#define	BMP_EXTRA_BYTES	2
#endif

/*
#ifndef	RGB565
#define RGB565(r, g, b)			((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | (((b & 0xF8) >> 3)))
#define RGB565_TO_RGB24_R(c)	(((c) >> 8) & 0xF8)
#define RGB565_TO_RGB24_G(c)	(((c) >> 3) & 0xFC)
#define RGB565_TO_RGB24_B(c)	(((c) << 3) & 0xF8)
#endif
*/

#ifndef	RGB555
#define RGB555(r, g, b)			((((r) & 0xF8) << 7) | (((g) & 0xF8) << 2) | (((b & 0xF8) >> 3)))
#define RGB555_TO_RGB24_R(c)	(((c) >> 7) & 0xF8)
#define RGB555_TO_RGB24_G(c)	(((c) >> 2) & 0xF8)
#define RGB555_TO_RGB24_B(c)	(((c) << 3) & 0xF8)
#endif

BOOL	GetImageType(LPCTSTR lpszFileName, int &nType, DWORD &dwSize, USHORT &uWidth, USHORT &uHeight, BOOL &bMask);

BOOL	DrawBMP(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc);
BOOL	DrawPNG(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc);

#if FALSE
BOOL	DrawJPG(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc);
BOOL	DrawGIF(CDC* pDC, LPCTSTR lpszFileName, LPRECT lprc);
#endif

BOOL	SaveBufferBMP(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferBMP(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	SaveBufferPNG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferPNG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);

#if FALSE
BOOL	SaveBufferJPG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferJPG(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	SaveBufferGIF(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferGIF(CArchive &ar, LPCTSTR lpszFileName, DWORD dwSize);
#endif

BOOL	SaveBufferBMP(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferBMP(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	SaveBufferPNG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferPNG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);

#if FALSE
BOOL	SaveBufferJPG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferJPG(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	SaveBufferGIF(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);
BOOL	LoadBufferGIF(CFile &file, LPCTSTR lpszFileName, DWORD dwSize);
#endif

BOOL	SaveDatabaseBMP(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress = TRUE);
BOOL	SaveDatabasePNG(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress = TRUE);

#if FALSE
BOOL	SaveDatabaseJPG(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress = TRUE);
BOOL	SaveDatabaseGIF(HANDLE hStream, LPCTSTR lpszFileName, UINT &uSize, UINT &uMaskSize, BOOL bCompress = TRUE);
#endif

BOOL	ResizeBMP(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize);
BOOL	ResizePNG(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize);

#if FALSE
BOOL	ResizeJPG(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize);
BOOL	ResizeGIF(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize);
#endif
