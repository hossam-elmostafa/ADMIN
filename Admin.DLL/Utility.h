#ifndef _CHANDOVER_H
#define _CHANDOVER_H

class CHandOver:public CCommonCategory
{
public:
	void DefineUserDefinedChecks();
	CHandOver(CCategory *pCategory):CCommonCategory(pCategory)
	{
		m_pCategory = pCategory;
	};
	~CHandOver();

	void SubjectType();
	void OpenedHandOver();
	void ClosedHandOver();
};
#endif
