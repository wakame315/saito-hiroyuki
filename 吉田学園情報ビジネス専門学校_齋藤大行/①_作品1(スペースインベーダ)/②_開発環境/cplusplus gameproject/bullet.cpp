//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
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
//�ÓI�����o�[�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAXBULLET] = {};//�e�N�X�`���̃|�C���^

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CBullet::CBullet():CScene2d(1)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_nlife = 0;								//�̗�
	m_nBulletDamage = 1;						//�e���^����_���[�W
	m_bHit = false;								//�������Ă��邩
	m_BulletType = BULLET_TYPE_NONE;			//�e�̃^�C�v�ݒ�
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
//�e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CBullet::Load(void)
{
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// �f�o�C�X�ւ̃|�C���^
	TEXTURE_NAME2,					// �t�@�C���̖��O
	&m_pTexture[0]);					// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),			// �f�o�C�X�ւ̃|�C���^
	TEXTURE_NAME2,					// �t�@�C���̖��O
	&m_pTexture[1]);					// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
//�e�N�X�`���A�����[�h�֐�
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
//���������֐�
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
//�����������֐�
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
//�I�������֐�
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 move;						//�ړ���
	CSound *pSound = CManager::GetSound();	//�T�E���h�̃|�C���^

	pos = GetPosition();					//�ʒu�̏���
	move = GetMove();						//�ړ��ʂ̏���
	m_nlife--;								//�e�̗̑̓f�N�������g

	SetPosition(pos += move);				//�ʒu�̐ݒ�

	
	CScene2d::Update();						//Scene2d�̓ǂݍ���
	CScene2d::SetTexture();					

	//�e�̓����蔻��
	CollisionBullet(pos);

	//�e�̔���
	CreateExplosion(pos);
}

void CBullet::Draw(void)
{
	//Scene2d��ǂݍ���
	CScene2d::Draw();
}

void CBullet::CollisionBullet(D3DXVECTOR3 pos)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h�̃|�C���^

	for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
	{
		CScene *pScene = GetScene(nCntScene);
		CScene2d *pScene2d = (CScene2d*)pScene;

		if (pScene != NULL)
		{
			D3DXVECTOR3 posEnemy = pScene2d->GetPosition();
			D3DXVECTOR3 posPlayer = pScene2d->GetPosition();
			//�G�ɓ��������ꍇ
			if (pScene->GetObjType() == TYPE_ENEMY)
			{		//���@�̒e��������
				if (m_BulletType == BULLET_TYPE_1 || m_BulletType == BULLET_TYPE_2)
				{		//�������Ă��邩�̔���
					if (pos.x >= posEnemy.x - (TEXTURE_WIDTH / 2) && pos.x <= posEnemy.x + (TEXTURE_WIDTH / 2) &&
						pos.y >= posEnemy.y - (TEXTURE_HEIGHT / 2) && pos.y <= posEnemy.y + (TEXTURE_HEIGHT / 2))
					{	//�^�C�v��1�A3�C5�̏ꍇ
						if (((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE1 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE3 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE5)
						{
							switch (m_BulletType)
							{
							case BULLET_TYPE_1:
								//�_���[�W������
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 1);
								//���ʉ��Đ�
								pSound->Play(CSound::SE_HIT2);
								//�������������true�ɂ���
								m_bHit = true;
								break;

							case BULLET_TYPE_2:
								//�񕜂�����
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 2);
								//���ʉ��Đ�
								pSound->Play(CSound::SE_HIT2);
								//�������������true�ɂ���
								m_bHit = true;
								break;

							default:
								break;
							}
						}
						else if (((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE2 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE4 || ((CEnemy*)pScene)->GetEnemyType() == CEnemy::ENEMY_TYPE6)
						{//�^�C�v��2�A4�C6�̏ꍇ

							switch (m_BulletType)
							{
							case BULLET_TYPE_1:
								//�񕜂�����
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 2);
								//���ʉ��Đ�
								pSound->Play(CSound::SE_HIT2);
								//�������������true�ɂ���
								m_bHit = true;
								break;

							case BULLET_TYPE_2:
								//�_���[�W������
								((CEnemy*)pScene)->Hit(1, ((CEnemy*)pScene)->GetEnemyType(), 1);
								//���ʉ��Đ�
								pSound->Play(CSound::SE_HIT2);
								//�������������true�ɂ���
								m_bHit = true;
								break;

							default:
								break;
							}
						}
					}
				}
			}		//���@�ɓ��������ꍇ
			else if (pScene->GetObjType() == TYPE_PLAYER)
			{		//�G�̒e��������
				if (m_BulletType == BULLET_TYPE_ENEMY)
				{		//�������Ă��邩����
					if (pos.x >= posPlayer.x - (TEXTURE_WIDTH / 2) && pos.x <= posPlayer.x + (TEXTURE_WIDTH / 2) &&
						pos.y >= posPlayer.y - (TEXTURE_HEIGHT / 2) && pos.y <= posPlayer.y + (TEXTURE_HEIGHT / 2))
					{	//�_���[�W������
						((CPlayer*)pScene)->Hit(1, 1);
						//���ʉ��Đ�
						pSound->Play(CSound::SE_HIT1);
						//�������������true�ɂ���
						m_bHit = true;
					}
				}
			}
		}
	}
}

void CBullet::CreateExplosion(D3DXVECTOR3 pos)
{
	CSound *pSound = CManager::GetSound();//�T�E���h�̃|�C���^

	if (m_nlife <= 0 || m_bHit)//�e�������������̗͂��Ȃ��Ȃ����Ƃ�
	{
		switch (m_BulletType)
		{
		case BULLET_TYPE_1:
			//���ʉ��Đ�
			pSound->Play(CSound::SE_EX);
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 0, 255, 255), 45, CExplosion::EXPLOSION_BULLET);
			break;

		case BULLET_TYPE_2:
			//���ʉ��Đ�
			pSound->Play(CSound::SE_EX);
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 45, CExplosion::EXPLOSION_BULLET);
			break;

		case BULLET_TYPE_ENEMY:
			CExplosion::Create(GetPosition(), D3DXCOLOR(100, 100, 110, 255), 45, CExplosion::EXPLOSION_BULLET);
			break;

		default:
			break;
		}
		//�I������
		Uninit();
	}
	else if (pos.y <= 0)//��ʉ��܂ōs������
	{	//���ʉ��Đ�
		pSound->Play(CSound::SE_EX);
		//�I������
		Uninit();
	}
}
