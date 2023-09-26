// ModEmp.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "사원관리프로그램MFC.h"
#include "사원관리프로그램MFCDlg.h"
#include "afxdialogex.h"
#include "ModEmp.h"
#include "AddEmp.h"
#include "DelEmp.h"
#include "UpdateEmp.h"
#include "EmpEventHandler.h"
#include "EmpManager.h"


// ModEmp 대화 상자

IMPLEMENT_DYNAMIC(ModEmp, CDialogEx)

ModEmp::ModEmp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MODEMP, pParent)
{

}

ModEmp::~ModEmp()
{
}

void ModEmp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ModEmp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDEMP, &ModEmp::OnBnClickedButtonAddemp)
	ON_BN_CLICKED(IDC_BUTTON_DELEMP, &ModEmp::OnBnClickedButtonDelemp)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEEMP, &ModEmp::OnBnClickedButtonUpdateemp)
END_MESSAGE_MAP()


// ModEmp 메시지 처리기



void ModEmp::OnBnClickedButtonAddemp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AddEmp* add = new AddEmp();
	add->Create(IDD_DIALOG_ADDEMP);
	add->ShowWindow(SW_SHOW);
}


void ModEmp::OnBnClickedButtonDelemp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DelEmp* del = new DelEmp();
	del->Create(IDD_DIALOG_DELEMP);
	del->ShowWindow(SW_SHOW);
}


void ModEmp::OnBnClickedButtonUpdateemp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateEmp* update = new UpdateEmp();
	update->Create(IDD_DIALOG_UPDATEEMP);
	update->ShowWindow(SW_SHOW);
}
