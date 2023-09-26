// 데이터 합친것//
// 사원관리프로그램MFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "사원관리프로그램MFC.h"
#include "사원관리프로그램MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum MY_W_MSG
{
	MWM_ENDED_REG = WM_APP + 1
};

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{

public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C사원관리프로그램MFCDlg 대화 상자



C사원관리프로그램MFCDlg::C사원관리프로그램MFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINDLG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(m_CellColors, 0, sizeof(m_CellColors));
	m_nSelectedRow = -1;
	m_nSelectedColumn = -1;	
}

void C사원관리프로그램MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMP, emplist);
	DDX_Control(pDX, IDC_STATIC_TIME, timertext);
}

 BEGIN_MESSAGE_MAP(C사원관리프로그램MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONEMP, &C사원관리프로그램MFCDlg::OnBnClickedButtonConemp)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EMP, &C사원관리프로그램MFCDlg::OnLvnItemchangedListEmp)
	ON_BN_CLICKED(IDC_BUTTON_CHECKEMP, &C사원관리프로그램MFCDlg::OnBnClickedButtonCheckemp)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &C사원관리프로그램MFCDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_END, &C사원관리프로그램MFCDlg::OnBnClickedButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_CHECKCAL, &C사원관리프로그램MFCDlg::OnBnClickedButtonCheckcal)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_EMP, OnCustomDraw)
	 ON_BN_CLICKED(IDC_BUTTON_INITATTEND, &C사원관리프로그램MFCDlg::OnBnClickedButtonInitattend)
 END_MESSAGE_MAP()


// C사원관리프로그램MFCDlg 메시지 처리기

BOOL C사원관리프로그램MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	aep = 0;
	//& em = EmpManager::GetEmpManager();
	//em.AddAEEventHandler(this);//도서 추가하면 나한테 알려줘//
	// +================================================== 진혁아 사랑해
	//LPWSTR texts[5] = { TEXT("사원 번호"),TEXT("사원 이름"),TEXT("직급"),TEXT("출근 시간"), TEXT("퇴근 시간") };
	//int widths[5] = { 50,100,70,200,200 };
	//LV_COLUMN col;
	//col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	//col.fmt = LVCFMT_CENTER;
	//for (int i = 0; i < 5; i++)
	//{
	//	col.pszText = texts[i];
	//	col.iSubItem = i;
	//	col.cx = widths[i];
	//	emplist.InsertColumn(i, &col);
	//}
		//}
	emplist.InsertColumn(0, TEXT("사원 번호"), 0, 60);
	emplist.InsertColumn(1, TEXT("사원 이름"), 0, 60);
	emplist.InsertColumn(2, TEXT("직급"), 0, 35);
	emplist.InsertColumn(3, TEXT("출근 시간"), 0, 152);
	emplist.InsertColumn(4, TEXT("퇴근 시간"), 0, 152);


	EmpManager& em = EmpManager::GetEmpManager();//-----------------------------------------------진혁이 귀여워
	em.AddAEEventHandler(this);//도서 추가하면 나한테 알려줘//
	em.AddREEventHandler(this);
	em.AddUEEventHandler(this);

	//em.AddEmployee(TEXT("01-0001"), TEXT("현진혁"), TEXT("부장"), TEXT("SW"), TEXT("현진혁.jpg"), TEXT("010-6359-3208"), TEXT("011"), TEXT("경기도 성남시 행복동 24-6"));  // DONT TOUCH!!!!!!!!
	//em.AddEmployee(TEXT("01-0002"), TEXT("오준택"), TEXT("대리"), TEXT("SW"), TEXT("오준택.jpg"), TEXT("010-6321-9810"), TEXT("012"), TEXT("경기도 오산시 기쁨동 기쁨아파트 901-212"));
	//em.AddEmployee(TEXT("02-0001"), TEXT("최종휘"), TEXT("과장"), TEXT("CS"), TEXT("최종휘.jpg"), TEXT("010-2346-9834"), TEXT("113"), TEXT("경기도 김포시 슬픔동 8 109-203"));
	//em.AddEmployee(TEXT("02-0002"), TEXT("최원민"), TEXT("사원"), TEXT("CS"), TEXT("최원민.jpg"), TEXT("010-3467-3411"), TEXT("114"), TEXT("충청남도 천안시 안서동 781-2"));

	//===================================================
	em.Load();

	emplist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void C사원관리프로그램MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void C사원관리프로그램MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR C사원관리프로그램MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C사원관리프로그램MFCDlg::OnBnClickedButtonConemp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InputInfo* info = new InputInfo();
	//vd->DoModal();//모달 대화상자
	info->Create(IDD_DIALOG_INPUTINFO);
	info->ShowWindow(SW_SHOW);
}


void C사원관리프로그램MFCDlg::OnLvnItemchangedListEmp(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


BOOL C사원관리프로그램MFCDlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	EmpManager& em = EmpManager::GetEmpManager();
	em.Save();
	return CDialogEx::DestroyWindow();	
}

void C사원관리프로그램MFCDlg::AddedEmployee(Employee* emp) {
	int index = emplist.GetItemCount();
	emplist.InsertItem(index, emp->Getnum());
	emplist.SetItemText(index, 1, emp->Getname());
	emplist.SetItemText(index, 2, emp->Getposit());	
	emplist.SetItemText(index, 3, emp->GetStartTime());
	emplist.SetItemText(index, 4, emp->GetEndTime());
}

void C사원관리프로그램MFCDlg::UpdatedEmployee(Employee* emp) {
	CString num = emp->Getnum();
	LVITEM li = { 0 };
	wchar_t buf[256] = TEXT("");
	int cnt = emplist.GetItemCount();
	for (int i = 0; i < cnt; i++)
	{
		li.iItem = i;
		li.iSubItem = 0;
		li.mask = LVIF_TEXT;
		li.pszText = buf;
		li.cchTextMax = 256;
		emplist.GetItem(&li);
		if (num == buf)
		{
			emplist.SetItemText(i, 1, emp->Getname());
			emplist.SetItemText(i, 2, emp->Getposit());
			return;
		}
	}
}
void C사원관리프로그램MFCDlg::RemovedEmployee(CString num) {
	LVITEM li = { 0 };
	wchar_t buf[256] = TEXT("");
	int cnt = emplist.GetItemCount();
	for (int i = 0; i < cnt; i++)
	{
		li.iItem = i;
		li.iSubItem = 0;
		li.mask = LVIF_TEXT;
		li.pszText = buf;
		li.cchTextMax = 256;
		emplist.GetItem(&li);
		if (num == buf)
		{
			emplist.DeleteItem(i);
			return;
		}
	}
}

void C사원관리프로그램MFCDlg::EndedDialog()
{
	PostMessage(MWM_ENDED_REG, 0, 0);
}

void C사원관리프로그램MFCDlg::OnBnClickedButtonCheckemp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	VerEmp* ve = new VerEmp();

	ve->Create(IDD_DIALOG_CHECKEMP);
	ve->ShowWindow(SW_SHOW);
}


int C사원관리프로그램MFCDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(1, 1000, NULL);
	return 0;
}


void C사원관리프로그램MFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString currentDate;
	CTime data = CTime::GetCurrentTime();
	currentDate.Format(_T("%d년 %d월 %d일 %d시 %d분 %d초"), data.GetYear(), data.GetMonth(), data.GetDay(), data.GetHour(), data.GetMinute(), data.GetSecond());
	timertext.SetWindowText(currentDate);
	CDialogEx::OnTimer(nIDEvent);
}

void C사원관리프로그램MFCDlg::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		int index = static_cast<int>(pLVCD->nmcd.dwItemSpec);


		// 여기에서 특정 조건을 확인합니다. 예를 들어 m_bButtonClicked가 true일 때만 색상 변경
		if (index == m_nSelectedRow && pLVCD->iSubItem == m_nSelectedColumn) {
			pLVCD->clrTextBk = m_CellColors[index][pLVCD->iSubItem]; // 배경색을 빨간색으로 변경
			*pResult = CDRF_NEWFONT; // 변경된 배경색을 적용
		}
	}
}



void C사원관리프로그램MFCDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = emplist.GetFirstSelectedItemPosition();
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_EMP);	

	int index = pListCtrl->GetNextSelectedItem(pos);
	if (index == -1) {
		return;
	}

	else {
		m_nSelectedRow = index;
		m_nSelectedColumn = 0;

		LVITEM li = { 0 };
		li.iItem = index;
		li.iSubItem = 0;
		wchar_t nbuf[256] = TEXT("");
		li.mask = LVIF_TEXT;
		li.pszText = nbuf;
		li.cchTextMax = 256;
		emplist.GetItem(&li);

		pListCtrl->SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		pListCtrl->SetItemState(index, 0, LVIS_SELECTED);
		pListCtrl->SetItemState(index, 0, LVIS_FOCUSED);
		pListCtrl->RedrawItems(index, index);

		m_CellColors[m_nSelectedRow][m_nSelectedColumn] = RGB(198, 255, 179);


		CString currentDate;
		CTime data = CTime::GetCurrentTime();

		currentDate.Format(_T("%d월 %d일 %d시 %d분 %d초"), data.GetMonth(), data.GetDay(), data.GetHour(), data.GetMinute(), data.GetSecond());

		EmpManager& em = EmpManager::GetEmpManager();
		Employee* emp = em.GetEmp(nbuf);


		emp->SetStartTime(currentDate);
		emplist.SetItemText(index, 3, currentDate);
	}
}


void C사원관리프로그램MFCDlg::OnBnClickedButtonEnd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = emplist.GetFirstSelectedItemPosition();
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_EMP);

	int index = pListCtrl->GetNextSelectedItem(pos);
	if (index == -1) {
		return;
	}
	else {
		m_nSelectedRow = index;
		m_nSelectedColumn = 0;

		LVITEM li = { 0 };
		li.iItem = index;
		li.iSubItem = 0;
		wchar_t nbuf[256] = TEXT("");
		li.mask = LVIF_TEXT;
		li.pszText = nbuf;
		li.cchTextMax = 256;
		emplist.GetItem(&li);

		pListCtrl->SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		pListCtrl->SetItemState(index, 0, LVIS_SELECTED);
		pListCtrl->SetItemState(index, 0, LVIS_FOCUSED);
		pListCtrl->RedrawItems(index, index);

		m_CellColors[m_nSelectedRow][m_nSelectedColumn] = RGB(255,179, 179);


		CString currentDate;
		CTime data = CTime::GetCurrentTime();

		currentDate.Format(_T("%d월 %d일 %d시 %d분 %d초"), data.GetMonth(), data.GetDay(), data.GetHour(), data.GetMinute(), data.GetSecond());

		EmpManager& em = EmpManager::GetEmpManager();
		Employee* emp = em.GetEmp(nbuf);


		emp->SetEndTime(currentDate);
		emplist.SetItemText(index, 4, currentDate);
	}
}


void C사원관리프로그램MFCDlg::OnBnClickedButtonCheckcal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CheckCalendar* cc = new CheckCalendar();
	cc->Create(IDD_DIALOG_CALENDAR);
	cc->ShowWindow(SW_SHOW);
}

void C사원관리프로그램MFCDlg::OnBnClickedButtonInitattend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = emplist.GetFirstSelectedItemPosition();
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_EMP);

	int index = pListCtrl->GetNextSelectedItem(pos);
	if (index == -1) {
		return;
	}
	else {
		m_nSelectedRow = index;
		m_nSelectedColumn = 0;

		LVITEM li = { 0 };
		li.iItem = index;
		li.iSubItem = 0;
		wchar_t nbuf[256] = TEXT("");
		li.mask = LVIF_TEXT;
		li.pszText = nbuf;
		li.cchTextMax = 256;
		emplist.GetItem(&li);

		pListCtrl->SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		pListCtrl->SetItemState(index, 0, LVIS_SELECTED);
		pListCtrl->SetItemState(index, 0, LVIS_FOCUSED);
		pListCtrl->RedrawItems(index, index);

		m_CellColors[m_nSelectedRow][m_nSelectedColumn] = RGB(255, 255, 255);

		EmpManager& em = EmpManager::GetEmpManager();
		Employee* emp = em.GetEmp(nbuf);

		emp->SetStartTime(TEXT(""));
		emp->SetEndTime(TEXT(""));

		emplist.SetItemText(index, 3, TEXT(""));
		emplist.SetItemText(index, 4, TEXT(""));


	}
}

void C사원관리프로그램MFCDlg::LoadSettings()
{
	CFile file;
	if (file.Open(_T("settings.txt"), CFile::modeRead))
	{
		file.Read(&m_bgColor, sizeof(COLORREF));
		file.Close();
		// 배경 색상을 불러와 m_bgColor 변수에 저장
	}
}

void C사원관리프로그램MFCDlg::SaveSettings()
{
	CFile file;
	if (file.Open(_T("settings.txt"), CFile::modeCreate | CFile::modeWrite))
	{
		file.Write(&m_bgColor, sizeof(COLORREF));
		file.Close();
		// 현재 배경 색상을 파일에 저장
	}
}

