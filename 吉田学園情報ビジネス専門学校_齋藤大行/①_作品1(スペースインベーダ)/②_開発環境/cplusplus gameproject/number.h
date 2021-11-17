//=============================================================================
//
// �����̒�` [number.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X�錾
//=============================================================================
class CNumber//�i���o�[�N���X
{
public:
	CNumber();					//�R���g���N�^
	~CNumber();					//�f�X�g���N�^
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum);	//�쐬����
	HRESULT Init();				//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(D3DXVECTOR3 size);
	void SetNumber(int nNumber);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;          //�ʒu
	D3DXVECTOR3				m_size;          //�ʒu
	int						m_nNumber;
protected:


};

#endif
