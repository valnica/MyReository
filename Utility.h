//////////////////////////////////////////////
// Name : Utility
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Name : Clamp
//
// Over View : �w�肵���͈͂ɐ�������
//
// Argument : �ŏ��l�A�ő�l�A ��������f�[�^
//
// Return : ����
//////////////////////////////////////////////
template <typename T>
void Clamp(T min, T max, T& data)
{
	if (data > max) data = max;
	else if (data < min) data = min;
}

//////////////////////////////////////////////
// Name : Swap
//
// Over View : �f�[�^�̓���ւ�
//
// Argument : ����ւ��f�[�^�P�A����ւ��f�[�^�Q
//
// Return : ����
//////////////////////////////////////////////
template <typename T>
void Swap(T& dataA, T& dataB)
{
	T data = dataA;
	dataA = dataB;
	dataB = data;
}