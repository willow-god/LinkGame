#pragma once // Ϊ�˷�ֹͷ�ļ����ظ�����
#ifndef _GLOBAL_H_
typedef struct tagVertex
{
	int row;  // ��
	int col;  // ��
	int info; // ��Ϣ��
} Vertex;

#define BLANK -1
#define MAX_ROW 15		   // ��ʼ����
#define MAX_COL 26		   // ��ʼ����
#define MAX_VERTEX_NUM 390 // ������
#define MAX_PIC_NUM 15	   // ͼƬ��ɫ
#define REPEAT_NUM 8	   // ÿ�ֻ�ɫͼƬ����
#define MAP_TOP 150		   // ��Ϸ��ͼ���Ͻ�������
#define MAP_LEFT 200		   // ��Ϸ��ͼ���ϽǺ�����
#define PIC_HEIGHT 40	   // ��Ϸ��ͼ�߶�
#define PIC_WIDTH 40	   // ��Ϸ��ͼ���

#define TIME 1200 // ʱ��
#define PLAY_TIMER_ID 1 // ��ʱ���ı��

#define GAME_LOSE -1   // ʧ��
#define GAME_SUCCESS 0 // ��ʤ
#define GAME_PLAY 1	   // ��Ϸ���ڽ���

#endif // _GLOBAL_H_
