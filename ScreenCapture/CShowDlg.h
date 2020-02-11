#pragma once

// CShowDlg 对话框

class CShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShowDlg)

public:
	CShowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	int m_nScreenWidth;//屏幕宽度
	int m_nScreenHeight;//屏幕宽度
	CDC m_memDC;  //内存DC
	CRectTracker m_tracker; //橡皮筋对象

	virtual BOOL OnInitDialog();
	void SavePic();
	void Cancel();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
