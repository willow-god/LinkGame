#include "pch.h"
#include "CGimeLogic.h"
#include "CGameControl.h"
#include "global.h"


// ��ʼ����Ϸ��ͼ����
int** CGimeLogic::InitMap()
{
    // TODO: �ڴ˴����ʵ�ִ���.
    //��ȡ��ͼ��С�ͻ�ɫ
    int nRows /*= CGameControl::s_nRows*/;
    int nCols /*= CGameControl::s_nCols*/;
    int nPicNum /*= CGameControl::s_nPicNum*/;

    nRows = MAX_ROW;
    nCols = MAX_COL;
    nPicNum = MAX_PIC_NUM;

    //�����ڴ�����
    int** pGameMap = new int* [nRows];
    if (NULL == pGameMap)
    {
        printf("�ڴ�����쳣\n");
        throw;
    }
    else
    {
        for (int i = 0; i < nRows; i++)
        {
            pGameMap[i] = new int[nCols];
            if (NULL == pGameMap) {
                printf("�ڴ�����쳣\n");
                throw;
            }
            memset(pGameMap[i], NULL, sizeof(int) * nCols);
        }
    }

    //���ٻ�ɫ
    if ((nRows * nCols) % nPicNum != 0)
    {
        ReleaseMap(pGameMap);
        printf("��Ϸ��ɫ����Ϸ��ͼ��С��ƥ��");
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

    //��������
    srand((int)time(NULL));

    //���⽻����������
    int nVertexNum = nRows * nCols;
    for (int i = 0; i < nVertexNum; i++)
    {
        int nIndex1 = rand() % nVertexNum;
        int nIndex2 = rand() % nVertexNum;

        //������ֵ
        int nTmp = pGameMap[nIndex1 / nCols][nIndex1 % nCols];
        pGameMap[nIndex1 / nCols][nIndex1 % nCols] = pGameMap[nIndex2 / nCols][nIndex2 % nCols];
        pGameMap[nIndex2 / nCols][nIndex2 % nCols] = nTmp;
    }
    return pGameMap;
}


// �ͷ��ڴ�
void CGimeLogic::ReleaseMap(int** pGameMap)
{ 
    // TODO: �ڴ˴����ʵ�ִ���.
    for (int i = 0; i < MAX_ROW; i++)
    {
        delete[] pGameMap[i];
    }
    delete[] pGameMap;
}

//�ж�����֮���߼����Ƿ����ӵȵ�
bool CGimeLogic::IsLink(int** m_MapGraph, Vertex firVex, Vertex SecVex)
{
    // TODO: �ڴ˴����ʵ�ִ���.

    return false;
}




void CGimeLogic::PushVertex(int nV)
{
    // TODO: �ڴ˴����ʵ�ִ���.
    m_anPath[m_nVexNum] = nV;
    m_nVexNum++;

    // �ж��Ƿ��γ��µĹյ�
   /* if (IsCorner())
    {
        m_nCorner++;
    }*/
}


void CGimeLogic::PopVertex()
{
    // TODO: �ڴ˴����ʵ�ִ���.
    /*if (IsCorner())
    {
        m_nCorner--;
    }*/
    m_nVexNum--;
}


int CGimeLogic::GetVexPath(Vertex* avPath)
{
    // TODO: �ڴ˴����ʵ�ִ���.
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




// ��������ҳ���ϵ�ͼƬ
void CGimeLogic::Clear(int** m_MapGraph, Vertex v1, Vertex v2)
{
    // TODO: �ڴ˴����ʵ�ִ���.
    m_MapGraph[v1.row][v1.col] = BLANK;
    m_MapGraph[v2.row][v2.col] = BLANK;
}


// ����ͼ������
void CGimeLogic::UpdateArc(int** m_MapGraph, int nRow, int nCol)
{
    // TODO: �ڴ˴����ʵ�ִ���.

}
