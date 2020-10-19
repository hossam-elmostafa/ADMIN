////StaticCategory.h
#ifndef _STATICCATEGORY_H
#define _STATICCATEGORY_H

class CStaticCategory:public CCommonCategory
{
public:
	CStaticCategory(CCategory *pCategory):CCommonCategory(pCategory)
	{
		m_pCategory = pCategory;
	};


	UINT LoadingDischargePort();
	UINT ShippingLine();

	UINT DefineDeliveryTerms();
	UINT PaymentTermTemplate();
	UINT DefineCountries();
	UINT DefineExpSTS();
	UINT DefineStoringCondition();
	UINT DefineManufact();
	UINT DefineSkills();
	UINT DefineTrades();
	UINT DefineAdjustVoucher();
	UINT DefineClassGroups();
	UINT DefineDepartment();
	UINT DefineItemGroup();
	UINT DefineItemSubGroup();
	UINT DefineTransActionDelReason();
	UINT DefineActivities();
	UINT DefineCreditTerms();
	UINT DefineTerms();
	UINT ItemHistory(BSTR strItem,BSTR bstrComesFrom);
	UINT DefinePacking();
	UINT DefineAdditionalExpenses();
	UINT DefineCostCenters();
	UINT DefineCompanies();

	UINT DocumentClass(CString strCriteria);
	UINT CompanyProfile(CString strCriteria);
	UINT BidEvaluationCritria(CString strCriteria);
	UINT BidEvaluationTemplate(CString strCriteria);
	UINT TermsTemplate(CString strCriteria);
	UINT ApprovalSignatureTemplate(CString strCriteria);
	UINT Locations(CString strCriteria);

	UINT DelayPenalty();
	UINT ShippingMethod();

//Control Methods
protected:
	void ConfirmToolBarButtonClicked(CString strForm_Tag,short Seleted_Tab,CString strButton_Name,CString strFullRecord,short nLoop,short Toolbar_ID);
	void ConfirmToolBarDelete(CString strForm_Tag,short Seleted_Tab,CString strButton_Name,CString strFullRecord,short nLoop);
	void MainSubReposition(CString strFormTag, long Main_Position, short Seleted_Tab,CString strSubFormTag);

};
#endif