#ifndef _TITLE_H_
#define _TITLE_H_
#include "renderer.h"
class CScene2d;
class CTitle
{
public:
	CTitle();											//コンストラクタ
	~CTitle();											//デストラクタ
	static HRESULT Load(void);						//テクスチャの読み込み
	static void Unload(void);						// テクスチャの破棄
	static CTitle *Create(void);	//生成処理
	HRESULT Init(void);			//初期化処理
	void Uninit(void);								//終了処理	
	void Update(void);
	void Draw(void);								//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャ変数
	CScene2d *m_apScene2d;

};
#endif // !_TITLE_H_
