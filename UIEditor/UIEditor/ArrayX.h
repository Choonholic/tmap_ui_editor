// ArrayX.h
// December 26, 2008

#pragma once

#ifndef SORTFUNCX_DEFINED
#define SORTFUNCX_DEFINED
typedef int (CALLBACK *SORTFUNCX)(const void *pParam1, const void *pParam2);
#endif	// SORTFUNCX_DEFINED

template <class T>
void QuickSortInternal(T *pT, int nLowerBound, int nUpperBound, SORTFUNCX SortFunc)
{
	int			nLow;
	int			nHigh;
	int			nLeft;
	int			nRight;
	T			Index;
	CUIntArray	arrStack;

	arrStack.Add(nUpperBound);
	arrStack.Add(nLowerBound);

	while (arrStack.GetSize())
	{
		nLow	= arrStack.GetAt(arrStack.GetUpperBound());

		arrStack.RemoveAt(arrStack.GetUpperBound());

		nHigh	= arrStack.GetAt(arrStack.GetUpperBound());

		arrStack.RemoveAt(arrStack.GetUpperBound());

		nLeft	= nHigh;
		nRight	= nLow;

		Index	= pT[static_cast<int>((nLow + nHigh) / 2)];

		do
		{
			while (SortFunc(&pT[nRight], &Index) < 0)
			{
				nRight++;
			}

			while (SortFunc(&pT[nLeft], &Index) > 0)
			{
				nLeft--;
			}

			if (nLeft >= nRight)
			{
				if (nLeft != nRight)
				{
					T	Temp;

					Temp		= pT[nLeft];
					pT[nLeft]	= pT[nRight];
					pT[nRight]	= Temp;
				}

				nLeft--;
				nRight++;
			}
		} while (nRight <= nLeft);

		if (nRight < nHigh)
		{
			arrStack.Add(nHigh);
			arrStack.Add(nRight);
		}

		if (nLow < nLeft)
		{
			arrStack.Add(nLeft);
			arrStack.Add(nLow);
		}
	}
}

template <class T>
BOOL QuickSort(T *pT, int iSize, SORTFUNCX SortFunc)
{
	BOOL	bResult	= TRUE;

	if (iSize > 1)
	{
		try
		{
			int nLeft	= 0;
			int	nRight	= iSize - 1;

			QuickSortInternal(pT, nLeft, nRight, SortFunc);
		}
		catch (...)
		{
			::SetLastError(ERROR_INVALID_PARAMETER);

			bResult	= FALSE;
		}
	}
	else
	{
		::SetLastError(ERROR_INVALID_PARAMETER);

		bResult	= FALSE;
	}

	return bResult;
}

template <class T, class PT>
class CArrayX : public CArray<T, PT>
{
public:
	void QuickSort(SORTFUNCX SortFunc);
};

template <class T, class PT>
void CArrayX<T, PT>::QuickSort(SORTFUNCX SortFunc)
{
	if (GetSize() > 1)
	{
		::QuickSort(GetData(), GetSize(), SortFunc);
	}
}
