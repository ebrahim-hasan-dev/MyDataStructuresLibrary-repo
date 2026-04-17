#pragma once

#include <iostream>
using namespace std;

#include "ClsMyQueue.h"


template <class T>
class ClsMyStack : public ClsMyQueue<T>
{
public:

	void Push(T Element)
	{
		ClsMyQueue<T>::_queue.InsertInFirst(Element);
	}

	void Fill()
	{
		int NumberOfElements = clsInput<int>::ReadPositiveNumber("How many elements you want to Fill : ");

		for (short i = 0; i < NumberOfElements; i++)
		{
			T Element;
			cout << "\nEnter Element Number " << i + 1 << " : ";

			// cin inside this fanction and his reseve the parametar by refrance 
			clsUtil<T>::MakeSureItisNumber2(Element);

			Push(Element);

		}
	}

	T GetTop()
	{
		return ClsMyQueue<T>::GetFront();
	}

	T Bottom()
	{
		return ClsMyQueue<T>::GetBack();
	}

};

