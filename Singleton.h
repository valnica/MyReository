//////////////////////////////////////////////
// Name : Singleton
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include <memory>

//////////////////////////////////////////////
// Class Name : Singleton
//
// Over View : �V���O���g���ɂ��邽�߂̃N���X
//////////////////////////////////////////////
template <class T>
class Singleton
{
private:
	//�V���O���g���p�̕ϐ�
	static std::shared_ptr<T> instance_;

public:
	Singleton<T>() = default;
	virtual ~Singleton<T>() = default;

	//�C���X�^���X�̎擾
	static std::shared_ptr<T> GetInstance()
	{
		if (!instance_)
			instance_.reset(new T);

		return instance_;
	}

	//�V���O���g���̃��Z�b�g
	void Reset()
	{
		instance_.reset();
	}
};

template <typename T>	
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;