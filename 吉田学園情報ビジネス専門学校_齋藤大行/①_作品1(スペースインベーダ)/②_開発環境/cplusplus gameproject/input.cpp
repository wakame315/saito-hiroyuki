//=============================================================================
//
// DirectX雛型処理 [main.h]
// Author :齋藤大行
//
//=============================================================================

//インクルードファイル
#include "input.h"

//=============================================================================
// マクロ定義
//=============================================================================


//===============================
//グローバル変数宣言
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
		//キーボードへのアクセス権を獲得(入力制御終了)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//Directinputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}






