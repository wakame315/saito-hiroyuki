//=============================================================================
//
// ポリゴン定義 [polygon.h]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CPolygon : public CScene2d//ポリゴンクラス
{
public:
	typedef enum
	{
		TEX_SIGNAL_NONE,
		TEX_SIGNAL_GO,
		TEX_SIGNAL_MISS,
	}TEX_SIGNAL;

	CPolygon();																		//コンストラクタ
	~CPolygon();																	//デストラクタ
	static HRESULT Load(void);														//テクスチャロード
	static void Unload(void);														//テクスチャアンロード
	HRESULT Init(TEX_SIGNAL signal);												//初期化処理
	void Uninit(void);																//終了処理
	void Update(void);																//更新処理
	void Draw(void);																//描画処理
	void SetTexSignal(TEX_SIGNAL signal);											//合図のテクスチャ設定
	bool SetbUse(bool bUse);														//合図を使うかどうか設定
	TEX_SIGNAL GetTexSignal(void) { return m_tSignal; }								//合図の所得
	bool GetUse(void);																//合図を使っているか所得
	int GetRandom(void);															//乱数の所得
		
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEX_SIGNAL signal);	//生成処理
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_SIGNAL];								//テクスチャのポインタ
	TEX_SIGNAL m_tSignal;															//合図の種類
	bool m_buse;																	//使っているか
	int m_nUseNum;																	//合図の表示時間
	int m_nOnePlay;																	//一度だけ読み込むためのフラグ
};
#endif 
