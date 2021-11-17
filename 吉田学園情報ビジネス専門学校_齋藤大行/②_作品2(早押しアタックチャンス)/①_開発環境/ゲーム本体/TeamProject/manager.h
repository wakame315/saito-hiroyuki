//=============================================================================
//
// マネージャー定義 [manager.h]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "polygon.h"
#include "protocol_ranking.h"
#include "sound.h"

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CNumber;
class CDisplaytime;
class CTitle;
class CTutorial;
class CResult;

//=============================================================================
// クラス定義
//=============================================================================
class CManager//マネージャークラス
{
public:
	
	//==============================================
	//列挙型宣言
	//==============================================
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_END,
	}MODE;
	CManager();																//コンストラクタ
	~CManager();															//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);				//初期化処理
	void Update(void);														//更新処理
	void Draw(void);														//描画処理
	void Uninit(void);														//終了処理
	void TextureLoad(void);													//テクスチャロード
	void TextureUnLoad(void);												//テクスチャアンロード
	static void SetMode(MODE mode);											//モード設定
	static MODE GetMode(void);												//モード所得
	static CManager *Create(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//作成処理
	static CRenderer *GetRenderer(void);									//レンダラー所得
	static CInputKeyboard *GetInputKeyboard(void);							//キーボード所得
	static CRanking::RankingData * GetRankinData(void);						//ランキング所得
	static bool GetGameEnd(void);											//ゲーム終了判定所得
	static DWORD GeResultTime(void);										//結果時間所得
	static CSound *GetSound(void);											//サウンド所得
	CPolygon *GetPlayer(void);												//プレイヤー所得
	
private:
	static DWORD m_Gettime;													//結果時間保存用
	static CRenderer *m_pRenderer;											//レンダラー
	static CInputKeyboard *m_pInputKeyboard;								//キーボード入力
	static MODE m_Mode;														//モード
	static CTitle*m_pTitle;													//タイトル
	static CTutorial*m_pTutorial;											//チュートリアル
	static CResult*m_pResult;												//リザルト
	static CRanking::RankingData m_RankingDeta[MAX_RANKING];				//ランキング
	static bool m_bGameEnd;													//ゲーム終了判定
	static CSound *m_pSound;												//サウンド
	CPolygon * m_pPlayer;													//プレイヤー

	int m_nGameEndState;													//ゲーム終了遷移カウント
};

#endif