
// 사원관리프로그램MFCDlg.h: 헤더 파일
//

#pragma once
#include "AddEmp.h"
#include "UpdateEmp.h"
#include "DelEmp.h"
#include "ModEmp.h"
#include "Employee.h"
#include "EmpEventHandler.h"
#include "EmpManager.h"
#include "EndDialogEventHandler.h"
#include "InputInfo.h"
#include "VerEmp.h"
#include "CheckCalendar.h"
#include <afxwin.h>


#define MAX_ROWS 100
#define MAX_COLUMNS 100

// C사원관리프로그램MFCDlg 대화 상자
class C사원관리프로그램MFCDlg : public CDialogEx,
	public AddEmployeeEventHandler,
	public RemoveEmployeeEventHandler,
	public UpdateEmployeeEventHandler,
	public EndDialogEventHandler
{
	AddEmp* aep;
// 생성입니다.
public:
	C사원관리프로그램MFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonConemp();
	CListCtrl emplist;
	afx_msg void OnLvnItemchangedListEmp(NMHDR* pNMHDR, LRESULT* pResult);

	virtual void AddedEmployee(Employee* emp);
	virtual void UpdatedEmployee(Employee* emp);
	virtual void RemovedEmployee(CString num);

	virtual void EndedDialog();

	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonCheckemp();
	CStatic timertext;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonEnd();
	afx_msg void OnBnClickedButtonCheckcal();
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);//커스텀드로우 사용

	COLORREF m_CellColors[MAX_ROWS][MAX_COLUMNS];
	int m_nSelectedRow;
	int m_nSelectedColumn;	
	afx_msg void OnBnClickedButtonInitattend();

	COLORREF m_bgColor;
	void LoadSettings(); // 설정 불러오기 함수
	void SaveSettings(); // 설정 저장하기 함수

};
