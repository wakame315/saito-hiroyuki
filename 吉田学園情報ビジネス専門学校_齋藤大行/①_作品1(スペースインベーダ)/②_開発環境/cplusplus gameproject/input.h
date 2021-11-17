//=============================================================================
//
// ���͂̒�` [input.cpp]
// Author :�V����s
//
//=============================================================================
//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_
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

class CInput//���̓N���X
{
public:
	CInput();
	virtual~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void    Uninit(void);
	virtual void    Update(void) = 0;

private:

	
protected: 
	LPDIRECTINPUTDEVICE8 m_pDevice;//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;//Directinput�I�u�W�F�N�g�ւ̃|�C���^
	
};

#endif
//class CInputMouse : public CInput
//{
//public:
//	CInputMouse();
//	~CInputMouse();
//
//private:
//
//};
//
//class CInputJoyPat : public CInput
//{
//public:
//	CInputJoyPat();
//	~CInputJoyPat();
//
//private:
//
//};
//
//

