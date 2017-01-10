//////////////////////////////////////////////
// Name : Debug
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "Debug.h"
#include "GameManager.h"
#include "Camera.h"

#include "Used\Direct3D.h"
#include <CommonStates.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;
using namespace DirectX::SimpleMath;

bool Debug::debugFlag_ = false;

//////////////////////////////////////////////
// Name : Debug
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Debug::Debug()
{
}

//////////////////////////////////////////////
// Name : ~Debug
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Debug::~Debug()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void Debug::Initialize()
{
	//�v���~�e�B�u�`��ɕK�v�ȏ�������
	basicEffect_.reset(new BasicEffect(g_pd3dDevice.Get()));
	basicEffect_->SetVertexColorEnabled(true);
	primitiveBatch_.reset(new PrimitiveBatch<VertexPositionColor>(g_pImmediateContext.Get()));

	void const* shaderByteCode;
	size_t byteCodeLength;
	basicEffect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	g_pd3dDevice.Get()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength, inputLayOut_.GetAddressOf());
}

//////////////////////////////////////////////
// Name : DrawLine
//
// Over View : �f�o�b�O���C���ѕ`��
//
// Argument : �n�_�A�I�_
//
// Return :  ����
//////////////////////////////////////////////
void Debug::DrawLine(Vector3 v1, Vector3 v2)
{
	if (!debugFlag_) return;

	CommonStates state(g_pd3dDevice.Get());

	g_pImmediateContext->OMSetBlendState(state.Opaque(), nullptr, 0xFFFFFFFF);
	g_pImmediateContext->OMSetDepthStencilState(state.DepthDefault(), 0);
	g_pImmediateContext->RSSetState(state.CullNone());

	basicEffect_->Apply(g_pImmediateContext.Get());
	g_pImmediateContext->IASetInputLayout(inputLayOut_.Get());

	Matrix world = Matrix::Identity;
	Matrix view = Camera::MainCamera().lock()->GetView();
	Matrix proj = Camera::MainCamera().lock()->GetProj();

	basicEffect_->SetWorld(world);
	basicEffect_->SetView(view);
	basicEffect_->SetProjection(proj);

	VertexPositionColor pos1(v1, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	VertexPositionColor pos2(v2, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	primitiveBatch_->Begin();

	primitiveBatch_->DrawLine(pos1, pos2);

	primitiveBatch_->End();
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : �f�o�b�O���̕`��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void Debug::Draw()
{
#ifdef DEBUG
	wchar_t mousePosX[20];
	swprintf_s(mousePosX, 20, L"mouse_x = %d", g_mouse.x);
	g_spriteFont->DrawString(g_spriteBatch.get(), mousePosX, Vector2(0, 20));

	wchar_t mousePosY[20];
	swprintf_s(mousePosY, 20, L"mouse_y = %d", g_mouse.y);
	g_spriteFont->DrawString(g_spriteBatch.get(), mousePosY, Vector2(0, 40));

	DrawLine(start_, end_);

#endif //DEBUG
}