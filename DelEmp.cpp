// DelEmp.cpp: 구현 파일
//

#include "pch.h"
#include "사원관리프로그램MFC.h"
#include "afxdialogex.h"
#include "DelEmp.h"
#include "EmpManager.h"
#include "EmpEventHandler.h"


// DelEmp 대화 상자

IMPLEMENT_DYNAMIC(DelEmp, CDialogEx)

DelEmp::DelEmp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELEMP, pParent)
{

}

DelEmp::~DelEmp()
{
}

void DelEmp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, dellist);
}


BEGIN_MESSAGE_MAP(DelEmp, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &DelEmp::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_DEPEMPOK, &DelEmp::OnBnClickedButtonDelempok)
	ON_BN_CLICKED(IDC_BUTTON_DELEMPCANCEL, &DelEmp::OnBnClickedButtonDelempcancel)
END_MESSAGE_MAP()


// DelEmp 메시지 처리기

void DelEmp::AddedEmployee(Employee* emp)
{
	CString num = emp->Getnum();
	CString name = emp->Getname();
	wchar_t nbuf[256] = TEXT("");
	wsprintf(nbuf, TEXT("%s"), emp);
	int i = dellist.GetItemCount();
	dellist.InsertItem(i, nbuf);
	dellist.SetItemText(i, 1, name);
}

void DelEmp::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnBnClickedButtonDelempcancel();
	*pResult = 0;
}


void DelEmp::OnBnClickedButtonDelempok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	EmpManager& em = EmpManager::GetEmpManager();	
	POSITION pos = dellist.GetFirstSelectedItemPosition();
	int index = dellist.GetNextSelectedItem(pos);
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
	dellist.GetItem(&li);
	if (em.RemoveEmp(nbuf)) {
		dellist.DeleteItem(index);
		MessageBox(TEXT("삭제 성공"));
	}
}


BOOL DelEmp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	dellist.InsertColumn(0, TEXT("사원번호"), 0, 100);
	dellist.InsertColumn(1, TEXT("이름"), 0, 70);
	EmpManager& em = EmpManager::GetEmpManager();
	em.AddAEEventHandler(this);

	NList nlist;
	em.GetEmpNumList(&nlist);
	NIter seek = nlist.begin();
	NIter end = nlist.end();

	wchar_t nbuf[256] = TEXT("");
	Employee* employee = 0;

	for (int i = 0; seek != end; ++seek, i++)
	{
		wsprintf(nbuf, TEXT("%s"), (*seek));
		dellist.InsertItem(i, nbuf);
		employee = em.GetEmp(*seek);
		dellist.SetItemText(i, 1, employee->Getname());

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DelEmp::OnBnClickedButtonDelempcancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = dellist.GetFirstSelectedItemPosition();
	int index = dellist.GetNextSelectedItem(pos);
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
	dellist.GetItem(&li);

	EmpManager& em = EmpManager::GetEmpManager();	
	Employee* emp = em.GetEmp(nbuf);	
	// UpdateDate(0);
}
