////////////////////////////////////////////////////////////////////////////////
/// @file Lerp.cpp
/// ���`��Ԋ֘A�N���X
///
/// @author  Takafumi Murase @ freeplay inc.
///
/// @version Ver1.00 date2012.06.06  ����
///
/// @since   2012.06.06
///
///  Copyright(c) TRIDENT college 2012 , Takafumi Murase All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////
#include "Lerp.h"
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


////////////////////////////////////////////////////////////////////////////////
/// @brief �J�[�u�ʉߓ_�̏��
////////////////////////////////////////////////////////////////////////////////
class LerpInfo
{
public:
	float time;
	float x, y, z;
};

class ILerpDebugData
{
public:
	// �擪�f�[�^�̎擾
	LerpInfo* GetStart();

	// �ŏI�f�[�^���擾
	LerpInfo* GetEnd();

};

////////////////////////////////////////////////////////////////////////////////
/// @brief �J�[�u�ʉߓ_�̃R���e�i
////////////////////////////////////////////////////////////////////////////////
class LerpData : public ILerpData
{
public:
	LerpData();
	virtual ~LerpData();

	// �f�[�^���Z�b�g
	void Reset();

	// �擪�f�[�^�̎擾
	LerpInfo* GetStart();

	// �ŏI�f�[�^���擾
	LerpInfo* GetEnd();

	// �f�[�^�̐����擾
	size_t GetCount() override;

	// �f�[�^��ǉ�����
	void Add(float time, float x, float y, float z) override;

	// �ǉ�����Ă���f�[�^��ύX
	void SetData(unsigned int n, float time, float x, float y, float z) override;

	// �ǉ�����Ă���f�[�^�̍��W��ύX
	void ChangePos(unsigned int n, float x, float y, float z) override;

	// �n�_����I�_�܂ł̒ʉߎ��Ԃ��œK������
	void ComputeConstant() override;

	const float* GetPosition(unsigned int num) override;

	const static unsigned int num = 100;
	LerpInfo data[num];
	unsigned int count;

};


//-----------------------------------------------------------------------------
// �J�[�u���R���e�i�N���X
//-----------------------------------------------------------------------------

LerpData::LerpData()
{
	count = 0;
}

LerpData::~LerpData()
{
}

// �f�[�^���Z�b�g
void LerpData::Reset()
{
	count = 0;
}

// �擪�f�[�^�̎擾
LerpInfo* LerpData::GetStart()
{
	if (count == 0) return nullptr;
	return &data[0];
}

// �ŏI�f�[�^���擾
LerpInfo* LerpData::GetEnd()
{
	if (count == 0) return nullptr;
	return &data[count - 1];
}

// �f�[�^�̐����擾
size_t LerpData::GetCount()
{
	return count;
}

// �f�[�^��ǉ�����
void LerpData::Add(float time, float x, float y, float z)
{
	if (count >= num) return;

	SetData(count, time, x, y, z);

	count++;
}

// �ǉ�����Ă���f�[�^��ύX
void LerpData::SetData(unsigned int n, float time, float x, float y, float z)
{
	if (n >= num) return;

	if (n == 0 && time != 0.0f) time = 0.0f;
	auto &d = data[n];
	d.time = time;
	d.x = x;
	d.y = y;
	d.z = z;

}

// �ǉ�����Ă���f�[�^�̍��W��ύX
void LerpData::ChangePos(unsigned int n, float x, float y, float z)
{
	if (n >= num) return;
	auto &d = data[n];
	d.x = x;
	d.y = y;
	d.z = z;
}


// ��Ԃ𓙑��ړ��ɂ���
void LerpData::ComputeConstant()
{

	// �o�^�����Q�����̏ꍇ�������Ȃ�
	if (count < 2) return;

	// ��Ԃ��Ƃ̒�����o�^����ꏊ
	float len_table[num];

	// �I�����Ԃ��擾����
	float end_time = data[count - 1].time;

	// �S�̂̒���
	float len = 0.0f;

	// ��Ԃ̐��J��Ԃ�
	for (unsigned int i = 0; i < count - 1; i++)
	{
		// ��Ԃ̋����ƁA�S�̂̋��������߂�
		float x = data[i + 1].x - data[i].x;
		float y = data[i + 1].y - data[i].y;
		float z = data[i + 1].z - data[i].z;

		// ��Ԃ̋���
		len_table[i] = sqrt(x*x + y*y + z*z);

		// �S�̂̋���
		len += len_table[i];
	}

	// ��Ԃ̐��J��Ԃ�
	for (unsigned int i = 0; i < count - 1; i++)
	{
		// ��Ԃ̒ʉߎ��Ԃ��A��Ԃ̋����Ŋ��蓖�Ă�
		data[i + 1].time = data[i].time + end_time * (len_table[i] / len);
	}
}

const float* LerpData::GetPosition(unsigned int num)
{
	if (num >= count) return nullptr;
	return &data[num].x;
}


//-----------------------------------------------------------------------------
// �����N���X
//-----------------------------------------------------------------------------
class Lerp::Impl
{
public:
	Impl() :
		data(nullptr),
		x(0), y(0), z(0), w(1),
		elapsed(1),
		total_time(0),
		time(0),
		count(0),
		end_time(0),
		looptype(STOP),
		world(Matrix::Identity)
	{};
	~Impl(){};

	std::shared_ptr<LerpData> data;  // �f�[�^

	float elapsed;	   // �o�ߎ���
	float total_time;  // �o�ߎ���
	float time;        // �P��̌o�ߎ���
	float end_time;    // �P��̏I������
	int count;         // �J��Ԃ���
	LoopType looptype; // �J��Ԃ��̃^�C�v
	Matrix world;

	union // ���ʂ̍��W
	{
		struct
		{
			float x, y, z, w;
		};
		float vec[4];
	};

	void SetData(std::shared_ptr<LerpData> &s)
	{

		if (s == nullptr) return;
		if (s->GetCount() == 0) return;
		data = s;
		LerpInfo *start = data->GetStart();
		LerpInfo *end = data->GetEnd();
		if (start == nullptr || end == nullptr) return;

		// �I������
		end_time = end->time;

		// ���Ԃ̃��Z�b�g
		total_time = 0;
		time = 0;
		count = 0;

		// �J�n���W
		x = start->x;
		y = start->y;
		z = start->z;
	}

	// ���Ԃ�߂��āA���W���J�n�ʒu�ɂ���
	void Reset()
	{
		total_time = 0;
		time = 0;
		count = 0;

		LerpInfo *start = data->GetStart();
		x = start->x;
		y = start->y;
		z = start->z;

	}

	// ���Ԃ�ύX
	void ChangeTime(float t)
	{
		total_time = t;
		float e = elapsed;
		elapsed = 0.0f;
		Update();
		elapsed = e;
	}


	bool IsEmpty() const
	{
		if (data == nullptr) return true;
		if (data->GetCount() == 0) return true;

		return false;
	}

	// �K�v�Ȏ��ԏ������߂�
	void ClipTime()
	{
		count = (int)(fabs(total_time) / end_time);
		time = total_time - (end_time * count);
	}



	// ��ԏ����X�V����
	void Update()
	{
		if (IsEmpty()) return;
		//----------------------------------------
		// ��ԂɕK�v�Ȏ��Ԃ����߂鏈��

		// ���Ԃ�i�߂�
		total_time += elapsed;
		if (total_time < 0.0f) total_time = 0.0f;

		// �f�[�^���ݒ肳��Ă��Ȃ��Ƃ�
		if (data == nullptr) return;

		// ���ԏ������߂�
		ClipTime();

		//----------------------------------------
		// ��ԂɎg���������߂鏈��

		// �f�[�^�̐擪�ƏI�[�����߂�
		LerpInfo *start = data->GetStart();
		LerpInfo *end = data->GetEnd();

		// �f�[�^���ݒ肳��Ă��Ȃ��Ƃ�
		if (start == nullptr || end == nullptr) return;

		// ���݂̎��Ԃ���A�g���Ă���f�[�^��T��
		LerpInfo *target = start;
		for (; target != end + 1; target++)
		{
			if (target->time > time)break;
		}

		// ���ݎg���Ă���f�[�^�́A�J�n�ƏI���̃|�C���^�����߂�
		LerpInfo *s = target - 1;
		LerpInfo *e = target;

		//----------------------------------------
		// ��ԂɎg���W�����߂鏈��

		// ���Ԃ���W���i0.0�`1.0�j�����߂�
		float t = (time - s->time) / (e->time - s->time); // �W�������߂�

		//----------------------------------------
		// �J��Ԃ��̂Ƃ��̍��i�I�t�Z�b�g�j�����߂�

		// �I�t�Z�b�g���W
		float ox, oy, oz;

		// �I�t�Z�b�g���W�����߂�
		switch (looptype)
		{
		case STOP:
			if (count > 0)
			{
				// ��ԏ����������A�I�_�̍��W�����ʂƂ���
				x = end->x;
				y = end->y;
				z = end->z;
				return;
			}
			// �I�t�Z�b�g���W�Ȃ�	
			ox = oy = oz = 0;
			break;
		case LOOP:
			// �I�t�Z�b�g���W�Ȃ�
			ox = oy = oz = 0;
			break;
		case STRIP:
			// �I�t�Z�b�g���W�����߂�
			ox = (end->x - start->x) * count;
			oy = (end->y - start->y) * count;
			oz = (end->z - start->z) * count;
			break;
		}


		//----------------------------------------
		// ��Ԃ̌v�Z�����āA���W�����߂�
		{

			// ���̐����Ɋ�Â��Đ��`��Ԃ��s���܂��Bx + s(y - x)
			x = s->x + t * (e->x - s->x);
			y = s->y + t * (e->y - s->y);
			z = s->z + t * (e->z - s->z);
		}

		//----------------------------------------
		// �I�t�Z�b�g��������
		x += ox;
		y += oy;
		z += oz;


		Vector3 pos = Vector3::Transform(Vector3(vec), world);

		x = pos.x;
		y = pos.y;
		z = pos.z;
	}

	// ��Ԃ��I���i��~�j���Ă��邩
	bool IsStop()
	{
		if (looptype == STOP && end_time < total_time) return true;

		return  false;
	}

};


Lerp::Lerp(void) : pImpl(std::make_shared<Impl>())
{
}

Lerp::Lerp(DataPtr & s) : Lerp()
{
	pImpl->SetData(std::dynamic_pointer_cast<LerpData>(s));
}


Lerp::~Lerp(void)
{
}

// �J��Ԃ��̃^�C�v�̐ݒ�
void Lerp::SetLoop(LoopType type)
{
	pImpl->looptype = type;
}

// ��ԂŎg���f�[�^��ݒ肷��
void Lerp::SetData(DataPtr &s)
{
	pImpl->SetData(std::dynamic_pointer_cast<LerpData>(s));
}


// ���Ԃ�߂��āA���W���J�n�ʒu�ɂ���
void Lerp::Reset()
{
	pImpl->Reset();
}

// �o�ߎ��Ԃ̐ݒ�
void Lerp::SetElapsedTime(float e)
{
	pImpl->elapsed = e;
}

// ���Ԃ�ύX
void Lerp::ChangeTime(float t)
{
	pImpl->ChangeTime(t);
}


bool Lerp::IsEmpty() const
{
	return pImpl->IsEmpty();
}

// ��ԏ����X�V����
void Lerp::Update()
{
	pImpl->Update();
}

// ��Ԃ��I���i��~�j���Ă��邩
bool Lerp::IsStop() const
{
	return pImpl->IsStop();
}

// �J��Ԃ��񐔂����߂�
int Lerp::GetCount() const
{
	return pImpl->count;
}


// X�̎擾
const float& Lerp::GetX() const
{
	return pImpl->x;
}

// Y�̎擾
const float& Lerp::GetY() const
{
	return pImpl->y;
}

// Z�̎擾
const float& Lerp::GetZ() const
{
	return pImpl->z;
}

// ���ʂ�float[4]�Ŏ擾
const float* Lerp::GetResult() const
{
	return pImpl->vec;
}

// ���ʂ�float[4]�Ŏ擾
Lerp::operator const float*() const
{
	return pImpl->vec;
}

const float & Lerp::operator[](int num) const
{
#ifdef _DEBUG
	// 0,1,2,3�Ŏw�肵�Ă�������
	if (num < 0 || num > 3) //throw std::out_of_range("range of 0-3");
#endif // _DEBUG
	return pImpl->vec[num];
}

const float & Lerp::operator[](char dimension) const
{
#ifdef _DEBUG
	// 'X','Y','Z','W'�Ŏw�肵�Ă�������
	if (dimension < 'X' || dimension > 'W') //throw std::out_of_range("range of 'X'-'Z'");
#endif // _DEBUG
	return pImpl->vec[dimension - 'X'];
}


Lerp::DataPtr Lerp::CreateData()
{
	return std::make_shared<LerpData>();
}

Lerp* Lerp::Clone() const
{
	auto clone = new Lerp();

	clone->pImpl.reset(new Impl(*pImpl.get()));

	return clone;
}

Lerp::DataPtr Lerp::GetData() const
{
	return pImpl->data;
}

// ���[���h�̐ݒ�
void Lerp::SetWorld(const XMFLOAT4X4& world)
{
	pImpl->world = world;
}

// ���[���h�̎擾
const XMFLOAT4X4& Lerp::GetWorld() const
{
	return pImpl->world;
}



// ���[�v�^�C�v�擾
Lerp::LoopType Lerp::GetLoopType() const
{
	return pImpl->looptype;
}