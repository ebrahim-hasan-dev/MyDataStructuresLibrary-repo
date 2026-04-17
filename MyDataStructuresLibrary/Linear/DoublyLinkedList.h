#pragma once

#include <iostream>
#include <stdexcept>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";



template <class T>
class DoublyLinkedList
{
public:

	struct stNode
	{
		T Data;
		stNode* NextNode;
		stNode* PreviousNode;
	};

private:

	stNode* _Head;
	stNode* _Temp;
	stNode* _Tail;

	int _Count;

	bool _IsNoSpaceInMemory()
	{
		return _Temp == NULL;
	}

public:

	DoublyLinkedList()
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
		}
		else
		{
			stNode* PrevNode = nullptr;
			stNode* Current = _Head;
			stNode* Next = nullptr;

			_Tail = _Head;

			while (Current != nullptr)
			{
				Next = Current->NextNode;
				Current->NextNode = PrevNode;
				Current->PreviousNode = Next;
				PrevNode = Current;
				Current = Next;
			}

			_Head = PrevNode;
		}

		//===================================

		/*stNode* temp2;

		for (stNode* temp = _Head->NextNode; temp != NULL; temp = temp2)
		{
			T D = temp->Data;

			temp2 = temp->NextNode;

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

	void DisPlayFromTail()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			cout << "\n\n{ ";

			for (stNode* temp = _Tail; temp != NULL; temp = temp->PreviousNode)
			{
				cout << temp->Data;

				if (temp->PreviousNode != NULL)
				{
					cout << ", ";
				}
			}

			cout << " }\n\n";
		}
	}

	int Size()
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
		}
		else
		{
			_Temp->Data = Element;
			_Temp->NextNode = _Head;
			_Temp->PreviousNode = nullptr;

			if (!IsEmpty())
			{
				_Head->PreviousNode = _Temp;
			}

			_Head = _Temp;
			
			// this check make _Tail refer to currect position
			if (_Head->NextNode == NULL)
			{
				_Tail = _Head;
			}

			_Count++;
		}

	}

	void InsertInLast(T Element)
	{
		if (IsEmpty())
		{
			InsertInFirst(Element);
		}
		else
		{
			_Temp = new stNode;

			if (_IsNoSpaceInMemory())
			{
				cout << "\nNo Space in Memory\n";
			}
			else
			{
				_Temp->Data = Element;
				_Temp->NextNode = NULL;
				_Temp->PreviousNode = _Tail;

				// this way to Insert in last faster from use loop
				_Tail->NextNode = _Temp;
				_Tail = _Temp;

				_Count++;
			}
		}

	}

	void InsertBeforeCertainElement(T Element, T BeforeThisElement)
	{
		if (_Head->Data == BeforeThisElement)
		{
			InsertInFirst(Element);
		}
		else
		{
			_Temp = new stNode;

			if (_IsNoSpaceInMemory())
			{
				cout << "\nNo Space in Memory\n";
			}
			else
			{
				_Temp->Data = Element;

				for (stNode* temp = _Head->NextNode; temp != NULL; temp = temp->NextNode)
				{
					if (temp->Data == BeforeThisElement)
					{
						stNode* prev = temp->PreviousNode;
						prev->NextNode = _Temp;
						_Temp->PreviousNode = prev;
						_Temp->NextNode = temp;
						temp->PreviousNode = _Temp;
						_Count++;
						return;
					}
				}

				// if list is empty this line wiil perform also
				cout << "\nThis Element (" << BeforeThisElement << ") Not Found!\n";

				delete _Temp;
			}
		}

	}

	void InsertAfterCertainElement(T Element, T AfterThisElement)
	{
		if (_Tail->Data == AfterThisElement)
		{
			InsertInLast(Element);
		}
		else
		{
			_Temp = new stNode;

			if (_IsNoSpaceInMemory())
			{
				cout << "\nNo Space in Memory\n";
			}
			else
			{
				_Temp->Data = Element;

				for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
				{
					if (temp->Data == AfterThisElement)
					{
						stNode* next = temp->NextNode;
						_Temp->NextNode = next;
						next->PreviousNode = _Temp;
						temp->NextNode = _Temp;
						_Temp->PreviousNode = temp;
						_Count++;
						return;
					}
				}

				// if list is empty this line will perform also
				cout << "\nThis Element (" << AfterThisElement << ") Not Found!\n";

				delete _Temp;
			}
		}

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
			_Temp = new stNode;
			_Temp->Data = Element;

			stNode* temp = _Head;

			for (short i = 0; i < index; i++)
			{
				temp = temp->NextNode;
			}

			stNode* prev = temp->PreviousNode;
			prev->NextNode = _Temp;
			_Temp->PreviousNode = prev;
			_Temp->NextNode = temp;
			temp->PreviousNode = _Temp;

			_Count++;

		}

	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(DoublyLinkedList<T>& List)
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
		}
		else
		{
			stNode* temp = _Head;

			_Head = _Head->NextNode;

			if (_Head != nullptr)
			{
				_Head->PreviousNode = nullptr;
			}
			else
			{
				_Tail = NULL;
			}

			delete temp;

			_Count--;
		}
	}

	void  DeleteLast()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			stNode* temp = _Tail;
			
			_Tail = _Tail->PreviousNode;

			if (_Tail != nullptr)
			{
				_Tail->NextNode = nullptr;
			}
			else
			{
				_Head = nullptr;
			}

			delete temp;

			_Count--;
		}

	}

	void  Delete(T Element)
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			if (_Head->Data == Element)
			{
				DeleteFirst();
			}
			else if (_Tail->Data == Element)
			{
				DeleteLast();
			}
			else
			{
				for (stNode* temp = _Head->NextNode; temp != NULL; temp = temp->NextNode)
				{
					if (temp->Data == Element)
					{
						stNode* prev = temp->PreviousNode;
						stNode* next = temp->NextNode;
						prev->NextNode = next;
						next->PreviousNode = prev;
						delete temp;
						_Count--;
						return;
					}
				}

				cout << "\nThis Element (" << Element << ") Not Found!\n";
			}
		}

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

			for (short i = 0; i < index; i++)
			{
				temp = temp->NextNode;
			}

			stNode* prev = temp->PreviousNode;
			stNode* next = temp->NextNode;
			prev->NextNode = next;
			next->PreviousNode = prev;
			delete temp;
			_Count--;

		}

	}

	void Replace(T ReplaceFrom, T ReplaceTo)
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
		}
		else
		{
			for (stNode* temp = _Head; temp != NULL; temp = temp->NextNode)
			{
				if (temp->Data == ReplaceFrom)
				{
					temp->Data = ReplaceTo;
					break;
				}
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

	// =============================================

	stNode* GetNode(int index)
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found\n";
			return nullptr;
		}

		if (index < 0 || index >= _Count)
		{
			cout << "\nOut Of Range\n";
			return nullptr;
		}

		stNode* tmp = _Head;

		for (int i = 0; i < index; i++)
		{
			tmp = tmp->NextNode;
		}

		return tmp;
	}

	T GetItem(int index)
	{
		stNode* node = GetNode(index);

		if (node == nullptr)
		{
			throw std::invalid_argument("Out Of Range");
		}
		else
		{
			return node->Data;
		}

	}

	bool UpdateItem(int index, T item)
	{
		stNode* node = GetNode(index);

		if (node != nullptr)
		{
			node->Data = item;
			return true;
		}
		else
		{
			return false;
		}
		
	}

	bool InsertAfter(int index, T item)
	{
		if (index < 0 || index >= _Count)
		{
			cout << "\nOut Of Range\n";
			return false;
		}

		stNode* tmp = _Head;

		for (int i = 0; i < index; i++)
		{
			tmp = tmp->NextNode;
		}

		if (tmp == _Tail)
		{
			InsertInLast(item);
			return true;
		}

		_Temp = new stNode;

		_Temp->Data = item;

		_Temp->NextNode = tmp->NextNode;
		tmp->NextNode->PreviousNode = _Temp;

		tmp->NextNode = _Temp;
		_Temp->PreviousNode = tmp;

		_Count++;

		return true;
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

	// ==============================================

	~DoublyLinkedList()
	{
		Clear();
	}




};

