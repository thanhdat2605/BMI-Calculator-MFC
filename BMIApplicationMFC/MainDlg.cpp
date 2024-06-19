
/************************************************************************
File Name   : MainDlg.cpp
Function    : BMI���v�Z���A�̏d�̕��ނ��s������Ǝ��s
System Name : �C���^�[��
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
ABSTRACT : �_�C�A���O����������
FUNCTION : �\��z�M�ݒ�_�C�A���O�����_�C�A���O�̏������������s��
NOTE     :
RETURN   : TRUE   �ŏ��̃R���g���[���Ƀt�H�[�J�X���Z�b�g
FALSE  �����I�ɓ���̃R���g���[���Ƀt�H�[�J�X���Z�b�g
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

	//�̏d�̒P�ʂ̕�����
	combo_weight_.AddString(_T("Kilograms"));
	combo_weight_.AddString(_T("Pounds"));
	//�g���̒P�ʂ̕�����
	combo_height_.AddString(_T("Meters"));
	combo_height_.AddString(_T("Feet"));
	//�g���̒P�ʂƑ̏d�̒P�ʂ̃f�t�H���g�l��ݒ肷��
	combo_weight_.SetCurSel(0);
	combo_height_.SetCurSel(0);
	//�^�C�g���̃t�H���g�ƃt�H���g�T�C�Y��ݒ肷��
	m_fontTitle.CreatePointFont(200, _T("�l�r �S�V�b�N"));
	m_staticFontTitle.SetFont(&m_fontTitle);

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ�����ATRUE��Ԃ�
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
FUNCTION : ���̓t�B�[���h�ƌ��ʕ\���t�B�[���h����ɂ��A�̏d�Ɛg���̒P�ʂ��f�t�H���g�i���[�g���ƃL���O�����j�ɐݒ肷��
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
FUNCTION : BMI�l��̏d�J�e�S���[�ɕ��ނ���
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
FUNCTION : ���̓f�[�^�Ƒ���P�ʂ�������������A���̌�BMI���v�Z���đ̏d�J�e�S���[�𕪗ނ��郁�C�������֐�
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
FUNCTION : BMI�ɂ��̏d���ޏ���\�����邽�߂ɁA�V�����w���v�_�C�A���O���J��
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
FUNCTION : ���O�ɐݒ肳�ꂽ�{�^���ɑΉ�����L�[�{�[�h����̓��͏����������A�@�\�ɃV���[�g�J�b�g�L�[�����蓖�Ă�
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
FUNCTION : �f�t�H���g�̃w���v����̃A�N�V�����ŏ㏑�����A�{�^���̃w���v�Ɠ����@�\�����s���܂�
NOTE     :
CREATE   : 2024/06/07 V1.00.00 DatNguyen
UPDATE   :
COMMENT  :
******************************************************************************/
void MainDlg::WinHelp(DWORD dwData, UINT nCmd)
{

}

