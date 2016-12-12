#pragma once
#include <memory>

template <class T>
class Singleton
{
private:
	static std::unique_ptr<T> instance_;
public:

	static std::unique_ptr<T>& GetInstance()
	{
		if (!instance_)
			instance_.reset(new T);

		return instance_;
	}

	void Reset()
	{
		instance_.reset();
	}
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance_ = nullptr;