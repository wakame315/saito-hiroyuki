#ifndef _RESULT_H_
#define _RESULT_H_
#include "renderer.h"
class CScene2d;
class CResult
{
public:
	CResult(int nPriority = 4);											//コンストラクタ
	~CResult();											//デストラクタ
	static HRESULT Load(void);						//テクスチャの読み込み
	static void Unload(void);						// テクスチャの破棄
	static CResult *Create(void);	//生成処理
	HRESULT Init(void);			//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);
	void Draw(void);								//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ変数
	CScene2d *m_apScene2d;
};
#endif // !_RESULT_H_
