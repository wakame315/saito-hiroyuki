#ifndef _MIN_H_
#define _MIN_H_

#define _CRT_SECURE_NO_WARNINGS

#pragma comment (lib,"ws2_32.lib")
//==============================================
//インクルードファイル
//==============================================
#include<WinSock2.h>
#include<stdio.h>
#include"tcp_server.h"
#include"tcp_client.h"
#include "protocol_ranking.h"

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct
{
	int nClearTime;
	char aName[MAX_NAME];
} RankingData;

#endif // _MIN_H_