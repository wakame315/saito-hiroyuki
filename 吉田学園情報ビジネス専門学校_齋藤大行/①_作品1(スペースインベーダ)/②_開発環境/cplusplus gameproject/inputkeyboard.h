//=============================================================================
//
// �L�[�{�[�h���͂̒�` [inputkeyboard.cpp]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#define DIRECTINPUT_VERSION (0x0800)
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//�}�N����`
//=============================================================================
#define NUM_KEY_MAX (256)//�L�[�̍ő吔
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <dinput.h>
#include "main.h"
#include "input.h"

class CInputKeyboard : public CInput//�L�[�{�[�h���̓N���X
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool Getkeyboardpress(int nkey);
	bool GetkeyboardTrigger(int nkey);
	bool GetkeyboardRelease(int nkey);
private:
	
	BYTE m_akeysrate[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏�񃏁[�N
	BYTE m_akeysrateTrigger[NUM_KEY_MAX];
	BYTE m_akeysrateRelease[NUM_KEY_MAX];

};

#endif