#pragma once
#include "global.h"
#include  "CGimeLogic.h"
#include "CGraph.h"
class CGameControl
{
public:
	int** m_pGameMap; // ��Ϸ��ͼ
	Vertex m_svSelFst; // ��һ��ѡ�еĵ�
	Vertex m_svSelSec; // �ڶ���ѡ�еĵ�
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
public:
	void StartGame(void);									// ��ʼ��Ϸ
	int GetElement(int nRow, int nCol);						/// ���ĳ��ĳ�е�ͼƬ���
	void SetFirstPoint(int nRow, int nCol);					// ���õ�һ���������
	void SetSecPoint(int nRow, int nCol);					// ���õڶ����������
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum); // �����жϺ���
										// �ж��Ƿ�ʤ��
	bool Help(Vertex pPathMap[MAX_VERTEX_NUM], int& nVexnum); // �ڵ�ͼ�в��ҿ���������һ����Ƭ����������·����·���ϵĶ�����
	void Resert();											// ���ú����������ݳ�Աm_graph�е����ݽ�������
	bool LinkInOneLine(Vertex* avPath, int& nVexNum);
	bool LinkInTwoLine(Vertex* avPath, int& nVexNum);
	bool LinkInThreeLine(Vertex* avPath, int& nVexNum);
	bool IsWin(int time);
};
