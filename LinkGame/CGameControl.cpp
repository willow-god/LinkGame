#include "pch.h"
#include "CGameControl.h"
#include  "CGimeLogic.h"

// ��ʼ��Ϸ
void CGameControl::StartGame(void)
{
	CGimeLogic gameLogic;
	m_pGameMap = gameLogic.InitMap();
}

// ����Ԫ����Ϣ
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_pGameMap[nRow][nCol];
}

// ���õ�һ����
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
}

// ���õڶ�����
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

// �����ж�
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	if (m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col )
	{
		return false;
	}
	int nInfo1 = GetElement(m_svSelFst.row, m_svSelFst.col);
	int nInfo2 = GetElement(m_svSelSec.row, m_svSelSec.col);

	//�ж��������Ƿ�һ�£�ֻ��һ�²�������
	if (nInfo1 != nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK) {
		return false;
	}

	//����ʵ�ֵ�͵�֮����жϣ�
	if (LinkInOneLine(avPath,nVexnum)||
		LinkInTwoLine(avPath,nVexnum) || 
		LinkInThreeLine(avPath, nVexnum))
	{
		m_pGameMap[m_svSelFst.row][m_svSelFst.col] = -1;
		m_pGameMap[m_svSelSec.row][m_svSelSec.col] = -1;
		return true;
	}
	
	return false;
}

// �ڵ�ͼ�в��ҿ���������һ����Ƭ����������·����·���ϵĶ�����
bool CGameControl::Help(Vertex pPathMap[MAX_VERTEX_NUM], int& nVexnum)
{
	Vertex V1 = m_svSelFst;
	Vertex V2 = m_svSelSec;
	for (int i = 0; i < MAX_ROW*MAX_COL; i++)
	{
		for (int j = 0; j < MAX_ROW * MAX_COL; j++)
		{
			//��һ��������
			m_svSelFst.row = i % MAX_ROW;
			m_svSelFst.col = i / MAX_ROW;

			//�ڶ���������
			m_svSelSec.row = j % MAX_ROW;
			m_svSelSec.col = j / MAX_ROW;

			//�ж��Ƿ�������һ��
			if (i == j)	continue;
			if (Link(pPathMap,nVexnum))
			{
				m_svSelFst = V1;
				m_svSelSec = V2;
				return true;
			}
		}
	}
	return false;
}

// ʵ������
void CGameControl::Resert(void)
{
	srand((int)time(NULL));
	int nVertexNum = MAX_ROW * MAX_COL;
	for (int i = 0; i < nVertexNum; i++)
	{
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		int row1 = nIndex1 % MAX_ROW;
		int col1 = nIndex1 / MAX_ROW;

		int row2 = nIndex2 % MAX_ROW;
		int col2 = nIndex2 / MAX_ROW;

		//������ֵ
		int nTmp = m_pGameMap[row1][col1];
		m_pGameMap[row1][col1] = m_pGameMap[row2][col2];
		m_pGameMap[row2][col2] = nTmp;
	}
}

bool CGameControl::LinkInOneLine(Vertex* avPath, int& nVexNum)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	int nCol1 = m_svSelFst.col;
	int nCol2 = m_svSelSec.col;
	int nRow1 = m_svSelFst.row;
	int nRow2 = m_svSelSec.row;
	if (nRow1 == nRow2){
		for (int i = (nCol1>nCol2?nCol2:nCol1)+1; i <= (nCol1>nCol2 ? nCol1 : nCol2); i++){
			if (i == (nCol1 > nCol2 ? nCol1 : nCol2)) {
				avPath[nVexNum++] = m_svSelFst;
				avPath[nVexNum++] = m_svSelSec;
				return true;
			}
			if (m_pGameMap[nRow1][i] != -1)  break;
		}
	}
	else if(nCol1 == nCol2) {
		for (int i = (nRow1 > nRow2 ? nRow2 : nRow1)+1; i <= (nRow1>nRow2 ? nRow1 : nRow2); i++){
			if (i == (nRow1 > nRow2 ? nRow1 : nRow2)){
				avPath[nVexNum++] = m_svSelFst;
				avPath[nVexNum++] = m_svSelSec;
				return true;
			}
			if (m_pGameMap[i][nCol1] != -1)  break;
		}
	}
	return false;
}


bool CGameControl::LinkInTwoLine(Vertex* avPath, int& nVexNum)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	Vertex V1 = m_svSelFst;
	Vertex V2 = m_svSelSec;
	bool isLink;
	if (m_pGameMap[V1.row][V2.col] == BLANK ) {
		isLink = true;
		//�����Ƿ���ͨ
		for (int i = (V1.col > V2.col ? V2.col : V1.col) + 1; i < (V1.col > V2.col ? V1.col : V2.col); i++)
			if (m_pGameMap[V1.row][i] != -1) {
				isLink = false;
				break;
			}
			//�����Ƿ���ͨ	
		for (int i = (V1.row > V2.row ? V2.row : V1.row) + 1; i < (V1.row > V2.row ? V1.row : V2.row); i++)
			if (m_pGameMap[i][V2.col] != -1) {
				isLink = false;
				break;
			}

		//�ж��Ƿ������·��
		if (isLink)
		{
			Vertex Vmid;
			Vmid.row = V1.row;
			Vmid.col = V2.col;
			Vmid.info = -1;
			avPath[nVexNum++] = V1;
			avPath[nVexNum++] = Vmid;
			avPath[nVexNum++] = V2;
			return true;
		}
	}
	if (m_pGameMap[V2.row][V1.col] == BLANK) {
		isLink = true;
		//�����Ƿ���ͨ
		for (int i = (V1.col > V2.col ? V2.col : V1.col) + 1; i < (V1.col > V2.col ? V1.col : V2.col); i++)
			if (m_pGameMap[V2.row][i] != -1) {
				isLink = false;
				break;
			}
		//�����Ƿ���ͨ	
		for (int i = (V1.row > V2.row ? V2.row : V1.row) + 1; i < (V1.row > V2.row ? V1.row : V2.row); i++)
			if (m_pGameMap[i][V1.col] != -1) {
				isLink = false;
				break;
			}

		//�ж��Ƿ������·��
		if (isLink)
		{
			Vertex Vmid;
			Vmid.row = V2.row;
			Vmid.col = V1.col;
			Vmid.info = -1;
			avPath[nVexNum++] = V1;
			avPath[nVexNum++] = Vmid;
			avPath[nVexNum++] = V2;
			return true;
		}
	}
	else return false;
}


bool CGameControl::LinkInThreeLine(Vertex* avPath, int& nVexNum)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	Vertex V1 = m_svSelFst;
	Vertex V2 = m_svSelSec;

	//�ж��Ƿ����ͨ�������߽�������
	//����һ�������ҵ�һ����ͨ�ĵ㣬�ж�ÿһ�����Ƿ���Խ�����������
	for (int i = 0; i < MAX_ROW; i++)
	{
		m_svSelFst = V1;
		m_svSelSec = V2;

		Vertex Vmid;
		Vmid.row = i;
		Vmid.col = V1.col;
		Vmid.info = -1;

		if ((m_svSelFst.row == Vmid.row && m_svSelFst.col == Vmid.col)||
			(m_svSelSec.row == Vmid.row && m_svSelSec.col == Vmid.col))
		{
			continue;
		}

		if (m_pGameMap[i][V1.col] != -1)
		{
			continue;
		}
		m_svSelSec = Vmid;

		if (LinkInOneLine(avPath ,nVexNum) == true)
		{
			m_svSelSec = V2;
			m_svSelFst = Vmid;
			if (LinkInTwoLine(avPath, nVexNum) == true)
			{
				m_svSelFst = V1;
				m_svSelSec = V2;
				return true;
			}
			else {
				nVexNum = 0;
			}
		}
		else {
			nVexNum = 0;
		}
	}


	//����һ�������ҵ�һ����ͨ�ĵ㣬�ж�ÿһ�����Ƿ���Խ�����������
	for (int i = 0; i < MAX_COL; i++)
	{
		m_svSelFst = V1;
		m_svSelSec = V2;
		Vertex Vmid;
		Vmid.row = V1.row;
		Vmid.col = i; 
		Vmid.info = -1;
		if ((m_svSelFst.row == Vmid.row && m_svSelFst.col == Vmid.col) ||
			(m_svSelSec.row == Vmid.row && m_svSelSec.col == Vmid.col))
		{
			continue;
		}

		if (m_pGameMap[V1.row][i] != -1)
		{
			continue;
		}
		m_svSelSec = Vmid;

		if (LinkInOneLine(avPath, nVexNum) == true)
		{
			m_svSelSec = V2;
			m_svSelFst = Vmid;
			if (LinkInTwoLine(avPath, nVexNum) == true)
			{
				m_svSelFst = V1;
				m_svSelSec = V2;
				return true;
			}
			else {
				nVexNum = 0;
			}
		}
		else {
			nVexNum = 0;
		}
	}
	m_svSelFst = V1;
	m_svSelSec = V2;
	return false;
}


bool CGameControl::IsWin(int time)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	if (time<=0)
	{
		return GAME_LOSE;
	}

	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (m_pGameMap[i][j] != -1)
			{
				return GAME_PLAY;
			}
		}
	}


	return GAME_SUCCESS;
}
