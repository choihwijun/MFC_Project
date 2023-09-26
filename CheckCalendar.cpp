// CheckCalendar.cpp: 구현 파일
//

#include "pch.h"
#include "사원관리프로그램MFC.h"
#include "afxdialogex.h"
#include "CheckCalendar.h"


// CheckCalendar 대화 상자

IMPLEMENT_DYNAMIC(CheckCalendar, CDialogEx)

CheckCalendar::CheckCalendar(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CALENDAR, pParent)
	, Monthdate(COleDateTime::GetCurrentTime())
	, Datedate(COleDateTime::GetCurrentTime())
{

}

CheckCalendar::~CheckCalendar()
{
}

void CheckCalendar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, Monthdate);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, Mccal);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, Datedate);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, ddcal);
	DDX_Control(pDX, IDC_EDIT_CALENDAR, contents);
}


BEGIN_MESSAGE_MAP(CheckCalendar, CDialogEx)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &CheckCalendar::OnMcnSelchangeMonthcalendar1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CheckCalendar::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CheckCalendar::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CheckCalendar 메시지 처리기


void CheckCalendar::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cent;
	*pResult = 0;
	UpdateData();
	ddcal.SetTime(Monthdate);
	wchar_t dbuf[256] = TEXT("");
	wsprintf(dbuf, TEXT("%d-%d-%d"), Monthdate.GetYear(), Monthdate.GetMonth(), Monthdate.GetDay());
	wchar_t querydbuf[256] = TEXT("");
	wsprintf(querydbuf, TEXT("select Schedule from DateSchedule where Dateid = '%s'"), dbuf);
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=LocalSQL;uid=scott;PWD=tiger"));
	if (re == FALSE) {
		return;
	}
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, querydbuf);
	if (rs.IsEOF()) {
		contents.SetWindowText(TEXT(""));
		return;
	}
	rs.GetFieldValue((short)0, cent);
	contents.SetWindowText(cent);
}


void CheckCalendar::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cent;
	*pResult = 0;
	UpdateData();
	Mccal.SetCurSel(Datedate);
	wchar_t dbuf[256] = TEXT("");
	wsprintf(dbuf, TEXT("%d-%d-%d"), Datedate.GetYear(), Datedate.GetMonth(), Datedate.GetDay());
	wchar_t querydbuf[256] = TEXT("");
	wsprintf(querydbuf, TEXT("select Schedule from DateSchedule where Dateid = '%s'"), dbuf);
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=LocalSQL;uid=scott;PWD=tiger"));
	if (re == FALSE) {
		return;
	}
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, querydbuf);
	if (rs.IsEOF()) {
		contents.SetWindowText(TEXT(""));
		return;
	}
	rs.GetFieldValue((short)0, cent);
	contents.SetWindowText(cent);
}


void CheckCalendar::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDatabase db;
	CString cent, result;
	contents.GetWindowText(result);
	wchar_t dbuf[256] = TEXT("");
	wsprintf(dbuf, TEXT("%d-%d-%d"), Monthdate.GetYear(), Monthdate.GetMonth(), Monthdate.GetDay());
	wchar_t querydbuf[256] = TEXT("");
	wsprintf(querydbuf, TEXT("select Schedule from DateSchedule where Dateid = '%s'"), dbuf);
	bool re = db.OpenEx(TEXT("DSN=LocalSQL;uid=scott;PWD=tiger"));
	if (re == FALSE) {
		return;
	}
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, querydbuf);
	if (rs.IsEOF()) {
		rs.Close();
		wchar_t insertbuf[256];
		wsprintf(insertbuf, TEXT("insert into Dateschedule values ('%s', '%s')"), dbuf, result);
		db.ExecuteSQL(insertbuf);
		MessageBox(TEXT("저장 성공"));
	}
	else {
		rs.Close();
		wchar_t updatebuf[256];
		wsprintf(updatebuf, TEXT("update DateSchedule set Schedule = '%s' where dateid = '%s'"), result, dbuf);
		db.ExecuteSQL(updatebuf);
		MessageBox(TEXT("업데이트 성공"));
	}
}


BOOL CheckCalendar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CDatabase db;
	CString cent;
	wchar_t dbuf[256] = TEXT("");
	wsprintf(dbuf, TEXT("%d-%d-%d"), Datedate.GetYear(), Datedate.GetMonth(), Datedate.GetDay());
	wchar_t querydbuf[256] = TEXT("");
	wsprintf(querydbuf, TEXT("select Schedule from DateSchedule where Dateid = '%s'"), dbuf);
	bool re = db.OpenEx(TEXT("DSN=LocalSQL;uid=scott;PWD=tiger"));
	if (re == FALSE) {
		return FALSE;
	}
	CRecordset rs(&db);
	rs.Open(CRecordset::forwardOnly, querydbuf);
	if (rs.IsEOF()) {
		contents.SetWindowText(TEXT(""));
		return FALSE;
	}
	rs.GetFieldValue((short)0, cent);
	contents.SetWindowText(cent);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

