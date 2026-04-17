#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";


template <class T>
class Stack
{
private:

	struct stNode
	{
		T Data;
		stNode* NextNode;
	};

	stNode* _Top;
	stNode* _Temp;

	int _Count = 0;

	bool _IsNoSpaceInMemory()
	{
		return _Temp == NULL;
	}

	void _InsertInLast(T Element)
	{
		stNode* temp;

		for (temp = _Top; temp != NULL; temp = temp->NextNode)
		{
			if (temp->NextNode == NULL)
			{
				break;
			}
		}

		_Temp = new stNode;

		if (_IsNoSpaceInMemory())
		{
			cout << "\nNo Space in Memory\n";
			return;
		}

		_Temp->Data = Element;
		_Temp->NextNode = NULL;

		temp->NextNode = _Temp;

	}

public:

	Stack()
	{
		_Top = NULL;
		_Temp = NULL;
	}

	bool IsEmpty()
	{
		return _Top == NULL;
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

	void DisPlay()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		cout << "\n\n{ ";

		for (stNode* temp = _Top; temp != NULL; temp = temp->NextNode)
		{
			cout << temp->Data;

			if (temp->NextNode != NULL)
			{
				cout << ", ";
			}
		}

		cout << " }\n\n";
	}

	T GetTop()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			return _Top->Data;
		}
	}

	int Count()
	{
		return _Count;
	}

	bool IsFound(T Element)
	{
		for (stNode* temp = _Top; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == Element)
			{
				return true;
			}
		}

		return false;
	}

	bool IsFull()
	{
		bool isFull = false;

		_Temp = new stNode;

		if (_Temp == NULL)
		{
			isFull = true;
		}
		else
		{
			delete _Temp;
		}

		return isFull;
	}

	void Push(T Element)
	{
		_Temp = new stNode;

		if (_IsNoSpaceInMemory())
		{
			cout << "\nNo Space in Memory\n";
			return;
		}

		_Temp->Data = Element;
		_Temp->NextNode = _Top;

		_Top = _Temp;

		_Count++;

	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(Stack<T>& stack)
	{
		if (!IsEmpty())
		{
			cout << "\nStack Must be Empty!\n";
			return;
		}

		this->Push(stack._Top->Data);

		for (stNode* temp = stack._Top->NextNode; temp != NULL; temp = temp->NextNode)
		{
			this->_InsertInLast(temp->Data);
		}

		this->_Count = stack._Count;
	}

	void  Pop()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		_Temp = _Top;

		_Top = _Top->NextNode;

		delete _Temp;

		_Count--;
	}

	void Clear()
	{
		while (_Top != NULL)
		{
			stNode* temp = _Top;
			_Top = _Top->NextNode;
			delete temp;
		}

		_Count = 0;
	}

	~Stack()
	{
		Clear();
	}


};

