//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
#include "scene.h"
#include "polygon.h"
#include "protocol_ranking.h"
#include "sound.h"

class CRenderer;
class CInputKeyboard;
class CNumber;
class CDisplaytime;
class CTitle;
class CTutorial;
class CResult;
class CManager
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
	static CRanking::RankingData * GetRankinData(void);
	static bool GetGameEnd(void);
	static DWORD GeResultTime(void);
	static CSound *GetSound(void);
	CPolygon *GetPlayer(void);
	
private:
	static DWORD m_Gettime;
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static MODE m_Mode;
	static CTitle*m_pTitle;
	static CTutorial*m_pTutorial;
	static CResult*m_pResult;
	static CRanking::RankingData m_RankingDeta[MAX_RANKING];
	static bool m_bGameEnd;
	static CSound *m_pSound;
	CPolygon * m_pPlayer;
	
	int m_nNumber;
	int m_nGameEndState;
	int m_nDisTimeinit;
	
};

#endif