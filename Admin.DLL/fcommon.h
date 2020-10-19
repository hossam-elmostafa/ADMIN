// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IMRArray wrapper class

class IMRArray : public COleDispatchDriver
{
public:
	IMRArray();		// Calls COleDispatchDriver default constructor
	~IMRArray();

	IMRArray(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMRArray(const IMRArray& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	void SetCount(long nNewValue);
	void SetArrayElement(long lItemIndex, LPCTSTR strItemCode, float fCount, long bSucceeded);
	void GetArrayElement(long lItemWanted, BSTR* strItemCode, float* fCount, long* pbSucceeded);
};
/////////////////////////////////////////////////////////////////////////////
// IAlternItem wrapper class

class IAlternItem : public COleDispatchDriver
{
public:
	IAlternItem();
	~IAlternItem();
	IAlternItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAlternItem(const IAlternItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	void SetCount(long nNewValue);
	void SetArrayElement(long lIndex, LPCTSTR strItemCode, LPCTSTR strDescription, LPCTSTR strUnit, float fLastUnitPrice, float fAveragePrice, float fTotalQty);
	void GetArrayElement(long lIndex, BSTR* strItemCode, BSTR* pstrDescription, BSTR* pstrUnit, float* pfLastUnitPrice, float* pfAveragePrice, float* pfTotalQty);
};
