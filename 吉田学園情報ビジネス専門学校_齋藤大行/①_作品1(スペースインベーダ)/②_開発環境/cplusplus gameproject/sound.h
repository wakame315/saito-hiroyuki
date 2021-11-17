//=============================================================================
//
// �T�E���h��` [sound.h]
// Author : saito hiroyuki
//
//=============================================================================

//=============================================================================
//��d�C���N���[�h�h�~
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include <xaudio2.h>



//=============================================================================
// �N���X�錾
//=============================================================================
class CSound//�T�E���h�N���X
{
public:
	CSound();
	~CSound();

	//==============================================
	//�񋓌^�錾
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
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	// �e���f�ނ̃p�����[�^
	static PARAM g_aParam[MAX];

	HRESULT Init(HWND hWnd);			//����������
	void Uninit(void);					//�I������	
	HRESULT Play(LABEL label);			//�Đ�
	void Stop(LABEL label);				//��~
	void Stop(void);					//��~�i���ׂāj

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};




#endif 
