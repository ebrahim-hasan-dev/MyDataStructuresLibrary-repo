#pragma once

#include <iostream>
using namespace std;

#include "ClsMyQueueArr.h"


template <class T>
class ClsMyStackArr : public ClsMyQueueArr<T>
{
public:

	void Push(T item)
	{
		ClsMyQueueArr<T>::_queue.InsertAtFirst(item);
	}

	T GetTop()
	{
		return ClsMyQueueArr<T>::_queue.GetItem(0);
	}

	T Bottom()
	{
		return ClsMyQueueArr<T>::_queue.GetLastItem();
	}

	void Fill()
	{
		int NumberOfElements = clsInput<int>::ReadPositiveNumber("How many elements you want to Fill : ");

		for (int i = 0; i < NumberOfElements; i++)
		{
			T Element;
			cout << "\nEnter Element Number " << i + 1 << " : ";

			// cin inside this fanction and his reseve the parametar by refrance 
			clsUtil<T>::MakeSureItisNumber2(Element);

			Push(Element);

		}
	}




};

