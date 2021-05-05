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
	//‘å‚«‚³‚Ì•Ï‰»
	//F(ƒ¿’l)‚Ì•Ï‰»

	//if(ˆê’èŠÔŒo‰ß)
	//{
	//Uninit();
	//}

}

void CEffect::Draw(void)
{
	//‰ÁZ‡¬‚Ìİ’èDESTBLEND‚ğNONE
	//CScene2d::Draw();
	//İ’è‚ğŒ³‚É–ß‚·DESTBLEND‚ğINVSRCALPHA
}
