//=============================================================================
//
// キーボードの入力定義 [inputkeyboard.h]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
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

//=============================================================================
// クラス定義
//=============================================================================
class CInputKeyboard : public CInput//キーボード入力クラス
{
public:
	CInputKeyboard();								//コンストラクタ
	~CInputKeyboard();								//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理

	bool Getkeyboardpress(int nkey);				//プレス
	bool GetkeyboardTrigger(int nkey);				//トリガー
	bool GetkeyboardRelease(int nkey);				//リリース
private:

	BYTE m_akeysrate[NUM_KEY_MAX];//キーボードの入力情報ワーク
	BYTE m_akeysrateTrigger[NUM_KEY_MAX];
	BYTE m_akeysrateRelease[NUM_KEY_MAX];

};

#endif