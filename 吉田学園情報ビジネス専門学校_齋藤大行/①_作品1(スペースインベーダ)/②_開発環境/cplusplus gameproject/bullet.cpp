#include "bullet.h"
#include "scene2d.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "enemy.h"
#include "scene.h"
#include "player.h"
#include "sound.h"

LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAXBULLET] = {};

CBullet::CBullet():CScene2d(1)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nlife = 0;
	m_nBulletDamage = 1;
	m_bHit = false;
	m_BulletType = BULLET_TYPE_NONE;
}

CBullet::~CBullet()
{

}

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

void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

void CBullet::Update(void)
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	CSound *pSound = CManager::GetSound();

	pos = GetPosition();
	move = GetMove();
	m_nlife--;	

	SetPosition(pos += move);

	
	CScene2d::Update();
	CScene2d::SetTexture();

	for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;

		if (pScene != NULL)
		{

			D3DXVECTOR3 posEnemy = pScene2d->GetPosition();
			D3DXVECTOR3 posPlayer = pScene2d->GetPosition();

			if (pScene->GetObjType() == TYPE_ENEMY)
			{
				if (((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE1 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE3 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE5)
				{
					if (m_BulletType == BULLET_TYPE_1)
					{
						if (pos.x >= posEnemy.x - (TEXTURE_WIDTH / 2) && pos.x <= posEnemy.x + (TEXTURE_WIDTH / 2) &&
							pos.y >= posEnemy.y - (TEXTURE_HEIGHT / 2) && pos.y <= posEnemy.y + (TEXTURE_HEIGHT / 2))
						{


							switch (m_BulletType)
							{
							case BULLET_TYPE_1:

								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 0, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							case BULLET_TYPE_2:
								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 200, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							default:
								break;
							}

							((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 1);
							pSound->Play(CSound::SE_HIT2);
							m_bHit = true;
						}
					}
					if (m_BulletType == BULLET_TYPE_2)
					{
						if (pos.x >= posEnemy.x - (TEXTURE_WIDTH / 2) && pos.x <= posEnemy.x + (TEXTURE_WIDTH / 2) &&
							pos.y >= posEnemy.y - (TEXTURE_HEIGHT / 2) && pos.y <= posEnemy.y + (TEXTURE_HEIGHT / 2))
						{


							switch (m_BulletType)
							{
							case BULLET_TYPE_1:

								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 0, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							case BULLET_TYPE_2:
								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 200, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							default:
								break;
							}

							((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 2);
							pSound->Play(CSound::SE_HIT2);
							m_bHit = true;
						}
					}
				}
				else if (((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE2 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE4 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE6)
				{
					if (m_BulletType == BULLET_TYPE_1)
					{
						if (pos.x >= posEnemy.x - (TEXTURE_WIDTH / 2) && pos.x <= posEnemy.x + (TEXTURE_WIDTH / 2) &&
							pos.y >= posEnemy.y - (TEXTURE_HEIGHT / 2) && pos.y <= posEnemy.y + (TEXTURE_HEIGHT / 2))
						{


							switch (m_BulletType)
							{
							case BULLET_TYPE_1:

								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 0, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							case BULLET_TYPE_2:
								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 200, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							default:
								break;
							}

							((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 2);
							pSound->Play(CSound::SE_HIT2);
							m_bHit = true;
						}
					}
					if (m_BulletType == BULLET_TYPE_2)
					{
						if (pos.x >= posEnemy.x - (TEXTURE_WIDTH / 2) && pos.x <= posEnemy.x + (TEXTURE_WIDTH / 2) &&
							pos.y >= posEnemy.y - (TEXTURE_HEIGHT / 2) && pos.y <= posEnemy.y + (TEXTURE_HEIGHT / 2))
						{


							switch (m_BulletType)
							{
							case BULLET_TYPE_1:

								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 0, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							case BULLET_TYPE_2:
								CExplosion::Create(GetPosition(), D3DXCOLOR(200, 200, 0, 255), 25, CExplosion::EXPLOSION_BULLET);
								break;

							default:
								break;
							}

							((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 1);
							pSound->Play(CSound::SE_HIT2);
							m_bHit = true;
						}
					}
				}
			}
			else if (pScene->GetObjType() == TYPE_PLAYER)
			{


				if (m_BulletType == BULLET_TYPE_ENEMY)
				{
					if (pos.x >= posPlayer.x - (TEXTURE_WIDTH / 2) && pos.x <= posPlayer.x + (TEXTURE_WIDTH / 2) &&
						pos.y >= posPlayer.y - (TEXTURE_HEIGHT / 2) && pos.y <= posPlayer.y + (TEXTURE_HEIGHT / 2))
					{
						((CPlayer*)pScene)->Hit(1,1);
						pSound->Play(CSound::SE_HIT1);
						m_bHit = true;
					}
				}
			}
		}
	}

	if (m_nlife <= 0 || m_bHit)
	{
		switch (m_BulletType)
		{
		case BULLET_TYPE_1:
			pSound->Play(CSound::SE_EX);
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 0, 255, 255), 45,CExplosion::EXPLOSION_BULLET);
			break;

		case BULLET_TYPE_2:
			pSound->Play(CSound::SE_EX);
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 45, CExplosion::EXPLOSION_BULLET);
			break; 

		case BULLET_TYPE_ENEMY:
			CExplosion::Create(GetPosition(), D3DXCOLOR(100, 100, 110, 255), 45, CExplosion::EXPLOSION_BULLET);
			break;

		default:
			break;
		}
		
		Uninit();
	}
	else if (pos.y <= 0)
	{
		pSound->Play(CSound::SE_EX);
		Uninit();
	}
}

void CBullet::Draw(void)
{
	CScene2d::Draw();
}
