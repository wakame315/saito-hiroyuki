//=============================================================================
//
// DirectX���^���� [inputkeyboard.cpp]
// Author :�V����s
//
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

class CInputKeyboard : public CInput
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