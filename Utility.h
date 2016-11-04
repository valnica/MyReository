#pragma once

//w’è‚µ‚½”ÍˆÍ‚É•â³‚·‚é
template <typename T>
void Clamp(T min, T max, T& data)
{
	if (data > max) data = max;
	else if (data < min) data = min;
}

template <typename T>
void Swap(T& dataA, T& dataB)
{
	T data = dataA;
	dataA = dataB;
	dataB = data;
}