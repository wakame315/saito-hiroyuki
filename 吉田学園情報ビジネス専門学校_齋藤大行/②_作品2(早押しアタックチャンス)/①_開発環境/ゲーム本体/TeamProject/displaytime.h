//=============================================================================
//
// 表示時間定義[displaytime.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _DISPLAYTIME_H_
#define _DISPLAYTIME_H_
#define _CRT_SECURE_NO_WARNINGS


//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================

//オブジェクトクラス
class CDisplaytime : public CScene
{
public:
	CDisplaytime();
	~CDisplaytime();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void DrawTime(DWORD time);
	static void TriggerTime(DWORD TriggerTime);
	static void DrawMiss(void);
	DWORD GetTime(void);
	DWORD GetTriggerTime(void);
	//静的関数
	static HRESULT FontCreate(void);
	static void FontUninit(void);
	static CDisplaytime *Create();
private:
	static LPD3DXFONT              m_pTimeFont;//フォントへのポインタ
	static LPD3DXFONT              m_pMissFont;//フォントへのポインタ
	DWORD                   m_dwGameStartTime;//開始時間
	DWORD                   m_dwGamePressStartTime;//開始時間
	DWORD                   m_dwGameTime;//経過時間
	DWORD                   m_dwTriggerTime;//結果開始時間
	DWORD                   m_dwTriggerGameTime;//結果時間
	bool                    m_bCntTimeUse;//結果時間のカウント
	bool					m_bDraw;//描画
	bool					m_bPressUse;//ボタンが押せるかどうか
	bool					m_bStartTime;//ゲームの開始の時間を一度だけ取るため
	int						m_nStop;

};





#endif 
#pragma once
