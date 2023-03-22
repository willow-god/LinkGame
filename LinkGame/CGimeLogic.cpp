#include "pch.h"
#include "CGimeLogic.h"
#include "CGameControl.h"
#include "global.h"


// 初始化游戏地图函数
int** CGimeLogic::InitMap()
{
    // TODO: 在此处添加实现代码.
    //获取地图大小和花色
    int nRows /*= CGameControl::s_nRows*/;
    int nCols /*= CGameControl::s_nCols*/;
    int nPicNum /*= CGameControl::s_nPicNum*/;

    nRows = MAX_ROW;
    nCols = MAX_COL;
    nPicNum = MAX_PIC_NUM;

    //开辟内存区域
    int** pGameMap = new int* [nRows];
    if (NULL == pGameMap)
    {
        printf("内存操作异常\n");
        throw;
    }
    else
    {
        for (int i = 0; i < nRows; i++)
        {
            pGameMap[i] = new int[nCols];
            if (NULL == pGameMap) {
                printf("内存操作异常\n");
                throw;
            }
            memset(pGameMap[i], NULL, sizeof(int) * nCols);
        }
    }

    //多少花色
    if ((nRows * nCols) % nPicNum != 0)
    {
        ReleaseMap(pGameMap);
        printf("游戏花色和游戏地图大小不匹配");
        throw;
    }

    int nRepeatNum = nRows * nCols / nPicNum;
    int nCount = 0;
    for (int i = 0; i < nPicNum; i++)
    {
        for (int j = 0; j < nRepeatNum; j++)
        {
            pGameMap[nCount / nCols][nCount % nCols] = i;
            nCount++;
        }
    }

    //设置种子
    srand((int)time(NULL));

    //任意交换两个数字
    int nVertexNum = nRows * nCols;
    for (int i = 0; i < nVertexNum; i++)
    {
        int nIndex1 = rand() % nVertexNum;
        int nIndex2 = rand() % nVertexNum;

        //交换数值
        int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
        pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
        pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
    }
    return pGameMap;
}


// 释放内存
void CGimeLogic::ReleaseMap(int** pGameMap)
{ 
    // TODO: 在此处添加实现代码.
    for (int i = 0; i < MAX_ROW; i++)
    {
        delete[] pGameMap[i];
    }
    delete[] pGameMap;
}

//判断两点之间逻辑，是否连接等等
bool CGimeLogic::IsLink(int** m_MapGraph, Vertex firVex, Vertex SecVex)
{
    // TODO: 在此处添加实现代码.

    return false;
}




void CGimeLogic::PushVertex(int nV)
{
    // TODO: 在此处添加实现代码.
    m_anPath[m_nVexNum] = nV;
    m_nVexNum++;

    // 判断是否形成新的拐点
   /* if (IsCorner())
    {
        m_nCorner++;
    }*/
}


void CGimeLogic::PopVertex()
{
    // TODO: 在此处添加实现代码.
    /*if (IsCorner())
    {
        m_nCorner--;
    }*/
    m_nVexNum--;
}


int CGimeLogic::GetVexPath(Vertex* avPath)
{
    // TODO: 在此处添加实现代码.
    Vertex point;
    for (int i = 0; i < m_nVexNum; i++)
        for (point.col = 0; point.col < MAX_COL; point.col++)
        {
            for (point.row = 0; point.row < MAX_ROW; point.row++)
            {
                if (point.row * MAX_COL + point.col == m_anPath[i])
                {
                    avPath[i] = point;
                }
            }
        }
    return m_nVexNum;
}




// 消除子在页面上的图片
void CGimeLogic::Clear(int** m_MapGraph, Vertex v1, Vertex v2)
{
    // TODO: 在此处添加实现代码.
    m_MapGraph[v1.row][v1.col] = BLANK;
    m_MapGraph[v2.row][v2.col] = BLANK;
}


// 生成图边数组
void CGimeLogic::UpdateArc(int** m_MapGraph, int nRow, int nCol)
{
    // TODO: 在此处添加实现代码.

}
