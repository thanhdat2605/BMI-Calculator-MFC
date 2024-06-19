#pragma once

class HelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDlg)

public:
	HelpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~HelpDlg();

	enum { IDD = ID_HelpDlg };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Title;
	CStatic m_txtIdx1;
	CStatic m_txtIdx2;
	CStatic m_txtIdx3;

	CFont m_fontTitle;
	CFont m_fontContent;
	afx_msg void OnStnClickedSttTitle();
};
