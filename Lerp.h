////////////////////////////////////////////////////////////////////////////////
/// @file Lerp.h
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
#pragma once
#include <memory>
#include <DirectXMath.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief ���`��ԃf�[�^�N���X
////////////////////////////////////////////////////////////////////////////////
class ILerpData
{
public:
	// �R���X�g���N�^
	ILerpData(){};

	// �f�X�g���N�^
	virtual ~ILerpData(){};

	// �f�[�^�����Z�b�g
	virtual void Reset() = 0;

	// �f�[�^�̌����擾
	virtual size_t GetCount() = 0;

	// �f�[�^��ǉ�����
	virtual void Add(float time, float x, float y, float z) = 0;

	// �����̃f�[�^�����ׂĂ�ύX����
	virtual void SetData(unsigned int n, float time, float x, float y, float z) = 0;

	// �����̃f�[�^��ύX����
	virtual void ChangePos(unsigned int n, float x, float y, float z) = 0;

	// ���Ԃ��ϓ��ɐݒ肷��
	virtual void ComputeConstant() = 0;

	// �f�[�^���擾����
	virtual const float* GetPosition(unsigned int num) = 0;
};


////////////////////////////////////////////////////////////////////////////////
/// @brief ���`��ԉ��Z�N���X
////////////////////////////////////////////////////////////////////////////////
class Lerp
{
public:
	// �J��Ԃ��̃^�C�v�̌^
	enum LoopType
	{
		STOP,  // �Ō�̍��W�Œ�~
		LOOP,  // �ŏ��̍��W�ɖ߂�J��Ԃ�
		STRIP  // �Ō�̍��W����p��
	};
public:
	// ���ʂ�X,Y,Z�����ꂼ��󂯎��
	const float& GetX() const;
	const float& GetY() const;
	const float& GetZ() const;

	// ���ʂ�float[4]�Ŏ󂯎��
	const float* GetResult() const;

	// ���ʂ�float[4]�Ŏ󂯎��
	operator const float*() const;
	const float& operator[](int num) const;
	const float& operator[](char dimension) const;

//	typedef std::shared_ptr<ILerpData> DataPtr;
	using DataPtr = std::shared_ptr < ILerpData > ;

	// �R���X�g���N�^
	Lerp(void);
	Lerp(DataPtr &s);

	// �f�X�g���N�^
	virtual ~Lerp(void);

	// �J��Ԃ��̃^�C�v�̐ݒ�
	void SetLoop(LoopType type);

	// ��ԂŎg���f�[�^��ݒ肷��
	void SetData(DataPtr &s);

	// ���Ԃ�߂��āA���W���J�n�ʒu�ɂ���
	void Reset();

	// �o�ߎ��Ԃ̐ݒ�
	void SetElapsedTime(float e);

	// ���Ԃ�ύX
	void ChangeTime(float t);

	// �f�[�^���󂩃`�F�b�N����
	bool IsEmpty() const;

	// ��ԏ����X�V����
	void Update();

	// ��Ԃ��I���i��~�j���Ă��邩
	bool IsStop() const;

	// �J��Ԃ��񐔂����߂�
	int GetCount() const;

	// �f�[�^�̍쐬
	static DataPtr CreateData();

	//---------------------------
	// DirectXTK�ˑ�����
	// ���[���h�̐ݒ�
	void SetWorld(const DirectX::XMFLOAT4X4& world);

	// ���[���h�̎擾
	const DirectX::XMFLOAT4X4& GetWorld() const;
	//---------------------------

	//---------------------------
	// �f�o�b�O�p
	// �f�[�^�̃N���[�����쐬
	Lerp* Clone() const;

	// �f�[�^�̎擾
	DataPtr GetData() const;

	// ���[�v�^�C�v�̎擾
	LoopType GetLoopType() const;
	//---------------------------


private:
	class Impl; std::shared_ptr<Impl> pImpl;
};


