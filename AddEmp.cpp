// AddEmp.cpp: 구현 파일
//

#include "pch.h"
#include "사원관리프로그램MFC.h"
#include "afxdialogex.h"
#include "AddEmp.h"
#include "EmpManager.h"

// AddEmp 대화 상자

IMPLEMENT_DYNAMIC(AddEmp, CDialogEx)

AddEmp::AddEmp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADDEMP, pParent)
	, num(_T(""))
	, name(_T(""))
	, dept(_T(""))
	, posit(_T(""))
	, phone(_T(""))
	, ext(_T(""))
	, address(_T(""))
{
	eeh = 0;
}

AddEmp::~AddEmp()
{
}

void AddEmp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EMPNUM, num);
	DDX_Text(pDX, IDC_EDIT_EMPNAME, name);
	DDX_Text(pDX, IDC_EDIT_EMPDEPT, dept);
	DDX_Text(pDX, IDC_EDIT_EMPPOSIT, posit);
	DDX_Text(pDX, IDC_EDIT_EMPPHONE, phone);
	DDX_Text(pDX, IDC_EDIT_EMPEXT, ext);
	DDX_Text(pDX, IDC_EDIT_EMPADDRESS, address);
	DDX_Control(pDX, IDC_STATIC_EMPPIC, pic_con);
	DDX_Control(pDX, IDC_STATIC_EMPPIC, pic_con);
}


BEGIN_MESSAGE_MAP(AddEmp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDPIC, &AddEmp::OnBnClickedButtonAddpic)
	ON_BN_CLICKED(IDC_BUTTON_ADDEMPOK, &AddEmp::OnBnClickedButtonAddempok)
END_MESSAGE_MAP()

void AddEmp::AddEndedEventHandler(EndDialogEventHandler* eeh)
{
	this->eeh = eeh;
}

// AddEmp 메시지 처리기


void AddEmp::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (eeh)
	{
		eeh->EndedDialog();//나 죽음을 통보한다.
	}
	CDialogEx::OnCancel();
}

void AddEmp::OnBnClickedButtonAddpic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* fod = new CFileDialog(TRUE, 0);
	int re = fod->DoModal();
	if (re != IDOK)
	{
		return;
	}
	image = fod->GetPathName();
	CImage cimg;
	cimg.Load(image);

	CDC* cdc = pic_con.GetDC();
	RECT rt;
	pic_con.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
}


void AddEmp::OnBnClickedButtonAddempok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();//컨트롤=>변수
	if (image == TEXT("")) {
		image = TEXT("noimage.bmp");
	}
	EmpManager& em = EmpManager::GetEmpManager();
	if (em.AddEmployee(num, name, posit, dept, image, phone, ext, address, starttime, endtime) == FALSE)
	{
		MessageBox(TEXT("추가 실패"));
	}
	MessageBox(TEXT("추가 성공"));
	InitControls();
}

void AddEmp::InitControls()
{
	image = TEXT("");
	num = TEXT("");
	name = TEXT("");
	dept = TEXT("");
	posit = TEXT("");
	phone = TEXT("");
	ext = TEXT("");
	address = TEXT("");
	UpdateData(FALSE);//변수=>컨트롤
	EmpManager& em = EmpManager::GetEmpManager();
}


BOOL AddEmp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	EmpManager& em = EmpManager::GetEmpManager();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

