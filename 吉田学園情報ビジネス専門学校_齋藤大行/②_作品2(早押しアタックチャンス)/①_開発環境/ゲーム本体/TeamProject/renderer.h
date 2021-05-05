#//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include"main.h"
#include "protocol_ranking.h"
#include "manager.h"

//レンダリングクラス
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
	
	void DrawFPS(void);
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
	int						m_nGameEnd;
	static CRanking::RankingData * m_RankingDeta[MAX_RANKING];

};
#endif
