// CRankDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "afxdialogex.h"
#include "CRankDlg.h"


// CRankDlg 对话框

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_RANK, pParent)
{

}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)
	ON_STN_CLICKED(IDC_RANK_TABLE, &CRankDlg::OnStnClickedRankTable)
END_MESSAGE_MAP()


// CRankDlg 消息处理程序


void CRankDlg::OnStnClickedRankTable()
{
	// TODO: 在此添加控件通知处理程序代码

}
