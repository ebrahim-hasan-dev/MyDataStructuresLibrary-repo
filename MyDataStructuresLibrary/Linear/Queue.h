#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";


template <class T>
class Queue
{
private:

	struct stNode
	{
		T Data;
		stNode* NextNode;
	};

	stNode* _Front;
	stNode* _Rear;
	stNode* _Temp;

	int _Count;

	bool _IsNoSpaceInMemory()
	{
		return _Temp == nullptr;
	}

public:

	Queue()
	{
		_Front = nullptr;
		_Temp = nullptr;
		_Rear = nullptr;
		_Count = 0;
	}

	bool IsEmpty()
	{
		return _Front == nullptr;
	}

	T GetFront()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			return _Front->Data;
		}
	}

	T GetBack()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			return _Rear->Data;
		}

	}

	bool IsFull()
	{
		bool isFull = false;

		_Temp = new stNode;

		if (_Temp == nullptr)
		{
			isFull = true;
		}
		else
		{
			delete _Temp;
		}

		return isFull;
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

		for (stNode* temp = _Front; temp != nullptr; temp = temp->NextNode)
		{
			cout << temp->Data;

			if (temp->NextNode != nullptr)
			{
				cout << ", ";
			}
		}

		cout << " }\n\n";
	}

	int Count()
	{
		return _Count;
	}

	bool IsFound(T Element)
	{
		for (stNode* temp = _Front; temp != nullptr; temp = temp->NextNode)
		{
			if (temp->Data == Element)
			{
				return true;
			}
		}

		return false;
	}

	void Enqueue(T Element)
	{
		_Temp = new stNode;

		if (_IsNoSpaceInMemory())
		{
			cout << "\nNo Space in Memory\n";
			return;
		}

		_Temp->Data = Element;
		_Temp->NextNode = nullptr;

		if (IsEmpty())
		{
			_Rear = _Temp;
			_Front = _Temp;
		}
		else
		{
			_Rear->NextNode = _Temp;
			_Rear = _Temp;
		}

		_Count++;

	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(Queue<T>& queue)
	{
		if (!IsEmpty())
		{
			cout << "\nList Must be Empty!\n";
			return;
		}

		for (stNode* temp = queue._Front; temp != nullptr; temp = temp->NextNode)
		{
			this->Push(temp->Data);
		}

	}

	void Dequeue()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			stNode* temp = _Front;

			_Front = _Front->NextNode;

			if (_Front == nullptr)
			{
				_Rear = nullptr;
			}

			delete temp;

			_Count--;
		}
	}

	/*void Clear()
	{
		while (_Front != nullptr)
		{
			this->Pop();
		}

		_Count = 0;
	}*/

	void Clear()
	{
		while (_Front != nullptr)
		{
			stNode* temp = _Front;
			_Front = _Front->NextNode;
			delete temp;
		}

		_Count = 0;
		_Rear = nullptr;
	}

	~Queue()
	{
		Clear();
	}




};

