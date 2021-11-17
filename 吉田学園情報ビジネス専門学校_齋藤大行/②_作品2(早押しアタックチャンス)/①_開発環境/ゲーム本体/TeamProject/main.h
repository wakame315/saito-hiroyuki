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
#include<WinSock2.h>
#include<windows.h>
#include<dinput.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include"d3dx9.h"

//=============================================================================
// ライブラリファイルリンク
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "ws2_32.lib")
//=============================================================================
//マクロ定義
//=============================================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)	
#define SCREEN_WIDTH	(1280)								//ウィンドサイズ横
#define SCREEN_HEIGHT	(720)								//ウィンドサイズ縦
#define NUM_VERTEX (4)										//頂点数
#define NUM_POLYGON (2)										//ポリゴン数
#define MAX_POLYGON (1024)									//ポリゴンの最大数
#define TEXTURE_WIDTH  (75)									//テクスチャの横サイズ
#define TEXTURE_HEIGHT (75)									//テクスチャの縦サイズ
#define NONE_CLO 255										//カラーの初期値

#define TEXTURE_NAME1 "Resource/TEXTURE/signal.png"			//合図
#define TEXTURE_NAME2 "Resource/TEXTURE/バツマーク.png"		//お手付き
#define TEXTURE_NAME3 "Resource/TEXTURE/Background.png"		//背景
#define TEXTURE_NAME4 "Resource/TEXTURE/pose_woman.png"		//キャラクター
#define TEXTURE_NAME5 "Resource/TEXTURE/target.png"			//的
#define TEXTURE_NAME6 "Resource/TEXTURE/title.png"			//タイトル
#define TEXTURE_NAME7 "Resource/TEXTURE/title_rogo2.png"	//タイトルlogo
#define TEXTURE_NAME8 "Resource/TEXTURE/explain_rules.png"	//チュートリアル
#define TEXT_NEMA1    "Resource/TEXT/NAME.txt"				//名前読み込み用FILE

			
#define PRIORITY_MAX 5										//プライオリティ最大数
#define POLYGON_SIZE_X (200)								//ポリゴンサイズ横
#define POLYGON_SIZE_Y (200)								//ポリゴンサイズ縦
#define MAX_SIGNAL (2)										//合図の最大数
#define MAX_RAND (10)										//乱数最大値
#define MIN_RAND (5)										//乱数最低値
#define MAX_TIME (10000)									//時間最大数
#define MIN_TIME (5000)										//時間最低数

#define MAX_RANKING (10)									//ランキング数
#define MAX_NAME 15											// 名前サイズ(文字数)

#define SERVER_PORT_NUM 12345								//ポート番号
#define MAX_ACCEPT_CONNECTION 5								//最大接続数
#define BUFFER_NUM 1024										//データ最大数
//#undef _DEBUG


//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CScene;

//プロトタイプ宣言
int GetFPS(void);


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