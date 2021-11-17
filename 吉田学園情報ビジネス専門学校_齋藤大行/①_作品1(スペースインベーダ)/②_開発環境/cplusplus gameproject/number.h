//=============================================================================
//
// 数字の定義 [number.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CNumber//ナンバークラス
{
public:
	CNumber();					//コントラクタ
	~CNumber();					//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum);	//作成処理
	HRESULT Init();				//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetNumber(int nNumber);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;          //位置
	D3DXVECTOR3				m_size;          //位置
	int						m_nNumber;
protected:


};

#endif
