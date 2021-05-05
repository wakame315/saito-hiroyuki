#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "main.h"
#include "scene2d.h"
#include "explosion.h"
#include "score.h"
#include "bullet.h"
#include "sound.h" 

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY] = {};
int CEnemy::m_nEnemyNum = 0;
int CEnemy::m_nEnemySpawnState = 0;
int CEnemy::m_nEnemydesu = 0;
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

CEnemy::~CEnemy()
{
	
}

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

CEnemy * CEnemy::Create(D3DXVECTOR3 pos, int nSize, int nLife, ENEMYTYPE Type)
{
	CEnemy * pEnemy;
	pEnemy = new CEnemy;
	pEnemy->SetClo(D3DXCOLOR(255, 255, 255, 255));
	pEnemy->SetSize(nSize, nSize);
	pEnemy->SetPosition(pos);
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 5.0f, 0.0f));
	pEnemy->Init(Type);
	pEnemy->m_nlife = nLife;

	return pEnemy;
}

int CEnemy::GetNumEnemy(void)
{
	return m_nEnemyNum;
}

void CEnemy::SetNumEnemy(int Num)
{
	m_nEnemyNum = Num;
}

int CEnemy::GetEnemyDesu(void)
{
	return m_nEnemydesu;
}

void CEnemy::SetEnemyDesu(int Numdesu)
{
	m_nEnemydesu = Numdesu;
}

HRESULT CEnemy::Init(ENEMYTYPE Type)
{
	CScene2d::Init();
	CScene2d::SetTexture();
	SetEnemyType(Type);
	SetObjType(TYPE_ENEMY);
	CScene2d::BindTexture(m_pTexture[Type]);
	return S_OK;
}

void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

void CEnemy::Update(void)
{
	CSound *pSound = CManager::GetSound();
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;

	pos = GetPosition();
	move = GetMove();

	

	switch (m_enemyState)
	{
	case ENEMYSTATE_NORMAL:

		SetClo(D3DXCOLOR(255, 255, 255, 255));
		
		break;

	case ENEMYSTATE_DAMAGE:
		m_nCntState--;

		SetClo(D3DXCOLOR(200, 50, 50, 255));
		
		if (m_nCntState <= 0)
		{
			m_enemyState = ENEMYSTATE_NORMAL;
		}
		break;
	case ENEMYSTATE_CUA:
		m_nCntState--;

		SetClo(D3DXCOLOR(0, 200, 20, 255));

		if (m_nCntState <= 0)
		{
			m_enemyState = ENEMYSTATE_NORMAL;
		}
		break;

	default:
		break;

	}

	if (rand() % 100 < 3)
	{
		AttackType(m_enemyType);
		pSound->Play(CSound::SE_BULLET_ENEMY);
	}
	
	if (m_nTrue == 0)
	{
		if (pos.y >= (ENEMY_SIZE / 2) + (int)rand() % 120 + 80)
		{
			move = (D3DXVECTOR3(5.0f, 0.0f, 0.0f));
			m_nTrue = 1;
		}
	}

	if (rand() % 100 < 1)
	{
		move.x = 5.0 * -1;
	}
	if (rand() % 100 < 1)
	{
		move.x = 5.0 * 1;
	}

	if (pos.x >= (-ENEMY_SIZE / 2) + SCREEN_WIDTH)
	{
		move.x = 5.0 * -1;
	}

	if (pos.x < (ENEMY_SIZE / 2))
	{
		move.x = 5.0 * 1;
	}

	SetPosition(GetPosition() + GetMove());
	SetMove(move);
	CScene2d::Update();

	if (m_bEnemydeath == true)
	{
		CScene2d::Uninit();
	}
}

void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

void CEnemy::Hit(int nDamage, ENEMYTYPE type , int nHitType)
{
	
	switch (nHitType)
	{
	case 1:
		m_nlife -= nDamage;
		m_enemyState = ENEMYSTATE_DAMAGE;
		m_nCntState = 8;

		break;

	case 2:
		m_nlife += nDamage;
		m_enemyState = ENEMYSTATE_CUA;
		m_nCntState = 8;

		if (m_nlife > ENEMY_INIT_LIFE && m_nScoreUp < ADD_SCORE_MAX)
		{
			m_nScoreUp += ADD_SCORE_UP;
		}

		break;

	default:
		break;
	}

	if (m_nlife >= ENEMY_MAX_LIFE)
	{
		m_nlife = ENEMY_MAX_LIFE;
	}
  

	switch (type)
	{

	case ENEMY_TYPE1:

		if (m_nlife <= 0)
		{	
			m_nEnemydesu++;
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100 ,CExplosion::EXPLOSION_CHARACTER);
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)
			{
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE5);
			}
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
			CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{
					if (pScene->GetObjType() == TYPE_SCORE)
					{
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);
						
					}
				}
			}
			m_nScoreUp = 0;
			m_nEnemyNum--;
			m_bEnemydeath = true;
		}
		break;
		

	case ENEMY_TYPE2:

		if (m_nlife <= 0)
		{
			m_nEnemydesu++;
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE,(ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)
			{
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE6);
			}
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{
					if (pScene->GetObjType() == TYPE_SCORE)
					{
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);
						
					}
				}
			}
			m_nScoreUp = 0;
			m_nEnemyNum--;
			m_bEnemydeath = true;
		}

		break;


	case ENEMY_TYPE3:

		if (m_nlife <= 0)
		{
			m_nEnemydesu++;
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= 1000)
			{
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE5);
			}
			
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{
					if (pScene->GetObjType() == TYPE_SCORE)
					{
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);
						
					}
				}
			}

			m_nScoreUp = 0;
			m_nEnemyNum--;
			m_bEnemydeath = true;
		}

		break;


	case ENEMY_TYPE4:

		if (m_nlife <= 0)
		{
			m_nEnemydesu++;
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)
			{
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE6);
			}
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{
					if (pScene->GetObjType() == TYPE_SCORE)
					{
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);
						
					}
				}
			}
			m_nScoreUp = 0;
			m_nEnemyNum--;
			m_bEnemydeath = true;
		}

		break;


	case ENEMY_TYPE5:

		if (m_nlife <= 0)
		{
			m_nEnemydesu++;
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));

			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{
					if (pScene->GetObjType() == TYPE_SCORE)
					{
						((CScore*)pScene)->AddScore(2000 + m_nScoreUp);
						
					}
				}
			}

			m_nScoreUp = 0;
			m_nEnemyNum--;
			m_bEnemydeath = true;
		}

		break;



	case ENEMY_TYPE6:

		if (m_nlife <= 0)
		{
			m_nEnemydesu++;
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{
					if (pScene->GetObjType() == TYPE_SCORE)
					{
						((CScore*)pScene)->AddScore(2000 + m_nScoreUp);
						
					}
				}
			}
			m_nScoreUp = 0;
			m_nEnemyNum--;
			m_bEnemydeath = true;
		}

		break;


	default:
		break;
	}
	
}

void CEnemy::SetEnemyType(ENEMYTYPE Type)
{
	m_enemyType = Type;
}

void CEnemy::AttackType(ENEMYTYPE Type)
{

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



