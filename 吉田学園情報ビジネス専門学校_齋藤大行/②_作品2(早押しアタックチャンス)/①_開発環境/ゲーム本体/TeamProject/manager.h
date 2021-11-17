//=============================================================================
//
// �}�l�[�W���[��` [manager.h]
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
#include "scene.h"
#include "polygon.h"
#include "protocol_ranking.h"
#include "sound.h"

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CNumber;
class CDisplaytime;
class CTitle;
class CTutorial;
class CResult;

//=============================================================================
// �N���X��`
//=============================================================================
class CManager//�}�l�[�W���[�N���X
{
public:
	
	//==============================================
	//�񋓌^�錾
	//==============================================
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_END,
	}MODE;
	CManager();																//�R���X�g���N�^
	~CManager();															//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);				//����������
	void Update(void);														//�X�V����
	void Draw(void);														//�`�揈��
	void Uninit(void);														//�I������
	void TextureLoad(void);													//�e�N�X�`�����[�h
	void TextureUnLoad(void);												//�e�N�X�`���A�����[�h
	static void SetMode(MODE mode);											//���[�h�ݒ�
	static MODE GetMode(void);												//���[�h����
	static CManager *Create(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//�쐬����
	static CRenderer *GetRenderer(void);									//�����_���[����
	static CInputKeyboard *GetInputKeyboard(void);							//�L�[�{�[�h����
	static CRanking::RankingData * GetRankinData(void);						//�����L���O����
	static bool GetGameEnd(void);											//�Q�[���I�����菊��
	static DWORD GeResultTime(void);										//���ʎ��ԏ���
	static CSound *GetSound(void);											//�T�E���h����
	CPolygon *GetPlayer(void);												//�v���C���[����
	
private:
	static DWORD m_Gettime;													//���ʎ��ԕۑ��p
	static CRenderer *m_pRenderer;											//�����_���[
	static CInputKeyboard *m_pInputKeyboard;								//�L�[�{�[�h����
	static MODE m_Mode;														//���[�h
	static CTitle*m_pTitle;													//�^�C�g��
	static CTutorial*m_pTutorial;											//�`���[�g���A��
	static CResult*m_pResult;												//���U���g
	static CRanking::RankingData m_RankingDeta[MAX_RANKING];				//�����L���O
	static bool m_bGameEnd;													//�Q�[���I������
	static CSound *m_pSound;												//�T�E���h
	CPolygon * m_pPlayer;													//�v���C���[

	int m_nGameEndState;													//�Q�[���I���J�ڃJ�E���g
};

#endif