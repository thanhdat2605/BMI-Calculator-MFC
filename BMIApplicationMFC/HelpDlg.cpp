// HelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BMIApplicationMFC.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// HelpDlg dialog

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HelpDlg::IDD, pParent)
{

}

HelpDlg::~HelpDlg()
{
}


void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_TITLE, m_Title);
	DDX_Control(pDX, IDC_txtIdx1, m_txtIdx1);
	DDX_Control(pDX, IDC_txtIdx2, m_txtIdx2);
	DDX_Control(pDX, IDC_txtIdx3, m_txtIdx3);
}

BOOL HelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_fontTitle.CreatePointFont(200, _T("ÇlÇr ÉSÉVÉbÉN"));
	m_Title.SetFont(&m_fontTitle);
	m_fontContent.CreatePointFont(140, _T("ÇlÇr ÉSÉVÉbÉN"));
	m_txtIdx1.SetFont(&m_fontContent);
	m_txtIdx2.SetFont(&m_fontContent);
	m_txtIdx3.SetFont(&m_fontContent);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)

END_MESSAGE_MAP()


// HelpDlg message handlers

