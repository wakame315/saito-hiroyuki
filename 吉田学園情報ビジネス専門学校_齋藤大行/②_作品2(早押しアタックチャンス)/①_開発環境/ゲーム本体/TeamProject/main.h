//=============================================================================
//
// メイン処理 [main.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include<WinSock2.h>
#include<windows.h>
#include<dinput.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include"d3dx9.h"

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "ws2_32.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define NUM_VERTEX (4)
#define NUM_POLYGON (2)
#define MAX_POLYGON (1024)
#define TEXTURE_WIDTH  (75)
#define TEXTURE_HEIGHT (75)
#define NONE_CLO 255

#define TEXTURE_NAME1 "Resource/TEXTURE/signal.png"
#define TEXTURE_NAME2 "Resource/TEXTURE/バツマーク.png"
#define TEXTURE_NAME3 "Resource/TEXTURE/Background.png"
#define TEXTURE_NAME4 "Resource/TEXTURE/pose_woman.png"
#define TEXTURE_NAME5 "Resource/TEXTURE/target.png"
#define TEXTURE_NAME6 "Resource/TEXTURE/title.png"
#define TEXTURE_NAME7 "Resource/TEXTURE/title_rogo2.png"
#define TEXTURE_NAME8 "Resource/TEXTURE/explain_rules.png"
#define TEXTURE_NAME9 "Resource/TEXTURE/gameover.png"
#define TEXT_NEMA1    "Resource/TEXT/NAME.txt"

#define PRIORITY_MAX 5
#define BULLET_SIZE (15)
#define EXPLOSION_SIZE (65)
#define POLYGON_SIZE_X (200)
#define POLYGON_SIZE_Y (200)
#define MAX_ENEMY (6)
#define MAX_NUM (7)
#define MAX_SIGNAL (2)
#define MAX_RAND (10)
#define MIN_RAND (5)
#define MAX_TIME (10000)
#define MIN_TIME (5000)

#define MAX_RANKING (10)
#define MAX_NAME 15					// 名前サイズ

#define SERVER_PORT_NUM 12345
#define MAX_ACCEPT_CONNECTION 5
#define BUFFER_NUM 1024
//#undef _DEBUG
//#define SU

//*********************************************************
// 前方宣言
//*********************************************************
class CRenderer;
class CScene;

//プロトタイプ宣言
int GetFPS(void);
//CRenderer *GetRenderer(void);
//CScene    ** GetScene(void);

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 Pos;
	float rhw;
	D3DCOLOR clo;
	D3DXVECTOR2 tex;

}VERTEX_2D;

#endif