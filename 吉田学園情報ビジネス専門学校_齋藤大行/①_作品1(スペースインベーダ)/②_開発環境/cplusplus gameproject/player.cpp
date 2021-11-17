//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "renderer.h"
#include "player.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inputkeyboard.h"
#include "bullet.h"
#include "number.h"
#include "enemy.h"
#include "explosion.h"
#include "manager.h"
#include "result.h"
#include "sound.h"

//=============================================================================
//静的メンバー変数
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture;


//=============================================================================
//コンストラクタ
//=============================================================================
CPlayer::CPlayer():CScene2d(2)
{
	m_playerVector = 0;
	m_nLife = 0;
	m_nBulletTime = 0;
	m_bBulletChange = false;
	m_playerstate = PLAYERSTATE_NORMAL;

}

//=============================================================================
//デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
//テクスチャロード
//=============================================================================
HRESULT CPlayer::Load(void)
{
	// テクスチャの生成
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),	// デバイスへのポインタ
		TEXTURE_NAME1,					// ファイルの名前
		&m_pTexture);					// 読み込むメモリー

	return S_OK;
}

//=============================================================================
//テクスチャアンロード
//=============================================================================
void CPlayer::Unload(void)
{
	//テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
//初期化処理関数
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2d::Init();
	CScene2d::BindTexture(m_pTexture);
	m_nBulletTime = 15;
	m_nLife = PLAYER_MAX_LIFE;
	m_bBulletChange = false;
	return S_OK;
}

//=============================================================================
//終了処理関数
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//更新処理関数
//=============================================================================
void CPlayer::Update(void)
{
	CInputKeyboard *pKey;				//キーボードポインタ
	pKey = CManager::GetInputKeyboard();
	D3DXVECTOR3 rot;								//向き
	D3DXVECTOR3 move;								//移動量
	D3DXVECTOR3 pos;								//位置
	CSound *pSound = CManager::GetSound();//サウンドポインタ
	SetTexture();//テクスチャ設定
	pos = GetPosition();		//位置所得
	rot = GetRot();				//移動量所得

	//static float fradian = 0.0f;
	//static float fradius = 0.0f;
	//fradius = sqrtf((float)(((TEXTURE_WIDTH / 2)*(TEXTURE_WIDTH / 2)) + ((TEXTURE_HEIGHT / 2)*(TEXTURE_HEIGHT / 2))));
	//fradian = atan2f((TEXTURE_HEIGHT / 2), (TEXTURE_WIDTH / 2));

	


	for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;

		if (pScene != NULL)
		{

			D3DXVECTOR3 posEnemy = pScene2d->GetPosition();
			if (pScene->GetObjType() == CEnemy::TYPE_ENEMY)
			{

				if (pos.x + (TEXTURE_WIDTH / 2) >= posEnemy.x - (TEXTURE_WIDTH / 2) && pos.x - (TEXTURE_WIDTH / 2) <= posEnemy.x + (TEXTURE_WIDTH / 2) &&
					pos.y + (TEXTURE_HEIGHT / 2) >= posEnemy.y - (TEXTURE_HEIGHT / 2) && pos.y - (TEXTURE_HEIGHT / 2) <= posEnemy.y + (TEXTURE_HEIGHT / 2))
				{
					m_nLife = 0;
				}
			}
		}
	}

	if (pKey->GetkeyboardTrigger(DIK_LSHIFT) == true)
	{
		if (m_bBulletChange == false)
		{
			m_bBulletChange = true;
		}
		else if (m_bBulletChange == true)
		{
			m_bBulletChange = false;
		}
	}


	if (pKey->Getkeyboardpress(DIK_Z) == true)
	{
		/*rot.z += D3DX_PI * 0.01f;
		if (rot.z >= D3DX_PI)
		{
			rot.z -= D3DX_PI * 2.0f;
		}*/

		if (m_bBulletChange == false)
		{
			if (m_nBulletTime % 15 == 0)
			{
				CBullet::Create(GetPosition(), D3DXVECTOR3(0.0f, -20.0f, 0.0f), PLAYER_BULLET_SIZE, PLAYER_BULLET_LIFE, D3DXCOLOR(0, 0, 255, 255), CBullet::BULLET_TYPE_1);
				pSound->Play(CSound::SE_BULLET_PLAYER);
			}
		}

		if (m_bBulletChange == true)
		{
			if (m_nBulletTime % 15 == 0)
			{
				CBullet::Create(GetPosition(), D3DXVECTOR3(0.0f, -20.0f, 0.0f), PLAYER_BULLET_SIZE, PLAYER_BULLET_LIFE, D3DXCOLOR(255, 255, 255, 255), CBullet::BULLET_TYPE_2);
				pSound->Play(CSound::SE_BULLET_PLAYER);
			}
		}
		m_nBulletTime++;
	}


	move = GetMove();

	if (pKey->GetkeyboardRelease(DIK_Z) == true)
	{
		m_nBulletTime = 15;
	}

	if (pKey->Getkeyboardpress(DIK_UP) == true)
	{
		m_playerVector = -90;
	}
	if (pKey->Getkeyboardpress(DIK_DOWN) == true)
	{
		m_playerVector = 90;
	}

	if (pKey->Getkeyboardpress(DIK_LEFT) == true)
	{
		m_playerVector = -180;

		if (pKey->Getkeyboardpress(DIK_UP) == true)
		{
			m_playerVector = -135;
		}
		else if (pKey->Getkeyboardpress(DIK_DOWN) == true)
		{
			m_playerVector = 135;
		}
		
	}
	if (pKey->Getkeyboardpress(DIK_RIGHT) == true)
	{
		m_playerVector = 0;

		if (pKey->Getkeyboardpress(DIK_UP) == true)
		{
			m_playerVector = -45;
		}
		else if (pKey->Getkeyboardpress(DIK_DOWN) == true)
		{
			m_playerVector = 45;
		}
	}
		move = D3DXVECTOR3(PLAYER_MOVE* cosf(D3DXToRadian(m_playerVector)), PLAYER_MOVE* sinf(D3DXToRadian(m_playerVector)), 0);


	if (pKey->Getkeyboardpress(DIK_UP) == true && pKey->Getkeyboardpress(DIK_DOWN) == true || pKey->Getkeyboardpress(DIK_LEFT) == true && pKey->Getkeyboardpress(DIK_RIGHT) == true)
	{
		move = D3DXVECTOR3(0, 0, 0);
	}

	if (pKey->Getkeyboardpress(DIK_UP) == true || pKey->Getkeyboardpress(DIK_DOWN) == true || pKey->Getkeyboardpress(DIK_LEFT) == true || pKey->Getkeyboardpress(DIK_RIGHT) == true)
	{


		if (pos.y > (-PLAYER_SIZE_Y / 2) + SCREEN_HEIGHT)
		{
			SetPosition(D3DXVECTOR3(pos.x,pos.y = (-PLAYER_SIZE_Y / 2) + SCREEN_HEIGHT, pos.z));
		}

		if (pos.x > (-PLAYER_SIZE_X / 2) + SCREEN_WIDTH)
		{
			SetPosition(D3DXVECTOR3(pos.x = (PLAYER_SIZE_X / 2), pos.y, pos.z));
		}

		if (pos.x < (PLAYER_SIZE_X / 2))
		{
			SetPosition(D3DXVECTOR3(pos.x = (-PLAYER_SIZE_X / 2) + SCREEN_WIDTH, pos.y, pos.z));
			
		}

		SetPosition(GetPosition() += move);

	}
	
	

	if (pos.y >= (-PLAYER_SIZE_Y / 2) + SCREEN_HEIGHT)
	{
		SetMove(D3DXVECTOR3(0, 0, 0));
	}

	if (pos.x >= (-PLAYER_SIZE_X / 2) + SCREEN_WIDTH)
	{
		SetMove(D3DXVECTOR3(0, 0, 0));
	}

	if (pos.x <= (PLAYER_SIZE_X / 2))
	{
		SetMove(D3DXVECTOR3(0, 0, 0));
	}

	switch (m_playerstate)
	{
	case PLAYERSTATE_NORMAL:

		SetClo(D3DXCOLOR(255, 255, 255, 255));

		break;

	case PLAYERSTATE_DAMAGE:
		m_nCntState--;

		SetClo(D3DXCOLOR(200, 50, 50, 255));

		if (m_nCntState <= 0)
		{
			m_playerstate = PLAYERSTATE_NORMAL;
		}
		break;
	case PLAYERSTATE_CUA:
		m_nCntState--;

		SetClo(D3DXCOLOR(0, 200, 20, 255));

		if (m_nCntState <= 0)
		{
			m_playerstate = PLAYERSTATE_NORMAL;
		}
		break;

	default:
		break;

	}

	SetRot(rot);

	//頂点情報を設定

	CScene2d::Update();

	if (m_nLife <= 0)
	{
		CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 100), 100, CExplosion::EXPLOSION_BULLET);

		CResult::SetClear(true);

		CManager::SetMode(CManager::MODE_RESULT);
		CScene2d::Uninit();
		
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//生成処理関数
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer * pPlayer;
	pPlayer = new CPlayer;
	pPlayer->SetPosition(pos);
	pPlayer->SetSize(PLAYER_SIZE_X, PLAYER_SIZE_Y);
	pPlayer->SetClo(D3DXCOLOR(255, 255, 255, 255));
	pPlayer->Init();
	pPlayer->SetObjType(TYPE_PLAYER);

	return pPlayer;
}
//=============================================================================
//攻撃ヒット処理関数
//=============================================================================
void CPlayer::Hit(int nDamage, int nHitType)
{

	switch (nHitType)
	{
	case 1://ダメージ状態
		m_nLife -= nDamage;
		m_playerstate = PLAYERSTATE_DAMAGE;
		m_nCntState = 8;

		break;

	case 2://回復
		m_nLife += nDamage;
		m_playerstate = PLAYERSTATE_CUA;
		m_nCntState = 8;

	

		break;

	default:
		break;
	}

}