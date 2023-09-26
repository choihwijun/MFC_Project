#pragma once
#include "afxdialogex.h"


// AddEmp 대화 상자
#include "EndDialogEventHandler.h"
class AddEmp : public CDialogEx
{
	EndDialogEventHandler* eeh;
	DECLARE_DYNAMIC(AddEmp)

public:
	AddEmp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AddEmp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADDEMP };
#endif

public:
	void AddEndedEventHandler(EndDialogEventHandler* eeh);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();

private:
	void InitControls();

public : 
	virtual BOOL OnInitDialog();
	CString image;
	CString num;
	CString name;
	CString dept;
	CString posit;
	CString phone;
	CString ext;
	CString address;

	CStatic pic_con;

	CString starttime;
	CString endtime ;

	afx_msg void OnBnClickedButtonAddpic();
	afx_msg void OnBnClickedButtonAddempok();
	
};
