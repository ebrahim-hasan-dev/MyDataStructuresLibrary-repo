#pragma once

#include <iostream>
using namespace std;


template <class T>
class PriorityQueue
{
private:

	int _Add;
	int _Length;
	int _Capasity;

	T* _arr;

	bool _isAscendingOrder;


	void _Swap(int& a, int& b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}

	void _Heapfy(int arr[], int len, int Father)
	{
		int LeftChild = 2 * Father + 1;
		int RightChild = 2 * Father + 2;
		int m = Father;

		if (_isAscendingOrder == true)
		{
			if (LeftChild < len && arr[LeftChild] < arr[m])
			{
				m = LeftChild;
			}

			if (RightChild < len && arr[RightChild] < arr[m])
			{
				m = RightChild;
			}
		}
		else
		{
			if (LeftChild < len && arr[LeftChild] > arr[m])
			{
				m = LeftChild;
			}

			if (RightChild < len && arr[RightChild] > arr[m])
			{
				m = RightChild;
			}
		}

		if (m != Father)
		{
			_Swap(arr[Father], arr[m]);
			_Heapfy(arr, len, m);
		}

	}
	
	void _BuildHeap(int arr[], int len)
	{
		for (int i = (len - 1) / 2; i >= 0; i--)
		{
			_Heapfy(arr, len, i);
		}
	}

	/*void _HeapSort(int arr[], int len)
	{
		_BuildHeap(arr, len);

		for (int i = len - 1; i >= 1; i--)
		{
			_Swap(arr[0], arr[i]);

			if (i == 1)
				return;

			_Heapfy(arr, i, 0);
		}
	}*/

	void _ReSize()
	{
		if (_Capasity > _Length)
		{
			return;
		}

		if (_Capasity > 50)
		{
			_Capasity += 50;
		}
		else
		{
			_Capasity++;
		}

		T* ptr = _arr;

		_arr = new T[_Capasity];

		for (int i = 0; i < _Length; i++)
		{
			_arr[i] = ptr[i];
		}

		delete[] ptr;
	}

	void _ReduceSize()
	{
		_Capasity = _Length + 1;

		T* ptr = _arr;

		_arr = new T[_Capasity];

		for (int i = 0; i < _Length; i++)
		{
			_arr[i] = ptr[i];
		}

		delete[] ptr;
	}

public:

	PriorityQueue(bool isAscendingOrder = false)
	{
		_isAscendingOrder = isAscendingOrder;
		_Add = -1;
		_Length = 0;
		_Capasity = 1;

		_arr = new T[_Capasity];
	}
	
	bool IsEmpty()
	{
		return _Length == 0;
	}

	void Push(T item)
	{
		_Length++;
		
		_Add++;

		_arr[_Add] = item;

		_ReSize();

		if (_Length > 1)
		{
			int father = (_Add - 1) / 2;

			if (_isAscendingOrder == true ? _arr[father] > _arr[_Add] : _arr[father] < _arr[_Add])
			{
				_BuildHeap(_arr, _Length);
			}
		}
	}

	void Pop()
	{
		if (IsEmpty())
		{
			cout << "\n\nPriority Queue is Empty!\n\n";
		}
		else
		{
			_Length--;

			if (_Length == 0)
			{
				Clear();
			}

			_Swap(_arr[0], _arr[_Length]);

			if (_Length < (_Capasity - 20))
			{
				_ReduceSize();
			}

			if (_Length > 1)
			{
				_Heapfy(_arr, _Length, 0);
			}
		}
	}

	T GetTop()
	{
		if (IsEmpty())
		{
			cout << "\n\nPriority Queue is Empty!\n\n";
		}
		else
		{
			return _arr[0];
		}
	}

	T GetCapasity()
	{
		if (IsEmpty())
		{
			cout << "\n\nPriority Queue is Empty!\n\n";
		}
		else
		{
			return _Capasity;
		}
	}

	T GetSize()
	{
		return _Length;
	}

	void Clear()
	{
		delete[] _arr;

		_Add = -1;
		_Length = 0;
		_Capasity = 1;

		_arr = new T[_Capasity];
	}

	int Search(T item)
	{
		if (IsEmpty())
		{
			cout << "\n\nPriority Queue is Empty!\n\n";
		}
		else
		{
			for (short i = 0; i < _Length; i++)
			{
				if (item == _arr[i])
				{
					return i;
				}
			}

			return -1;
		}
	}

	~PriorityQueue()
	{
		delete[] _arr;
	}



};

