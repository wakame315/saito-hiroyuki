//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
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
//�ÓI�����o�[�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_ENEMY] = {};
int CEnemy::m_nEnemyNum = 0;
int CEnemy::m_nEnemySpawnState = 0;
int CEnemy::m_nEnemydesu = 0;

//=============================================================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
	
}

//=============================================================================
//�e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CEnemy::Load(void)
{
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME7,					// �t�@�C���̖��O
		&m_pTexture[0]);									// �ǂݍ��ރ������[

															// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME8,					// �t�@�C���̖��O
		&m_pTexture[1]);									// �ǂݍ��ރ������[

															// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME9,					// �t�@�C���̖��O
		&m_pTexture[2]);									// �ǂݍ��ރ������[

															// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME10,					// �t�@�C���̖��O
		&m_pTexture[3]);									// �ǂݍ��ރ������[

															// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME11,					// �t�@�C���̖��O
		&m_pTexture[4]);									// �ǂݍ��ރ������[


	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(),				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME12,					// �t�@�C���̖��O
		&m_pTexture[5]);									// �ǂݍ��ރ������[


	return S_OK;
}

//=============================================================================
//�e�N�X�`���A�����[�h�֐�
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
//���������֐�
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, int nSize, int nLife, ENEMYTYPE Type)
{
	CEnemy * pEnemy;								//�|�C���^
	pEnemy = new CEnemy;							//�C���X�^���X����
	pEnemy->SetClo(D3DXCOLOR(255, 255, 255, 255));	//�F�̐ݒ�
	pEnemy->SetSize(nSize, nSize);					//�T�C�Y�ݒ�
	pEnemy->SetPosition(pos);						//�ʒu�ݒ�
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 5.0f, 0.0f));	//�ړ��ʐݒ�
	pEnemy->Init(Type);								//����������
	pEnemy->m_nlife = nLife;						//���C�t�̐ݒ�

	return pEnemy;
}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CEnemy::Init(ENEMYTYPE Type)
{
	CScene2d::Init();							//�����������ǂݍ���
	CScene2d::SetTexture();						//�e�N�X�`���̐ݒ�
	SetEnemyType(Type);							//�^�C�v�ݒ�
	SetObjType(TYPE_ENEMY);						//�I�u�W�F�N�g�ݒ�
	CScene2d::BindTexture(m_pTexture[Type]);	//�e�N�X�`���̓K�p
	return S_OK;
}

//=============================================================================
//�I�������֐�
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CEnemy::Update(void)
{
	CSound *pSound = CManager::GetSound();//�T�E���h�̃|�C���^
	D3DXVECTOR3 pos;					  //�ʒu
	D3DXVECTOR3 move;					  //�ړ���

	pos = GetPosition();				  //�ʒu����
	move = GetMove();					  //�ړ��ʏ���

	
	//��Ԕ���
	switch (m_enemyState)
	{
	case ENEMYSTATE_NORMAL://�ʏ�

		SetClo(D3DXCOLOR(255, 255, 255, 255));
		
		break;

	case ENEMYSTATE_DAMAGE://�_���[�W
		m_nCntState--;

		SetClo(D3DXCOLOR(200, 50, 50, 255));
		
		if (m_nCntState <= 0)
		{
			m_enemyState = ENEMYSTATE_NORMAL;
		}
		break;
	case ENEMYSTATE_CUA://��
		m_nCntState--;

		SetClo(D3DXCOLOR(0, 200, 20, 255));
		//�ʏ��ԂɑJ��
		if (m_nCntState <= 0)
		{
			m_enemyState = ENEMYSTATE_NORMAL;
		}
		break;

	default:
		break;

	}
	//�����_���ȃ^�C�~���O�ōU��
	if (rand() % 100 < 3)
	{
		//�U������
		AttackType(m_enemyType);
		//���ʉ��Đ�
		pSound->Play(CSound::SE_BULLET_ENEMY);

	}
	//���ړ��ɑJ��
	if (m_nTrue == 0)
	{
		if (pos.y >= (ENEMY_SIZE / 2) + (int)rand() % 120 + 80)//�ǂ��܂ŗ��邩�����Ŕ���
		{
			move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));//���ړ��ɂ���
			m_nTrue = 1;//��x�����ǂݍ��ނ��߂�1�ɂ���
		}
	}

	//�����̕ύX
	if (rand() % 100 < 1)
	{
		move.x = 5.0 * -1;
	}
	if (rand() % 100 < 1)
	{
		move.x = 5.0 * 1;
	}

	//�E��ʒ[�Œ��˕Ԃ�
	if (pos.x >= (-ENEMY_SIZE / 2) + SCREEN_WIDTH)
	{
		move.x = 5.0 * -1;
	}
	//����ʒ[�Œ��˕Ԃ�
	if (pos.x < (ENEMY_SIZE / 2))
	{
		move.x = 5.0 * 1;
	}

	//�ʒu�̐ݒ�
	SetPosition(GetPosition() + GetMove());
	//�ړ��ʂ̐ݒ�
	SetMove(move);
	//Scene2d�̓ǂݍ���
	CScene2d::Update();

	//���񂾂Ƃ�
	if (m_bEnemydeath == true)
	{	//�I������
		CScene2d::Uninit();
	}
}

//=============================================================================
//�`�揈���֐�
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
//�U���q�b�g�����֐�
//=============================================================================
void CEnemy::Hit(int nDamage, ENEMYTYPE type , int nHitType)
{
	//�e�̃^�C�v�𔻒�
	switch (nHitType)
	{
	case 1:
		//�̗͂����炷
		m_nlife -= nDamage;
		//�_���[�W��Ԃ�
		m_enemyState = ENEMYSTATE_DAMAGE;
		//��Ԃ̃J�E���g�ݒ�
		m_nCntState = 8;

		break;

	case 2:
		//�̗͂𑝂₷
		m_nlife += nDamage;
		//�񕜏�Ԃ�
		m_enemyState = ENEMYSTATE_CUA;
		//��Ԃ̃J�E���g�ݒ�
		m_nCntState = 8;

		//�X�R�A�̐��l���グ��
		if (m_nlife > ENEMY_INIT_LIFE && m_nScoreUp < ADD_SCORE_MAX)//�G�̗̑͂�3�ȏォ�X�R�A�㏸�̏���łȂ����
		{
			m_nScoreUp += ADD_SCORE_UP;
		}

		break;

	default:
		break;
	}

	//�G�̗͉̑񕜂̏��
	if (m_nlife >= ENEMY_MAX_LIFE)
	{
		m_nlife = ENEMY_MAX_LIFE;
	}

		//�G�̗̑͂��Ȃ��Ȃ�����
	if (m_nlife <= 0)
	{	
		m_nEnemydesu++;//�|�������𑝂₷

		//�^�C�v�̔���
		switch (type)
		{
		case ENEMY_TYPE1:
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//�G�l�~�[����
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)//�X�R�A�㏸������ɂȂ��Ă�����
			{
				//���A�G�l�~�[����
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE5);
			}
			//Scene�����ׂČ���
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//�I�u�W�F�N�g���X�R�A��������
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//�X�R�A���Z����
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;			//�o�������f�N�������g
			m_bEnemydeath = true;	//���S�t���O

			break;

		case ENEMY_TYPE2:
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//�G�l�~�[����
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)//�X�R�A�㏸������ɂȂ��Ă�����
			{
				//���A�G�l�~�[����
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE6);
			}
			//Scene�����ׂČ���
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//�I�u�W�F�N�g���X�R�A��������
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//�X�R�A���Z����
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				//�o�������f�N�������g
			m_bEnemydeath = true;		//���S�t���O

			break;

		case ENEMY_TYPE3:
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//�G�l�~�[����
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)
			{
				//���A�G�l�~�[����
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE5);
			}
			//Scene�����ׂČ���
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//�I�u�W�F�N�g���X�R�A��������
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//�X�R�A���Z����
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				 //�o�������f�N�������g
			m_bEnemydeath = true;		 //���S�t���O

			break;

		case ENEMY_TYPE4:
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//�G�l�~�[����
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			if (m_nScoreUp >= ADD_SCORE_MAX)//�X�R�A�㏸������ɂȂ��Ă�����
			{
				//���A�G�l�~�[����
				CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_RARE_SIZE, ENEMY_RARE_INIT_LIFE, ENEMYTYPE::ENEMY_TYPE6);
			}
			//Scene�����ׂČ���
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//�I�u�W�F�N�g���X�R�A��������
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//�X�R�A���Z����
						((CScore*)pScene)->AddScore(1000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				//�o�������f�N�������g
			m_bEnemydeath = true;		//���S�t���O

			break;

		case ENEMY_TYPE5:
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(0, 200, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//�G�l�~�[����
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			//Scene�����ׂČ���
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//�I�u�W�F�N�g���X�R�A��������
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//�X�R�A���Z����
						((CScore*)pScene)->AddScore(2000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				//�o�������f�N�������g
			m_bEnemydeath = true;		//���S�t���O

			break;

		case ENEMY_TYPE6:
			//�����̐���
			CExplosion::Create(GetPosition(), D3DXCOLOR(255, 255, 255, 255), 100, CExplosion::EXPLOSION_CHARACTER);
			//�G�l�~�[����
			CEnemy::Create(D3DXVECTOR3((int)rand() % 1160 + 70, (int)rand() % -20 + -80, 0.0f), ENEMY_SIZE, ENEMY_INIT_LIFE, (ENEMYTYPE)(rand() % (ENEMY_TYPE_MAX - 2)));
			//Scene�����ׂČ���
			for (int nCntScene = 0; nCntScene < MAX_SCENE*PRIORITY_MAX; nCntScene++)
			{
				CScene *pScene = GetScene(nCntScene);
				CScene2d *pScene2d = (CScene2d*)pScene;

				if (pScene != NULL)
				{		//�I�u�W�F�N�g���X�R�A��������
					if (pScene->GetObjType() == TYPE_SCORE)
					{	//�X�R�A���Z����
						((CScore*)pScene)->AddScore(2000 + m_nScoreUp);

					}
				}
			}
			m_nEnemyNum--;				 //�o�������f�N�������g
			m_bEnemydeath = true;		 //���S�t���O

			break;

		default:
			break;
		}
	}
	
}

//=============================================================================
//�G�l�~�[�^�C�v�ݒ�
//=============================================================================
void CEnemy::SetEnemyType(ENEMYTYPE Type)
{
	m_enemyType = Type;
}

//=============================================================================
//�U���p�^�[���ݒ�
//=============================================================================
void CEnemy::AttackType(ENEMYTYPE Type)
{
	//�G�l�~�[���Ƃɐݒ�
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
//�o��������
//=============================================================================
int CEnemy::GetNumEnemy(void)
{
	return m_nEnemyNum;
}

//=============================================================================
//�o�����ݒ�
//=============================================================================
void CEnemy::SetNumEnemy(int Num)
{
	m_nEnemyNum = Num;
}

//=============================================================================
//�|�������̔���
//=============================================================================
int CEnemy::GetEnemyDesu(void)
{
	return m_nEnemydesu;
}
//=============================================================================
//�������ݒ�
//=============================================================================
void CEnemy::SetEnemyDesu(int Numdesu)
{
	m_nEnemydesu = Numdesu;
}
