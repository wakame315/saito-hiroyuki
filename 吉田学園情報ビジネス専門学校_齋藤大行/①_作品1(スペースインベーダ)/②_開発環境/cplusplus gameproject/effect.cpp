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
	//大きさの変化
	//色(α値)の変化

	//if(一定時間経過)
	//{
	//Uninit();
	//}

}

void CEffect::Draw(void)
{
	//加算合成の設定DESTBLENDをNONE
	//CScene2d::Draw();
	//設定を元に戻すDESTBLENDをINVSRCALPHA
}
