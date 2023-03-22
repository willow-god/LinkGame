#pragma once
#include "afxdialogex.h"
#include <MMSystem.h>
#include <Digitalv.h>

#pragma comment(lib, "Winmm.lib")


// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL isMusicOn;
	int ChoiceMusic;
	int ChoiceBGPic;

	//音乐相关
	HWND m_hWnd;
	DWORD DeviceId;
	MCI_OPEN_PARMS mciopenparms;
	CString strFilepath;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnMusicOnandclose();
	afx_msg void OnBnClickedCheckMusic1();
	afx_msg void OnBnClickedCheckMusic2();
	afx_msg void OnBnClickedCheckMusic3();
	afx_msg void OnBnClickedCheckBgpic1();
	afx_msg void OnBnClickedCheckBgpic2();
	afx_msg void OnBnClickedCheckBgpicNone();
	afx_msg void OnBnClickedBtnCancel();
	// //专门为页面设置
	void DoLinkGameDlg();
};
