// ShellUtilities.h

#pragma once

// File Manipulations

BOOL	ShellCreate(LPCTSTR lpszItem);
BOOL	ShellCopy(LPCTSTR lpszSource, LPCTSTR lpszTarget);
BOOL	ShellMove(LPCTSTR lpszSource, LPCTSTR lpszTarget);
BOOL	ShellDelete(LPCTSTR lpszItem);

LPCTSTR	TakeName(LPCTSTR lpszFullPath, LPTSTR lpszName, int nSize);
LPCTSTR	TakePath(LPCTSTR lpszFullPath, LPTSTR lpszPath, int nSize, BOOL bAddSeparator = FALSE);
LPCTSTR	TakeFileName(LPCTSTR lpszFullPath, LPTSTR lpszFileName, int nSize);
LPCTSTR	TakeTitle(LPCTSTR lpszFullPath, LPTSTR lpszTitle, int nSize);
LPCTSTR	TakeExtension(LPCTSTR lpszFullPath, LPTSTR lpszExt, int nSize);

BOOL	ReadFileString(HANDLE hFile, LPSTR lpszBuffer, int nMax);

// String Manipulations

BOOL	MakeCapitalized(LPTSTR lpszNew, int nLen, LPCTSTR lpszOld);