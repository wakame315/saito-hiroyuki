//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "scene.h"
#include "player.h"
#include "sound.h"

//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAXBULLET] = {};//テクスチャのポインタ

//=============================================================================
//コンストラクタ
//=============================================================================
CBullet::CBullet():CScene2d(1)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_nlife = 0;								//体力
	m_nBulletDamage = 1;						//弾が与えるダメージ
	m_bHit = false;								//当たっているか
	m_BulletType = BULLET_TYPE_NONE;			//弾のタイプ設定
}

//=============================================================================
//デストラクタ
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
//テクスチャロード関数
//=============================================================================
HRESULT CBullet::Load(void)
{
	// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// デバイスへのポインタ
	TEXTURE_NAME2,					// ファイルの名前
	&m_pTexture[0]);					// 読み込むメモリー

	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// デバイスへのポインタ
	TEXTURE_NAME2,					// ファイルの名前
	&m_pTexture[1]);					// 読み込むメモリー

	return S_OK;
}

//=============================================================================
//テクスチャアンロード関数
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCount = 0; nCount < MAXBULLET; nCount++)
	{
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//生成処理関数
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nSize, int nLife, D3DXCOLOR col, BULLETTYPE type)
{
	CBullet * pBullet;
	pBullet = new CBullet;
	pBullet->Init(type);
	pBullet->SetClo(col);
	pBullet->SetSize(nSize, nSize);
	pBullet->SetMove(move);
	pBullet->SetPosition(pos + D3DXVECTOR3(0,0,0));
	pBullet->m_nlife = nLife;
	return pBullet;
}

//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT CBullet::Init(BULLETTYPE type)
{
	CScene2d::Init();
	if (type == 2)
	{
		CScene2d::BindTexture(m_pTexture[type - 1]);
	}
	else
	{
		CScene2d::BindTexture(m_pTexture[type - type]);
	}

	SetObjType(CScene::TYPE_BULLET);
	m_BulletType = type;
	
	
	m_bHit = false;

	return S_OK;
}

//=============================================================================
//終了処理関数
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理関数
//=============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 move;						//移動量
	CSound *pSound = CManager::GetSound();	//サウンドのポインタ

	pos = GetPosition();					//位置の所得
	move = GetMove();						//移動量の所得
	m_nlife--;								//弾の体力デクリメント

	SetPosition(pos += move);				//位置の設定

	
	CScene2d::Update();						//Scene2dの読み込み
	CScene2d::SetTexture();					

	//弾の当たり判定
	CollisionBullet(pos);

	//弾の爆発
	CreateExplosion(pos);
}

void CBullet::Draw(void)
{
	//Scene2dを読み込む
	CScene2d::Draw();
}

void CBullet::CollisionBullet(D3DXVECTOR3 pos)
{
	CSound *pSound = CManager::GetSound();	//サウンドのポインタ

	for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;

		if (pScene != NULL)
		{
			D3DXVECTOR3 posEnemy = pScene2d->GetPosition();
			D3DXVECTOR3 posPlayer = pScene2d->GetPosition();
			//敵に当たった場合
			if (pScene->GetObjType() == TYPE_ENEMY)
			{		//自機の弾だったら
				if (m_BulletType == BULLET_TYPE_1 || m_BulletType == BULLET_TYPE_2)
				{		//当たっているかの判定
					if (pos.x >= posEnemy.x - (TEXTURE_WIDTH / 2) && pos.x <= posEnemy.x + (TEXTURE_WIDTH / 2) &&
						pos.y >= posEnemy.y - (TEXTURE_HEIGHT / 2) && pos.y <= posEnemy.y + (TEXTURE_HEIGHT / 2))
					{	//タイプが1、3，5の場合
						if (((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE1 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE3 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE5)
						{
							switch (m_BulletType)
							{
							case BULLET_TYPE_1:
								//ダメージを入れる
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 1);
								//効果音再生
								pSound->Play(CSound::SE_HIT2);
								//当たった判定をtrueにする
								m_bHit = true;
								break;

							case BULLET_TYPE_2:
								//回復を入れる
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 2);
								//効果音再生
								pSound->Play(CSound::SE_HIT2);
								//当たった判定をtrueにする
								m_bHit = true;
								break;

							default:
								break;
							}
						}
						else if (((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE2 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE4 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE6)
						{//タイプが2、4，6の場合

							switch (m_BulletType)
							{
							case BULLET_TYPE_1:
								//回復を入れる
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 2);
								//効果音再生
								pSound->Play(CSound::SE_HIT2);
								//当たった判定をtrueにする
								m_bHit = true;
								break;

							case BULLET_TYPE_2:
								//ダメージを入れる
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 1);
								//効果音再生
								pSound->Play(CSound::SE_HIT2);
								//当たった判定をtrueにする
								m_bHit = true;
								break;

							default:
								break;
							}
						}
					}
				}
			}		//自機に当たった場合
			else if (pScene->GetObjType() == TYPE_PLAYER)
			{		//敵の弾だったら
				if (m_BulletType == BULLET_TYPE_ENEMY)
				{		//当たっているか判定
					if (pos.x >= posPlayer.x - (TEXTURE_WIDTH / 2) && pos.x <= posPlayer.x + (TEXTURE_WIDTH / 2) &&
						pos.y >= posPlayer.y - (TEXTURE_HEIGHT / 2) && pos.y <= posPlayer.y + (TEXTURE_HEIGHT / 2))
					{	//ダメージを入れる
						((CPlayer*)pScene)->Hit(1, 1);
						//効果音再生
						pSound->Play(CSound::SE_HIT1);
						//当たった判定をtrueにする
						m_bHit = true;
					}
				}
			}
		}
	}
}

void CBullet::CreateExplosion(D3DXVECTOR3 pos)
{
	CSound *pSound = CManager::GetSound();//サウンドのポインタ

	if (m_nlife <= 0 || m_bHit)//弾が当たったか体力がなくなったとき
	{
		switch (m_BulletType)
		{
		case BULLET_TYPE_1:
			//効果音再生
			pSound->Play(CSound::SE_EX);
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 0, 255, 255), 45, CExplosion::EXPLOSION_BULLET);
			break;

		case BULLET_TYPE_2:
			//効果音再生
			pSound->Play(CSound::SE_EX);
			//爆発の生成
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 45, CExplosion::EXPLOSION_BULLET);
			break;

		case BULLET_TYPE_ENEMY:
			CExplosion::Create(GetPosition(), D3DXCOLOR(100, 100, 110, 255), 45, CExplosion::EXPLOSION_BULLET);
			break;

		default:
			break;
		}
		//終了処理
		Uninit();
	}
	else if (pos.y <= 0)//画面下まで行った時
	{	//効果音再生
		pSound->Play(CSound::SE_EX);
		//終了処理
		Uninit();
	}
}
