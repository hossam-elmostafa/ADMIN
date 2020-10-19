#ifndef ADMNAPP_H
#define	ADMNAPP_H
class CADMNObj;
class CADMNApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void	SetADMNObj(CADMNObj	*pADMNobj)
	{
		m_pADMNobj=pADMNobj;
	};
	CADMNObj	*GetADMNObj()
	{
		return m_pADMNobj;
	};

	long GetAppCode();
	CString GetAppODBC();

protected:
	CADMNObj	*m_pADMNobj;
};

#endif	//ADMNAPP_H
