// CSettingDlg.cpp: 实现文件
//

#include "global.h"
#include "pch.h"
#include "LinkGame.h"
#include "afxdialogex.h"
#include "CSettingDlg.h"

//音乐相关
#include <string>
#include <Digitalv.h>
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>

extern LPCWSTR ElementPath;
extern LPCWSTR MaskPath;
extern BOOL isMusicOn;
extern int ChoiceMusic;
extern int ChoiceBGPic;

// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{
	
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MUSIC_SLIDER, slide);
	DDX_Control(pDX, IDC_EDIT_VOLUME_SHOW, VolumeShow);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_MUSIC_ONANDCLOSE, &CSettingDlg::OnBnClickedBtnMusicOnandclose)
	ON_BN_CLICKED(IDC_CHECK_MUSIC1, &CSettingDlg::OnBnClickedCheckMusic1)
	ON_BN_CLICKED(IDC_CHECK_MUSIC2, &CSettingDlg::OnBnClickedCheckMusic2)
	ON_BN_CLICKED(IDC_CHECK_MUSIC3, &CSettingDlg::OnBnClickedCheckMusic3)
	ON_BN_CLICKED(IDC_CHECK_BGPIC1, &CSettingDlg::OnBnClickedCheckBgpic1)
	ON_BN_CLICKED(IDC_CHECK_BGPIC2, &CSettingDlg::OnBnClickedCheckBgpic2)
	ON_BN_CLICKED(IDC_CHECK_BGPIC_NONE, &CSettingDlg::OnBnClickedCheckBgpicNone)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSettingDlg::OnBnClickedBtnCancel)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ChoiceBGPic == 1)
	{
		ElementPath = _T("theme\\picture\\fruit_element1.bmp");
		MaskPath = _T("theme\\picture\\fruit_mask1.bmp");
	}
	else if (ChoiceBGPic == 2) {
		ElementPath = _T("theme\\picture\\fruit_element2.bmp");
		MaskPath = _T("theme\\picture\\fruit_mask2.bmp");
	}
	else if (ChoiceBGPic == 3)
	{
		ElementPath = _T("theme\\picture\\fruit_element.bmp");
		MaskPath = _T("theme\\picture\\fruit_mask.bmp");
	}

	if (isMusicOn == TRUE)
	{
		PlaySound(strFilepath, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	} else if (isMusicOn == FALSE) {
		PlaySound(NULL, NULL, SND_FILENAME);
	}
	CDialogEx::OnOK();
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	slide.SetRange(0, 100);//设置滑动范围为1到20
	slide.SetTicFreq(1);//每1个单位画一刻度

	SetCheckBox();

	CoInitialize(0);
	nVolume = GetVolume();
	CoUninitialize();
	slide.SetPos(nVolume);//设置滑块初始位置为1
	volume = nVolume;
	UpdateData(FALSE);

	CString str;
	str.Format(_T("  %d"), volume);
	VolumeShow.SetWindowText(str);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CSettingDlg::OnBnClickedBtnMusicOnandclose()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isMusicOn == TRUE)
	{
		GetDlgItem(IDC_BTN_MUSIC_ONANDCLOSE)->SetWindowText((CString)"音乐关");
		GetDlgItem(IDC_CHECK_MUSIC1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MUSIC2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MUSIC3)->EnableWindow(FALSE);
		GetDlgItem(IDC_MUSIC_SLIDER)->EnableWindow(FALSE);
		isMusicOn = FALSE;
	} else {
		GetDlgItem(IDC_BTN_MUSIC_ONANDCLOSE)->SetWindowText((CString)"音乐开");
		GetDlgItem(IDC_CHECK_MUSIC1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_MUSIC2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_MUSIC3)->EnableWindow(TRUE);
		GetDlgItem(IDC_MUSIC_SLIDER)->EnableWindow(TRUE);
		isMusicOn = TRUE;
	}
}


void CSettingDlg::OnBnClickedCheckMusic1()
{
	// TODO: 在此添加控件通知处理程序代码
	ChoiceMusic = 1;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC2);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC3);
	pBtn->SetCheck(0);

	//加载音乐
	strFilepath = (CString)"theme\\music\\music1.wav";
	//LoadMusic(this->m_hWnd, strFilepath);
	
}


void CSettingDlg::OnBnClickedCheckMusic2()
{
	// TODO: 在此添加控件通知处理程序代码
	ChoiceMusic = 2;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC1);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC3);
	pBtn->SetCheck(0);

	//加载音乐
	strFilepath = (CString)"theme\\music\\music2.wav";
	
}


void CSettingDlg::OnBnClickedCheckMusic3()
{
	// TODO: 在此添加控件通知处理程序代码
	ChoiceMusic = 3;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC1);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC2);
	pBtn->SetCheck(0);

	//加载音乐
	strFilepath = (CString)"theme\\music\\music3.wav";
	//LoadMusic(this->m_hWnd, strFilepath);
}


void CSettingDlg::OnBnClickedCheckBgpic1()
{
	// TODO: 在此添加控件通知处理程序代
	ChoiceBGPic = 1;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC2);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC_NONE);
	pBtn->SetCheck(0);
}


void CSettingDlg::OnBnClickedCheckBgpic2()
{
	// TODO: 在此添加控件通知处理程序代码
	ChoiceBGPic = 2;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC1);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC_NONE);
	pBtn->SetCheck(0);
}


void CSettingDlg::OnBnClickedCheckBgpicNone()
{
	// TODO: 在此添加控件通知处理程序代码
	ChoiceBGPic = 3;
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC1);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC2);
	pBtn->SetCheck(0);
}


void CSettingDlg::OnBnClickedBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



// //专门为主页面的高级玩意页面设置
void CSettingDlg::DoLinkGameDlg()
{
	// TODO: 在此处添加实现代码.
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC2);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC_NONE);
	pBtn->SetCheck(0);
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC1);
	pBtn->SetCheck(0);
}


void CSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);
	volume = slide.GetPos();
	CoInitialize(0);
	nVolume = SetVolum(volume);
	CoUninitialize();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	UpdateData(FALSE);
}


// 设置音量
bool CSettingDlg::SetVolum(int volume)
{
	HRESULT hr;
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	IMMDevice* pDevice = 0;
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	IAudioClient* pAudioClient = 0;

	try {
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
		if (FAILED(hr)) throw "CoCreateInstance";
		hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
		if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
		hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
		if (FAILED(hr)) throw "pDevice->Active";
		hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
		if (FAILED(hr)) throw "pDevice->Active";

		float fVolume;
		fVolume = volume / 100.0f;
		hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
		if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";

		pAudioClient->Release();
		pAudioEndpointVolume->Release();
		pDevice->Release();
		pDeviceEnumerator->Release();

		CString str;
		str.Format(_T("  %d"), volume);
		VolumeShow.SetWindowText(str);

		return true;
	}

	catch (...) {
		if (pAudioClient) pAudioClient->Release();
		if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
		if (pDevice) pDevice->Release();
		if (pDeviceEnumerator) pDeviceEnumerator->Release();
		throw;
	}
	return false;
}


int CSettingDlg::GetVolume()
{
	// TODO: 在此处添加实现代码.
	HRESULT hr;
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	IMMDevice* pDevice = 0;
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	IAudioClient* pAudioClient = 0;

	try {
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
		if (FAILED(hr)) throw "CoCreateInstance";
		hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
		if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
		hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
		if (FAILED(hr)) throw "pDevice->Active";
		hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
		if (FAILED(hr)) throw "pDevice->Active";


		float fVolume;


		hr = pAudioEndpointVolume->GetMasterVolumeLevelScalar(&fVolume);

		if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";


		pAudioClient->Release();
		pAudioEndpointVolume->Release();
		pDevice->Release();
		pDeviceEnumerator->Release();


		int  intVolume = fVolume * 100;
		if (fVolume > 100)
		{
			fVolume = 100;
		}
		return intVolume;

	}
	catch (...) {
		if (pAudioClient) pAudioClient->Release();
		if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
		if (pDevice) pDevice->Release();
		if (pDeviceEnumerator) pDeviceEnumerator->Release();
		throw;
	}
}


// 设置按钮状态
void CSettingDlg::SetCheckBox()
{
	VolumeShow.SetReadOnly(TRUE);
	//设置音乐按钮
	if (isMusicOn == TRUE)
	{
		GetDlgItem(IDC_BTN_MUSIC_ONANDCLOSE)->SetWindowText((CString)"音乐开");
		GetDlgItem(IDC_CHECK_MUSIC1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_MUSIC2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_MUSIC3)->EnableWindow(TRUE);
		GetDlgItem(IDC_MUSIC_SLIDER)->EnableWindow(TRUE);
		if (ChoiceMusic == 1) {
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC1);
			pBtn->SetCheck(1);
			pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC2);
			pBtn->SetCheck(0);
			pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC3);
			pBtn->SetCheck(0);
		}
		else if (ChoiceMusic == 2)
		{
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC1);
			pBtn->SetCheck(0);
			pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC2);
			pBtn->SetCheck(1);
			pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC3);
			pBtn->SetCheck(0);
		}
		else if(ChoiceMusic == 3)
		{
			CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC1);
			pBtn->SetCheck(0);
			pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC2);
			pBtn->SetCheck(0);
			pBtn = (CButton*)GetDlgItem(IDC_CHECK_MUSIC3);
			pBtn->SetCheck(1);
		}
	}
	else {
		GetDlgItem(IDC_BTN_MUSIC_ONANDCLOSE)->SetWindowText((CString)"音乐关");
		GetDlgItem(IDC_CHECK_MUSIC1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MUSIC2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_MUSIC3)->EnableWindow(FALSE);
		GetDlgItem(IDC_MUSIC_SLIDER)->EnableWindow(FALSE);
	}
	
	if (ChoiceBGPic == 1)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC1);
		pBtn->SetCheck(1);
		pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC2);
		pBtn->SetCheck(0);
		pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC_NONE);
		pBtn->SetCheck(0);
	}
	else if (ChoiceBGPic == 2)
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC1);
		pBtn->SetCheck(0);
		pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC2);
		pBtn->SetCheck(1);
		pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC_NONE);
		pBtn->SetCheck(0);
	}
	else
	{
		CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC1);
		pBtn->SetCheck(0);
		pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC2);
		pBtn->SetCheck(0);
		pBtn = (CButton*)GetDlgItem(IDC_CHECK_BGPIC_NONE);
		pBtn->SetCheck(1);
	}
}
