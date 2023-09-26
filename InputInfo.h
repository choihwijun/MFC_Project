#pragma once
#include "afxdialogex.h"


// InputInfo 대화 상자

class InputInfo : public CDialogEx
{
	DECLARE_DYNAMIC(InputInfo)

public:
	InputInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InputInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUTINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public :
	afx_msg void OnBnClickedButtonInfo();
};
