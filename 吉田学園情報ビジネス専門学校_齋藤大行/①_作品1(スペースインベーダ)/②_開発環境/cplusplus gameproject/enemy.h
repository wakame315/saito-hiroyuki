//=============================================================================
//
// 敵の定義 [enemy.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// クラス宣言
//=============================================================================
class CEnemy : public CScene2d//敵クラス
{
public:

	//==============================================
	//列挙型宣言
	//==============================================
typedef enum
{ 
	ENEMY_TYPE1 = 0,		//敵の種類
	ENEMY_TYPE2,		
	ENEMY_TYPE3,
	ENEMY_TYPE4,
	ENEMY_TYPE5,
	ENEMY_TYPE6,
	ENEMY_TYPE_MAX,
}ENEMYTYPE;
typedef enum
{
	ENEMYSTATE_NORMAL = 0,//敵の状態
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_CUA,
	ENEMYSTATE_MAX,
}ENEMYSTATE;


	CEnemy();					//コントラクタ
	~CEnemy();					//デストラクタ
	static HRESULT Load(void);
	static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 pos, int nSize, int nLife, ENEMYTYPE Type);	//作成処理
	static int GetNumEnemy(void);
	static void SetNumEnemy(int Num);
	static int GetEnemyDesu(void);
	static void SetEnemyDesu(int Numdesu);
	HRESULT Init(ENEMYTYPE Type);			//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理
	void Hit(int nDamage , ENEMYTYPE type ,int nHitType);//弾が当たった時の処理
	void SetEnemyType(ENEMYTYPE Type);					 //敵のタイプの設定
	void AttackType(ENEMYTYPE Type);					 //攻撃のパターン	 
	ENEMYTYPE GetEnemyType(void) {return m_enemyType;}	 //出現した敵の数所得処理
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ENEMY];//テクスチャ
	static int m_nEnemyNum;							//出現数
	static int m_nEnemySpawnState;					//スポーンするまでの時間
	static int m_nEnemydesu;						//倒した数
	bool m_bEnemydeath;								//死んだかどうか
	int m_nlife;									//ライフ
													
	int m_nCntState;								//状態移行のカウント
	int m_nScoreUp;									//スコア上昇数
	int m_nTrue;									//移動方向変更の判定
	
	ENEMYTYPE m_enemyType;							//タイプ
	ENEMYSTATE m_enemyState;						//状態


protected:


};

#endif
