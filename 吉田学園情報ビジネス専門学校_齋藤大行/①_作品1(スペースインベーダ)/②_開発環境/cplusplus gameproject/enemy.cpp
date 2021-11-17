//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "scene2d.h"
#include "explosion.h"
#include "score.h"
#include "bullet.h"
#include "sound.h" 

//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY] = {};
int CEnemy::m_nEnemyNum = 0;
int CEnemy::m_nEnemySpawnState = 0;
int CEnemy::m_nEnemydesu = 0;

//=============================================================================
//コンストラクタ
//=============================================================================
CEnemy::CEnemy():CScene2d(2)
{
	m_enemyState = ENEMYSTATE_NORMAL;
	m_bEnemydeath = false;
	m_nTrue = 0;
	m_nCntState = 0;
	m_nlife = 0;
	m_nScoreUp = 0;
	m_nEnemyNum++;
}

//=============================================================================
//デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
	
}

//=============================================================================
//テクスチャロード関数
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// デバイスへのポインタ
		TEXTURE_NAME7,					// ファイルの名前
		&m_pTexture[0]);									// 読み込むメモリー

															// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// デバイスへのポインタ
		TEXTURE_NAME8,					// ファイルの名前
		&m_pTexture[1]);									// 読み込むメモリー

															// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// デバイスへのポインタ
		TEXTURE_NAME9,					// ファイルの名前
		&m_pTexture[2]);									// 読み込むメモリー

															// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// デバイスへのポインタ
		TEXTURE_NAME10,					// ファイルの名前
		&m_pTexture[3]);									// 読み込むメモリー

															// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// デバイスへのポインタ
		TEXTURE_NAME11,					// ファイルの名前
		&m_pTexture[4]);									// 読み込むメモリー


	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// デバイスへのポインタ
		TEXTURE_NAME12,					// ファイルの名前
		&m_pTexture[5]);									// 読み込むメモリー


	return S_OK;
}

//=============================================================================
//テクスチャアンロード関数
//=============================================================================
void CEnemy::Unload(void)
{
	
	for (int nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//生成処理関数
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, int nSize, int nLife, ENEMYTYPE Type)
{
	CEnemy * pEnemy;								//ポインタ
	pEnemy = new CEnemy;							//インスタンス生成
	pEnemy->SetClo(D3DXCOLOR(255, 255, 255, 255));	//色の設定
	pEnemy->SetSize(nSize, nSize);					//サイズ設定
	pEnemy->SetPosition(pos);						//位置設定
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 5.0f, 0.0f));	//移動量設定
	pEnemy->Init(Type);								//初期化処理
	pEnemy->m_nlife = nLife;						//ライフの設定

	return pEnemy;
}

//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT CEnemy::Init(ENEMYTYPE Type)
{
	CScene2d::Init();							//初期化処理読み込み
	CScene2d::SetTexture();						//テクスチャの設定
	SetEnemyType(Type);							//タイプ設定
	SetObjType(TYPE_ENEMY);						//オブジェクト設定
	CScene2d::BindTexture(m_pTexture[Type]);	//テクスチャの適用
	return S_OK;
}

//=============================================================================
//終了処理関数
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理関数
//=============================================================================
void CEnemy::Update(void)
{
	CSound *pSound = CManager::GetSound();//サウンドのポインタ
	D3DXVECTOR3 pos;					  //位置
	D3DXVECTOR3 move;					  //移動量

	pos = GetPosition();				  //位置所得
	move = GetMove();					  //移動量所得

	
	//状態判定
	switch (m_enemyState)
	{
	case ENEMYSTATE_NORMAL://通常

		SetClo(D3DXCOLOR(255, 255, 255, 255));
		
		break;

	case ENEMYSTATE_DAMAGE://ダメージ
		m_nCntState--;

		SetClo(D3DXCOLOR(200, 50, 50, 255));
		
		if (m_nCntState <= 0)
		{
			m_enemyState = ENEMYSTATE_NORMAL;
		}
		break;
	case ENEMYSTATE_CUA://回復
		m_nCntState--;

		SetClo(D3DXCOLOR(0, 200, 20, 255));
		//通常状態に遷移
		if (m_nCntState <= 0)
		{
			m_enemyState = ENEMYSTATE_NORMAL;
		}
		break;

	default:
		break;

	}
	//ランダムなタイミングで攻撃
	if (rand() % 100 < 3)
	{
		//攻撃処理
		AttackType(m_enemyType);
		//効果音再生
		pSound->Play(CSound::SE_BULLET_ENEMY);

	}
	//横移動に遷移
	if (m_nTrue == 0)
	{
		if (pos.y >= (ENEMY_SIZE / 2) + (int)rand() % 120 + 80)//どこまで来るか乱数で判定
		{
			move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));//横移動にする
			m_nTrue = 1;//一度だけ読み込むために1にする
		}
	}

	//向きの変更
	if (rand() % 100 < 1)
	{
		move.x = 5.0 * -1;
	}
	if (rand() % 100 < 1)
	{
		move.x = 5.0 * 1;
	}

	//右画面端で跳ね返る
	if (pos.x >= (-ENEMY_SIZE / 2) + SCREEN_WIDTH)
	{
		move.x = 5.0 * -1;
	}
	//左画面端で跳ね返る
	if (pos.x < (ENEMY_SIZE / 2))
	{
		move.x = 5.0 * 1;
	}

	//位置の設定
	SetPosition(GetPosition() + GetMove());
	//移動量の設定
	SetMove(move);
	//Scene2dの読み込み
	CScene2d::Update();

	//死んだとき
	if (m_bEnemydeath == true)
	{	//終了処理
		CScene2d::Uninit();
	}
}

//=============================================================================
//描画処理関数
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//攻撃ヒット処理関数
//=============================================================================
void CEnemy::Hit(int nDamage, ENEMYTYPE type , int nHitType)
{
	//弾のタイプを判定
	switch (nHitType)
	{
	case 1:
		//体力を減らす
		m_nlife -= nDamage;
		//ダメージ状態へ
		m_enemyState = ENEMYSTATE_DAMAGE;
		//状態のカウント設定
		m_nCntState = 8;

		break;

	case 2:
		//体力を増やす
		m_nlife += nDamage;
		//回復状態へ
		m_enemyState = ENEMYSTATE_CUA;
		//状態のカウント設定
		m_nCntState = 8;

		//スコアの数値を上げる
		if (m_nlife > ENEMY_INIT_LIFE && m_nScoreUp < ADD_SCORE_MAX)//敵の体力が3以上かスコア上昇の上限でなければ
		{
			m_nScoreUp += ADD_SCORE_UP;
		}

		break;

	default:
		break;
	}

	//敵の体力回復の上限
	if (m_nlife >= ENEMY_MAX_LIFE)
	{
		m_nlife = ENEMY_MAX_LIFE;
	}

		//敵の体力がなくなったら
	if (m_nlife <= 0)
	{	
		m_nEnemydesu++;//倒した数を増やす

		//タイプの判定
		switch (type)
		{
		case ENEMY_TYPE1:
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//エネミー生成
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)//スコア上昇が上限になっていた時
			{
				//レアエネミー生成
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE5);
			}
			//Sceneをすべて見る
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//オブジェクトがスコアだったら
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//スコア加算処理
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;			//出現数をデクリメント
			m_bEnemydeath = true;	//死亡フラグ

			break;

		case ENEMY_TYPE2:
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//エネミー生成
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)//スコア上昇が上限になっていた時
			{
				//レアエネミー生成
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE6);
			}
			//Sceneをすべて見る
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//オブジェクトがスコアだったら
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//スコア加算処理
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				//出現数をデクリメント
			m_bEnemydeath = true;		//死亡フラグ

			break;

		case ENEMY_TYPE3:
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//エネミー生成
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)
			{
				//レアエネミー生成
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE5);
			}
			//Sceneをすべて見る
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//オブジェクトがスコアだったら
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//スコア加算処理
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				 //出現数をデクリメント
			m_bEnemydeath = true;		 //死亡フラグ

			break;

		case ENEMY_TYPE4:
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//エネミー生成
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)//スコア上昇が上限になっていた時
			{
				//レアエネミー生成
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE6);
			}
			//Sceneをすべて見る
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//オブジェクトがスコアだったら
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//スコア加算処理
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				//出現数をデクリメント
			m_bEnemydeath = true;		//死亡フラグ

			break;

		case ENEMY_TYPE5:
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//エネミー生成
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			//Sceneをすべて見る
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//オブジェクトがスコアだったら
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//スコア加算処理
						((CScore*)pScene)->AddScore(2000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				//出現数をデクリメント
			m_bEnemydeath = true;		//死亡フラグ

			break;

		case ENEMY_TYPE6:
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//エネミー生成
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			//Sceneをすべて見る
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//オブジェクトがスコアだったら
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//スコア加算処理
						((CScore*)pScene)->AddScore(2000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				 //出現数をデクリメント
			m_bEnemydeath = true;		 //死亡フラグ

			break;

		default:
			break;
		}
	}
	
}

//=============================================================================
//エネミータイプ設定
//=============================================================================
void CEnemy::SetEnemyType(ENEMYTYPE Type)
{
	m_enemyType = Type;
}

//=============================================================================
//攻撃パターン設定
//=============================================================================
void CEnemy::AttackType(ENEMYTYPE Type)
{
	//エネミーごとに設定
	switch (m_enemyType)
	{
	case ENEMY_TYPE1:
		CBullet::Create(GetPosition() + D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), ENEMY_BULLET_SIZE, ENEMY_BULLET_LIFE, D3DXCOLOR(100, 100, 100, 255), CBullet::BULLET_TYPE_ENEMY);

		break;

	case ENEMY_TYPE2:
		CBullet::Create(GetPosition() + D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR3(0.0f, 15.0f, 0.0f), ENEMY_BULLET_SIZE, ENEMY_BULLET_LIFE, D3DXCOLOR(100, 100, 100, 255), CBullet::BULLET_TYPE_ENEMY);

		break;

	case ENEMY_TYPE3:
		CBullet::Create(GetPosition() + D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 17.0f, 0.0f), ENEMY_BULLET_SIZE, ENEMY_BULLET_LIFE, D3DXCOLOR(100, 100, 100, 255), CBullet::BULLET_TYPE_ENEMY);

		break;

	case ENEMY_TYPE4:
		CBullet::Create(GetPosition() + D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 17.0f, 0.0f), ENEMY_BULLET_SIZE, ENEMY_BULLET_LIFE, D3DXCOLOR(100, 100, 100, 255), CBullet::BULLET_TYPE_ENEMY);

		break;

	case ENEMY_TYPE5:
		CBullet::Create(GetPosition() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 25.0f, 0.0f), ENEMY_BULLET_SIZE, ENEMY_BULLET_LIFE_2, D3DXCOLOR(100, 100, 100, 255), CBullet::BULLET_TYPE_ENEMY);


		break;

	case ENEMY_TYPE6:
		CBullet::Create(GetPosition() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 25.0f, 0.0f), ENEMY_BULLET_SIZE, ENEMY_BULLET_LIFE_2, D3DXCOLOR(100, 100, 100, 255), CBullet::BULLET_TYPE_ENEMY);


		break;

	default:
		break;
	}
}


//=============================================================================
//出現数所得
//=============================================================================
int CEnemy::GetNumEnemy(void)
{
	return m_nEnemyNum;
}

//=============================================================================
//出現数設定
//=============================================================================
void CEnemy::SetNumEnemy(int Num)
{
	m_nEnemyNum = Num;
}

//=============================================================================
//倒したかの判定
//=============================================================================
int CEnemy::GetEnemyDesu(void)
{
	return m_nEnemydesu;
}
//=============================================================================
//討伐数設定
//=============================================================================
void CEnemy::SetEnemyDesu(int Numdesu)
{
	m_nEnemydesu = Numdesu;
}
