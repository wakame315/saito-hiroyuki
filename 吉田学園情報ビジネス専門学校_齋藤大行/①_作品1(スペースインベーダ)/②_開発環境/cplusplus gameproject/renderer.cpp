#include"renderer.h"
#include"scene.h"
#include "manager.h"
#include "number.h"

CRenderer::CRenderer()
{ 
	m_pD3D = 0;
	m_pD3DDevice = 0;
	m_pFont = 0;
	
}

CRenderer::~CRenderer()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
																	// �C���^�[�o��

	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �f�o�C�X�̐���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	CScene::UpdateAll();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 5), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{

		CScene::DrawAll();

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif
		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifndef Si

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CRenderer::InitPolygon(void)
{

	// �|���S���̈ʒu��ݒ�
	m_posPolygon = D3DXVECTOR3(640, 360, 0);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(m_pD3DDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME,					// �t�@�C���̖��O
		&m_pTexture);									// �ǂݍ��ރ������[

														// ���_�o�b�t�@�̐���
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	// ���_����ݒ�
	pVtx[0].Pos = D3DXVECTOR3(m_posPolygon.x + (-POLYGON_SIZE_Y / 2), m_posPolygon.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_posPolygon.x + (POLYGON_SIZE_X / 2) , m_posPolygon.y + (-POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_posPolygon.x + (-POLYGON_SIZE_X / 2), m_posPolygon.y + (POLYGON_SIZE_Y / 2), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_posPolygon.x + (POLYGON_SIZE_X / 2) , m_posPolygon.y + (POLYGON_SIZE_Y / 2), 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhwn�̐ݒ�i�l��1.0�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�̃J���[(0�`255�͈̔͂Őݒ�)
	pVtx[0].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].clo = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();


	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CRenderer::UninitPolygon(void)
{
	//�e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{	
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{	
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CRenderer::UpdatePolygon(void)
{

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static float fradian = 0.0f;
	static float fradius = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fradius = sqrtf(((TEXTURE_WIDTH / 2)*(TEXTURE_WIDTH / 2)) + ((TEXTURE_HEIGHT / 2)*(TEXTURE_HEIGHT / 2)));
	fradian = atan2f((TEXTURE_HEIGHT / 2), (TEXTURE_WIDTH / 2));


	m_rot.z += D3DX_PI * 0.01f;
	if (m_rot.z >= D3DX_PI)
	{	
		m_rot.z -= D3DX_PI * 2.0f;
	}

	//���_����ݒ�
	VERTEX_2D *pVtx;


	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].Pos = D3DXVECTOR3(m_posPolygon.x - (cosf(fradian - m_rot.z) * fradius), m_posPolygon.y - (sinf(fradian - m_rot.z) * fradius), 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_posPolygon.x + (cosf(fradian + m_rot.z) * fradius), m_posPolygon.y - (sinf(fradian + m_rot.z) * fradius), 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_posPolygon.x - (cosf(fradian + m_rot.z) * fradius), m_posPolygon.y + (sinf(fradian + m_rot.z) * fradius), 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_posPolygon.x + (cosf(fradian - m_rot.z) * fradius), m_posPolygon.y + (sinf(fradian - m_rot.z) * fradius), 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhwn�̐ݒ�i�l��1.0�ŌŒ�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�̃J���[(0�`255�͈̔͂Őݒ�)
	pVtx[0].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].clo = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].clo = D3DCOLOR_RGBA(255, 255, 255, 255);

	m_pVtxBuff->Unlock();


}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CRenderer::DrawPolygon(void)
{

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	m_pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

#endif // !SU

#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", GetFPS());

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif


