//=============================================================================
//
// �L�[�{�[�h�̓��͏��� [main.h]
// Author :�V����s
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "inputkeyboard.h"
#include "input.h"
#include "main.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	ZeroMemory(m_akeysrate, sizeof(m_akeysrate));//Windows�̂ݎg�p�\
												 //memset(m_akeysrate, 0, sizeof(m_akeysrate));
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//=============================================================================
//�����������֐�
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X��(�L�[�{�[�h)�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h�ݒ�(�t�H�A�O���E���h&�r�����[�h)
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���I��)
	m_pDevice->Acquire();

	return S_OK;

}

//=============================================================================
//�I�������֐�
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();

}

//=============================================================================
//�X�V�����֐�
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE akeystate[NUM_KEY_MAX];//�L�[�{�[�h���͏��
	int nCntkey;
	//�f�o�C�X����f�[�^������
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(akeystate), akeystate)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_akeysrateTrigger[nCntkey] = (m_akeysrate[nCntkey] ^ akeystate[nCntkey]) & akeystate[nCntkey];
			m_akeysrateRelease[nCntkey] = (m_akeysrate[nCntkey] ^ akeystate[nCntkey]) &~akeystate[nCntkey];
			//�L�[�v���X����ۑ�
			m_akeysrate[nCntkey] = akeystate[nCntkey];
		}
	}
	else
	{
		//�L�[�{�[�h�̃A�N�Z�X��������
		m_pDevice->Acquire();
	}
}


//�L�[�{�[�h�̃v���X��Ԃ�����
bool CInputKeyboard::Getkeyboardpress(int nkey)
{
	return (m_akeysrate[nkey] & 0x80) ? true : false;
}
//�L�[�{�[�h�̃g���K�O��Ԃ�����
bool CInputKeyboard::GetkeyboardTrigger(int nkey)
{
	return (m_akeysrateTrigger[nkey] & 0x80) ? true : false;
}
//�L�[�{�[�h�̃����[�X��Ԃ�����
bool CInputKeyboard::GetkeyboardRelease(int nkey)
{
	return (m_akeysrateRelease[nkey] & 0x80) ? true : false;
}