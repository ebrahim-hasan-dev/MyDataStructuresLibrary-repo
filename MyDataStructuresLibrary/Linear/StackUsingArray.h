#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";



const int MAXSIZE = 100;

template <class T>
class StackUsingArray
{
private:

	T _stack[MAXSIZE];

	int _top;

public:

	StackUsingArray() : _top (-1){}

	void Fill()
	{
		int NumberOfElements = clsInput<int>::ReadPositiveNumber("How many elements you want to Fill : ");

		for (short i = 0; i < NumberOfElements; i++)
		{
			T Element;
			cout << "\nEnter Element Number " << i + 1 << " : ";

			// cin inside this fanction and his reseve the parametar by refrance 
			clsUtil<T>::MakeSureItisNumber2(Element);

			push(Element);

		}

	}

	bool IsFull()
	{
		return _top == (MAXSIZE - 1);
	}

	void push(T item)
	{
		if (IsFull())
		{
			cout << "\n\nstack overflue\n\n";
		}
		else
		{
			_top++;
			_stack[_top] = item;
		}
		
	}

	void pop()
	{
		if (IsEmpty())
		{
			cout << "\n\nSatck Empty!\n\n";
		}
		else
		{
			_top--;
		}

	}

	T GetTop()
	{
		if (IsEmpty())
		{
			cout << "\n\nSatck Empty!\n\n";
		}
		else
		{
			return _stack[_top];
		}
	}

	bool IsEmpty()
	{
		return _top == -1;
	}

	void Display()
	{
		if (IsEmpty())
		{
			cout << "\n\nSatck Empty!\n\n";
		}
		else
		{
			cout << "\n\n{ ";

			for (short i = _top; i >= 0; i--)
			{
				cout << _stack[i] << " ";
			}

			cout << " }\n\n";
		}
	}

	int Count()
	{
		return _top + 1;
	}

	bool IsFound(T Element)
	{
		if (IsEmpty())
		{
			cout << "\n\nSatck Empty!\n\n";
			return;
		}

		for (int i = 0; i < _top + 1; i++)
		{
			if (_stack[i] == Element)
			{
				return true;
			}
		}

		return false;
	}

	void Copy(StackUsingArray<T> stack)
	{
		if (!IsEmpty())
		{
			cout << "\nStack Must be Empty!\n";
			return;
		}

		for (short i = 0; i < stack._top + 1; i++)
		{
			_stack[i] = stack._stack[i];
		}

		this->_top = stack._top;
	}

	void Clear()
	{
		_top = -1;
	}


};

