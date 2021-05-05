#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "renderer.h"
class CScene2d;
class CTutorial
{
public:
	CTutorial();											//�R���X�g���N�^
	~CTutorial();											//�f�X�g���N�^
	static HRESULT Load(void);						//�e�N�X�`���̓ǂݍ���
	static void Unload(void);						// �e�N�X�`���̔j��
	static CTutorial *Create(void);	//��������
	HRESULT Init(void);			//����������
	void Uninit(void);								//�I������	
	void Update(void);
	void Draw(void);								//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//�e�N�X�`���ϐ�
	CScene2d *m_apScene2d;
	bool m_bDrawUse;

};
#endif // !_TITLE_H_
