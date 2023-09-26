#pragma once
#include "afxdialogex.h"
#include "EmpEventHandler.h"

// VerEmp 대화 상자

class VerEmp : public CDialogEx,
	public AddEmployeeEventHandler
{
	DECLARE_DYNAMIC(VerEmp)

public:
	VerEmp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~VerEmp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHECKEMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox cbox_no;
	CStatic pbox_img;
	CString name;
	CString dept;
	CString posit;
	CString phone;
	CString ext;
	CString address;

	afx_msg void OnCbnSelchangeComboEmpnum();
	virtual void AddedEmployee(Employee* employee);
	virtual BOOL OnInitDialog();
};
