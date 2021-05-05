#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*********************************************************
// 前方宣言
//*********************************************************

//オブジェクトクラス
class CScene2d : public CScene
{
public:
	CScene2d(int nPriority = 2);
	~CScene2d();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//静的関数
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

	void SetMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetMove(void);

	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRot(void);

	void SetSize(int Size_x, int Size_y);
	void SetAnim(int nPatternAnim);
	D3DXCOLOR GetClo(void);
	void SetClo(D3DXCOLOR nClo);
	void SetTexture(void);
	bool GetDraw(void);
	void SetDraw(bool DrawUse);
	static CScene2d *Create();
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

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
