#ifndef _TITLE_H_
#define _TITLE_H_
#include "renderer.h"
class CScene2d;
class CTitle
{
public:
	CTitle();											//�R���X�g���N�^
	~CTitle();											//�f�X�g���N�^
	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						// �e�N�X�`���̔j��
	static CTitle *Create(void);	//��������
	HRESULT Init(void);			//����������
	void Uninit(void);								//�I������	
	void Update(void);
	void Draw(void);								//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���ϐ�
	CScene2d *m_apScene2d;
	
};
#endif // !_TITLE_H_
