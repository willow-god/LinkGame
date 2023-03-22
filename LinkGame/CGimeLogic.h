#pragma once
#include "global.h"
#include "CGraph.h"
class CGimeLogic
{
public:
	Vertex m_avPath[MAX_VERTEX_NUM]; // 保存在进行连接判断时所经过的顶点
	int m_anPath[MAX_VERTEX_NUM];	 // 保存连通路径的顶点索引
	int m_nVexNum;					 // 顶点数
	int m_nCorner;					 // 连接路径数组m_anPath中的拐点数

	// 初始化游戏地图函数
	int** InitMap();
	// 释放内存
	void ReleaseMap(int** pGameMap);
	bool IsLink(int** m_MapGraph, Vertex firVex, Vertex SecVex);
	void PushVertex(int nV);
	void PopVertex();
	int GetVexPath(Vertex* avPath);
	// 消除子在页面上的图片
	void Clear(int** m_MapGraph, Vertex v1, Vertex v2);
	// 生成图边数组
	void UpdateArc(int** m_MapGraph, int nRow, int nCol);
};

