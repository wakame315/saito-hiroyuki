//=============================================================================
//
// DirectX雛型処理 [life.cpp]
// Author :齋藤大行
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene2d.h"


class CLife : public CScene
{
public:
	CLife();					//コントラクタ
	~CLife();					//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CLife *Create(void);	//作成処理
	HRESULT Init();				//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理
	void lifeMode(int Damage);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	CScene2d *m_apScene2d[PLAYER_MAX_LIFE];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;          //位置
	D3DXVECTOR3				m_size;          //位置
	static int				m_life;
	
protected:


};

#endif
