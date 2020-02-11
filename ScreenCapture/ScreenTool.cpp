// ScreenTool.cpp: 实现文件
//

#include "pch.h"
#include "ScreenCapture.h"
#include "ScreenTool.h"
#include "CShowDlg.h"
#include "afxdialogex.h"

extern CShowDlg* dlgAll;
// ScreenTool 对话框

IMPLEMENT_DYNAMIC(ScreenTool, CDialogEx)

ScreenTool::ScreenTool(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOL_DLG, pParent)
{
	this->picWidth = 0;
	this->picHeight = 0;
}

ScreenTool::ScreenTool(int w , int h , CWnd* pParent )
	: CDialogEx(IDD_TOOL_DLG, pParent)
{
	this->picWidth = w;
	this->picHeight = h;
}

ScreenTool::~ScreenTool()
{
}

void ScreenTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ScreenTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &ScreenTool::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &ScreenTool::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT, &ScreenTool::OnEnChangeEdit)
	ON_STN_CLICKED(IDC_STATIC3, &ScreenTool::OnStnClickedStatic3)
END_MESSAGE_MAP()


// ScreenTool 消息处理程序


void ScreenTool::OnBnClickedButton2()
{
	//保存
	// TODO: 在此添加控件通知处理程序代码
	this->DestroyWindow();
	dlgAll->SavePic();
}


void ScreenTool::OnBnClickedButton1()
{
	//取消
	// TODO: 在此添加控件通知处理程序代码
	this->DestroyWindow();
	dlgAll->Cancel();
}


void ScreenTool::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL ScreenTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_font.CreatePointFont(150, L"微软雅黑");//代表15号字体，华文行楷
	m_brush.CreateSolidBrush(RGB(0, 255, 0));//画刷为绿色
	// TODO:  在此添加额外的初始化
	
	SetDlgItemText(IDC_STATIC3, this->getPicWidthAndHeight());
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH ScreenTool::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetBkColor(RGB(255, 255, 255));//背景色为绿色
		pDC->SetTextColor(RGB(0, 0, 0));//文字为红色
		pDC->SelectObject(&m_font);//文字为15号字体，微软雅黑
		return m_brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void ScreenTool::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void ScreenTool::setPicWidthAndHeight(int width , int height) {
	this->picWidth = width;
	this->picHeight = height;
}

CString ScreenTool::getPicWidthAndHeight() {
	CString str;
	str.Format(_T("%d * %d"), this->picWidth , this->picHeight);
	return str;
	//return ("" + this->picWidth + " * " + this->picHeight);
}



void ScreenTool::OnStnClickedStatic3()
{
	// TODO: 在此添加控件通知处理程序代码
}
