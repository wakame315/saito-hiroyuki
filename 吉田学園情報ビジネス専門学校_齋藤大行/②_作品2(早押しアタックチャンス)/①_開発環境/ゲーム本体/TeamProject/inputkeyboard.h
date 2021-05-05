//=============================================================================
//
// DirectX雛型処理 [inputkeyboard.cpp]
// Author :齋藤大行
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#define _CRT_SECURE_NO_WARNINGS

//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数
//=============================================================================
// インクルードファイル
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

	BYTE m_akeysrate[NUM_KEY_MAX];//キーボードの入力情報ワーク
	BYTE m_akeysrateTrigger[NUM_KEY_MAX];
	BYTE m_akeysrateRelease[NUM_KEY_MAX];

};

#endif