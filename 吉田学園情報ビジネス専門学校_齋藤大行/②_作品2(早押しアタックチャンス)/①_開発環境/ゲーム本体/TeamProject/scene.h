//=============================================================================
//
// シーン定義 [scene.h]
// Author : 齋藤大行
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include"main.h"



//=============================================================================
// クラス定義
//=============================================================================
class CScene
{
public:
	//==============================================
	//列挙型宣言
	//==============================================
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_POLYGON,		
		TYPE_DISPLAYTIME,
		TYPE_RANKING,
		TYPE_BG,
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

	static CScene *m_apScene[PRIORITY_MAX][MAX_POLYGON];  //ポリゴンのポインタ変数
	static int m_nNumAll;					//ポリゴンの数
	int m_nID;
	int m_nPriority;
	OBJTYPE m_objType;//オブジェクト種類
};

#endif 