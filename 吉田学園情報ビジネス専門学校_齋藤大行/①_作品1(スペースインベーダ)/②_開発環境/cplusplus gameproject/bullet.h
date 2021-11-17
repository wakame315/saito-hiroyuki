//=============================================================================
//
// 弾の定義 [bullet.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CBullet : public CScene2d//弾クラス
{
public:
	//==============================================
	//列挙型宣言
	//==============================================
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_1,
		BULLET_TYPE_2,
		BULLET_TYPE_ENEMY,
		BULLET_TYPE_MAX,
	}BULLETTYPE;

	CBullet();					//コントラクタ
	~CBullet();					//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nSize, int nLife, D3DXCOLOR col, BULLETTYPE type);	//作成処理
	HRESULT Init(BULLETTYPE type);				//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理
	void CollisionBullet(D3DXVECTOR3 pos);	//弾の当たり判定
	void CreateExplosion(D3DXVECTOR3 pos);

private:
	D3DXVECTOR3 m_move;//移動量
	static LPDIRECT3DTEXTURE9 m_pTexture[MAXBULLET];
	int m_nlife;
	int m_nBulletDamage;
	bool m_bHit;
	BULLETTYPE m_BulletType;
protected:



};

#endif
