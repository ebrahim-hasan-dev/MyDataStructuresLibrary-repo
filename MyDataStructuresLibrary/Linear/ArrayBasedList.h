#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";


template <class T>
class ArrayBasedList
{
private:

	int _MaxSize;
	int _Length;

	T* _arr;

	void _Initialization(int begin = 0)
	{
		for (int i = begin; i < _MaxSize; i++)
		{
			_arr[i] = T();
		}
	}

public:

	ArrayBasedList(int Size = 0)
	{
		if (Size <= 0)
		{
			Size = 0;
		}

		_MaxSize = Size;
		_Length = 0;

		_arr = new T[_MaxSize];

		_Initialization();
	}

	bool IsEmpty()
	{
		return _Length == 0;
	}

	bool IsFull()
	{
		if (_Length == _MaxSize && _MaxSize != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Reverse()
	{
		if (_Length < 2)
		{
			return;
		}

		for (int i = 0; i < _Length / 2; i++)
		{
			swap(_arr[i], _arr[_Length - (i + 1)]);
		}	
	}

	void Fill()
	{
		int NumberOfElements = clsInput<int>::ReadPositiveNumber("How many elements you want to Fill : ");

		if (NumberOfElements > _MaxSize)
		{
			Resize(NumberOfElements);
		}

		_Length = NumberOfElements;

		for (int i = 0; i < NumberOfElements; i++)
		{
			T Element;
			cout << "\nEnter Element Number " << i + 1 << " : ";

			// cin inside this fanction and his reseve the parametar by refrance 
			clsUtil<T>::MakeSureItisNumber2(Element);

			Push_Back(Element);

		}
		
	}

	// here we must use & because not destractor call towice and Delete same places towice, one here and one in fanction main  
	void Copy(ArrayBasedList<T>& ArrayBasedList)
	{
		if (_MaxSize >= ArrayBasedList._MaxSize)
		{
			_Length = ArrayBasedList._Length;

			for (int i = 0; i < ArrayBasedList._MaxSize; i++)
			{
				_arr[i] = ArrayBasedList._arr[i];
			}
		}
		else
		{
			cout << "\nSize Of ArrayBasedList Not Valide!\n";
		}

	}

	void DisPlay()
	{
		if (IsEmpty())
		{
			cout << "\nno items found\n";
			return;
		}

		cout << "\n\n{ ";

		for (int i = 0; i < _MaxSize; i++)
		{
			if (_arr[i] != T())
			{
				cout << _arr[i] << ", ";
			}
		}

		cout << "}\n\n";
	}

	void Insert(int index, T NewItem)
	{
		if (index >= _MaxSize || index < 0)
		{
			cout << "\nOut Of Range\n";
			return;
		}

		Resize(_MaxSize + 1);
		
		for (int i = _MaxSize - 1; i > index; i--)
		{
			_arr[i] = _arr[i - 1];
		}

		_arr[index] = NewItem;
	
		_Length++;
	}

	void InsertAtFirst(T NewItem)
	{
		Insert(0, NewItem);
	}

	void InsertBefore(int index, T NewItem)
	{
		if (index < 1)
		{
			Insert(0, NewItem);
		}
		else
		{
			Insert(index - 1, NewItem);
		}
	}

	void InsertAfter(int index, T NewItem)
	{
		if (index >= _MaxSize - 1)
		{
			Push_Back(NewItem);
		}
		else
		{
			Insert(index + 1, NewItem);
		}
		
	}

	void Push_Back(T Element)
	{
		Resize(_MaxSize + 1);
		
		_arr[_MaxSize - 1] = Element;
		_Length++;
	}

	void Pop_Back()
	{
		if (IsEmpty() || _MaxSize == 0)
		{
			cout << "\nno items found\n";
			return;
		}

		if (_arr[_MaxSize - 1] != T())
		{
			_Length--;
		}

		Resize(_MaxSize - 1);
	}

	int Find(T Key)
	{
		if (IsEmpty())
		{
			cout << "\nno items found\n";
			return -1;
		}

		for (int i = 0; i < _MaxSize; i++)
		{
			if (_arr[i] == Key)
				return i;
		}

		return -1;
	}

	void InsertNoDuplecate(T Element)
	{
		if (Find(Element) == -1)
		{
			Push_Back(Element);
		}
		else
		{
			cout << "\n Element is there... \n";
		}
	}

	void DeleteByElement(T Element)
	{
		if (IsEmpty())
		{
			cout << "\nno items found\n";
			return;
		}

		short index = Find(Element);

		if (index == -1)
		{
			cout << "\nThe Element not Found in ArrayBasedList!\n";
		}
		else
		{
			DeleteByIndex(index);
		}
	}

	void DeleteByIndex(int index)
	{
		if (index >= _MaxSize || index < 0)
		{
			cout << "\nOut Of Range\n";
			return;
		}

		if (IsEmpty())
		{
			cout << "\nno items found\n";
			return;
		}

		if (_arr[index] != T())
		{
			_Length--;

			for (int i = index; i < _MaxSize - 1; i++)
			{
				_arr[i] = _arr[i + 1];
			}

			Resize(_MaxSize - 1);
		}

	}
	
	void DeleteFirst()
	{
		if (IsEmpty())
		{
			cout << "\nNo items found\n";
			return;
		}

		T* tmp = new T[_MaxSize - 1];

		for (int i = 1; i < _MaxSize; i++)
		{
			tmp[i - 1] = _arr[i];
		}

		_arr = tmp;

		_MaxSize--;
		_Length--;
	}

	void Resize(int NewSize)
	{
		if (NewSize > 0)
		{
			T* ptr = _arr;

			_arr = new T[NewSize];

			int tmp_MaxSize = -1;

			if (NewSize <= _MaxSize)
			{
				_MaxSize = NewSize;

				if (NewSize < _Length)
				{
					_Length = NewSize;
				}
			}
			else
			{
				tmp_MaxSize = _MaxSize;
			}


			for (int i = 0; i < _MaxSize; i++)
			{
				_arr[i] = ptr[i];
			}
			
			_MaxSize = NewSize;

			if (tmp_MaxSize != -1)
			{
				_Initialization(tmp_MaxSize);
			}

			delete[] ptr;
		}
		else
		{
			cout << "\nnew size must bigger than 0\n";
		}
	}

	/*void Merge(ArrayBasedList<T>& AnotherArray)
	{
		Resize(_MaxSize + AnotherArray._MaxSize);
		
		int len = AnotherArray.GetLength();

		for (short i = 0; i < len; i++)
		{
			_arr[_Length] = AnotherArray[i];

			_Length++;
		}
		
	}*/

	int GetSize()
	{
		return _MaxSize;
	}

	int GetLength()
	{
		return _Length;
	}

	void Clear()
	{
		delete[] _arr;
		_arr = new T[0];

		_MaxSize = 0;
		_Length = 0;
	}

	void UpdateItem(int index, T item)
	{
		if (index >= _MaxSize || index < 0)
		{
			cout << "\nOut Of Range\n";
			return;
		}

		_arr[index] = item;
	}

	T GetItem(int index)
	{
		if (index >= _MaxSize || index < 0)
		{
			throw std::invalid_argument("Out Of Range");
		}

		if (IsEmpty())
		{
			cout << "\nno items found\n";
			return T();
		}

		return _arr[index];
	}

	T GetLastItem()
	{
		if (IsEmpty())
		{
			throw std::invalid_argument("Out Of Range");
		}

		return _arr[_MaxSize - 1];
	}


	~ArrayBasedList()
	{
		delete[] _arr;
		_arr = nullptr;

		_MaxSize = 0;
		_Length = 0;
	}





};

