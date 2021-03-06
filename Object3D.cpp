//////////////////////////////////////////////
// Class Name : Object3D
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "Object3D.h"

#include <VertexTypes.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;
using namespace DirectX::SimpleMath;

ID3D11Device* Object3D::device_;
ID3D11DeviceContext* Object3D::deviceContext_;
CommonStates* Object3D::state_;
std::shared_ptr<DGSLEffectFactory> Object3D::effect_;
std::map<std::wstring, std::unique_ptr<DirectX::Model>> Object3D::modelArray_;

//////////////////////////////////////////////
// Name : Object3D
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Object3D::Object3D()
	:parentMatrix_(nullptr), model_(nullptr)
{
	scale_ = Vector3(1, 1, 1);
	useQuaternion_ = false;
}


//////////////////////////////////////////////
// Name : ~Object3D
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Object3D::~Object3D()
{
}

//////////////////////////////////////////////
// Name : LoadModelFromFile
//
// Over View : モデルの読み込み
//
// Argument : モデルのパス
//
// Return :  無し
//////////////////////////////////////////////
void Object3D::LoadModelFromFile(const wchar_t * fileName)
{
	assert(effect_);

	//読み込んだことあるか判定
	if (modelArray_.count(fileName) == 0)
		modelArray_[fileName] = Model::CreateFromCMO(device_, fileName, *effect_);

	model_ = modelArray_[fileName].get();
}

//////////////////////////////////////////////
// Name : DesableLighting
//
// Over View : ライトの設定
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void Object3D::DesableLighting()
{
	if (!model_) return;

	for (auto it_mesh = model_->meshes.begin(); it_mesh != model_->meshes.end(); it_mesh++)
	{
		ModelMesh* modelMesh = it_mesh->get();
		assert(modelMesh);

		for (auto it_meshPart = modelMesh->meshParts.begin(); it_meshPart != modelMesh->meshParts.end(); it_meshPart++)
		{
			ModelMeshPart* meshPart = it_meshPart->get();
			assert(meshPart);

			BasicEffect* effect = static_cast<BasicEffect*>(meshPart->effect.get());
			
			if (!effect) continue;

			XMVECTOR emissive;
			emissive.m128_f32[0] = 1.0f;
			emissive.m128_f32[1] = 1.0f;
			emissive.m128_f32[2] = 1.0f;
			emissive.m128_f32[3] = 1.0f;
			effect->SetEmissiveColor(emissive);

			for (int i = 0; i < BasicEffect::MaxDirectionalLights; i++)
			{
				effect->SetLightEnabled(i, false);
			}
		}
	}
}

//////////////////////////////////////////////
// Name : Calc
//
// Over View : ワールドの計算
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void Object3D::Calc()
{
	//ラジアン値に変換
	float rotX = XMConvertToRadians(rot_.x);
	float rotY = XMConvertToRadians(rot_.y);
	float rotZ = XMConvertToRadians(rot_.z);

	Matrix scale = Matrix::CreateScale(scale_);
	Matrix rot = Matrix::CreateFromYawPitchRoll(rotY, rotX, rotZ);
	Matrix trans = Matrix::CreateTranslation(trans_);

	//クォータニオン計算するかどうか
	if (useQuaternion_)
		rot = Matrix::CreateFromQuaternion(quaternion_);
	else
		rot = Matrix::CreateFromYawPitchRoll(rotY, rotX, rotZ);

	//ワールドの更新
	localWorld_ = scale * rot * trans;
	world_ = localWorld_;

	//親がいたら計算
	if (parentMatrix_)
		world_ = localWorld_ * (*parentMatrix_);
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : 描画処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void Object3D::Draw()
{
	if (!model_) return;

	assert(Camera::MainCamera().lock());
	const Matrix& view = Camera::MainCamera().lock()->GetView();
	const Matrix& proj = Camera::MainCamera().lock()->GetProj();

	assert(deviceContext_);
	assert(state_);

	model_->Draw(deviceContext_, *state_, world_, view, proj);
}