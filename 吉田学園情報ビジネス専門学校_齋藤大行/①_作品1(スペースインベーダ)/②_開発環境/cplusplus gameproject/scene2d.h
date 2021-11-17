//=============================================================================
//
// シーン2d定義 [scene2d.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"


//=============================================================================
// クラス宣言
//=============================================================================
class CScene2d : public CScene//シーン2dクラス
{
public:
	CScene2d(int nPriority = 2);			//コントラクタ
    virtual~CScene2d();						//デストラクタ
	virtual HRESULT Init(void);				//初期化処理
	virtual void Uninit(void);				//終了処理			
	virtual void Update(void);				//更新処理			
	virtual void Draw(void);				//描画処理			
	//静的関数								
    void SetPosition(D3DXVECTOR3 pos);		//位置設定
	D3DXVECTOR3 GetPosition(void);			//位置所得

	void SetMove(D3DXVECTOR3 move);			//移動量設定
	D3DXVECTOR3 GetMove(void);				//移動量所得
	
	void SetRot(D3DXVECTOR3 rot);			//向き設定
	D3DXVECTOR3 GetRot(void);				//向き所得

	void SetSize(int Size_x, int Size_y);	//サイズ設定
	void SetAnim(int nPatternAnim);			//アニメーション設定
	D3DXCOLOR GetClo(void);					//色所得
	void SetClo(D3DXCOLOR nClo);			//色設定
	void SetTexture(void);					//テクスチャ設定
	static CScene2d *Create();				//生成処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);//テクスチャ割り当て

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;          //位置
	D3DXVECTOR3				m_rot;			// 向き
	D3DXVECTOR3             m_move;			//移動量
	D3DXCOLOR               m_clo;			//色
	D3DXCOLOR               m_clo_r;		//レッド値
	D3DXCOLOR               m_clo_g;		//グリーン値
	D3DXCOLOR               m_clo_b;		//ブルー値
	D3DXCOLOR               m_clo_a;		//アルファ知
	int m_Size_x;							//ポリゴンのxの幅
	int m_Size_y;							//ポリゴンのyの幅
	int m_nPatternAnim;						//アニメーションのパターン

};





#endif 
