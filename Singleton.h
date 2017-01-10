//////////////////////////////////////////////
// Name : Singleton
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include <memory>

//////////////////////////////////////////////
// Class Name : Singleton
//
// Over View : シングルトンにするためのクラス
//////////////////////////////////////////////
template <class T>
class Singleton
{
private:
	//シングルトン用の変数
	static std::shared_ptr<T> instance_;

public:
	Singleton<T>() = default;
	virtual ~Singleton<T>() = default;

	//インスタンスの取得
	static std::shared_ptr<T> GetInstance()
	{
		if (!instance_)
			instance_.reset(new T);

		return instance_;
	}

	//シングルトンのリセット
	void Reset()
	{
		instance_.reset();
	}
};

template <typename T>	
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;