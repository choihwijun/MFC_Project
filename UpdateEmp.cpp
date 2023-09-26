// UpdateEmp.cpp: 구현 파일
//

#include "pch.h"
#include "사원관리프로그램MFC.h"
#include "afxdialogex.h"
#include "UpdateEmp.h"
#include "Employee.h"
#include "사원관리프로그램MFCDlg.h"

// UpdateEmp 대화 상자

IMPLEMENT_DYNAMIC(UpdateEmp, CDialogEx)

UpdateEmp::UpdateEmp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATEEMP, pParent)
	, dept(_T(""))
	, posit(_T(""))
	, phone(_T(""))
	, ext(_T(""))
	, address(_T(""))
{

}

UpdateEmp::~UpdateEmp()
{
}

void UpdateEmp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UPDATEEMP, updatelist);
	DDX_Control(pDX, IDC_STATIC_UPDATEIMG, pic_img);
	DDX_Text(pDX, IDC_EDIT_EMPDEPT_UP, dept);
	DDX_Text(pDX, IDC_EDIT_EMPPOSIT_UP, posit);
	DDX_Text(pDX, IDC_EDIT_EMPPHONE_UP, phone);
	DDX_Text(pDX, IDC_EDIT_EMPEXT_UP, ext);
	DDX_Text(pDX, IDC_EDIT_EMPADDRESS_UP, address);
}


BEGIN_MESSAGE_MAP(UpdateEmp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEPIC, &UpdateEmp::OnBnClickedButtonUpdatepic)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEEMPOK, &UpdateEmp::OnBnClickedButtonUpdateempok)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEEMPCANCEL, &UpdateEmp::OnBnClickedButtonUpdateempcancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_UPDATEEMP, &UpdateEmp::OnLvnItemchangedListUpdateemp)
END_MESSAGE_MAP()


// UpdateEmp 메시지 처리기
void UpdateEmp::AddedEmployee(Employee* emp)
{
	CString num = emp->Getnum();
	CString name = emp->Getname();
	wchar_t nbuf[256] = TEXT("");
	wsprintf(nbuf, TEXT("%s"), emp);
	int i = updatelist.GetItemCount();
	updatelist.InsertItem(i, nbuf);
	updatelist.SetItemText(i, 1, name);
}

void UpdateEmp::RemovedEmployee(CString num)
{
	LVITEM li = { 0 };
	wchar_t buf[256] = TEXT("");
	int cnt = updatelist.GetItemCount();
	for (int i = 0; i < cnt; i++)
	{
		li.iItem = i;
		li.iSubItem = 0;
		li.mask = LVIF_TEXT;
		li.pszText = buf;
		li.cchTextMax = 256;
		updatelist.GetItem(&li);
		if ( num == buf )
		{
			updatelist.DeleteItem(i);
			return;
		}
	}
}

void UpdateEmp::OnBnClickedButtonUpdatepic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog* fod = new CFileDialog(TRUE, 0);
	int re = fod->DoModal();
	if (re != IDOK) return;

	image = fod->GetPathName();
	CImage cimg;
	cimg.Load(image);

	CDC* cdc = pic_img.GetDC();
	RECT rt;
	pic_img.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);

}


void UpdateEmp::OnBnClickedButtonUpdateempok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	POSITION pos = updatelist.GetFirstSelectedItemPosition();
	int index = updatelist.GetNextSelectedItem(pos);
	if (index == -1) {
		return;
	}
	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t nbuf[256] = TEXT("");
	li.mask = LVIF_TEXT;
	li.pszText = nbuf;
	li.cchTextMax = 256;
	updatelist.GetItem(&li);
	EmpManager& em = EmpManager::GetEmpManager();
	if (em.UpdateEmp(nbuf, image, dept, posit, phone, ext, address)) {
		MessageBox(TEXT("수정 성공"));
	}
}


void UpdateEmp::OnBnClickedButtonUpdateempcancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = updatelist.GetFirstSelectedItemPosition();
	int index = updatelist.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}
	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t nbuf[256] = TEXT("");
	li.mask = LVIF_TEXT;
	li.pszText = nbuf;
	li.cchTextMax = 256;
	updatelist.GetItem(&li);

	EmpManager& em = EmpManager::GetEmpManager();
	Employee* emp = em.GetEmp(nbuf);

	dept = emp->Getdept();
	posit = emp->Getposit();
	phone = emp->Getphone();
	ext = emp->Getext();
	address = emp->Getaddress();
	CImage cimg;
	image = emp->Getimage();
	cimg.Load(image);
	CDC* cdc = pic_img.GetDC();
	RECT rt;
	pic_img.GetClientRect(&rt);
	cimg.StretchBlt(*cdc, 0, 0, rt.right, rt.bottom, SRCCOPY);
	UpdateData(0);
}


BOOL UpdateEmp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	updatelist.InsertColumn(0, TEXT("사원 번호"), 0, 140);
	updatelist.InsertColumn(1, TEXT("이름"), 0, 50);


	EmpManager& em = EmpManager::GetEmpManager();

	em.AddAEEventHandler(this);
	em.AddREEventHandler(this);

	NList nlist;
	em.GetEmpNumList(&nlist);
	NIter seek = nlist.begin();
	NIter end = nlist.end();

	wchar_t nbuf[256] = TEXT("");
	Employee* emp = 0;

	for (int i = 0; seek != end; ++seek, i++) {
		wsprintf(nbuf, TEXT("%s"), (*seek));
		updatelist.InsertItem(i, nbuf);
		emp = em.GetEmp(*seek);
		updatelist.SetItemText(i, 1, emp->Getname());
	}
	//em.Load();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void UpdateEmp::OnLvnItemchangedListUpdateemp(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	OnBnClickedButtonUpdateempcancel();
}
