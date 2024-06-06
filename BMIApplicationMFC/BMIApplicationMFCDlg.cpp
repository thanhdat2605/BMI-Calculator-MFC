
// BMIApplicationMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BMIApplicationMFC.h"
#include "BMIApplicationMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBMIApplicationMFCDlg dialog



CBMIApplicationMFCDlg::CBMIApplicationMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBMIApplicationMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBMIApplicationMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_HEIGHT, edt_height_);
	DDX_Control(pDX, IDC_EDT_WEIGHT, edt_weight_);
	DDX_Control(pDX, IDC_COMBOX_HEIGHT, combo_height_);
	DDX_Control(pDX, IDC_COMBOX_WEIGHT, combo_weight_);
	DDX_Control(pDX, IDC_EDT_RESULT, edt_bmi_);
	DDX_Control(pDX, IDC_EDT_CATEGORY, edt_category_);
	DDX_Control(pDX, IDC_STT_TITLE, m_staticText);
}

BEGIN_MESSAGE_MAP(CBMIApplicationMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RESET, &CBMIApplicationMFCDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_CAL, &CBMIApplicationMFCDlg::OnBnClickedBtnCal)
END_MESSAGE_MAP()


// CBMIApplicationMFCDlg message handlers

BOOL CBMIApplicationMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//CWnd* lblTitle = GetDlgItem(IDC_STT_TITLE);
	//CFont font;
	//font.CreateFont(
	//	12,                        // nHeight
	//	0,                         // nWidth
	//	0,                         // nEscapement
	//	0,                         // nOrientation
	//	FW_NORMAL,                 // nWeight
	//	FALSE,                     // bItalic
	//	FALSE,                     // bUnderline
	//	0,                         // cStrikeOut
	//	ANSI_CHARSET,              // nCharSet
	//	OUT_DEFAULT_PRECIS,        // nOutPrecision
	//	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	//	DEFAULT_QUALITY,           // nQuality
	//	DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
	//	_T("Microsoft Sans Serif"));                 // lpszFacename

	//GetDlgItem(IDC_STT_TITLE)->SetFont(&font);


	combo_weight_.AddString(_T("Kilograms"));
	combo_weight_.AddString(_T("Pounds"));
	combo_height_.AddString(_T("Meters"));
	combo_height_.AddString(_T("Feet"));
	combo_weight_.SetCurSel(0);
	combo_height_.SetCurSel(0);

	CDialog::OnInitDialog();

	m_font.CreatePointFont(120, _T("Arial"));



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBMIApplicationMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBMIApplicationMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBMIApplicationMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBMIApplicationMFCDlg::OnBnClickedBtnReset()
{
	edt_height_.SetWindowText(_T(""));  // 
	edt_weight_.SetWindowText(_T(""));
	edt_bmi_.SetWindowText(_T(""));
	edt_category_.SetWindowText(_T(""));
	combo_height_.SetCurSel(0);
	combo_weight_.SetCurSel(0);
}

CString GetBMICategory(double bmi)
{
	if (bmi < 18.5)
		return _T("You are underweight.");
	else if (bmi >= 18.5 && bmi < 24.9)
		return _T("You have a normal weight.");
	else if (bmi >= 25 && bmi < 29.9)
		return _T("You are overweight.");
	else
		return _T("You are obese.");
}

void CBMIApplicationMFCDlg::OnBnClickedBtnCal()
{
	UpdateData(TRUE);

	CString str_valHeight = _T("");
	CString str_valWeight = _T("");

	edt_height_.GetWindowText(str_valHeight);
	edt_weight_.GetWindowText(str_valWeight);

	float height = 0;
	float weight = 0;

	try
	{
		height = _tstof(str_valHeight);
		weight = _tstof(str_valWeight);
		if (height <= 0 || weight <= 0)
		{
			MessageBox(_T("Invalid height or weight. Please enter again!"), _T("Error"), MB_ICONWARNING);
			edt_bmi_.SetWindowText(_T(""));
			edt_category_.SetWindowText(_T(""));
			if (height <= 0)
			{
				edt_height_.SetWindowText(_T(""));
			}
			if (weight <= 0)
			{
				edt_weight_.SetWindowText(_T(""));
			}
			return;
		}
	}
	catch (const char* e)
	{
		MessageBox(_T("Invalid height or weight. Please enter again!"), _T("Error"), MB_ICONWARNING);
		return;
	}

	int idxHeight = combo_height_.GetCurSel();
	int idxWeight = combo_weight_.GetCurSel();

	if (idxHeight == 1)
	{
		height *= 0.3048;
	}

	if (idxWeight == 1)
	{
		weight *= 0.453592;
	}

	float bmi = weight / (height * height);

	CString strBMI;
	strBMI.Format(_T("%.2f"), bmi);
	CString strCategory = GetBMICategory(bmi);

	edt_bmi_.SetWindowText(strBMI);
	edt_category_.SetWindowTextW(strCategory);

	UpdateData(FALSE);

}


