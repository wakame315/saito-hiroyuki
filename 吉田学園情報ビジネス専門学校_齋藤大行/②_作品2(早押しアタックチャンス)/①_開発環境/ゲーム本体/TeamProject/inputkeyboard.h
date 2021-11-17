//=============================================================================
//
// �L�[�{�[�h�̓��͒�` [inputkeyboard.h]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#define _CRT_SECURE_NO_WARNINGS

//�}�N����`
#define NUM_KEY_MAX (256)//�L�[�̍ő吔
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CInputKeyboard : public CInput//�L�[�{�[�h���̓N���X
{
public:
	CInputKeyboard();								//�R���X�g���N�^
	~CInputKeyboard();								//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����

	bool Getkeyboardpress(int nkey);				//�v���X
	bool GetkeyboardTrigger(int nkey);				//�g���K�[
	bool GetkeyboardRelease(int nkey);				//�����[�X
private:

	BYTE m_akeysrate[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_akeysrateTrigger[NUM_KEY_MAX];
	BYTE m_akeysrateRelease[NUM_KEY_MAX];

};

#endif