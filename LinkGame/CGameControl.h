#pragma once
#include "global.h"
#include  "CGimeLogic.h"
#include "CGraph.h"
class CGameControl
{
public:
	int** m_pGameMap; // 游戏地图
	Vertex m_svSelFst; // 第一次选中的点
	Vertex m_svSelSec; // 第二次选中的点
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
public:
	void StartGame(void);									// 开始游戏
	int GetElement(int nRow, int nCol);						/// 获得某行某列的图片编号
	void SetFirstPoint(int nRow, int nCol);					// 设置第一个点的坐标
	void SetSecPoint(int nRow, int nCol);					// 设置第二个点的坐标
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum); // 连接判断函数
										// 判断是否胜利
	bool Help(Vertex pPathMap[MAX_VERTEX_NUM], int& nVexnum); // 在地图中查找可以消除的一堆照片，返回连接路径和路径上的顶点数
	void Resert();											// 调用函数，对数据成员m_graph中的数据进行重排
	bool LinkInOneLine(Vertex* avPath, int& nVexNum);
	bool LinkInTwoLine(Vertex* avPath, int& nVexNum);
	bool LinkInThreeLine(Vertex* avPath, int& nVexNum);
	bool IsWin(int time);
};
