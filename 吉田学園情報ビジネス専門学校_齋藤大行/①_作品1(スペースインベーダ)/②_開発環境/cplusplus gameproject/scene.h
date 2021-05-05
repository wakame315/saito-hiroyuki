#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"



//オブジェクトクラス
class CScene
{
public:
	
typedef enum
{
	TYPE_NONE = 0,
	TYPE_PLAYER,		//プレイヤー
	TYPE_ENEMY,			//エネミー
	TYPE_EXPLOSION,		//爆発
	TYPE_BULLET,		//弾
	TYPE_BULLET2,
	TYPE_BG,
	TYPE_SCORE,
	TYPE_TITLE,
	TYPE_RESULT,
	TYPE_TUTORIAL,
	TYPR_MAX,
}OBJTYPE;

	CScene(int nPriority = 2);                           //コントラクタ
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
	static  void    UpdateAll(void);
	static  void	DrawAll(void);
	static  void	ReleaseAll(void);
	        void	Release(void);
private:

	static CScene *m_apScene[PRIORITY_MAX][MAX_SCENE];  //ポリゴンのポインタ変数
	static int m_nNumAll;					//ポリゴンの数
	int m_nID;
	int m_nPriority;
	OBJTYPE m_objType;//オブジェクト種類
};

#endif 