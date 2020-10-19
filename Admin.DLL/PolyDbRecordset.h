//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYDBRECORDSET_H__D876C062_5917_11D7_AD5F_0080C895CEFC__INCLUDED_)
#define AFX_POLYDBRECORDSET_H__D876C062_5917_11D7_AD5F_0080C895CEFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CPolyDbRecordset  
{
public:
 	CPolyDbRecordset(UINT unConnectionDB=PDBRS_LOAD_FROM_APP_DB);
	~CPolyDbRecordset();
	long	Open(int,CString strSql);
	long	Open(CString strSql);

	bool	IsEOF();
	void	Close();
	void	GetFieldValue(CString strFieldName,CString &strRetValue);
	void	GetFieldValue(CString strFieldName,int &nRetValue);
	int		GetFieldValue(CString strFieldName);
	void	GetFieldValue(CString strFieldName,long &lRetValue);
	void	GetFieldValue(CString strFieldName,double &dRetValue);
	void	GetFieldValue(CString strFieldName,COleDateTime &OleDateTimeRetValue);
	//void	GetFieldValue(CString strFieldName,DATE &Date);
	CString ConvertDate(CString strDate);
	void	Move(long lRows);
	void	MoveFirst();
	void	MoveNext();
	void	MoveLast();
	void	AddNew();
	void	Edit();
	void	Update();
	void	SetFieldValue(LPCTSTR lpszName, LPCTSTR lpszValue);
	bool	Find(long lFindType, LPCTSTR lpszFilter);
	long	GetAbsolutePosition();
	void	SetAbsolutePosition(long lNewPos);
	long	GetRecordCount();
	short	Delete();
	_DBPtr		GetPolyDb(){return m_pPolyDb;};
	

protected:
	_DB*		m_pPolyDb;
	bool	m_bEOF,m_bLoadFromData;
	bool	m_bOpenFlag;					
};

#endif // !defined(AFX_POLYDBRECORDSET_H__D876C062_5917_11D7_AD5F_0080C895CEFC__INCLUDED_)
