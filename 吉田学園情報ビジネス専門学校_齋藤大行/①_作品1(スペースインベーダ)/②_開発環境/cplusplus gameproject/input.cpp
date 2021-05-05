//=============================================================================
//
// DirectX���^���� [main.h]
// Author :�V����s
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================


//===============================
//�O���[�o���ϐ��錾
//===============================


LPDIRECTINPUT8 CInput::m_pInput = NULL;


CInput::CInput()
{
	m_pDevice = NULL;
}

CInput::~CInput()
{
}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���I��)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//Directinput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}






