#include "stdafx.h"
#include "HandOver.h"
#include "ADMNapp.h"
#include "ADMN.h"
#include "ADMNobj.h"

CHandOver::~CHandOver()
{
}

void CHandOver::SubjectType()
{
	MovePolydbForm();
	m_nCurrentCard=CMN_EMAILS;
	m_pADMNPolyDb->ShowAutomaticEmails(m_pCategory->GetParentHWnd());
}

void CHandOver::OpenedHandOver()
{
	MovePolydbForm();
	m_nCurrentCard=CMN_SEGMENTCODE;
	m_pADMNPolyDb->ShowSegmentsSystem(m_pCategory->GetParentHWnd());
}

void CHandOver::ClosedHandOver()
{
	MovePolydbForm();
	m_nCurrentCard=CMN_USERDEFCRITRIA;
	m_pADMNPolyDb->ShowUserDefinedChecks();
}


