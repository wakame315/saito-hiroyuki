//=============================================================================
//
// �V�[����` [scene.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"


//=============================================================================
// �N���X�錾
//=============================================================================
class CScene//�V�[���N���X
{
public:
	//==============================================
	//�񋓌^�錾
	//==============================================
typedef enum
{
	TYPE_NONE = 0,
	TYPE_PLAYER,		//�v���C���[
	TYPE_ENEMY,			//�G�l�~�[
	TYPE_EXPLOSION,		//����
	TYPE_BULLET,		//�e
	TYPE_BG,			//�w�i
	TYPE_SCORE,			//�X�R�A
	TYPE_TITLE,			//�^�C�g��
	TYPE_RESULT,		//���U���g
	TYPE_TUTORIAL,		//�`���[�g���A��
	TYPR_MAX,			//�ő吔
}OBJTYPE;

	CScene(int nPriority = 2);          //�R���g���N�^
	virtual ~CScene();					//�f�X�g���N�^
	//�������z�֐�					  
	virtual HRESULT Init(void) = 0;		//����������
	virtual void    Uninit(void) = 0;	//�I������
	virtual void    Update(void) = 0;	//�X�V����
	virtual void    Draw(void) = 0;		//�`�揈��
	void SetObjType(OBJTYPE objType);	//�^�C�v����
	OBJTYPE GetObjType(void) { return m_objType; }			//�^�C�v�ݒ�
	static CScene *GetScene(int nCnt);
	//�ÓI�֐�
	static  void    UpdateAll(void);	//�S�X�V
	static  void	DrawAll(void);		//�S�`��
	static  void	ReleaseAll(void);	//�S�폜
	        void	Release(void);		//�폜
private:

	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];  //�|���S���̃|�C���^�ϐ�
	static int m_nNumAll;					//�|���S���̐�
	int m_nID;								//�V�[���̔ԍ�
	int m_nPriority;						//�`�揇
	OBJTYPE m_objType;						//�I�u�W�F�N�g���
};

#endif 