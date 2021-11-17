//=============================================================================
//
// �}�l�[�W���[�̒�` [manager.h]
// Author : �V����s
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "sound.h"

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CPlayer;
class CTitle;
class CResult;
class CTutorial;




class CManager//�}�l�[�W���[�N���X
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_END,
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Update(void);
	void Draw(void);
	void Uninit(void);
	void TextureLoad(void);
	void TextureUnLoad(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CManager *Create(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//�쐬����
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	CPlayer *GetPlayer(void);
private:
	static CRenderer *m_pRenderer;
	static CTutorial*m_pTutorial;
	static CInputKeyboard *m_pInputKeyboard;
	static CPlayer *m_pPlayer;
	static MODE m_Mode;
	static CTitle*m_pTitle;
	static CResult*m_pResult;
	static int m_nEnemy;
	static CSound *m_pSound;
};

#endif