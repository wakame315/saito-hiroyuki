//=============================================================================
//
// メイン定義 [main.h]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include<windows.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include"d3dx9.h"

//=============================================================================
// ライブラリファイルリンク
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//=============================================================================
//マクロ定義
//=============================================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define NUM_VERTEX (4)
#define NUM_POLYGON (2)
#define MAX_SCENE (1024)
#define TEXTURE_WIDTH  (75)
#define TEXTURE_HEIGHT (75)
#define NONE_CLO 255

#define TEXTURE_NAME1 "data/TEXTURE/棒人間 改2.png"
#define TEXTURE_NAME2 "data/TEXTURE/bullet001.PNG"
#define TEXTURE_NAME3 "data/TEXTURE/explosion000.png"
#define TEXTURE_NAME4 "data/TEXTURE/bg100.png"
#define TEXTURE_NAME5 "data/TEXTURE/bg101.png"
#define TEXTURE_NAME6 "data/TEXTURE/bg102.png"
#define TEXTURE_NAME7 "data/TEXTURE/enemy000.png"
#define TEXTURE_NAME8 "data/TEXTURE/enemy001.png"
#define TEXTURE_NAME9 "data/TEXTURE/enemy002.png"
#define TEXTURE_NAME10 "data/TEXTURE/enemy003.png"
#define TEXTURE_NAME11 "data/TEXTURE/enemy004.png"
#define TEXTURE_NAME12 "data/TEXTURE/enemy005.png"
#define TEXTURE_NAME13 "data/TEXTURE/number000.png"
#define TEXTURE_NAME14 "data/TEXTURE/タイトル.png"
#define TEXTURE_NAME15 "data/TEXTURE/gameover.png"
#define TEXTURE_NAME16 "data/TEXTURE/ゲームクリア.png"
#define TEXTURE_NAME17 "data/TEXTURE/life000.png"
#define TEXTURE_NAME18 "data/TEXTURE/チュートリアル.png"

#define PRIORITY_MAX 5
#define PLAYER_SIZE_X (75)
#define PLAYER_SIZE_Y (75)
#define PLAYER_MAX_LIFE (8)
#define PLAYER_BULLET_SIZE (15)
#define PLAYER_BULLET_LIFE (25)
#define ENEMY_MAX_LIFE (10)
#define ENEMY_INIT_LIFE (3)
#define ENEMY_RARE_INIT_LIFE (5)
#define ENEMY_BULLET_SIZE (25)
#define ENEMY_BULLET_LIFE (30)
#define ENEMY_BULLET_LIFE_2 (20)
#define ENEMY_SIZE (70)
#define ENEMY_RARE_SIZE (85)


#define EXPLOSION_SIZE (65)
#define POLYGON_SIZE_X (75)
#define POLYGON_SIZE_Y (75)
#define NUM_SIZE_X (25)
#define NUM_SIZE_Y (50)
#define LIFE_SIZE (45)
#define MAX_ENEMY (6)
#define MAX_NUM (7)
#define MAX_EXPLOSION_TEXTURE (2)
#define MAXBULLET (2)
#define ADD_SCORE_UP (300)
#define ADD_SCORE_MAX (1500)
#define RESULT_TEXTURE (2)


#define Si
//#undef Si
//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CScene;

//プロトタイプ宣言
int GetFPS(void);
//CRenderer *GetRenderer(void);
//CScene    ** GetScene(void);

//=============================================================================
//構造体
//=============================================================================
typedef struct
{
	D3DXVECTOR3 Pos;
	float rhw;
	D3DCOLOR clo;
	D3DXVECTOR2 tex;

}VERTEX_2D;

#endif