//=============================================================================
//
// DirectX雛型処理 [score.cpp]
// Author :齋藤大行
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "number.h"

class CScore : public CScene
{
public:
	CScore();					//コントラクタ
	~CScore();					//デストラクタ
	static CScore *Create(void);	//作成処理
	HRESULT Init(void);				//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理
	void Draw(void);			//描画処理
	void SetScore(int nScore);  //スコア設定
	void AddScore(int nScore);

private:
	CNumber *m_apNumber[MAX_NUM];
	int m_nScore;
protected:


};

#endif
