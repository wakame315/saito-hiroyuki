//=============================================================================
//
// �V�[����` [scene.h]
// Author : �V����s
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include"main.h"



//=============================================================================
// �N���X��`
//=============================================================================
class CScene
{
public:
	//==============================================
	//�񋓌^�錾
	//==============================================
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_POLYGON,		
		TYPE_DISPLAYTIME,
		TYPE_RANKING,
		TYPE_BG,
		TYPR_MAX,
	}OBJTYPE;

	CScene(int nPriority = 2);                           //�R���g���N�^
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
	static  void    UpdateAll(void);
	static  void	DrawAll(void);
	static  void	ReleaseAll(void);
	void	Release(void);
private:

	static CScene *m_apScene[PRIORITY_MAX][MAX_POLYGON];  //�|���S���̃|�C���^�ϐ�
	static int m_nNumAll;					//�|���S���̐�
	int m_nID;
	int m_nPriority;
	OBJTYPE m_objType;//�I�u�W�F�N�g���
};

#endif 