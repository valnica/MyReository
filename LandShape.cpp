#include "LandShape.h"
#include <fstream>
#include <algorithm>
#include "CollisionNode.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

unique_ptr<LandShapeCommon> LandShape::common_;
map<wstring, unique_ptr<LandShapeData>> LandShape::dataArray_;

LandShapeCommon::LandShapeCommon(LandShapeCommonDef* def)
{
	camera_ = def->camera_;
	state_.reset(new CommonStates(def->device_));
	primitiveBatch_.reset(new PrimitiveBatch<VertexPositionNormal>(def->deviceContext_));

	effect_.reset(new BasicEffect(def->device_));
	effect_->SetLightingEnabled(true);
	effect_->SetAmbientLightColor(Color(0.0f, 0.0f, 0.0f));
	effect_->SetDiffuseColor(Vector3(1.0f, 1.0f, 1.0f));
	effect_->SetLightEnabled(0, true);
	effect_->SetLightDiffuseColor(0, Vector3(0.2f, 1.0f, 0.2f));
	effect_->SetLightDirection(0, Vector3(1.0f, -0.5f, 2.0f));
	effect_->SetLightEnabled(1, true);
	effect_->SetLightDiffuseColor(1, Vector3(0.5f, 0.2f, 0.3f));
	effect_->SetLightDirection(1, Vector3(-1.0f, -0.5f, -2.0f));

	void const* shaderByteCode;
	size_t byteCodeLenght;
	effect_->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLenght);

	def->device_->CreateInputLayout(VertexPositionNormal::InputElements,
		VertexPositionNormal::InputElementCount,
		shaderByteCode, byteCodeLenght,
		&inputLayout_);

	deviceContext_ = def->deviceContext_;
}

LandShapeCommon::~LandShapeCommon()
{
	if (inputLayout_)
	{
		inputLayout_->Release();
		inputLayout_ = nullptr;
	}
}

void LandShape::InitializeCommon(LandShapeCommonDef* def)
{
	if (common_) return;

	common_.reset(new LandShapeCommon(def));
}

LandShape::LandShape()
	:data_(nullptr)
{
}

void LandShape::Initialize(const wchar_t * fileNameMDL, const wchar_t * fileNameCMO)
{
	if (fileNameMDL)
	{
		if (dataArray_.count(fileNameMDL) == 0)
		{
			dataArray_[fileNameMDL] = LandShapeData::CreateFromMDL(fileNameMDL);
		}
		data_ = dataArray_[fileNameMDL].get();
	}

	if (fileNameCMO)
	{
		object_.LoadModelFromFile(fileNameCMO);
	}
}

void LandShape::Calc()
{
	object_.Calc();
	const Matrix& world = object_.GetWorld();
	world_ = world.Invert();
}

void LandShape::Draw()
{
	if (!CollisionNode::GetDebugVisible())
	{
		object_.Draw();
	}
	else if (data_)
	{
		const Matrix& view = common_->camera_->GetView();
		const Matrix& proj = common_->camera_->GetProj();

		common_->effect_->SetWorld(object_.GetWorld());
		common_->effect_->SetView(view);
		common_->effect_->SetProjection(proj);

		common_->effect_->Apply(common_->deviceContext_);

		common_->deviceContext_->OMSetDepthStencilState(common_->state_->DepthDefault(), 0);

		common_->deviceContext_->OMSetBlendState(common_->state_->NonPremultiplied(), nullptr, 0xfffffff);

		common_->deviceContext_->RSSetState(common_->state_->CullClockwise());

		auto samplerState = common_->state_->PointWrap();
		common_->deviceContext_->PSSetSamplers(0, 1, &samplerState);

		common_->deviceContext_->IASetInputLayout(common_->inputLayout_);

		common_->primitiveBatch_->Begin();

		const uint16_t* index = &data_->indices_[0];
		int numIndex = data_->indices_.size();

		const VertexPositionNormal* vertex = (VertexPositionNormal*)&data_->vertices_[0];
		int numVertex = data_->vertices_.size();

		common_->primitiveBatch_->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, index, numIndex, vertex, numVertex);

		common_->primitiveBatch_->End();
	}
}

bool LandShape::IntersectSphere(const Sphere & sphere, DirectX::SimpleMath::Vector3* reject)
{
	if (!data_) return false;

	int tri = data_->indices_.size() / 3;
	bool hit = false;

	float distance = 1.0e5;
	Vector3 inter;
	Vector3 normal;
	Vector3 down;
	
	float scale = GetScale();

	Sphere localSphere = sphere;

	if (scale <= 1.0e-10)return false;

	localSphere.center_ = Vector3::Transform(sphere.center_, world_);
	localSphere.radius_ = sphere.radius_ / scale;

	Collision collision;

	for (int i = 0; i < tri; i++)
	{
		int index0 = data_->indices_[i * 3];
		int index1 = data_->indices_[i * 3 + 1];
		int index2 = data_->indices_[i * 3 + 2];

		Vector3 pos0 = data_->vertices_[index0].pos_;
		Vector3 pos1 = data_->vertices_[index1].pos_;
		Vector3 pos2 = data_->vertices_[index2].pos_;

		Triangle triangle;

		collision.ComputeTriangle(pos0, pos1, pos2,&triangle);

		float tempDistance;
		Vector3 tempInter;

		if (collision.CheckSphere2Triangle(localSphere, triangle, &tempInter))
		{
			hit = true;
			tempDistance = Vector3::Distance(localSphere.center_, tempInter);
			if (tempDistance < distance)
			{
				inter = tempInter;
				normal = triangle.Normal;
				distance = tempDistance;
			}
		}
	}

	if (hit)
	{
		distance *= scale;

		const Matrix& localWorld = object_.GetWorld();

		if (reject)
		{
			*reject = Vector3::TransformNormal(normal, localWorld);
			reject->Normalize();
			*reject = (*reject)* (sphere.radius_ - distance);
		}
	}

	return hit;
}

//--------------------------------------------------------------------------------------
// 地形と線分の交差判定
// segment : 線分
// （出力）inter : 交点（ポリゴンの平面上で、点との再接近点の座標を返す）
//--------------------------------------------------------------------------------------
bool LandShape::IntersectSegment(const Segment& segment, Vector3* inter)
{
	if (data_ == nullptr) return false;

	Collision collision;

	// 三角形の数
	int nTri = data_->indices_.size() / 3;
	// ヒットフラグを初期化
	bool hit = false;
	// 大きい数字で初期化
	float distance = 1.0e5;
	// 角度判定用に地面とみなす角度の限界値<度>
	const float limit_angle = XMConvertToRadians(30.0f);
	Vector3 l_inter;

	// コピー
	Segment localSegment = segment;
	// 線分をワールド座標からモデル座標系に引き込む
	localSegment.start_ = Vector3::Transform(localSegment.start_, world_);
	localSegment.end_ = Vector3::Transform(localSegment.end_, world_);
	// 線分の方向ベクトルを取得
	Vector3 segmentNormal = localSegment.end_ - localSegment.start_;
	segmentNormal.Normalize();

	for (int i = 0; i < nTri; i++)
	{
		// 三角形の各頂点のインデックスを取得
		int index0 = data_->indices_[i * 3];
		int index1 = data_->indices_[i * 3 + 1];
		int index2 = data_->indices_[i * 3 + 2];
		// 各頂点のローカル座標を取得
		Vector3 pos0 = data_->vertices_[index0].pos_;
		Vector3 pos1 = data_->vertices_[index1].pos_;
		Vector3 pos2 = data_->vertices_[index2].pos_;

		Triangle tri;

		// 3点から三角形を構築（TODO:先に計算しておく）
		collision.ComputeTriangle(pos0, pos1, pos2, &tri);

		float temp_distance;
		Vector3 temp_inter;

		// 上方向ベクトルと法線の内積
		float dot = -segmentNormal.Dot(tri.Normal);
		// 上方向との角度差を計算
		float angle = acosf(dot);
		// 上方向との角度が限界角より大きければ、地面とみなさず、スキップ
		if (angle > limit_angle) continue;

		// 線分と三角形（ポリゴン）の交差判定
		if (collision.CheckSegment2Triangle(localSegment, tri, &temp_inter))
		{
			hit = true;
			// 衝突点までの距離を算出
			temp_distance = Vector3::Distance(localSegment.start_, temp_inter);
			// 距離が一番近いものを記録
			if (temp_distance < distance)
			{
				l_inter = temp_inter;
				distance = temp_distance;
			}
		}
	}

	if (hit && inter != nullptr)
	{
		// 交点をモデル座標系からワールド座標系に変換
		const Matrix& localworld = object_.GetWorld();
		*inter = Vector3::Transform(l_inter, localworld);
	}

	return hit;
}