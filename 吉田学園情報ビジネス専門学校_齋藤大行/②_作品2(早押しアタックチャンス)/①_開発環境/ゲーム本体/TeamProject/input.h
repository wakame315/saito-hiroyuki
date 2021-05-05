#pragma once
//=============================================================================
//
// DirectX雛型処理 [input.cpp]
// Author :齋藤大行
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#define _CRT_SECURE_NO_WARNINGS

//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

class CInput
{
public:
	CInput();
	virtual~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void    Uninit(void);
	virtual void    Update(void) = 0;

private:


protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;//入力デバイス（キーボード）へのポインタ
	static LPDIRECTINPUT8 m_pInput;//Directinputオブジェクトへのポインタ

};

#endif
