//=============================================================================
//
// サウンド定義 [sound.h]
// Author : saito hiroyuki
//
//=============================================================================

//=============================================================================
//二重インクルード防止
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include <xaudio2.h>



//=============================================================================
// クラス宣言
//=============================================================================
class CSound//サウンドクラス
{
public:
	CSound();
	~CSound();

	//==============================================
	//列挙型宣言
	//==============================================
	typedef enum
	{
		SE_EX= 0,
		SE_HIT1,
		SE_HIT2,
		SE_BULLET_PLAYER,
		SE_BULLET_ENEMY,
		MAX
	} LABEL;

	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	// 各音素材のパラメータ
	static PARAM g_aParam[MAX];

	HRESULT Init(HWND hWnd);			//初期化処理
	void Uninit(void);					//終了処理	
	HRESULT Play(LABEL label);			//再生
	void Stop(LABEL label);				//停止
	void Stop(void);					//停止（すべて）

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[MAX];	// ソースボイス
	BYTE *m_apDataAudio[MAX];					// オーディオデータ
	DWORD m_aSizeAudio[MAX];					// オーディオデータサイズ
};




#endif 
