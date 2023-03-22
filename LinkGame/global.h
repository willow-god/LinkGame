#pragma once // 为了防止头文件被重复包含
#ifndef _GLOBAL_H_
typedef struct tagVertex
{
	int row;  // 行
	int col;  // 列
	int info; // 信息类
} Vertex;

#define BLANK -1
#define MAX_ROW 15		   // 初始行数
#define MAX_COL 26		   // 初始列数
#define MAX_VERTEX_NUM 390 // 顶点数
#define MAX_PIC_NUM 15	   // 图片花色
#define REPEAT_NUM 8	   // 每种花色图片个数
#define MAP_TOP 150		   // 游戏地图左上角纵坐标
#define MAP_LEFT 200		   // 游戏地图左上角横坐标
#define PIC_HEIGHT 40	   // 游戏地图高度
#define PIC_WIDTH 40	   // 游戏地图宽度

#define TIME 1200 // 时间
#define PLAY_TIMER_ID 1 // 计时器的编号

#define GAME_LOSE -1   // 失败
#define GAME_SUCCESS 0 // 获胜
#define GAME_PLAY 1	   // 游戏正在进行

#endif // _GLOBAL_H_
