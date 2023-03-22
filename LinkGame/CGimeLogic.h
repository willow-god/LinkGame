#pragma once
#include "global.h"
#include "CGraph.h"
class CGimeLogic
{
public:
	Vertex m_avPath[MAX_VERTEX_NUM]; // �����ڽ��������ж�ʱ�������Ķ���
	int m_anPath[MAX_VERTEX_NUM];	 // ������ͨ·���Ķ�������
	int m_nVexNum;					 // ������
	int m_nCorner;					 // ����·������m_anPath�еĹյ���

	// ��ʼ����Ϸ��ͼ����
	int** InitMap();
	// �ͷ��ڴ�
	void ReleaseMap(int** pGameMap);
	bool IsLink(int** m_MapGraph, Vertex firVex, Vertex SecVex);
	void PushVertex(int nV);
	void PopVertex();
	int GetVexPath(Vertex* avPath);
	// ��������ҳ���ϵ�ͼƬ
	void Clear(int** m_MapGraph, Vertex v1, Vertex v2);
	// ����ͼ������
	void UpdateArc(int** m_MapGraph, int nRow, int nCol);
};

