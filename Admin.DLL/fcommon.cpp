#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMRArray::IMRArray()
{
	CreateDispatch("MRArray.MRArray.1");
}
IMRArray::~IMRArray()
{
	ReleaseDispatch();
}


long IMRArray::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IMRArray::SetCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IMRArray::SetArrayElement(long lItemIndex, LPCTSTR strItemCode, float fCount, long bSucceeded)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_R4 VTS_I4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lItemIndex, strItemCode, fCount, bSucceeded);
}

void IMRArray::GetArrayElement(long lItemWanted, BSTR* strItemCode, float* fCount, long* pbSucceeded)
{
	static BYTE parms[] =
		VTS_I4 VTS_PBSTR VTS_PR4 VTS_PI4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lItemWanted, strItemCode, fCount, pbSucceeded);
}


IAlternItem::IAlternItem()
{
	CreateDispatch("AlternItem.AlternItem.1");
}
IAlternItem::~IAlternItem()
{
	ReleaseDispatch();
}


long IAlternItem::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAlternItem::SetCount(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAlternItem::SetArrayElement(long lIndex, LPCTSTR strItemCode, LPCTSTR strDescription, LPCTSTR strUnit, float fLastUnitPrice, float fAveragePrice, float fTotalQty)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_R4 VTS_R4 VTS_R4;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lIndex, strItemCode, strDescription, strUnit, fLastUnitPrice, fAveragePrice, fTotalQty);
}

void IAlternItem::GetArrayElement(long lIndex, BSTR* strItemCode, BSTR* pstrDescription, BSTR* pstrUnit, float* pfLastUnitPrice, float* pfAveragePrice, float* pfTotalQty)
{
	static BYTE parms[] =
		VTS_I4 VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PR4 VTS_PR4 VTS_PR4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lIndex, strItemCode, pstrDescription, pstrUnit, pfLastUnitPrice, pfAveragePrice, pfTotalQty);
}
