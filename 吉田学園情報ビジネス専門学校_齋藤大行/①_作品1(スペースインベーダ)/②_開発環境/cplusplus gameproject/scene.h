//=============================================================================
//
// シーン定義 [scene.cpp]
// Author :齋藤大行
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include"main.h"


//=============================================================================
// クラス宣言
//=============================================================================
class CScene//シーンクラス
{
public:
	//==============================================
	//列挙型宣言
	//==============================================
typedef enum
{
	TYPE_NONE = 0,
	TYPE_PLAYER,		//プレイヤー
	TYPE_ENEMY,			//エネミー
	TYPE_EXPLOSION,		//爆発
	TYPE_BULLET,		//弾
	TYPE_BG,			//背景
	TYPE_SCORE,			//スコア
	TYPE_TITLE,			//タイトル
	TYPE_RESULT,		//リザルト
	TYPE_TUTORIAL,		//チュートリアル
	TYPR_MAX,			//最大数
}OBJTYPE;

	CScene(int nPriority = 2);          //コントラクタ
	virtual ~CScene();					//デストラクタ
	//純粋仮想関数					  
	virtual HRESULT Init(void) = 0;		//初期化処理
	virtual void    Uninit(void) = 0;	//終了処理
	virtual void    Update(void) = 0;	//更新処理
	virtual void    Draw(void) = 0;		//描画処理
	void SetObjType(OBJTYPE objType);	//タイプ所得
	OBJTYPE GetObjType(void) { return m_objType; }			//タイプ設定
	static CScene *GetScene(int nCnt);
	//静的関数
	static  void    UpdateAll(void);	//全更新
	static  void	DrawAll(void);		//全描画
	static  void	ReleaseAll(void);	//全削除
	        void	Release(void);		//削除
private:

	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];  //ポリゴンのポインタ変数
	static int m_nNumAll;					//ポリゴンの数
	int m_nID;								//シーンの番号
	int m_nPriority;						//描画順
	OBJTYPE m_objType;						//オブジェクト種類
};

#endif 