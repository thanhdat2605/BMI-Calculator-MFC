
// BMIApplicationMFCDlg.h : header file
//

#pragma once
#include "afxwin.h"


// MainDlg dialog
class MainDlg : public CDialogEx
{
// Construction
public:
	MainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BMIAPPLICATIONMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CEdit edt_height_;
	CEdit edt_weight_;
	CEdit edt_bmi_;
	CEdit edt_category_;
	CComboBox combo_height_;
	CComboBox combo_weight_;
public:
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnCal();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	void WinHelp(DWORD dwData, UINT nCmd);
	CStatic m_staticFontTitle;
	CStatic m_staticFontContent;
	CFont m_fontTitle;
	CFont m_fontContent;

};

