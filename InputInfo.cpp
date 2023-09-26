// InputInfo.cpp: 구현 파일
//

#include "pch.h"
#include "사원관리프로그램MFC.h"
#include "afxdialogex.h"
#include "InputInfo.h"
#include<iostream>
#include <string>
#include "ModEmp.h"

using namespace std;


// InputInfo 대화 상자

IMPLEMENT_DYNAMIC(InputInfo, CDialogEx)

InputInfo::InputInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUTINFO, pParent)
{

}

InputInfo::~InputInfo()
{
}

void InputInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INFO, &InputInfo::OnBnClickedButtonInfo)
END_MESSAGE_MAP()


// InputInfo 메시지 처리기

void InputInfo::OnBnClickedButtonInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	wchar_t username[256], password[256];
	GetDlgItemText(IDC_EDIT_ID, username, 256);
	GetDlgItemText(IDC_EDIT_PW, password, 256);
	if (wcscmp(username,TEXT("admin")) == 0 && wcscmp(password, TEXT("password")) == 0) {
		MessageBox(TEXT("로그인 성공"), TEXT("알림"), MB_OK);

		ModEmp* mod = new ModEmp();
		//vd->DoModal();//모달 대화상자
		mod->Create(IDD_DIALOG_MODEMP);
		mod->ShowWindow(SW_SHOW);
	}
	else 
		MessageBox( TEXT("로그인 실패. 올바른 사용자 이름과 비밀번호를 입력하세요."), TEXT("경고"), MB_OK | MB_ICONWARNING);
}
