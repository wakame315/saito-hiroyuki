//=============================================================================
//
// 通信プロトコル定義 [protocol_ranking.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _PROTOCOL_RANKING_H_
#define _PROTOCOL_RANKING_H_



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKING 10				// ランキングデータ数
#define MAX_NAME 15					// 名前サイズ
#define IPADDRESS "127.0.0.1"	    //piアドレス(ローカル)
#define IPADDRESSSERVER "13.78.94.222"//piアドレス()


//*****************************************************************************
// 列挙型宣言
//*****************************************************************************
typedef enum
{
	COMMAND_TYPE_NONE = 0,
	COMMAND_TYPE_GET_RANKING,		// ランキング一覧を取得
	COMMAND_TYPE_SET_RANKING		// ランキングを設定
} COMMAND_TYPE;

#endif
