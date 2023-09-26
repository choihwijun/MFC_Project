// VerEmp.cpp: 구현 파일
//

#include "pch.h"
#include "사원관리프로그램MFC.h"
#include "afxdialogex.h"
#include "VerEmp.h"
#include "EmpManager.h"

// VerEmp 대화 상자

IMPLEMENT_DYNAMIC(VerEmp, CDialogEx)

VerEmp::VerEmp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHECKEMP, pParent)
	, name(_T(""))
	, dept(_T(""))
	, posit(_T(""))
	, phone(_T(""))
	, ext(_T(""))
	, address(_T(""))
{

}

VerEmp::~VerEmp()
{
}

void VerEmp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EMPNUM, cbox_no);
	DDX_Text(pDX, IDC_EDIT_EMPNAME_CHECK, name);
	DDX_Text(pDX, IDC_EDIT_EMPDEPT_CHECK, dept);
	DDX_Text(pDX, IDC_EDIT_EMPPOSIT_CHECK, posit);
	DDX_Text(pDX, IDC_EDIT_EMPPHONE_CHECK, phone);
	DDX_Text(pDX, IDC_EDIT_EMPEXT_CHECK, ext);
	DDX_Text(pDX, IDC_EDIT_EMPADDRESS_CHECK, address);
	DDX_Control(pDX, IDC_STATIC_EMPPIC_CHECK, pbox_img);
}


BEGIN_MESSAGE_MAP(VerEmp, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_EMPNUM, &VerEmp::OnCbnSelchangeComboEmpnum)
END_MESSAGE_MAP()


// VerEmp 메시지 처리기


void VerEmp::OnCbnSelchangeComboEmpnum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = cbox_no.GetCurSel();
	if (index == -1)
	{

		name = TEXT("");
		dept = TEXT("");
		posit = TEXT("");
		phone = TEXT("");
		ext = TEXT("");
		address = TEXT("");
	}
	else
	{
		wchar_t nbuf[256];
		cbox_no.GetLBText(index, nbuf);
		//int numInt = _ttoi(nos);
		//CString num = nos;
		//num.Format(TEXT("%d"), numInt);
		EmpManager& em = EmpManager::GetEmpManager();//------이상함
		Employee* employee = em.GetEmp(nbuf);
		if (employee == 0)
		{
			throw "오류";
		}
		name = employee->Getname();
		dept = employee->Getdept();
		posit = employee->Getposit();
		phone = employee->Getphone();
		ext = employee->Getext();
		address = employee->Getaddress();
		CImage cimg;
		cimg.Load(employee->Getimage());
		CDC* cdc = pbox_img.GetDC();
		RECT rt;
		pbox_img.GetClientRect(&rt);
		cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
	}
	UpdateData(0);

}


BOOL VerEmp::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	EmpManager& em = EmpManager::GetEmpManager();
	em.AddAEEventHandler(this);
	NList* nlist = new NList();
	em.GetEmpNumList(nlist);
	NIter seek = nlist->begin();
	NIter end = nlist->end();
	wchar_t buf[256];
	for (; seek != end; ++seek)
	{
		wsprintf(buf, TEXT("%s"), (*seek));
		cbox_no.AddString(buf);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void VerEmp::AddedEmployee(Employee* employee)
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%s"), employee->Getnum());
	cbox_no.AddString(buf);
}
