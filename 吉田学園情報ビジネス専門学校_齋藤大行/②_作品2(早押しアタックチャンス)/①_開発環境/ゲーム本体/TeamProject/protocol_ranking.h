//=============================================================================
//
// �����L���O��` [protocol_ranking.h]
// Author : �V����s
//
//=============================================================================
#ifndef _PROTOCOL_RANKING_H_
#define _PROTOCOL_RANKING_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
//=============================================================================
//�}�N����`
//=============================================================================
#define IPADDRESSSERVER "13.78.94.222"
#define IPADDRESS "127.0.0.1"


//=============================================================================
// �N���X��`
//=============================================================================
class CRanking
{
public:
	//==============================================
	//�\����
	//==============================================
	typedef struct
	{
		int nClearTime;
		int nRank;
		char aName[MAX_NAME];
	} RankingData;
 

	 //==============================================
	 //�񋓌^�錾
	 //==============================================
	typedef enum
	{
		COMMAND_TYPE_NONE = 0,
		COMMAND_TYPE_GET_RANKING,		// �����L���O�ꗗ���擾
		COMMAND_TYPE_SET_RANKING		// �����L���O��ݒ�
	} COMMAND_TYPE;

	CRanking();
	~CRanking();
	//********************************************
	//�v���g�^�C�v�錾
	//********************************************
	void ReadFile(void);
	static HRESULT FontCreate(void);
	static void FontUninit(void);
	static int SetRanking(int nTime);//�����L���O�o�^
	static void GetRanking(RankingData * pRankingData);//�����L���O�o�^
	static void Ranking(RankingData * RankingData, int Rank);//���ʐݒ�
private:
	static LPD3DXFONT				m_pRankingFont;				//�����L���O�p�t�H���g
	static LPD3DXFONT				m_pRankFont;				//���ʗp�t�H���g
	char m_aName[10];											//���O�ۑ��p

};
#endif
