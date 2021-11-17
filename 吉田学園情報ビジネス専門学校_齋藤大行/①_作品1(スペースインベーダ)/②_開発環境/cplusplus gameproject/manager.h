//=============================================================================
//
// マネージャーの定義 [manager.h]
// Author : 齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "sound.h"

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CTitle;
class CResult;
class CTutorial;




class CManager//マネージャークラス
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_END,
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	void TextureLoad(void);
	void TextureUnLoad(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CManager *Create(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//作成処理
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	CPlayer *GetPlayer(void);
private:
	static CRenderer *m_pRenderer;
	static CTutorial*m_pTutorial;
	static CInputKeyboard *m_pInputKeyboard;
	static CPlayer *m_pPlayer;
	static MODE m_Mode;
	static CTitle*m_pTitle;
	static CResult*m_pResult;
	static int m_nEnemy;
	static CSound *m_pSound;
};

#endif