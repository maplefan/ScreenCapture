// CShowDlg.cpp: 实现文件
//

#include "pch.h"
#include "ScreenCapture.h"
#include "ScreenTool.h"
#include "CShowDlg.h"
#include "afxdialogex.h"

static ScreenTool* tool = NULL;
// CShowDlg 对话框

IMPLEMENT_DYNAMIC(CShowDlg, CDialogEx)

CShowDlg::CShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW_DLG, pParent)
{
	m_nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	//获取桌面DC
	CDC* pDesktopDC = GetDesktopWindow()->GetDC();
	//创建一张位图
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDesktopDC, m_nScreenWidth, m_nScreenHeight);

	//创建内存DC
	m_memDC.CreateCompatibleDC(pDesktopDC);
	m_memDC.SelectObject(&bmp);
	m_memDC.BitBlt(0, 0, m_nScreenWidth, m_nScreenHeight, pDesktopDC, 0, 0, SRCCOPY);

	//释放内存
	pDesktopDC->DeleteDC();
	bmp.DeleteObject();
}

CShowDlg::~CShowDlg()
{
}

void CShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CShowDlg 消息处理程序


BOOL CShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0, 0, m_nScreenWidth, m_nScreenHeight, FALSE);//移动对话框大小
	// TODO:  在此添加额外的初始化

	//初始化
	m_tracker.m_nStyle = CRectTracker::solidLine | CRectTracker::resizeInside;//样式
	m_tracker.m_nHandleSize = 5;//控制柄边框像素大小
	m_tracker.m_rect.SetRect(0, 0, 0, 0);//初始化选框矩形大小
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CShowDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, m_nScreenWidth, m_nScreenHeight, &m_memDC, 0, 0, SRCCOPY);
	m_tracker.Draw(&dc);
}


void CShowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_tracker.HitTest(point) < 0) {
		//没有点中，重画
		m_tracker.TrackRubberBand(this, point, TRUE);
		m_tracker.m_rect.NormalizeRect();
	}
	else {
		m_tracker.Track(this, point, TRUE);
		m_tracker.m_rect.NormalizeRect();
	}
	int toolPointX = point.x;
	int toolPointY = point.y + m_tracker.m_rect.Height();
	Invalidate(FALSE);
	if (tool != NULL) {
		delete tool;
		tool = NULL;
	} 
	int w = m_tracker.m_rect.Width();
	int h = m_tracker.m_rect.Height();
	tool = new ScreenTool(w , h);
	tool->Create(IDD_TOOL_DLG);
	tool->ShowWindow(SW_SHOWNORMAL);
	//智能移动工具栏位置
	if (toolPointX + 428 < m_nScreenWidth && toolPointY + 59 < m_nScreenHeight)
	{
		tool->MoveWindow(toolPointX, toolPointY, 428, 59);
	}
	else if(toolPointX + 428 < m_nScreenWidth){
		tool->MoveWindow(toolPointX, toolPointY - 59 - h, 428, 59);
	}
	else {
		tool->MoveWindow(toolPointX + w - 428, toolPointY - h - 59 , 428, 59);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CShowDlg::Cancel() {
	EndDialog(IDCANCEL);
}

void CShowDlg::SavePic() {
	int width = m_tracker.m_rect.Width();
	int height = m_tracker.m_rect.Height();

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&m_memDC, width, height);
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	memDC.BitBlt(0, 0, width, height, &m_memDC, m_tracker.m_rect.left, m_tracker.m_rect.top, SRCCOPY);

	//打开剪切板
	OpenClipboard();
	//清空剪切板
	EmptyClipboard();
	//设置剪切板数据
	SetClipboardData(CF_BITMAP, bmp);
	//关闭剪切板
	CloseClipboard();

	//保存位图
	CImage img1;
	img1.Attach(bmp);

	SYSTEMTIME str;
	GetLocalTime(&str);
	CString timePath;
	CString img = _T("Image");
	CString cs = _T("-");
	CString cs1 = _T("__");
	//用当前时间创建默认图片名称
	timePath.Format(_T("%s%s%2d%s%02d%s%02d%s%02d%s%02d%s%02d"), img, cs1, str.wYear, cs, str.wMonth, cs, str.wDay, cs1, str.wHour, cs, str.wMinute, cs, str.wSecond);

	TCHAR szFilter[] = _T("JPG图片(*.jpg)|*.jpg|BMP图片(*.bmp)|*.bmp|PNG图片(*.png)|*.png|JPEG图片(*.jpeg)|*.jpeg|DIB图片(*dib)|*.dib|PBM图片(*.pbm)|*.pbm||");
	CFileDialog fileDlg(FALSE, _T("jpg"), timePath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;
	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		img1.Save(strFilePath);
	}
	img1.Detach();

	//释放内存
	memDC.DeleteDC();
	bmp.DeleteObject();
	m_memDC.DeleteDC();
	EndDialog(IDCANCEL);
}
void CShowDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
}


void CShowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);
}
