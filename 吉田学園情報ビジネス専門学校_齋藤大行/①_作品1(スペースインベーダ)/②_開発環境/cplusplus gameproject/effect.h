//=============================================================================
//
// DirectX雛型処理 [effect.cpp]
// Author :齋藤大行
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

class CEffect : public CScene2d
{
public:
	CEffect();					//コントラクタ
	~CEffect();					//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 pos, int nSize_X, int nSize_Y);	//作成処理
	HRESULT Init();				//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];
	
protected:


};

#endif
