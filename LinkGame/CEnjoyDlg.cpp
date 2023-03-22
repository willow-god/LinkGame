// CEnjoyDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "afxdialogex.h"
#include "CEnjoyDlg.h"
#include "CSettingDlg.h"

//背景图像位置
extern LPCWSTR ElementPath;
extern LPCWSTR MaskPath;

// CEnjoyDlg 对话框

IMPLEMENT_DYNAMIC(CEnjoyDlg, CDialogEx)

CEnjoyDlg::CEnjoyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ENJOY_DIALOG, pParent)
{
	//图片位置选中，防止因为先打开娱乐模式导致没有初始化背景或者掩码图片
	ElementPath = _T("theme\\picture\\fruit_element.bmp");
	MaskPath = _T("theme\\picture\\fruit_mask.bmp");

	m_rtGameRect.top = MAP_TOP;
	m_rtGameRect.left = MAP_LEFT;
	m_rtGameRect.right = MAP_LEFT + PIC_WIDTH * MAX_COL;
	m_rtGameRect.bottom = MAP_TOP + PIC_HEIGHT * MAX_ROW;

	//游戏状态设定
	isFirstPoint = true;
	isPlaying = false;
	isPause = false;
}

CEnjoyDlg::~CEnjoyDlg()
{
}

void CEnjoyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEnjoyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CEnjoyDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CEnjoyDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_TIP, &CEnjoyDlg::OnBnClickedBtnTip)
	ON_BN_CLICKED(IDC_BTN_REARRANGE, &CEnjoyDlg::OnBnClickedBtnRearrange)
	ON_BN_CLICKED(IDC_BTN_HELP, &CEnjoyDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CEnjoyDlg::OnBnClickedBtnSetting)
END_MESSAGE_MAP()


// CEnjoyDlg 消息处理程序


BOOL CEnjoyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetWindowText((CString)"欢乐连连看----娱乐模式，尽情的玩耍吧！！！");

	InitBackground();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


// 初始化背景图像
void CEnjoyDlg::InitBackground()
{
	// TODO: 在此处添加实现代码.
	//加载背景文件
	CBitmap  bmpDialog;
	bmpDialog.LoadBitmap(IDB_DIALOG_BG);

	//创建当前对话框视频内容
	CClientDC dc(this);

	//创建与视频内容兼容的DC
	m_dcBGPic.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcBGPic.SelectObject(&bmpDialog);

	//初始化DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 1700, 1100);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景到内存DC
	m_dcMem.BitBlt(0, 0, 1700, 1100, &m_dcBGPic, 0, 0, SRCCOPY);
}


void CEnjoyDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 1700, 1100, &m_dcMem, 0, 0, SRCCOPY);
}


// 加载元素图片或者掩码图片
void CEnjoyDlg::InitElement()
{
	// TODO: 在此处添加实现代码.
	//获取当前多画框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmp = ::LoadImageW(NULL, ElementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcElement.SelectObject(hBmp);

	//加载掩码BMP图片资源
	HANDLE hMask = ::LoadImageW(NULL, MaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);

	//加载暂停图片资源
	HANDLE hPause = ::LoadImageW(NULL, _T("theme\\picture\\PAUSE_IMG.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcPauseImg.CreateCompatibleDC(&dc);

	//将位图资源选入DC
	m_dcPauseImg.SelectObject(hPause);
}



void CEnjoyDlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	isPlaying = true;

	//现在开始调用函数实操
	m_GameC.StartGame();

	//计时时间为20分钟，可以在global里面改
	int timeCount = TIME;

	//将游戏标识设置为真表示正在游戏
	isPlaying = true;

	//禁止按钮点击导致重复生成图片
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_TIP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(TRUE);

	//初始化进度条
	//更新界面
	UpdateMap();

	//更新窗口
	InvalidateRect(m_rtGameRect, false);
}


void CEnjoyDlg::UpdateMap()
{
	// TODO: 在此处添加实现代码.
	// TODO: 在此处添加实现代码.
	int nRows = MAX_ROW;
	int nCols = MAX_COL;
	int nLeft = MAP_LEFT;
	int nTop = MAP_TOP;
	int nElemW = PIC_WIDTH;
	int nElemH = PIC_HEIGHT;


	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			int nElemVal = m_GameC.GetElement(i, j);
			if (nElemVal == -1)
			{
				//将值为-1的位置进行背景图像的绘画
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcBGPic, nLeft + j * nElemW, nTop + i * nElemH, SRCCOPY);
			}
			else {
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT);
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
			}
		}
	}
	Invalidate(FALSE);
}


void CEnjoyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//判断坐标是否有效并求出行和列
	if (point.x < MAP_LEFT || point.y < MAP_TOP)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - MAP_TOP) / PIC_HEIGHT;
	int nCol = (point.x - MAP_LEFT) / PIC_HEIGHT;
	if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//判断对话框是否已经消去过
	if (m_GameC.GetElement(nRow, nCol) == -1) {
		return CDialogEx::OnLButtonUp(nFlags, point);

	}

	//绘制提示框
	if (isFirstPoint == true) {
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
		isFirstPoint = false;
	}
	else {
		DrawTipFrame(nRow, nCol);
		m_GameC.SetSecPoint(nRow, nCol);
		isFirstPoint = true;

		//现在需要判断是否可以消掉
		Vertex avPath[MAX_VERTEX_NUM]; //路径定义的16个长，实际上不可能
		int nVexnum = 0; //顶点个数

		//判断连线是否可以连上
		if (m_GameC.Link(avPath, nVexnum))
		{
			// 画提示线
			DrawTipLine(avPath, nVexnum);
			// 更新地图

			UpdateMap();
		}

		Sleep(200);
		InvalidateRect(m_rtGameRect, false);

		//判断胜负
		JudgeIsWin();

	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


// 画框框
void CEnjoyDlg::DrawTipFrame(int nRow, int nCol)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;

	rtTipFrame.left = MAP_LEFT + nCol * PIC_WIDTH;
	rtTipFrame.top = MAP_TOP + nRow * PIC_HEIGHT;
	rtTipFrame.right = rtTipFrame.left + PIC_WIDTH;
	rtTipFrame.bottom = rtTipFrame.top + PIC_HEIGHT;

	dc.FrameRect(rtTipFrame, &brush);
}




// //画线
void CEnjoyDlg::DrawTipLine(Vertex* avPath, int nVexnum)
{
	// TODO: 在此处添加实现代码.
	// 获取DC
	CClientDC dc(this);

	// 设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	// 将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	dc.MoveTo(MAP_LEFT + avPath[0].col * PIC_WIDTH + PIC_WIDTH / 2,
		MAP_TOP + avPath[0].row * PIC_HEIGHT + PIC_HEIGHT / 2);
	// 绘制连接线
	for (int i = 0; i < nVexnum - 1; i++)
	{

		dc.LineTo(MAP_LEFT + avPath[i + 1].col * PIC_WIDTH + PIC_WIDTH / 2,
			MAP_TOP + avPath[i + 1].row * PIC_HEIGHT + PIC_HEIGHT / 2);
	}

	dc.SelectObject(pOldPen);
}




void CEnjoyDlg::JudgeIsWin()
{
	// TODO: 在此处添加实现代码.
	// TODO: 在此处添加实现代码.
	// 游戏胜负判断
	BOOL bGameStatus = m_GameC.IsWin(1);//随便定义一个大于1的时间表示时间无限长即可

	// 判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		// 将游戏表示改为false
		isPlaying = false;
		// 提示获胜
		CString strTitle;

		this->GetWindowTextW(strTitle);

		if (bGameStatus == GAME_SUCCESS)
		{

			MessageBox(_T("恭喜你，获胜了！得分："), strTitle);

		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("\nGame Over!"), strTitle);
		}

		// 还原游戏按钮可点击
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}
}


void CEnjoyDlg::OnBnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);

	// 游戏未正在进行，直接返回
	if (isPlaying == false)
	{
		return;
	}

	if (isPause == false)
	{
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, MAX_COL * PIC_WIDTH, MAX_ROW * PIC_HEIGHT, &m_dcPauseImg, 0, 0, SRCCOPY);
		GetDlgItem(IDC_BTN_TIP)->EnableWindow(false);
		GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(false);
		InvalidateRect(m_rtGameRect, false); // 更新界面
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}

	//如果游戏暂停状态
	if (isPause == true)
	{
		m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBGPic, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
		UpdateMap();
		GetDlgItem(IDC_BTN_TIP)->EnableWindow(1);
		GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新

		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}
	isPause = !isPause;
}


void CEnjoyDlg::OnBnClickedBtnTip()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isPause == TRUE)
	{
		return;
	}

	Vertex avPath[MAX_VERTEX_NUM]; // 获得路径
	int nVexnum = 0;			   // 顶点个数

	if (m_GameC.Help(avPath, nVexnum))
	{
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[nVexnum - 1].row, avPath[nVexnum - 1].col);

		// 画提示线
		DrawTipLine(avPath, nVexnum);

		// 为了使第二个提示框可以看到，暂停200ms后，再刷新页面
		Sleep(1000);

		UpdateMap(); // 更新地图

		// 局部矩形更新
		InvalidateRect(m_rtGameRect, FALSE);

		//判断是否成功
		JudgeIsWin();
	}
	else {
		MessageBox(_T("当前页面无可消点，请点击重排后重试"), (CString)"！！！注意！！！");
	}
}


void CEnjoyDlg::OnBnClickedBtnRearrange()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameC.Resert();

	//重绘图片,将图片区域先设置为空白，否则，由于为了节约算法的区域局部覆盖方法会重复生成图片
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBGPic, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	//这里重绘地图
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新
}


void CEnjoyDlg::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("连连看规则：\n连连看需要玩家将2个相同图案连接起来\n第一次使用鼠标点击牌池里的图案\n该图案此时为“被选中”，图案四周有光环围住，\n再用鼠标点击你所看到的另一个相同图案，\n如果两个相同的图案之间有通路，\n且通路中间的连线没有超过三根，\n这样就可以消掉这两个相同的图案。\n \
               \t\t     ----LiuShen"), (CString)"游戏帮助");
}


void CEnjoyDlg::OnBnClickedBtnSetting()
{
	if (isPlaying == false)
	{
		MessageBox(_T("请点击开始游戏后设置"), (CString)"！！！");
		return;
	}

	CSettingDlg settingDlg;
	settingDlg.DoModal();

	//InitElement();
	HANDLE hBmp = ::LoadImageW(NULL, ElementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcElement.SelectObject(hBmp);
	HANDLE hMask = ::LoadImageW(NULL, MaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//将位图资源选入DC
	m_dcMask.SelectObject(hMask);
	//重绘图片,将图片区域先设置为空白，否则，由于为了节约算法的区域局部覆盖方法会重复生成图片
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBGPic, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	//这里重绘地图
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新
}
