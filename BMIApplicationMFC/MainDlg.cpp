
/************************************************************************
File Name   : MainDlg.cpp
Function    : BMIを計算し、体重の分類を行う操作と実行
System Name : インターン
Create      : 2024.06.07 V1.00.00 N.Dat
Update      :
Comment     :
************************************************************************/
#include "stdafx.h"
#include "Main.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "HelpDlg.h"
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


MainDlg::MainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDE_HEIGHT, edt_height_);
	DDX_Control(pDX, IDE_WEIGHT, edt_weight_);
	DDX_Control(pDX, IDC_HEIGHT_UNITS, combo_height_);
	DDX_Control(pDX, IDC_WEIGHT_UNITS, combo_weight_);
	DDX_Control(pDX, IDE_RESULT, edt_bmi_);
	DDX_Control(pDX, IDE_CATEGORY, edt_category_);

	DDX_Control(pDX, IDC_STT_TITLE, m_staticFontTitle);
}

BEGIN_MESSAGE_MAP(MainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_RESET, &MainDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDB_CAL, &MainDlg::OnBnClickedBtnCal)
	ON_BN_CLICKED(IDB_HELP, &MainDlg::OnBnClickedBtnHelp)
END_MESSAGE_MAP()


/******************************************************************************
MODULE   : MainDlg::OnInitDialog()
ABSTRACT : ダイアログ初期化処理
FUNCTION : 予約配信設定ダイアログ処理ダイアログの初期化処理を行う
NOTE     :
RETURN   : TRUE   最初のコントロールにフォーカスをセット
FALSE  明示的に特定のコントロールにフォーカスをセット
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
BOOL MainDlg::OnInitDialog()
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

	//体重の単位の文字列
	combo_weight_.AddString(_T("Kilograms"));
	combo_weight_.AddString(_T("Pounds"));
	//身長の単位の文字列
	combo_height_.AddString(_T("Meters"));
	combo_height_.AddString(_T("Feet"));
	//身長の単位と体重の単位のデフォルト値を設定する
	combo_weight_.SetCurSel(0);
	combo_height_.SetCurSel(0);
	//タイトルのフォントとフォントサイズを設定する
	m_fontTitle.CreatePointFont(200, _T("ＭＳ ゴシック"));
	m_staticFontTitle.SetFont(&m_fontTitle);

	return TRUE;  // コントロールにフォーカスを設定しない限り、TRUEを返す
}

void MainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void MainDlg::OnPaint()
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
HCURSOR MainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/******************************************************************************
MODULE   : MainDlg::OnBnClickedBtnReset()
FUNCTION : 入力フィールドと結果表示フィールドを空にし、体重と身長の単位をデフォルト（メートルとキログラム）に設定する
NOTE     :
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
void MainDlg::OnBnClickedBtnReset()
{
	edt_height_.SetWindowText(_T(""));  
	edt_weight_.SetWindowText(_T(""));
	edt_bmi_.SetWindowText(_T(""));
	edt_category_.SetWindowText(_T(""));
	combo_height_.SetCurSel(0);
	combo_weight_.SetCurSel(0);
	GetDlgItem(IDE_HEIGHT)->SetFocus();
}
/******************************************************************************
MODULE   : MainDlg::GetBMICategory()
FUNCTION : BMI値を体重カテゴリーに分類する
NOTE     :
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
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
/******************************************************************************
MODULE   : MainDlg::OnBnClickedBtnCal()
FUNCTION : 入力データと測定単位から情報を処理し、その後BMIを計算して体重カテゴリーを分類するメイン処理関数
NOTE     : 
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
void MainDlg::OnBnClickedBtnCal()
{
	UpdateData(TRUE);

	CString str_valHeight = _T("");
	CString str_valWeight = _T("");
	float height = 0;
	float weight = 0;

	edt_height_.GetWindowText(str_valHeight);
	edt_weight_.GetWindowText(str_valWeight);

	try
	{
		height = _tstof(str_valHeight);
		weight = _tstof(str_valWeight);
		if (height < str_valHeight.GetLength())
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
	edt_category_.SetWindowText(strCategory);

	UpdateData(FALSE);

}
/******************************************************************************
MODULE   : MainDlg::OnBnClickedBtnHelp()
FUNCTION : BMIによる体重分類情報を表示するために、新しいヘルプダイアログを開く
NOTE     : 
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
void MainDlg::OnBnClickedBtnHelp()
{
	HelpDlg help_dlg;
	help_dlg.DoModal();
}
/******************************************************************************
MODULE   : MainDlg::PreTranslateMessage()
FUNCTION : 事前に設定されたボタンに対応するキーボードからの入力情報を処理し、機能にショートカットキーを割り当てる
NOTE     :
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
BOOL MainDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedBtnCal();
			return TRUE;
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			OnBnClickedBtnReset();
			return TRUE;
		}
		else if (pMsg->wParam == VK_F1)
		{
			OnBnClickedBtnHelp();
			return TRUE;
		}
		else if ((pMsg->wParam >= '1' && pMsg->wParam <= '2') &&
			(GetFocus()->IsKindOf(RUNTIME_CLASS(CComboBox))))
		{
			int index = pMsg->wParam - '1';
			CComboBox* pComboBox = (CComboBox*)GetFocus();
			if (index < pComboBox->GetCount())
			{
				pComboBox->SetCurSel(index);
				return TRUE;
			}
		}
	}		

	return CDialogEx::PreTranslateMessage(pMsg);
}
/******************************************************************************
MODULE   : MainDlg::WinHelp()
FUNCTION : デフォルトのヘルプを空のアクションで上書きし、ボタンのヘルプと同じ機能を実行します
NOTE     :
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
void MainDlg::WinHelp(DWORD dwData, UINT nCmd)
{

}

