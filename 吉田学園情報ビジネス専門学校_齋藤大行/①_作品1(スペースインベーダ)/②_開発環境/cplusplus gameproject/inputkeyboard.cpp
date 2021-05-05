#include"inputkeyboard.h"

CInputKeyboard::CInputKeyboard()
{
	ZeroMemory(m_akeysrate,sizeof(m_akeysrate));//Windowsのみ使用可能
	//memset(m_akeysrate, 0, sizeof(m_akeysrate));
}

CInputKeyboard::~CInputKeyboard()
{

}
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	
	CInput::Init(hInstance, hWnd);

	//入力デバイスの(キーボード)の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モード設定(フォアグラウンド&排他モード)
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得(入力制御終了)
	m_pDevice->Acquire();

	return S_OK;

}
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
	
}
void CInputKeyboard::Update(void)
{
	BYTE akeystate[NUM_KEY_MAX];//キーボード入力情報
	int nCntkey;
	//デバイスからデータを所得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(akeystate), akeystate)))
	{
		for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			m_akeysrateTrigger[nCntkey] = (m_akeysrate[nCntkey] ^ akeystate[nCntkey]) & akeystate[nCntkey];
			m_akeysrateRelease[nCntkey] = (m_akeysrate[nCntkey] ^ akeystate[nCntkey]) &~akeystate[nCntkey];
			//キープレス情報を保存
			m_akeysrate[nCntkey] = akeystate[nCntkey];
		}
	}
	else
	{
		//キーボードのアクセス権を所得
		m_pDevice->Acquire();
	}
}


//キーボードのプレス状態を所得
bool CInputKeyboard::Getkeyboardpress(int nkey)
{
	return (m_akeysrate[nkey] & 0x80) ? true : false;
}

bool CInputKeyboard::GetkeyboardTrigger(int nkey)
{
	return (m_akeysrateTrigger[nkey] & 0x80) ? true : false;
}

bool CInputKeyboard::GetkeyboardRelease(int nkey)
{
	return (m_akeysrateRelease[nkey] & 0x80) ? true : false;
}