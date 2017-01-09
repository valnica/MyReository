//////////////////////////////////////////////
// Class Name : LandShape
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "LandShape.h"
#include <fstream>
#include <algorithm>
#include "CollisionNode.h"
#include "Collision.h"

#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

unique_ptr<LandShapeCommon> LandShape::common_;
map<wstring, unique_ptr<LandShapeData>> LandShape::dataArray_;

//////////////////////////////////////////////
// Name : LansShapeCommon
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
LandShapeCommon::LandShapeCommon(std::shared_ptr<LandShapeCommonDef> def)
{
	//�n�`�̕`��ɕK�v�ȕϐ��̏�������
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
		inputLayout_.GetAddressOf());

	deviceContext_ = def->deviceContext_;
}

//////////////////////////////////////////////
// Name : ~LansShapeCommon
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
LandShapeCommon::~LandShapeCommon()
{
}

//////////////////////////////////////////////
// Name : InitializeCommon
//
// Over View : �n�`�̋��ʐݒ�N���X�̏�����
//
// Argument : �n�`�̃f�t�H���g�ݒ�p�N���X
//
// Return :  ����
//////////////////////////////////////////////
void LandShape::InitializeCommon(std::shared_ptr<LandShapeCommonDef> def)
{
	if (common_) return;

	common_.reset(new LandShapeCommon(def));
}

//////////////////////////////////////////////
// Name : LandShape
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
LandShape::LandShape()
	:data_(nullptr)
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : MDL�̃p�X�ACMO�̃p�X
//
// Return :  ����
//////////////////////////////////////////////
void LandShape::Initialize(const wchar_t * fileNameMDL, const wchar_t * fileNameCMO)
{
	//MDL�ǂݍ��񂾂��Ƃ����邩����
	if (fileNameMDL)
	{
		if (dataArray_.count(fileNameMDL) == 0)
		{
			dataArray_[fileNameMDL] = LandShapeData::CreateFromMDL(fileNameMDL);
		}
		data_ = dataArray_[fileNameMDL].get();
	}

	//cmo�̓ǂݍ���
	if (fileNameCMO)
	{
		object_.LoadModelFromFile(fileNameCMO);
	}
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void LandShape::Update()
{
	//�����蔻��ɓo�^
	CollisionManager::GetInstance()->Entry(this);
}

//////////////////////////////////////////////
// Name : Calc
//
// Over View : ���[���h�v�Z
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void LandShape::Calc()
{
	object_.Calc();
	const Matrix& world = object_.GetWorld();
	world_ = world.Invert();
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : �n�`�̃��f���̕`��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void LandShape::Draw()
{
	if (!Debug::GetFlag())
	{
		object_.Draw();
	}
#ifdef DEBUG
	else if (data_)
	{
		const Matrix& view = Camera::MainCamera().lock()->GetView();
		const Matrix& proj = Camera::MainCamera().lock()->GetView();

		common_->effect_->SetWorld(object_.GetLocalWorld());
		common_->effect_->SetView(view);
		common_->effect_->SetProjection(proj);

		common_->effect_->Apply(common_->deviceContext_);

		common_->deviceContext_->OMSetDepthStencilState(common_->state_->DepthDefault(), 0);

		common_->deviceContext_->OMSetBlendState(common_->state_->NonPremultiplied(), nullptr, 0xfffffff);

		common_->deviceContext_->RSSetState(common_->state_->CullClockwise());

		auto samplerState = common_->state_->PointWrap();
		common_->deviceContext_->PSSetSamplers(0, 1, &samplerState);

		common_->deviceContext_->IASetInputLayout(common_->inputLayout_.Get());

		common_->primitiveBatch_->Begin();

		const uint16_t* index = &data_->indices_[0];
		int numIndex = data_->indices_.size();

		const VertexPositionNormal* vertex = (VertexPositionNormal*)&data_->vertices_[0];
		int numVertex = data_->vertices_.size();

		common_->primitiveBatch_->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, index, numIndex, vertex, numVertex);

		common_->primitiveBatch_->End();
		box_.Draw();
	}
#endif //DEBUG
}

//////////////////////////////////////////////
// Name : IntersectSphere
//
// Over View : �n�`�Ƌ��̓����蔻��
//
// Argument : ���A���������ꏊ��ۑ�����ϐ�
//
// Return :  ����
//////////////////////////////////////////////
bool LandShape::IntersectSphere(const Sphere & sphere, DirectX::SimpleMath::Vector3* reject)
{
	//MDL�����邩�ǂ���
	if (!data_) return false;

	//�O�p�`�̐�
	int tri = data_->indices_.size() / 3;
	
	//���������t���O
	bool hit = false;

	//�傫�������ŏ�����
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

	//�����蔻��
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

	//�߂��ꏊ��ۑ�
	if (hit)
	{
		distance *= scale;

		const Matrix& localWorld = object_.GetLocalWorld();

		if (reject)
		{
			*reject = Vector3::TransformNormal(normal, localWorld);
			reject->Normalize();
			*reject = (*reject)* (sphere.radius_ - distance);
		}
	}

	return hit;
}

//////////////////////////////////////////////
// Name : IntersectSegment
//
// Over View : �n�`�Ɛ����̓����蔻��
//
// Argument : �����A���������ꏊ��ۑ�����ϐ�
//
// Return :  ����
//////////////////////////////////////////////
bool LandShape::IntersectSegment(const Segment& segment, Vector3* inter,float angleofFloor)
{
	if (data_ == nullptr) return false;

	Collision collision;

	// �O�p�`�̐�
	int nTri = data_->indices_.size() / 3;
	// �q�b�g�t���O��������
	bool hit = false;
	// �傫�������ŏ�����
	float distance = 1.0e5;
	// �p�x����p�ɒn�ʂƂ݂Ȃ��p�x�̌��E�l<�x>
	const float limit_angle = XMConvertToRadians(angleofFloor);
	Vector3 l_inter;

	// �R�s�[
	Segment localSegment = segment;
	// ���������[���h���W���烂�f�����W�n�Ɉ�������
	localSegment.start_ = Vector3::Transform(localSegment.start_, world_);
	localSegment.end_ = Vector3::Transform(localSegment.end_, world_);
	// �����̕����x�N�g�����擾
	Vector3 segmentNormal = localSegment.end_ - localSegment.start_;
	segmentNormal.Normalize();

	for (int i = 0; i < nTri; i++)
	{
		// �O�p�`�̊e���_�̃C���f�b�N�X���擾
		int index0 = data_->indices_[i * 3];
		int index1 = data_->indices_[i * 3 + 1];
		int index2 = data_->indices_[i * 3 + 2];
		// �e���_�̃��[�J�����W���擾
		Vector3 pos0 = data_->vertices_[index0].pos_;
		Vector3 pos1 = data_->vertices_[index1].pos_;
		Vector3 pos2 = data_->vertices_[index2].pos_;

		Triangle tri;

		// 3�_����O�p�`���\�z�iTODO:��Ɍv�Z���Ă����j
		collision.ComputeTriangle(pos0, pos1, pos2, &tri);

		float temp_distance;
		Vector3 temp_inter;

		// ������x�N�g���Ɩ@���̓���
		float dot = -segmentNormal.Dot(tri.Normal);
		// ������Ƃ̊p�x�����v�Z
		float angle = acosf(dot);
		// ������Ƃ̊p�x�����E�p���傫����΁A�n�ʂƂ݂Ȃ����A�X�L�b�v
		if (angle > limit_angle) continue;

		// �����ƎO�p�`�i�|���S���j�̌�������
		if (collision.CheckSegment2Triangle(localSegment, tri, &temp_inter))
		{
			hit = true;
			// �Փ˓_�܂ł̋������Z�o
			temp_distance = Vector3::Distance(localSegment.start_, temp_inter);
			// ��������ԋ߂����̂��L�^
			if (temp_distance < distance)
			{
				l_inter = temp_inter;
				distance = temp_distance;
			}
		}
	}

	if (hit && inter != nullptr)
	{
		// ��_�����f�����W�n���烏�[���h���W�n�ɕϊ�
		const Matrix& localworld = object_.GetLocalWorld();
		*inter = Vector3::Transform(l_inter, localworld);
	}

	return hit;
}
