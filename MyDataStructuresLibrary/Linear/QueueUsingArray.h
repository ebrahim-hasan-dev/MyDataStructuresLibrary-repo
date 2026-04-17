#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";


template <class T>
class QueueUsingArray
{
private:

	int _Frount;
	int _Rear;

	int _Count;

	int _MaxSize;

	T *_arr;

public:

	QueueUsingArray(int size)
	{
		if (size <= 0)
		{
			_MaxSize = 100;
		}
		else
		{
			_MaxSize = size;
		}
		
		//_Frount = -1;
		//_Rear = -1;

		_arr = new T[_MaxSize];

		_Frount = 0;
		_Rear = _MaxSize - 1;
		_Count = 0;
		
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

	bool IsEmpty()
	{
		return _Count == 0;
	}

	bool IsFull()
	{
		return _Count == _MaxSize;
	}

	void Push(T item)
	{
		if (IsFull())
		{
			cout << "\n\nQueue is full!\n\n";
		}
		else
		{
			/*if (_Rear == _MaxSize - 1)
			{
				_Rear = 0;
			}
			else
			{
				_Rear++;
				
				if (IsEmpty())
				{
					_Frount++;
				}
			}

			_arr[_Rear] = item;
			_Count++;*/

			_Rear = (_Rear + 1) % _MaxSize;

			_arr[_Rear] = item;

			_Count++;
		}
	}

	void Pop()
	{
		/*if (IsEmpty())
		{
			cout << "\n\nQueue is empty!\n\n";
		}
		else
		{
			if (_Frount == _MaxSize - 1)
			{
				_Frount = 0;
			}
			else
			{
				_Frount++;
			}

			_Count--;
		}*/

		if (IsEmpty())
		{
			cout << "\n\nQueue is empty!\n\n";
		}
		else
		{
			_Frount = (_Frount + 1) % _MaxSize;

			_Count--;
		}
	}

	T GetFrount()
	{
		if (IsEmpty())
		{
			cout << "\nQueue Empty!\n";
		}
		else
		{
			return _arr[_Frount];
		}
	}

	T GetBack()
	{
		if (IsEmpty())
		{
			cout << "\nQueue Empty!\n";
		}
		else
		{
			return _arr[_Rear];
		}
	}

	T GetSize()
	{
		return _Count;
	}

	void Clear()
	{
		//_Frount = -1;
		//_Rear = -1;

		_Frount = 0;
		_Rear = _MaxSize - 1;
		_Count = 0;
	}

	int Search(T item)
	{
		int temp = _Frount;

		for (short i = 0; i < _Count; i++)
		{
			if (item == _arr[temp])
			{
				return temp;
			}

			temp = (temp + 1) % _MaxSize;
		}

		return -1;
	}

	void Print()
	{
		int temp = _Frount;

		cout << "\n\n{  ";

		/*for (short i = 0; i < _Count; i++)
		{
			cout << *_arr[temp] << " ";

			if (temp == _MaxSize - 1)
			{
				temp = 0;
			}
			else
			{
				temp++;
			}

			if (i != _Count - 1)
			{
				cout << ", ";
			}
		 
		}*/

		for (short i = 0; i < _Count; i++)
		{
			cout << _arr[temp] << " ";

			temp = (temp + 1) % _MaxSize;

			if (i != _Count - 1)
			{
				cout << ", ";
			}
		}

		cout << " }\n\n";
	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(QueueUsingArray<T>& queue)
	{
		if (!IsEmpty())
		{
			cout << "\nList Must be Empty!\n";
			return;
		}

		if (_MaxSize != queue._MaxSize)
		{
			cout << "\nthe size of the two queues must be the same!\n";
			return;
		}

		int temp = queue._Frount;

		for (int i = 0; i < queue._Count; i++)
		{
			_arr[temp] = queue._arr[temp];

			temp = (temp + 1) % _MaxSize;
		}

		_Frount = queue._Frount;
		_Rear = queue._Rear;
		_Count = queue._Count;
	}

	~QueueUsingArray()
	{
		delete[]_arr;
		_arr = nullptr;
	}


};

