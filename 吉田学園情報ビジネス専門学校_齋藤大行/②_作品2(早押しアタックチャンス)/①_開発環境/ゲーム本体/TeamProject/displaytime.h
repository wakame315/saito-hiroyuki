//=============================================================================
//
// �\�����Ԓ�`[displaytime.h]
// Author : �V����s
//
//=============================================================================
#ifndef _DISPLAYTIME_H_
#define _DISPLAYTIME_H_
#define _CRT_SECURE_NO_WARNINGS


//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================

//�I�u�W�F�N�g�N���X
class CDisplaytime : public CScene
{
public:
	CDisplaytime();
	~CDisplaytime();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void DrawTime(DWORD time);
	static void TriggerTime(DWORD TriggerTime);
	static void DrawMiss(void);
	DWORD GetTime(void);
	DWORD GetTriggerTime(void);
	//�ÓI�֐�
	static HRESULT FontCreate(void);
	static void FontUninit(void);
	static CDisplaytime *Create();
private:
	static LPD3DXFONT              m_pTimeFont;//�t�H���g�ւ̃|�C���^
	static LPD3DXFONT              m_pMissFont;//�t�H���g�ւ̃|�C���^
	DWORD                   m_dwGameStartTime;//�J�n����
	DWORD                   m_dwGamePressStartTime;//�J�n����
	DWORD                   m_dwGameTime;//�o�ߎ���
	DWORD                   m_dwTriggerTime;//���ʊJ�n����
	DWORD                   m_dwTriggerGameTime;//���ʎ���
	bool                    m_bCntTimeUse;//���ʎ��Ԃ̃J�E���g
	bool					m_bDraw;//�`��
	bool					m_bPressUse;//�{�^���������邩�ǂ���
	bool					m_bStartTime;//�Q�[���̊J�n�̎��Ԃ���x������邽��
	int						m_nStop;

};





#endif 
#pragma once
