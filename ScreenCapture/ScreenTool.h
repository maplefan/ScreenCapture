#pragma once


// ScreenTool 对话框

class ScreenTool : public CDialogEx
{
    int picWidth;
    int picHeight;
    static ScreenTool* getInstance() {
        if (nullptr == ptr) {
            ptr = new ScreenTool(); //调用构造函数对对象进行实例化
        }
        return ptr; //返回指向该对象的指针
    }

    static void destory() {
        if (ptr) {
            delete ptr; // 回收堆空间
            ptr = nullptr;  // 防止野指针
        }
    }

	DECLARE_DYNAMIC(ScreenTool)

public:
	ScreenTool(CWnd* pParent = nullptr);   // 标准构造函数
    ScreenTool(int w, int h, CWnd* pParent = nullptr);
	virtual ~ScreenTool();
    static ScreenTool* ptr;  //指向该对象的指针
    CBrush m_brush;
    CFont m_font;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnEnChangeEdit();
    void setPicWidthAndHeight(int width, int height);
    CString getPicWidthAndHeight();
    afx_msg void OnStnClickedStatic3();
};

//ScreenTool* ScreenTool::ptr = nullptr; //静态对象在类外进行初始化