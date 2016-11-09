#include "Debug.h"
#include "Direct3D.h"
#include <CommonStates.h>
#include "GameManager.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

bool Debug::debugFlag_ = false;

Debug::Debug()
{
}


Debug::~Debug()
{
	if (inputLayOut_)
		inputLayOut_->Release();
}

void Debug::Initialize()
{
	basicEffect_.reset(new BasicEffect(g_pd3dDevice.Get()));
	basicEffect_->SetVertexColorEnabled(true);
	primitiveBatch_.reset(new PrimitiveBatch<VertexPositionColor>(g_pImmediateContext.Get()));

	void const* shaderByteCode;
	size_t byteCodeLength;
	basicEffect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	g_pd3dDevice.Get()->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,&inputLayOut_);
}

void Debug::DrawLine(Vector3 v1,Vector3 v2)
{
	if (!debugFlag_) return;

	CommonStates state(g_pd3dDevice.Get());

	g_pImmediateContext->OMSetBlendState(state.Opaque(), nullptr, 0xFFFFFFFF);
	g_pImmediateContext->OMSetDepthStencilState(state.DepthDefault(), 0);
	g_pImmediateContext->RSSetState(state.CullNone());

	basicEffect_->Apply(g_pImmediateContext.Get());
	g_pImmediateContext->IASetInputLayout(inputLayOut_);

	Matrix world = Matrix::Identity;
	Matrix view = GameManager::GetInstance()->GetCamera()->GetView();
	Matrix proj = GameManager::GetInstance()->GetCamera()->GetProj();

	basicEffect_->SetWorld(world);
	basicEffect_->SetView(view);
	basicEffect_->SetProjection(proj);

	VertexPositionColor pos1(v1, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	VertexPositionColor pos2(v2, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	primitiveBatch_->Begin();

	primitiveBatch_->DrawLine(pos1, pos2);

	primitiveBatch_->End();
}