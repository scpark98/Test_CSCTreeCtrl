
// Test_CTreeCtrlExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test_CTreeCtrlEx.h"
#include "Test_CTreeCtrlExDlg.h"

#include <functional>
#include "Common/MemoryDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CTest_CTreeCtrlExDlg dialog



CTest_CTreeCtrlExDlg::CTest_CTreeCtrlExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_CTREECTRLEX_DIALOG, pParent)
	, m_edit_indent(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_CTreeCtrlExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_BOX, m_check_box);
	DDX_Control(pDX, IDC_CHECK_BOX_ROOT, m_check_atRoot);
	DDX_Control(pDX, IDC_CHECK_SCROLLBAR, m_check_scrollbar);
	DDX_Control(pDX, IDC_COMBO_COLOR_THEME, m_combo_color_theme);
	DDX_Control(pDX, IDC_CHECK_LINE, m_check_line);
	DDX_Control(pDX, IDC_CHECK_EXPAND, m_check_expand);
	DDX_Control(pDX, IDC_CHECK_ALWAYS_ON_TOP, m_check_alwaysOnTop);
	DDX_Control(pDX, IDC_CHECK_ALWAYS_SHOW_SELECTION, m_check_always_show_selection);
	DDX_Text(pDX, IDC_EDIT_INDENT, m_edit_indent);
	DDV_MinMaxInt(pDX, m_edit_indent, 0, 99);
	DDX_Control(pDX, IDC_SPIN_INDENT, m_spin_indent);
	DDX_Control(pDX, IDC_CHECK_IMAGE_LIST, m_check_imagelist);
	DDX_Control(pDX, IDC_CHECK_IMAGE_LIST_LARGE, m_check_image_list_large);
	DDX_Control(pDX, IDC_TREE, m_tree);
}

BEGIN_MESSAGE_MAP(CTest_CTreeCtrlExDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTest_CTreeCtrlExDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTest_CTreeCtrlExDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_BOX, &CTest_CTreeCtrlExDlg::OnBnClickedCheckBox)
	ON_BN_CLICKED(IDC_CHECK_BOX_ROOT, &CTest_CTreeCtrlExDlg::OnBnClickedCheckBoxRoot)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ERASEBKGND()
	//ON_MESSAGE(MESSAGE_TREECTRLEX_CHECK_CHANGED, &CTest_CTreeCtrlExDlg::OnMessageTreeCtrlCheckChanged)
	ON_BN_CLICKED(IDC_CHECK_SCROLLBAR, &CTest_CTreeCtrlExDlg::OnBnClickedCheckScrollbar)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR_THEME, &CTest_CTreeCtrlExDlg::OnCbnSelchangeComboColorTheme)
	ON_BN_CLICKED(IDC_CHECK_LINE, &CTest_CTreeCtrlExDlg::OnBnClickedCheckLine)
	ON_BN_CLICKED(IDC_CHECK_EXPAND, &CTest_CTreeCtrlExDlg::OnBnClickedCheckExpand)
	ON_BN_CLICKED(IDC_CHECK_ALWAYS_ON_TOP, &CTest_CTreeCtrlExDlg::OnBnClickedCheckAlwaysOnTop)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &CTest_CTreeCtrlExDlg::OnBnClickedButtonFont)
	ON_BN_CLICKED(IDC_CHECK_ALWAYS_SHOW_SELECTION, &CTest_CTreeCtrlExDlg::OnBnClickedCheckAlwaysShowSelection)
	ON_EN_CHANGE(IDC_EDIT_INDENT, &CTest_CTreeCtrlExDlg::OnChangeEditIndent)
	ON_BN_CLICKED(IDC_CHECK_IMAGE_LIST, &CTest_CTreeCtrlExDlg::OnBnClickedCheckImageList)
	ON_BN_CLICKED(IDC_CHECK_IMAGE_LIST_LARGE, &CTest_CTreeCtrlExDlg::OnBnClickedCheckImageListLarge)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTest_CTreeCtrlExDlg message handlers

BOOL CTest_CTreeCtrlExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	HWND hwnd = GetSafeHwnd();

	m_resize.Create(this);
	m_resize.Add(IDC_TREE, 0, 0, 100, 100);
	//m_resize.SetMinimumTrackingSize();

	RestoreWindowPosition(&theApp, this);

	bool check = theApp.GetProfileInt(_T("setting"), _T("use checkbox"), false);
	m_check_box.SetCheck(check);
	//m_tree.use_check_box(check);

	check = theApp.GetProfileInt(_T("setting"), _T("use checkbox at root"), false);
	m_check_atRoot.SetCheck(check);
	//m_tree.use_check_box_at_root(check);

	//m_tree.set_font_name(theApp.GetProfileString( _T("setting"), _T("face name"), _T("")));
	//m_tree.set_font_size(theApp.GetProfileInt( _T("setting"), _T("font size"), 9));
	//m_tree.set_font_bold(theApp.GetProfileInt( _T("setting"), _T("font bold"), false));
	//m_tree.set_font_italic(theApp.GetProfileInt( _T("setting"), _T("font italic"), false));
	//m_tree.use_scrollbar(false);
	//m_tree.set_scroll_unit(2);
	//m_tree.use_expand_button();

	m_check_expand.SetCheck(true);

	m_check_line.SetCheck(true);
	m_check_always_show_selection.SetCheck(true);

	std::deque<CString> color_theme_list;
	CSCColorTheme::get_color_theme_list(color_theme_list);
	for (int i = 0; i < color_theme_list.size(); i++)
		m_combo_color_theme.AddString(color_theme_list[i]);

	int cur_theme = theApp.GetProfileInt(_T("setting"), _T("cur color theme"), 0);
	Clamp(cur_theme, 0, (int)(color_theme_list.size() - 1));
	m_combo_color_theme.SetCurSel(cur_theme);
	m_tree.set_color_theme(cur_theme);

	m_tree.set_function_check_is_dim_text(check_is_dim_text);

	//m_edit_indent = m_tree.get_indent_size();
	m_spin_indent.SetRange(0, 99);
	UpdateData(false);

#if 0
	//탐색기 트리로 동작
	m_tree.set_as_shell_treectrl(&m_ShellImageList, true);
	m_tree.select_folder(_T("C:\\"));
#else
	//사용자 데이터 트리로 동작
	//m_tree.load_from_file(true, _T("tree_item_unicode.txt"));
	//m_tree.load_from_file(true, _T("tree_item_utf8.txt"));


	m_tree.set_imagelist(IDI_EMPTY, IDI_EMPTY, IDI_FLOPPY, IDI_FIXEDDISK, IDI_HARDDISK, IDI_CDROM, IDI_NETWORKPLACE);

	//노드들이 추가되기 전에 가상 root를 추가하는 경우에 대한 테스트 코드
	//m_tree.set_root_item(_T("root"), 0);

	int image_size = 16;// theApp.GetProfileInt(_T("setting"), _T("image size"), 16);
	//m_spin_iconSize.SetRange(8, 44);
	//m_spin_iconSize.SetPos(image_size);
	//m_edit_iconSize = image_size;
	m_tree.set_use_own_imagelist(true, image_size);


	m_tree.load_from_string(_T("\
1\n\
	11\n\
	12\n\
		121\n\
			1211\n\
				12111\n\
	13\n\
2\n\
	21\n\
		211\n\
		212한글\n\
		213English\n\
		214にほんご\n\
		214漢字\n\
	22\n\
	23\n\
		231\n\
			2311\n\
			2312\n\
				23121\n\
				23122\n\
3\n\
	31\n\
	32\n\
	33\n\
		331\n\
4\n\
	41\n\
	"));

	m_tree.expand_all();
	m_tree.iterate_tree_in_order();
	//m_tree.SetItemHeight(24);

	//SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
	//m_tree.find_item(_T("루트2"), _T("apple"), 1);
#endif

	//가상 루트가 없는 상태에서 노드들이 추가된 후에 가상 루트를 추가할 경우
	//가상 루트를 추가하고 기존 노드들을 모두 가상루트의 child로 이동시킨다.
	//m_tree.set_root_item(_T("root"), IDR_MAINFRAME);

	m_tree.set_use_drag_and_drop();

	SetTimer(timer_ime_to_native, 100, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTest_CTreeCtrlExDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTest_CTreeCtrlExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc1(this);
		CRect rc;

		GetClientRect(rc);
		CMemoryDC dc(&dc1, &rc, false);

		//dc.FillSolidRect(rc, GRAY(32));

		dc.FillSolidRect(rc, ::GetSysColor(COLOR_3DFACE));

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTest_CTreeCtrlExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTest_CTreeCtrlExDlg::OnBnClickedOk()
{
	//AfxMessageBox(m_tree.get_item_text(m_tree.get_selected_item()));
	//m_tree.ensure_visible(m_tree.get_selected_item());
}


void CTest_CTreeCtrlExDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CTest_CTreeCtrlExDlg::OnBnClickedCheckBox()
{
	bool check = m_check_box.GetCheck();
	m_tree.use_checkbox(check);
	//theApp.WriteProfileInt(_T("setting"), _T("use checkbox"), check);

	//if (!check)
	//	m_check_atRoot.SetCheck(check);

	//m_check_atRoot.EnableWindow(check);
}


void CTest_CTreeCtrlExDlg::OnBnClickedCheckBoxRoot()
{
	bool check = m_check_atRoot.GetCheck();
	//m_tree.use_check_box_at_root(check);
	//theApp.WriteProfileInt(_T("setting"), _T("use checkbox at root"), check);
}


void CTest_CTreeCtrlExDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: Add your message handler code here
	SaveWindowPosition(&theApp, this);
}


BOOL CTest_CTreeCtrlExDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	return CDialogEx::OnEraseBkgnd(pDC);
}

LRESULT CTest_CTreeCtrlExDlg::OnMessageTreeCtrlCheckChanged(WPARAM wParam, LPARAM lParam)
{
	UINT nID = (UINT)wParam;
	if (nID == IDC_TREE)
	{
		//tree<CTreeItem>::pre_order_iterator *it = (tree<CTreeItem>::pre_order_iterator *)lParam;
		//TRACE(_T("check changed item = %s, checked = %d\n"), it->node->data.text, it->node->data.get_check());
	}

	return 0;
}

void CTest_CTreeCtrlExDlg::OnBnClickedCheckScrollbar()
{
	//m_tree.use_scrollbar(m_check_scrollbar.GetCheck());
}


void CTest_CTreeCtrlExDlg::OnCbnSelchangeComboColorTheme()
{
	int index = m_combo_color_theme.GetCurSel();
	theApp.WriteProfileInt(_T("setting"), _T("cur color theme"), index);
	m_tree.set_color_theme(index);
}


void CTest_CTreeCtrlExDlg::OnBnClickedCheckLine()
{
	//m_tree.draw_line_node(m_check_line.GetCheck());
}


void CTest_CTreeCtrlExDlg::OnBnClickedCheckExpand()
{
	//m_tree.use_expand_button(m_check_expand.GetCheck());
}


void CTest_CTreeCtrlExDlg::OnBnClickedCheckAlwaysOnTop()
{
	SetWindowPos( (m_check_alwaysOnTop.GetCheck() ? &wndTopMost : &wndNoTopMost), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
}


void CTest_CTreeCtrlExDlg::OnBnClickedButtonFont()
{
	LOGFONT m_lf = m_tree.get_log_font();

	CFontDialog dlg(&m_lf);
	if ( dlg.DoModal() == IDCANCEL )
		return;

	m_tree.set_log_font(m_lf);
	theApp.WriteProfileString( _T("setting"), _T("face name"), m_lf.lfFaceName );
	theApp.WriteProfileInt( _T("setting"), _T("font size"), m_tree.get_font_size());
	theApp.WriteProfileInt( _T("setting"), _T("font bold"), (m_lf.lfWeight == 700) );
	theApp.WriteProfileInt( _T("setting"), _T("font italic"), m_lf.lfItalic );
	//ReconstructFont(0);
}


void CTest_CTreeCtrlExDlg::OnBnClickedCheckAlwaysShowSelection()
{
	//m_tree.always_show_selection(m_check_always_show_selection.GetCheck());
}


void CTest_CTreeCtrlExDlg::OnChangeEditIndent()
{
	if (m_tree.m_hWnd == NULL)
		return;
	UpdateData(true);
	//m_tree.set_indent_size(m_edit_indent);
}

void CTest_CTreeCtrlExDlg::set_tree_image_list()
{
	//if(m_tree.get_image_list())
	//	m_tree.get_image_list()->DeleteImageList();

	//int image_size = m_tree.get_image_list_size();

	//m_tree.get_image_list()->Create(image_size, image_size, ILC_COLOR32|ILC_MASK,5,1);
	//m_tree.get_image_list()->Add(AfxGetApp()->LoadIcon(IDI_FLOPPY));
	//m_tree.get_image_list()->Add(AfxGetApp()->LoadIcon(IDI_FIXEDDISK));
	//m_tree.get_image_list()->Add(AfxGetApp()->LoadIcon(IDI_HARDDISK));
	//m_tree.get_image_list()->Add(AfxGetApp()->LoadIcon(IDI_CDROM));
	//m_tree.get_image_list()->Add(AfxGetApp()->LoadIcon(IDI_NETWORKPLACE));

	m_tree.Invalidate();
}

void CTest_CTreeCtrlExDlg::OnBnClickedCheckImageList()
{
	bool use = m_check_imagelist.GetCheck();
	m_tree.set_use_own_imagelist(use, m_check_image_list_large.GetCheck() ? 32 : 16);
	//set_tree_image_list();
}


void CTest_CTreeCtrlExDlg::OnBnClickedCheckImageListLarge()
{
	m_tree.set_image_size(m_check_image_list_large.GetCheck() ? 32 : 16);
	//set_tree_image_list();
}

//레이블의 첫 숫자가 홀수이면 dim_text로 출력하게 하는 콜백함수 샘플
//static으로 선언되야 한다.
bool CTest_CTreeCtrlExDlg::check_is_dim_text(CWnd* pWnd, HTREEITEM hItem)
{
	if (pWnd == NULL || hItem == NULL)
		return false;

	CString text = ((CTreeCtrl*)pWnd)->GetItemText(hItem);
	if (text.GetLength() == 0)
		return false;

	return ((text[0] - '0') % 2);
}


void CTest_CTreeCtrlExDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == timer_ime_to_native)
	{
		KillTimer(timer_ime_to_native);
		ime_convert(m_hWnd, true);
	}

	CDialogEx::OnTimer(nIDEvent);
}
