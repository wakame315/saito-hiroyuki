//=============================================================================
//
// シーン2d定義 [scene2d.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"



//=============================================================================
// クラス定義
//=============================================================================
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 2);
	~CScene2d();
	HRESULT Init(void);					            //初期化処理
	void Uninit(void);					            //終了処理
	void Update(void);					            //更新処理
	void Draw(void);					            //描画処理
	//静的関数							            
	void SetPosition(D3DXVECTOR3 pos);	            //位置設定
	D3DXVECTOR3 GetPosition(void);		            //位置所得
										         
	void SetMove(D3DXVECTOR3 move);		            //移動量設定
	D3DXVECTOR3 GetMove(void);			            //移動量設定
										          
	void SetRot(D3DXVECTOR3 rot);		            //向き設定
	D3DXVECTOR3 GetRot(void);			            //向き所得
												
	void SetSize(int Size_x, int Size_y);			//サイズ設定
	void SetAnim(int nPatternAnim);					//アニメーション設定
	D3DXCOLOR GetClo(void);							//色所得
	void SetClo(D3DXCOLOR nClo);					//色設定
	void SetTexture(void);							//テクスチャ設定
	bool GetDraw(void);								//描画設定
	void SetDraw(bool DrawUse);						//描画所得
	static CScene2d *Create();						//生成処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//テクスチャ割り当て

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;          //位置
	D3DXVECTOR3				m_rot;			// 向き
	D3DXVECTOR3             m_move;
	D3DXCOLOR               m_clo;
	D3DXCOLOR               m_clo_r;
	D3DXCOLOR               m_clo_g;
	D3DXCOLOR               m_clo_b;
	D3DXCOLOR               m_clo_a;
	int m_Size_x;							//ポリゴンのxの幅
	int m_Size_y;							//ポリゴンのyの幅
	int m_nPatternAnim;
	bool m_bDraw;

};





#endif 
