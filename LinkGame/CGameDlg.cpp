// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "CSettingDlg.h"

LPCWSTR ElementPath = _T("theme\\picture\\fruit_element.bmp");
LPCWSTR MaskPath = _T("theme\\picture\\fruit_mask.bmp");


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	// 初始化游戏更新区域
	m_rtGameRect.top = MAP_TOP;
	m_rtGameRect.left = MAP_LEFT;
	m_rtGameRect.right = MAP_LEFT + PIC_WIDTH * MAX_COL;
	m_rtGameRect.bottom = MAP_TOP + PIC_HEIGHT * MAX_ROW;

	//游戏状态设定
	isFirstPoint = true;
	isPlaying = false;
	isPause = false;

	//按钮禁用和启用不能使用
}

CGameDlg::~CGameDlg()
{

}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressBar);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_TIP, &CGameDlg::OnClickedBtnTip)
	ON_BN_CLICKED(IDC_BTN_REARRANGE, &CGameDlg::OnClickedBtnRearrange)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_DIALOG_HELP, &CGameDlg::OnClickedBtnDialogHelp)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CGameDlg::OnClickedBtnSetting)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground()
{
	// TODO: 在此处添加实现代码.
	/*HANDLE bmp = ::LoadImage(NULL, _T("\\theme\\picture\\fruit_bg.bmp"), IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	CClientDC dc(this);

	m_dcMem.CreateCompatibleDC(&dc);

	m_dcMem.SelectObject(&bmp);*/
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

	//调整窗口
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	this->SetWindowText((CString)"欢乐连连看----基本模式");

	InitBackground();
	InitElement();

	//时间插件是否可见
	GetDlgItem(IDC_BTN_TIP)->EnableWindow(false);
	GetDlgItem(IDC_BTN_REARRANGE)->EnableWindow(false);
	GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 1700, 1100, &m_dcMem, 0, 0, SRCCOPY);
}


void CGameDlg::InitElement()
{
	// TODO: 在此处添加实现代码.
	//获取当前多画框的视频内存
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmp = ::LoadImageW(NULL, ElementPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

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


void CGameDlg::OnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//简单调试，可以生成图片
	//int anMap[4][4] = { 0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3 };
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		m_anMap[i][j] = anMap[i][j];
	//	}
	//}
	//int nLeft = 50;
	//int nTop = 50;
	//int nElemW = 40;
	//int nElemH = 40;
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		//m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCCOPY);
	//		m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, m_anMap[i][j] * nElemH, SRCPAINT);
	//		m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_anMap[i][j] * nElemH, SRCAND);
	//	}
	//}
	//Invalidate(FALSE);

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
	// 启动定时器
	InitProcrssBar();

	//更新界面
	UpdateMap();

	//更新窗口
	InvalidateRect(m_rtGameRect, false);
}


void CGameDlg::UpdateMap()
{
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


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//MessageBox(_T("      时间到！游戏失败！！！       "), _T("失败"), NULL);

	//判断坐标是否有效并求出行和列
	if (point.x < MAP_LEFT || point.y < MAP_TOP)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - MAP_TOP) / PIC_HEIGHT;
	int nCol = (point.x - MAP_LEFT) / PIC_HEIGHT;
	if (nRow>MAX_ROW-1 || nCol>MAX_COL-1)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	//判断对话框是否已经消去过
	if(m_GameC.GetElement(nRow,nCol) == -1){
		return CDialogEx::OnLButtonUp(nFlags, point);

	}

	//绘制提示框
	if (isFirstPoint == true) {
		DrawTipFrame(nRow, nCol);
		m_GameC.SetFirstPoint(nRow, nCol);
		isFirstPoint = false;
	} else {
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

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;

	rtTipFrame.left = MAP_LEFT + nCol * PIC_WIDTH;
	rtTipFrame.top = MAP_TOP + nRow * PIC_HEIGHT;
	rtTipFrame.right = rtTipFrame.left +PIC_WIDTH ;
	rtTipFrame.bottom = rtTipFrame.top + PIC_HEIGHT;

	dc.FrameRect(rtTipFrame, &brush);
}


void CGameDlg::DrawTipLine(Vertex* avPath, int nVexnum)
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


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1&&!isPause)
	{
		m_ProgressBar.StepIt();
		if (m_ProgressBar.GetPos() == 0)
		{
			//时间到关闭计时器
			KillTimer(nIDEvent);

			//显示窗口
			MessageBox(_T("      时间到！游戏失败！！！       "), _T("失败"), NULL);
		}

	}
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::InitProcrssBar()
{
	
		//初始化进度条长度
	m_ProgressBar.SetRange(0, TIME);
		//设置进度条步长
	m_ProgressBar.SetStep(-1);
		//设置进度条起始位置
	m_ProgressBar.SetPos(TIME);

		//为进度条添加定时器
	SetTimer(1, TIME, NULL);//定时器ID为1 间隔时间1000ms 回调函数为系统默认
	// TODO: 在此处添加实现代码.
}


// 判断是否获胜
void CGameDlg::JudgeIsWin()
{
	// TODO: 在此处添加实现代码.
	// 游戏胜负判断
	BOOL bGameStatus = m_GameC.IsWin(m_ProgressBar.GetPos());

	// 判断是否继续游戏
	if (bGameStatus == GAME_PLAY)
	{
		return;
	}
	else
	{
		// 将游戏表示改为false
		isPlaying = false;

		double grade = 0;
		int time = 1200 - m_ProgressBar.GetPos();
		grade = (double)(1200 - time)*100 / 1200;
		// 关闭定时器
		KillTimer(PLAY_TIMER_ID);

		// 提示获胜
		CString str;
		CString strTitle;
		str.Format(_T("恭喜你，获胜了！得分：%.2f"), grade);
		this->GetWindowTextW(strTitle);

		if (bGameStatus == GAME_SUCCESS)
		{

			MessageBox(str, strTitle);

		}
		else if (bGameStatus == GAME_LOSE)
		{
			MessageBox(_T("Time Out!\nGame Over!"), strTitle);
		}

		// 还原游戏按钮可点击
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	}
}


void CGameDlg::OnClickedBtnTip()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isPause == TRUE)
	{
		return;
	}

	Vertex avPath[MAX_VERTEX_NUM]; // 获得路径
	int nVexnum = 0;			   // 顶点个数

	if (m_GameC.Help(avPath,nVexnum))
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


void CGameDlg::OnClickedBtnRearrange()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameC.Resert();

	//重绘图片,将图片区域先设置为空白，否则，由于为了节约算法的区域局部覆盖方法会重复生成图片
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBGPic, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	//这里重绘地图
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新
}


void CGameDlg::OnClickedBtnPause()
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
		m_dcMem.BitBlt(MAP_LEFT, MAP_TOP, MAX_COL*PIC_WIDTH, MAX_ROW*PIC_HEIGHT, &m_dcPauseImg, 0, 0, SRCCOPY);
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




void CGameDlg::OnClickedBtnDialogHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("连连看规则：\n连连看需要玩家将2个相同图案连接起来\n第一次使用鼠标点击牌池里的图案\n该图案此时为“被选中”，图案四周有光环围住，\n再用鼠标点击你所看到的另一个相同图案，\n如果两个相同的图案之间有通路，\n且通路中间的连线没有超过三根，\n这样就可以消掉这两个相同的图案。\n \
               \t\t     ----LiuShen"), (CString)"游戏帮助");
}


void CGameDlg::OnClickedBtnSetting()
{
	// TODO: 在此添加控件通知处理程序代码
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
