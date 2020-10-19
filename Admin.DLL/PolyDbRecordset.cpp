// PolyDbRecordset.cpp: implementation of the CPolyDbRecordset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "PolyDbRecordset.h"
#include "FIMSobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


extern CFIMSobj *pFIMSobj;


CPolyDbRecordset::CPolyDbRecordset(UINT unConnectionDB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	USES_CONVERSION;
	CLSID dbCLSID;
	HRESULT hr = CLSIDFromProgID( T2OLE("PolyDB.DB"),  &dbCLSID); 
	hr = m_pPolyDb.CreateInstance(dbCLSID);
	if(hr!=0)
		pFIMSobj->ErrorExit(hr,"Display engine");

	
	switch(unConnectionDB)
	{
	case PDBRS_LOAD_FROM_APP_DB:
		{
			m_bLoadFromData = true;
			break;
		}
	case PDBRS_LOAD_FROM_SYS_DB:
		{
			m_bLoadFromData = false;
			break;
		}
	}
	long lRes = pFIMSobj->DBInit(m_pPolyDb,m_bLoadFromData);
}

CPolyDbRecordset::~CPolyDbRecordset()
{
}

long CPolyDbRecordset::Open(int,CString strSql)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bEOF=true;
	long lRetVal;
	CString strToWrite;
	extern CFile sqlReportFile;
	if(m_pPolyDb==NULL)
	{
		USES_CONVERSION;
		CLSID dbCLSID;
		HRESULT hr = CLSIDFromProgID( T2OLE("PolyDB.DB"),  &dbCLSID); 
		hr = m_pPolyDb.CreateInstance(dbCLSID);
		if(hr!=0)
			ErrorExit(hr,"Display engine");
		long lRes = pFIMSobj->DBInit(m_pPolyDb,NULL);
	}
	try
	{		
		if(m_bLoadFromData)
			lRetVal = m_pPolyDb->DBBuildSet(SILENTPOLYDBRECORDSET,(LPCSTR)strSql,1,"",NULL);
		else
			lRetVal = m_pPolyDb->DBBuildSet(SILENTPOLYDBRECORDSETFSDB,(LPCSTR)strSql,1,"",NULL);
		if(lRetVal>0 && lRetVal<0x70000000)
		{			
			MoveLast();
			MoveFirst();
			m_bOpenFlag = TRUE;
		}
	}
	catch(...)
	{
	}
	CString strSqlStatement;
	strSqlStatement.Format ("RecordSet Open : %s",strSql);
	return lRetVal;
}
long CPolyDbRecordset::Open(CString strSql)
{
	return Open(SILENTPOLYDBRECORDSET,strSql);
}
bool CPolyDbRecordset::IsEOF()
{
	if(m_bEOF)
		return m_bEOF;
	VARIANT_BOOL bRes;
	bRes = m_pPolyDb->RecSetEOF();
	return (bRes==FALSE)?false:true;
}

void CPolyDbRecordset::Close()
{
	short sRetVal;
	try
	{
		sRetVal = m_pPolyDb->RecClose();
	}
	catch(...)
	{
	}
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,CString &strRetValue)
{
	strRetValue= (char*)m_pPolyDb->RecFieldGet(strFieldName.GetBuffer(0));
	strRetValue.TrimRight ();
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,int &nRetValue)
{
	CString strRetValue ;
	strRetValue = (char*)m_pPolyDb->RecFieldGet(strFieldName.GetBuffer(0));
	if(strRetValue=="")
		nRetValue=0;
	if(strRetValue.Find ((char)'//')>0)
	{
		strRetValue = ConvertDate(strRetValue);
		COleDateTime OleDateTimeRetValue;
		OleDateTimeRetValue=pFIMSobj->FromStringToDate(strRetValue);
		nRetValue=(int)OleDateTimeRetValue.m_dt;
	}
	else
		nRetValue=atoi(strRetValue);
}

int CPolyDbRecordset::GetFieldValue(CString strFieldName)
{
	CString strRetValue ;
	strRetValue = (char*)m_pPolyDb->RecFieldGet(strFieldName.GetBuffer(0));
	if(strRetValue=="-3021")// CHECK WITH AHMED
		strRetValue="";
	int nRetValue=0;
	if(strRetValue!="")
		nRetValue=atoi(strRetValue);
	return nRetValue;
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,long &lRetValue)
{
	CString strRetValue ;
	strRetValue = (char*)m_pPolyDb->RecFieldGet(strFieldName.GetBuffer(0));
	if(strRetValue=="")
		lRetValue=0;
	lRetValue=atol(strRetValue);
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,double &dRetValue)
{
	CString strRetValue ;
	strRetValue = (char*)m_pPolyDb->RecFieldGet(strFieldName.GetBuffer (0));
	if(strRetValue=="")
		dRetValue=0;
	dRetValue=atof(strRetValue);
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,COleDateTime &OleDateTimeRetValue)
{
	CString strRetValue ;
	strRetValue = (char*)m_pPolyDb->RecFieldGet(strFieldName.GetBuffer (0));
	// United state
	strRetValue = ConvertDate(strRetValue);
	if(strRetValue != "")
		OleDateTimeRetValue=pFIMSobj->FromStringToDate(strRetValue);
}
CString CPolyDbRecordset::ConvertDate(CString strDate)
{
	LCID lcid;
	char chCountryId[5];
	lcid =  GetSystemDefaultLangID();
	BOOL bRetVal = GetLocaleInfo(lcid,LOCALE_ICOUNTRY,chCountryId,5);
	long CountryId = atol(chCountryId);
	if(CountryId != 1)
		return strDate;
		
	CString strTemp = strDate;
	CString strFirstPart=strtok(strDate.GetBuffer (0),"/");
	CString strSecondPart=strtok(NULL,"/");
	CString strThirdPart=strtok(NULL,"/");
	CString strRetVal;
	strRetVal.Format ("%s/%s/%s",strSecondPart,strFirstPart,strThirdPart);
	return strRetVal;
}

void CPolyDbRecordset::Move(long lRows)
{
	short sRetVal;
	sRetVal = m_pPolyDb->RecMoveAbsolute(-1,lRows);
}

void CPolyDbRecordset::MoveFirst()
{
	short sRetval;
	sRetval = m_pPolyDb->RecMoveFirst();
	m_bEOF=false;
}

void CPolyDbRecordset::MoveNext()
{
	short sRetval;
	sRetval = m_pPolyDb->RecMoveNext();
}

void CPolyDbRecordset::MoveLast()
{
	short sRetval;
	sRetval = m_pPolyDb->RecMoveLast();
}

void CPolyDbRecordset::AddNew()
{
	short sRetval;
	sRetval = m_pPolyDb->RecAddNew();
}

void CPolyDbRecordset::Edit()
{
	short sRetval;
	sRetval = m_pPolyDb->RecEdit();
}

void CPolyDbRecordset::Update()
{
	short sRetval;
	sRetval = m_pPolyDb->RecUpdate();
}

void CPolyDbRecordset::SetFieldValue(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	short sRetval;
	sRetval = m_pPolyDb->RecFieldPut(lpszName, lpszValue);
}

bool CPolyDbRecordset::Find(long lFindType, LPCTSTR lpszFilter)
{
	short shRetVal=-1;
	switch(lFindType)
	{
	case AFX_DAO_NEXT:
		ASSERT(FALSE);
		break;
	case AFX_DAO_PREV:
		ASSERT(FALSE);
		break;
	case AFX_DAO_FIRST:
		shRetVal = m_pPolyDb->RecFindFirst(lpszFilter);
		break;
	case AFX_DAO_LAST:
		shRetVal = m_pPolyDb->RecFindLast(lpszFilter);
		break;
	}
	return shRetVal==1;
}

long CPolyDbRecordset::GetAbsolutePosition()
{
	long lRetVal;
	lRetVal = m_pPolyDb->RecGetAbsolute();
	return lRetVal;
}

void CPolyDbRecordset::SetAbsolutePosition(long lNewPos)
{
	short sRetVal;
	sRetVal = m_pPolyDb->RecMoveAbsolute(-1, lNewPos);
}

long CPolyDbRecordset::GetRecordCount()
{
	MoveLast();
	long lAbsolutePosition= GetAbsolutePosition() + 1;
	MoveFirst();
	return lAbsolutePosition;
}


short CPolyDbRecordset::Delete()
{
	short sRetVal;
	sRetVal = m_pPolyDb->RecDelete();
	return sRetVal;
}


