#pragma once

template <class T>
class State
{
private:

public:
	State() {};
	virtual ~State() {};

	virtual State<T>* Input(T& data) = 0;
	virtual void Update(T& data) = 0;
};