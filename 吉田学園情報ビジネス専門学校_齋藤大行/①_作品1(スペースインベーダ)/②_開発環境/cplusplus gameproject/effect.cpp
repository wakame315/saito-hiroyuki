#include "effect.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

HRESULT CEffect::Load(void)
{
	return S_OK;
}

void CEffect::Unload(void)
{
}

CEffect * CEffect::Create(D3DXVECTOR3 pos, int nSize_X, int nSize_Y)
{
	return nullptr;
}

HRESULT CEffect::Init()
{
	return S_OK;
}

void CEffect::Uninit(void)
{
}

void CEffect::Update(void)
{
	//�傫���̕ω�
	//�F(���l)�̕ω�

	//if(��莞�Ԍo��)
	//{
	//Uninit();
	//}

}

void CEffect::Draw(void)
{
	//���Z�����̐ݒ�DESTBLEND��NONE
	//CScene2d::Draw();
	//�ݒ�����ɖ߂�DESTBLEND��INVSRCALPHA
}
