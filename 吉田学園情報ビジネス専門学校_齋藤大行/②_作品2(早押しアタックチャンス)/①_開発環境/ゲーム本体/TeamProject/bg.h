//=============================================================================
//
// DirectX雛型処理 [bg.cpp]
// Author :齋藤大行
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXTURE 3

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

class CBg : public CScene
{
public:
	typedef enum
	{
		BG_TYPE_NONE = 0,
		BG_TYPE1,		
		BG_TYPE2,
		BG_TYPE3,
		BG_TYPR_MAX,
	}BGTYPE;
	CBg();					//コントラクタ
	~CBg();					//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CBg *Create(void);	//作成処理
	HRESULT Init(void);				//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理
	BGTYPE GetBG(void);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];
	CScene2d *m_apScene2d[MAX_POLYGON];
	BGTYPE m_bBgType;
protected:


};

#endif
