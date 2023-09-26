#pragma once
#include "afxdialogex.h"
#include "EmpEventHandler.h"

// DelEmp 대화 상자

class DelEmp : public CDialogEx,
	public AddEmployeeEventHandler
{
	DECLARE_DYNAMIC(DelEmp)

public:
	DelEmp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DelEmp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELEMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl dellist;

	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonDelempok();
	afx_msg void OnBnClickedButtonDelempcancel();

	virtual BOOL OnInitDialog();
	
	void AddedEmployee(Employee* emp);


};
