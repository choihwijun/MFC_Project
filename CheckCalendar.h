#pragma once
#include "afxdialogex.h"
#include <afxdb.h>


// CheckCalendar 대화 상자

class CheckCalendar : public CDialogEx
{
	DECLARE_DYNAMIC(CheckCalendar)

public:
	CheckCalendar(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CheckCalendar();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CALENDAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime Monthdate;
	CMonthCalCtrl Mccal;
	COleDateTime Datedate;
	CDateTimeCtrl ddcal;
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	CEdit contents;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSave();
};
