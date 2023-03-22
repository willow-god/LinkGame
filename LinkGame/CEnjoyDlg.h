#pragma once
#include "afxdialogex.h"
#include "global.h"
#include "CGameControl.h"


// CEnjoyDlg 对话框

class CEnjoyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnjoyDlg)

public:
	CEnjoyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEnjoyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENJOY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_dcMem ;//视频DC
	CDC m_dcElement; //元素DC
	CDC m_dcMask;//掩码DC
	CDC m_dcPauseImg;
	CDC m_dcBGPic;//背景图片DC

	int** m_anMap;//整个地图

	bool isFirstPoint;//判断是否是第一次点的点
	bool isPlaying;//是否正在游戏
	bool isPause;//是否正在暂停

	CRect m_rtGameRect; // 游戏区域大小

	CGameControl m_GameC;//游戏操作内部控制

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 初始化背景图像
	void InitBackground();
	afx_msg void OnPaint();
	// 加载元素图片或者掩码图片
	void InitElement();
	afx_msg void OnBnClickedBtnStart();
	void UpdateMap();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 画框框
	void DrawTipFrame(int nRow, int nCol);
	// //画线线
	void DrawTipLine(Vertex* avPath, int nVexnum);
	void JudgeIsWin();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnTip();
	afx_msg void OnBnClickedBtnRearrange();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedBtnSetting();
};
