#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";
#include "..\Linear\Queue.h";


template <class T>
class BinarySearchTree
{
private:

	struct stNode
	{
		T Data;
		stNode* Left;
		stNode* Right;
	};

	stNode* _Root;
	
	int _Count;


	bool _IsNoSpaceInMemory(stNode* Root)
	{
		return Root == NULL;
	}


	// parameter -> ( stNode*& Root ) must be reseve by refrance 
	// parameter -> ( T& Element ) not must be reseve by refrance, we need reduce space in memory only 
	void _Insert(stNode*& Root, T& Element)
	{
		if (Root == NULL)
		{
			Root = new stNode;

			if (_IsNoSpaceInMemory(Root))
			{
				cout << "\nNo Space in Memory\n";
				return;
			}

			Root->Data = Element;
			Root->Left = NULL;
			Root->Right = NULL;

			_Count++;

			return;
		}

		if (Element < Root->Data)
		{
			_Insert(Root->Left, Element);
			return;
		}

		// else here mean >= 
		else
		{
			_Insert(Root->Right, Element);
			return;
		}

		// =========================

	/*	stNode* NewNode = new stNode;
		NewNode->Data = Element;
		NewNode->Left = nullptr;
		NewNode->Right = nullptr;

		stNode* temp = Root;

		while (temp != nullptr)
		{
			if (Element < temp->Data)
			{
				if (temp->Left == nullptr)
				{
					temp->Left = NewNode;
					break;
				}

				temp = temp->Left;
			}

			else if (Element >= temp->Data)
			{
				if (temp->Right == nullptr)
				{
					temp->Right = NewNode;
					break;
				}
				
				temp = temp->Right;
			}
		}

		 _Count++;*/

	}


	// parameter -> ( stNode*& Root ) must be reseve by refrance
	/*void _DeleteHelper(stNode*& Root)
	 {
		// here we must use ( if and else if ) no ( if and if)
		if (Root->Left == NULL && Root->Right == NULL)
		{
			delete Root;

			Root = NULL;
		}

		else if (Root->Left == NULL && Root->Right != NULL)
		{
			stNode* temp = Root;

			Root = Root->Right;

			delete temp;
		}

		else if (Root->Left != NULL && Root->Right == NULL)
		{
			stNode* temp = Root;

			Root = Root->Left;

			delete temp;
		}

		else if (Root->Left != NULL && Root->Right != NULL)
		{
			stNode* MaxElementInLeft = _FindMax(Root->Left);

			Root->Data = MaxElementInLeft->Data;

			_Delete(Root->Left, MaxElementInLeft->Data);
		}
	}*/


	// parameter -> ( stNode*& Root ) must be reseve by refrance
	bool _Delete(stNode*& Root, T& Element)
	{
		if (Root == NULL)
		{
			return false;
		}

		if (Element < Root->Data)
		{
			return _Delete(Root->Left, Element);
		}

		else if (Element > Root->Data)
		{
			return _Delete(Root->Right, Element);
		}

		else
		{
			// here we must use ( if and else if ) no ( if and if)
			if (Root->Left == NULL && Root->Right == NULL)
			{
				delete Root;

				Root = NULL;
			}

			else if (Root->Left == NULL && Root->Right != NULL)
			{
				stNode* temp = Root;

				Root = Root->Right;

				delete temp;
			}

			else if (Root->Left != NULL && Root->Right == NULL)
			{
				stNode* temp = Root;

				Root = Root->Left;

				delete temp;
			}

			else if (Root->Left != NULL && Root->Right != NULL)
			{
				stNode* MaxElementInLeft = _FindMax(Root->Left);

				Root->Data = MaxElementInLeft->Data;

				_Delete(Root->Left, MaxElementInLeft->Data);
			}
			
		}

		// ================================

		/*stNode* temp = Root;
		
		while (temp != nullptr)
		{
			if (Element < temp->Data)
			{
				if (temp->Left != nullptr && Element == temp->Left->Data)
				{
					// here we must pass temp->Left as paremeter not temp 
					_DeleteHelper(temp->Left);

					return true;
				}
				else
				{
					temp = temp->Left;
				}
			}

			else if (Element > temp->Data)
			{
				if (temp->Right != nullptr && Element == temp->Right->Data)
				{
					// here we must pass temp->Right as paremeter not temp 
					_DeleteHelper(temp->Right);

					return true;
				}
				else
				{
					temp = temp->Right;
				}
			}

			else
			{
				// here we must pass Root as a parameter not temp
				_DeleteHelper(Root);

				return true;
			}

		}

		return false;*/

	}

	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	bool _IsFound(stNode*& Root, T& Element)
	{
		/*if (Root == NULL)
		{
			return false;
		}

		if (Element < Root->Data)
		{
			
			return _IsFound(Root->Left, Element);
		}

		else if (Element > Root->Data)
		{
			return _IsFound(Root->Right, Element);
		}

		else
		{
			return true;
		}*/

		stNode* curr = Root;

		while (curr != nullptr)
		{
			if (curr->Data == Element)
			{
				return true;
			}

			else if (Element < curr->Data)
			{
				curr = curr->Left;
			}

			else if (Element > curr->Data)
			{
				curr = curr->Right;
			}
		}

		return false;
	}

	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	void _DisPlayUsingINOrder(stNode*& Root)
	{
		if (Root == NULL)
		{
			return;
		}
		
		_DisPlayUsingINOrder(Root->Left);

		cout << Root->Data << " ";
	
		_DisPlayUsingINOrder(Root->Right);

	}

	void _DisPlayUsingPreOrder(stNode*& Root)
	{
		if (Root == NULL)
		{
			return;
		}

		cout << Root->Data << " ";

		_DisPlayUsingPreOrder(Root->Left);

		_DisPlayUsingPreOrder(Root->Right);

	}

	void _DisPlayUsingPostOrder(stNode*& Root)
	{
		if (Root == NULL)
		{
			return;
		}

		_DisPlayUsingPostOrder(Root->Left);

		_DisPlayUsingPostOrder(Root->Right);

		cout << Root->Data << " ";

	}

	void _DisPlayUsingLevelOrder(stNode* Root)
	{
		Queue <stNode*> q;

		q.Enqueue(Root);

		stNode* curr;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			cout << curr->Data << " ";

			if (curr->Left != nullptr)
			{
				q.Enqueue(curr->Left);
			}

			if (curr->Right != nullptr)
			{
				q.Enqueue(curr->Right);
			}

			q.Dequeue();
		}

	}

	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	void _Clear(stNode*& Root)
	{
		Queue <stNode*> q;

		q.Enqueue(Root);

		stNode* curr;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			if (curr->Left != nullptr)
			{
				q.Enqueue(curr->Left);
			}

			if (curr->Right != nullptr)
			{
				q.Enqueue(curr->Right);
			}

			q.Dequeue();

			delete curr;
		}

	}


	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	void _Copy(stNode*& Root)
	{
		Queue <stNode*> q;

		q.Enqueue(Root);

		stNode* curr;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			this->Insert(curr->Data);

			if (curr->Left != nullptr)
			{
				q.Enqueue(curr->Left);
			}

			if (curr->Right != nullptr)
			{
				q.Enqueue(curr->Right);
			}

			q.Dequeue();
		}

	}


	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	stNode* _FindMin(stNode*& Root)
	{
		if (Root->Left == NULL)
		{
			return Root;
		}

		_FindMin(Root->Left);


		/*stNode* temp = Root;

		while (temp->Left != nullptr)
		{
			temp = temp->Left;
		}

		return temp;*/

	}

	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	stNode* _FindMax(stNode*& Root)
	{
		if (Root->Right == NULL)
		{
			return Root;
		}

		_FindMax(Root->Right);


		/*stNode* temp = Root;

		while (temp->Right != nullptr)
		{
			temp = temp->Right;
		}

		return temp;*/

	}


	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	int _GetHeight(stNode*& Root)
	{
		if (Root == nullptr)
		{
			return -1;
		}

		int LeftSubTree = _GetHeight(Root->Left);
		int RightSubTree = _GetHeight(Root->Right);

		return 1 + max(LeftSubTree, RightSubTree);
	}

	int _IsBalancedBinarySearchTreeHerper(stNode* Root, bool& IsBalabced)
	{
		if (Root == nullptr)
		{
			return -1;
		}

		// this fanction must be that order
		int LeftSubTree = _IsBalancedBinarySearchTreeHerper(Root->Left, IsBalabced);
		int RightSubTree = _IsBalancedBinarySearchTreeHerper(Root->Right, IsBalabced);

		int sub = LeftSubTree - RightSubTree;

		if (sub != 1 && sub != -1 && sub != 0)
		{
			IsBalabced = false;
		}

		return 1 + max(LeftSubTree, RightSubTree);
	}


public:


	BinarySearchTree()
	{
		_Root = NULL;
		_Count = 0;
	}

	int GetHeight()
	{
		if (_Root == nullptr)
		{
			return -1;
		}
		else
		{
			return _GetHeight(_Root);
		}
	}

	T FindMax()
	{
		if (_Root == NULL)
		{
			cout << "\n\nEmpty Tree, No Element Found\n\n";
		}
		else
		{
			stNode* MaxElement = _FindMax(_Root);

			return MaxElement->Data;
		}
	}

	T FindMin()
	{
		if (_Root == NULL)
		{
			cout << "\n\nEmpty Tree, No Element Found\n\n";
		}
		else
		{
			stNode* MinElement = _FindMin(_Root);

			return MinElement->Data;
		}
	}

	bool IsBalancedBinarySearchTree()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return false;
		}
		
		bool IsBalabced = true;

		_IsBalancedBinarySearchTreeHerper(_Root, IsBalabced);

		if (IsBalabced == true)
		{
			return true;
		}
		
		return false;
	
	}

	int GetNumberOfBrunchs()
	{
		return _Count - 1;
	}

	void Clear()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		_Clear(_Root);

		_Root = NULL;
		_Count = 0;
	}

	bool IsEmpty()
	{
		return _Root == NULL;
	}

	void Fill()
	{
		int NumberOfElements = clsInput<int>::ReadPositiveNumber("How many elements you want to Fill : ");

		for (short i = 0; i < NumberOfElements; i++)
		{
			T Element;
			cout << "\nEnter Element Number " << i + 1 << " : ";

			// cin inside this fanction ( MakeSureItisNumber2 ) and his reseve the parametar by refrance 
			clsUtil<T>::MakeSureItisNumber2(Element);

			Insert(Element);

		}

	}

	void DisPlayUsingINOrder()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		cout << "\n\n{ ";
		_DisPlayUsingINOrder(_Root);
		cout << "}\n\n";
	}

	void DisPlayUsingPreOrder()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		cout << "\n\n{ ";
		_DisPlayUsingPreOrder(_Root);
		cout << "}\n\n";
	}

	void DisPlayUsingPostOrder()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		cout << "\n\n{ ";
		_DisPlayUsingPostOrder(_Root);
		cout << "}\n\n";
	}

	void DisPlayUsingLevelOrder()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		cout << "\n\n{ ";
		_DisPlayUsingLevelOrder(_Root);
		cout << "}\n\n";
	}

	int Count()
	{
		return _Count;
	}

	bool IsFound(T Element)
	{
		return _IsFound(_Root, Element);
	}

	void Insert(T Element)
	{
		if (IsEmpty())
		{
			_Root = new stNode;

			if (_IsNoSpaceInMemory(_Root))
			{
				cout << "\nNo Space in Memory\n";
				return;
			}

			_Root->Data = Element;
			_Root->Left = NULL;
			_Root->Right = NULL;

			_Count++;
		}
		else
		{
			_Insert(_Root, Element);
		}

	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(BinarySearchTree<T>& CopyTreeBinarySearch)
	{
		if (!IsEmpty())
		{
			cout << "\nTree Must be Empty!\n";
			return;
		}

		_Copy(CopyTreeBinarySearch._Root);
	}

	void  Delete(T Element)
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		if (_Delete(_Root, Element) == false)
		{
			return;
		}

		_Count--;

	}

	~BinarySearchTree()
	{
		Clear();
	}



};

