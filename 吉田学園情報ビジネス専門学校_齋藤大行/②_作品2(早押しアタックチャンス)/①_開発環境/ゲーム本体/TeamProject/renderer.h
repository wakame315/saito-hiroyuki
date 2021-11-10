//=============================================================================
//
// レンダラー定義 [renderer.h]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include"main.h"
#include "protocol_ranking.h"
#include "manager.h"

//=============================================================================
// クラス定義
//=============================================================================
class CRenderer
{
public:
	CRenderer();												//コンストラクタ
	~CRenderer();												//デストラクタ
	HRESULT Init(HWND hWnd, bool bWindow);						//初期化処理
	void Uninit(void);											//終了処理
	void Update(void);											//更新処理
	void Draw(void);											//描画処理
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//デバイス所得

private:
	
	void DrawFPS(void);						// FPS表示
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
	int						m_nGameEnd;		// ゲーム終了判定
	static CRanking::RankingData * m_RankingDeta[MAX_RANKING];//ランキングポインタ

};
#endif
