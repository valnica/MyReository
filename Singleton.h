#pragma once
#include <memory>

template <class T>
class Singleton
{
private:
	static std::unique_ptr<T> instance_;
public:

	static std::unique_ptr<T>& Get()
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