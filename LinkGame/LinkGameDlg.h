
// LinkGameDlg.h: 头文件
//

#pragma once


// CLinkGameDlg 对话框
class CLinkGameDlg : public CDialogEx
{
// 构造
public:
	CLinkGameDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINKGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	protected:CDC m_dcMem;//位图内存

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void InitBackground(void);
	DECLARE_MESSAGE_MAP()
};
