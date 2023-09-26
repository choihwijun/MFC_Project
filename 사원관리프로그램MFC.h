
// 사원관리프로그램MFC.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// C사원관리프로그램MFCApp:
// 이 클래스의 구현에 대해서는 사원관리프로그램MFC.cpp을(를) 참조하세요.
//

class C사원관리프로그램MFCApp : public CWinApp
{
public:
	C사원관리프로그램MFCApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern C사원관리프로그램MFCApp theApp;
