
// Test_CTreeCtrlExDlg.h : header file
//

#pragma once

#include "Common/Functions.h"
#include "Common/ResizeCtrl.h"
#include "Common/CTreeCtrl/SCTreeCtrl/SCTreeCtrl.h"
#include "Common/system/ShellImageList/ShellImageList.h"

// CTest_CTreeCtrlExDlg dialog
class CTest_CTreeCtrlExDlg : public CDialogEx
{
// Construction
public:
	CTest_CTreeCtrlExDlg(CWnd* pParent = NULL);	// standard constructor

	CResizeCtrl		m_resize;
	LRESULT			OnMessageTreeCtrlCheckChanged(WPARAM, LPARAM);

	void			set_tree_image_list();

	static bool		check_is_dim_text(CWnd* pWnd, HTREEITEM hItem);
	void			test_function();

	//Shell의 imagelist 및 shell과 관계된 멤버 제공
	CShellImageList		m_ShellImageList;

	enum TIMER_ID
	{
		timer_ime_to_native = 0,
	};

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_CTREECTRLEX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CButton m_check_box;
	afx_msg void OnBnClickedCheckBox();
	CButton m_check_atRoot;
	afx_msg void OnBnClickedCheckBoxRoot();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CButton m_check_scrollbar;
	afx_msg void OnBnClickedCheckScrollbar();
	CComboBox m_combo_color_theme;
	afx_msg void OnCbnSelchangeComboColorTheme();
	CButton m_check_line;
	afx_msg void OnBnClickedCheckLine();
	CButton m_check_expand;
	afx_msg void OnBnClickedCheckExpand();
	CButton m_check_alwaysOnTop;
	afx_msg void OnBnClickedCheckAlwaysOnTop();
	afx_msg void OnBnClickedButtonFont();
	CButton m_check_always_show_selection;
	afx_msg void OnBnClickedCheckAlwaysShowSelection();
	int m_edit_indent;
	afx_msg void OnChangeEditIndent();
	CSpinButtonCtrl m_spin_indent;
	CButton m_check_imagelist;
	afx_msg void OnBnClickedCheckImageList();
	CButton m_check_image_list_large;
	afx_msg void OnBnClickedCheckImageListLarge();
	CSCTreeCtrl m_tree;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
