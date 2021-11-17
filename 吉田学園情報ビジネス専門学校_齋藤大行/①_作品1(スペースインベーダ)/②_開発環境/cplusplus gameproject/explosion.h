//=============================================================================
//
// 爆発の定義 [explosion.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#define _CRT_SECURE_NO_WARNINGS



//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

class CExplosion : public CScene2d//爆発クラス
{
public:
	//==============================================
	//列挙型宣言
	//==============================================
	typedef enum
	{
		EXPLOSION_NORMAL = 0,
		EXPLOSION_BULLET,
		EXPLOSION_CHARACTER,
		ENEMYSTATE_MAX,
	}EXPLOSION;


	CExplosion();																			//コントラクタ
	~CExplosion();																			//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos , D3DXCOLOR clo, int nSize ,EXPLOSION type);	//作成処理
	HRESULT Init(EXPLOSION type);															//初期化処理
	void Uninit(void);																		//終了処理
	void Update(void);																		//更新処理
	void Draw(void);																		//描画処理
	int GetPatternAnim(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_EXPLOSION_TEXTURE];
	int m_nCounterAnim;//カウンター
	int m_nPatternAnim;//パターンNO
protected:


};

#endif
