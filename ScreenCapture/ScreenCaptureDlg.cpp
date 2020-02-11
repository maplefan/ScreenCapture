
// ScreenCaptureDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ScreenCapture.h"
#include "ScreenCaptureDlg.h"
#include "afxdialogex.h"
#include "CShowDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CScreenCaptureDlg 对话框
CShowDlg *dlgAll;


CScreenCaptureDlg::CScreenCaptureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCREENCAPTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenCaptureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CScreenCaptureDlg::OnBnClickedButtonCapture)
END_MESSAGE_MAP()


// CScreenCaptureDlg 消息处理程序

BOOL CScreenCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenCaptureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScreenCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//点击截图按钮
void CScreenCaptureDlg::OnBnClickedButtonCapture()
{
	ShowWindow(SW_HIDE);
	Sleep(1000);
	CShowDlg dlg;
	dlgAll = &dlg;
	//弹出一个模态对话框
	if (IDCANCEL == dlg.DoModal()) {
		ShowWindow(SW_SHOW);
	}
	/*
	1、创建一个对话框，并且弹出
	2、将对话框的大小调整为整个桌面大小
	3、将对话框的风格改为没有边框
	4、获取点击截图这一瞬间桌面图像
	5、将这图像显示到弹出对话框上面来
	6、选择区域，并且保存选择区域图像
	7、复制到剪切板
	*/
	// TODO: 在此添加控件通知处理程序代码
}
