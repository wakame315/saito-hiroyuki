#ifndef _POLGON_H_
#define _POLGON_H_

#include "main.h"
#include "scene2d.h"

//*********************************************************
// 前方宣言
//*********************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//
//オブジェクトクラス
class CPolygon : public CScene2d
{
public:
	typedef enum
	{
		TEX_SIGNAL_NONE,
		TEX_SIGNAL_GO,
		TEX_SIGNAL_MISS,
	}TEX_SIGNAL;

	CPolygon();
	~CPolygon();
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(TEX_SIGNAL signal);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexSignal(TEX_SIGNAL signal);
	bool SetbUse(bool bUse);
	TEX_SIGNAL GetTexSignal(void) { return m_tSignal; }
	bool GetUse(void);
	int GetRandom(void);
	//静的関数
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TEX_SIGNAL signal);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_SIGNAL];
	TEX_SIGNAL m_tSignal;
	bool m_buse;
	int m_nUseNum;
	int m_nMultiplication;
	int m_nOnePlay;
};
#endif 
