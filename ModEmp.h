#pragma once
#include "afxdialogex.h"
#include "EndDialogEventHandler.h"
#include "EmpEventHandler.h"
#include "AddEmp.h"
#include "UpdateEmp.h"
#include "DelEmp.h"
#include "Employee.h"


// ModEmp 대화 상자

class ModEmp : public CDialogEx
{
	DECLARE_DYNAMIC(ModEmp)

public:
	ModEmp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ModEmp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MODEMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddemp();
	afx_msg void OnBnClickedButtonDelemp();
	afx_msg void OnBnClickedButtonUpdateemp();


};
