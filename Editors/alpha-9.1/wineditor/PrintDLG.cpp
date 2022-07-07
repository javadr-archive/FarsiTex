// PrintDLG.cpp : implementation file
//

#include "stdafx.h"
#include "Ftexed.h"
#include "PrintDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintDLG dialog


CPrintDLG::CPrintDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintDLG)
	m_ToPage = 0;
	m_FromPage = 0;
	m_EditToFile = _T("");
	//}}AFX_DATA_INIT
	PrinterType = 0;
}


void CPrintDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintDLG)
	DDX_Text(pDX, IDC_EDITTOPAGE, m_ToPage);
	DDV_MinMaxUInt(pDX, m_ToPage, 0, 5000);
	DDX_Text(pDX, IDC_EDITFROMPAGE, m_FromPage);
	DDV_MinMaxUInt(pDX, m_FromPage, 0, 5000);
	DDX_Text(pDX, IDC_EDITTOFILE, m_EditToFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintDLG, CDialog)
	//{{AFX_MSG_MAP(CPrintDLG)
	ON_BN_CLICKED(IDC_RADIOHPLJ, OnRadiohplj)
	ON_BN_CLICKED(IDC_RADIOHPLJH, OnRadiohpljh)
	ON_BN_CLICKED(IDC_RADIOLQH, OnRadiolqh)
	ON_BN_CLICKED(IDC_RADIOLQL, OnRadiolql)
	ON_BN_CLICKED(IDC_RADIOLQM, OnRadiolqm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintDLG message handlers

void CPrintDLG::OnRadiohplj() 
{
	// TODO: Add your control notification handler code here
	
	PrinterType = 0;
}

void CPrintDLG::OnRadiohpljh() 
{
	// TODO: Add your control notification handler code here
	PrinterType = 1;
}

void CPrintDLG::OnRadiolqh() 
{
	// TODO: Add your control notification handler code here
	PrinterType = 2;
}

void CPrintDLG::OnRadiolql() 
{
	// TODO: Add your control notification handler code here
	PrinterType = 3;
}

void CPrintDLG::OnRadiolqm() 
{
	// TODO: Add your control notification handler code here
	PrinterType = 4;
}
