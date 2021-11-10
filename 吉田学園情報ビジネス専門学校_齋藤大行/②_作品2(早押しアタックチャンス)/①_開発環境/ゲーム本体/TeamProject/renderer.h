//=============================================================================
//
// �����_���[��` [renderer.h]
// Author : �V����s
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include"main.h"
#include "protocol_ranking.h"
#include "manager.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CRenderer
{
public:
	CRenderer();												//�R���X�g���N�^
	~CRenderer();												//�f�X�g���N�^
	HRESULT Init(HWND hWnd, bool bWindow);						//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//�f�o�C�X����

private:
	
	void DrawFPS(void);						// FPS�\��
	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont;		// �t�H���g�ւ̃|�C���^
	int						m_nGameEnd;		// �Q�[���I������
	static CRanking::RankingData * m_RankingDeta[MAX_RANKING];//�����L���O�|�C���^

};
#endif
