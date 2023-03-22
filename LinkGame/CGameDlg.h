#pragma once
#include "afxdialogex.h"
#include "global.h"
#include "CGameControl.h"


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDC m_dcMem, //视频DC
		m_dcElement, //元素DC
		m_dcMask,//掩码DC
		m_dcPauseImg,
		m_dcBGPic;//背景图片DC
	int** m_anMap;//整个地图
	CRect m_rtGameRect; // 游戏区域大小
	bool isFirstPoint;//判断是否是第一次点的点
	bool isPlaying ;//是否正在游戏
	bool isPause ;//是否正在暂停


	CGameControl m_GameC;//游戏操作内部控制

	DECLARE_MESSAGE_MAP()
public:
	
	void InitBackground();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
protected:
	void InitElement();
public:
	afx_msg void OnClickedBtnStart();
	void UpdateMap();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex* avPath, int nVexnum);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_ProgressBar;
	void InitProcrssBar();
	// 判断是否获胜
	void JudgeIsWin();
	afx_msg void OnClickedBtnTip();
	afx_msg void OnClickedBtnRearrange();
	afx_msg void OnClickedBtnPause();
	afx_msg void OnClickedBtnDialogHelp();
	afx_msg void OnClickedBtnSetting();
};
