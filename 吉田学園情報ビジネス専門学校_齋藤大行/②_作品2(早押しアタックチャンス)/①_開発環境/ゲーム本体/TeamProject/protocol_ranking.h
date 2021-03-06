//=============================================================================
//
// タッチナンバーゲームの通信プロトコル定義 [protocol_ranking.h]
// Author : NOBUYOSHI CHIBA
//
//=============================================================================
#ifndef _PROTOCOL_RANKING_H_
#define _PROTOCOL_RANKING_H_

//==============================================
//インクルードファイル
//==============================================
#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define IPADDRESSSERVER "13.78.94.222"
#define IPADDRESS "127.0.0.1"

class CRanking
{
public:
	//*****************************************************************************
	// 構造体宣言
	//*****************************************************************************
	typedef struct
	{
		int nClearTime;
		int nRank;
		char aName[MAX_NAME];
	} RankingData;


	//*****************************************************************************
	// 列挙型宣言
	//*****************************************************************************
	typedef enum
	{
		COMMAND_TYPE_NONE = 0,
		COMMAND_TYPE_GET_RANKING,		// ランキング一覧を取得
		COMMAND_TYPE_SET_RANKING		// ランキングを設定
	} COMMAND_TYPE;

	CRanking();
	~CRanking();
	//********************************************
	//プロトタイプ宣言
	//********************************************
	void ReadFile(void);
	static HRESULT FontCreate(void);
	static void FontUninit(void);
	static int SetRanking(int nTime);//ランキング登録
	static void GetRanking(RankingData * pRankingData);//ランキング登録
	static void Ranking(RankingData * RankingData, int Rank);//順位設定
private:
	static LPD3DXFONT				m_pRankingFont;
	static LPD3DXFONT				m_pRankFont;
	char m_aName[10];

};
#endif
