#ifndef _RESULT_H_
#define _RESULT_H_
#include "renderer.h"
class CScene2d;
class CResult 
{
	public:
		CResult(int nPriority = 4);											//�R���X�g���N�^
		~CResult();											//�f�X�g���N�^
		static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
		static void Unload(void);						// �e�N�X�`���̔j��
		static CResult *Create(void);	//��������
		static void SetClear(bool Clear);
		HRESULT Init(void);			//����������
		void Uninit(void);								//�I������	
		void Update(void);
		void Draw(void);								//�`�揈��
		
	private:
		static LPDIRECT3DTEXTURE9 m_pTexture[RESULT_TEXTURE];		//�e�N�X�`���ϐ�
		static bool m_bClear;
		CScene2d *m_apScene2d;
		
};
#endif // !_RESULT_H_
