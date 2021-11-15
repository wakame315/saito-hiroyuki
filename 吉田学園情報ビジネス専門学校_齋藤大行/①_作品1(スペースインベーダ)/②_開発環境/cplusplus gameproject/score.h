//=============================================================================
//
// DirectX���^���� [score.cpp]
// Author :�V����s
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "number.h"

class CScore : public CScene
{
public:
	CScore();					//�R���g���N�^
	~CScore();					//�f�X�g���N�^
	static CScore *Create(void);	//�쐬����
	HRESULT Init(void);				//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
	void AddScore(int nScore);  //�X�R�A�ݒ�
	

private:
	CNumber *m_apNumber[MAX_NUM];
	int m_nScore;
protected:


};

#endif
