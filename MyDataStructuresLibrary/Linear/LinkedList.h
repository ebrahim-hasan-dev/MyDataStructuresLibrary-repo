#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";




template <class T>
class LinkedList
{
private:

	struct stNode
	{
		T Data;
		stNode* NextNode;
	};


	stNode* _Head;
	stNode* _Temp;
	stNode* _Tail;

	int _Count;

	
	bool _IsNoSpaceInMemory()
	{
		return _Temp == NULL;
	}


public:


	LinkedList()
	{
		_Head = NULL;
		_Temp = NULL;
		_Tail = NULL;
		_Count = 0;
	}


	void Reverse()
	{
		if (_Head == nullptr)
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		stNode* PrevNode = nullptr;
		stNode* Current = _Head;
		stNode* Next = nullptr;
		
		_Tail = _Head;

		while (Current != nullptr)
		{
			Next = Current->NextNode;
			Current->NextNode = PrevNode;
			PrevNode = Current;
			Current = Next;
		}

		_Head = PrevNode;

		//=======================================

		/*stNode* next;

		for (stNode* temp = _Head->NextNode; temp != NULL; temp = next)
		{
			T D = temp->Data;

			next = temp->NextNode;

			Delete(D);

			InsertInFirst(D);	
		}*/

	}

	bool IsEmpty()
	{
		return _Head == NULL;
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

			InsertInLast(Element);

		}

	}

	/*void DisPlay()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		_Temp = _Head;

		cout << "\n\n{ ";

		for (short i = 0; i < _Count; i++)
		{
			cout << _Temp->Data;
			_Temp = _Temp->NextNode;

			if (i != _Count - 1)
			{
				cout << ", ";
			}
		} 

		cout << " }\n\n";
	}*/

	void DisPlay()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		cout << "\n\n{ ";

		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			cout << temp->Data;

			if (temp->NextNode != NULL)
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
		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == Element)
			{
				return true;
			}
		}

		return false;
	}
	
	int Search(T Element)
	{
		int index = 0;

		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == Element)
			{
				return index;
			}

			index++;
		}

		return -1;
	}

	T& GetCertainElement(T Element)
	{
		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == Element)
			{
				return temp->Data;
			}
		}

		cout << "\nElement Not Found!\n";
	}

	void Append(T Element)
	{
		InsertInLast(Element);
	}

	void InsertInFirst(T Element)
	{
		_Temp = new stNode;

		if (_IsNoSpaceInMemory())
		{
			cout << "\nNo Space in Memory\n";
			 return;
		}
	
		_Temp->Data = Element;
		_Temp->NextNode = _Head;

		_Head = _Temp;

		// this check make _Tail refer to currect position
		if (_Head->NextNode == NULL)
		{
			_Tail = _Head;
		}

		_Count++;
	}

	void InsertInLast(T Element)
	{
		if (IsEmpty())
		{
			InsertInFirst(Element);
			return;
		}

		_Temp = new stNode;

		if (_IsNoSpaceInMemory())
		{
			cout << "\nNo Space in Memory\n";
			return;
		}

		_Temp->Data = Element;
		_Temp->NextNode = NULL;

		// this way to Insert in last faster from useing loop
		_Tail->NextNode = _Temp;
		_Tail = _Temp;

		_Count++;
	}

	void InsertBeforeCertainElement(T Element, T BeforeThisElement)
	{
		_Temp = new stNode;

		if (_IsNoSpaceInMemory())
		{
			cout << "\nNo Space in Memory\n";
			return;
		}

		_Temp->Data = Element;
		
		stNode* PrevNode = _Head;

		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == BeforeThisElement)
			{
				if (PrevNode == temp)
				{
					InsertInFirst(Element);
				}
				else
				{
					_Temp->NextNode = temp;
					PrevNode->NextNode = _Temp;
					_Count++;
				}

				return;
			}

			PrevNode = temp;

		}

		// if list is empty this line wiil perform also
		cout << "\nThis Element (" << BeforeThisElement << ") Not Found!\n";

		delete _Temp;

	}

	void InsertAfterCertainElement(T Element, T AfterThisElement)
	{
		_Temp = new stNode;

		if (_IsNoSpaceInMemory())
		{
			cout << "\nNo Space in Memory\n";
			return;
		}

		_Temp->Data = Element;

		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == AfterThisElement)
			{
				if (temp->NextNode == nullptr)
				{
					_Tail = _Temp;
				}

				_Temp->NextNode = temp->NextNode;
				temp->NextNode = _Temp;
				_Count++;
				return;
			}
		}

		// if list is empty this line will perform also
		cout << "\nThis Element (" << AfterThisElement << ") Not Found!\n";

		delete _Temp;

	}

	void InsertByIndex(int index, T Element)
	{
		if (index < 0 || index > _Count)
		{
			cout << "\nOut Of Range\n";
		}

		else if (index == 0)
		{
			InsertInFirst(Element);
		}

		else if (index == _Count)
		{
			InsertInLast(Element);
		}

		else
		{
			stNode* temp = _Head;

			// this for loop stop when temp = place before the place which deleted 
			for (short i = 1; i < index; i++)
			{
				temp = temp->NextNode;
			}

			_Temp = new stNode;
			_Temp->Data = Element;

			_Temp->NextNode = temp->NextNode;
			temp->NextNode = _Temp;
			_Count++;

		}

	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(LinkedList<T>& List)
	{
		if (!IsEmpty())
		{
			cout << "\nList Must be Empty!\n";
			return;
		}

		for (stNode* temp = List._Head; temp != NULL; temp = temp->NextNode)
		{
			this->InsertInLast(temp->Data);
		}

	}

	void DeleteFirst()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		if (_Tail == _Head)
		{
			_Tail = NULL;
		}

		stNode* temp = _Head;

		_Head = _Head->NextNode;

		delete temp;

		_Count--;
	}

	void  DeleteLast()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		stNode* PrevNode = _Head;

		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->NextNode == NULL)
			{
				if (PrevNode == temp)
				{
					delete temp;
					_Head = NULL;
					_Tail = NULL;
					_Count--;
					return;
				}

				PrevNode->NextNode = NULL;
				_Tail = PrevNode;
				delete temp;
				_Count--;
				return;

			}

			PrevNode = temp;
		}

	}

	void  Delete(T Element)
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		stNode* PrevNode = _Head;

		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == Element)
			{
				if (PrevNode == temp)
				{
					DeleteFirst();
				}
				else
				{
					PrevNode->NextNode = temp->NextNode;

					// check if this is last element (PrevNode)
					if (PrevNode->NextNode == NULL)
					{
						_Tail = PrevNode;
					}

					delete temp;

					_Count--;
				}

				return;
			}

			PrevNode = temp;
		}

		cout << "\nThis Element (" << Element << ") Not Found!\n";

	}

	void DeleteByIndex(int index)
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}

		else if (index < 0 || index >= _Count)
		{
			cout << "\nOut Of Range\n";
		}

		else if (index == 0)
		{
			DeleteFirst();
		}

		else if (index == _Count - 1)
		{
			DeleteLast();
		}

		else
		{
			stNode* temp = _Head;

			// this for loop stop when temp = place before the place which deleted 
			for (short i = 1; i < index; i++)
			{
				temp = temp->NextNode;
			}

			_Temp = temp->NextNode;
			temp->NextNode = _Temp->NextNode;
			delete _Temp;
			_Count--;

		}

	}

	void Replace(T ReplaceFrom, T ReplaceTo)
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
		{
			if (temp->Data == ReplaceFrom)
			{
				temp->Data = ReplaceTo;
				return;
			}
		}


	}

	T GetTail()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found\n";
		}
		else
		{
			return _Tail->Data;
		}
	}

	T GetHead()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found\n";
		}
		else
		{
			return _Head->Data;
		}
	}

	void Clear()
	{
		while (_Head != NULL)
		{
			stNode* temp = _Head;
			_Head = _Head->NextNode;
			delete temp;
		}

		_Tail = NULL;

		_Count = 0;
	}


	~LinkedList()
	{
		Clear();
	}



};

