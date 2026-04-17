#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";
#include "..\Linear\Queue.h";


template <class T>
class AVLTree
{
private:

	struct stNode
	{
		T Data;
		stNode* Left;
		stNode* Right;
		int Height;

		stNode(T data)
		{
			Data = data;
			Left = nullptr;
			Right = nullptr;
			Height = 0;
		}

		stNode()
		{
			Left = nullptr;
			Right = nullptr;
			Height = 0;
		}
	};

	stNode* _Root;

	int _CountAll;


	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	void _UpdateHeight(stNode*& node)
	{
		// this condetion for function delete
		if (node == nullptr)
		{
			return;
		}

		int leftHeight = 0;
		int rightHeight = 0;

		if (node->Left == nullptr)
		{
			leftHeight = -1;
		}
		else
		{
			leftHeight = node->Left->Height;
		}

		if (node->Right == nullptr)
		{
			rightHeight = -1;
		}
		else
		{
			rightHeight = node->Right->Height;
		}

		node->Height = max(rightHeight, leftHeight) + 1;
	}
	
	// parameter -> ( stNode*& node ) must be reseve by refrance 
	void _RotationToRight(stNode*& node)
	{
		stNode* tmp = node->Left;

		node->Left = node->Left->Right;

		tmp->Right = node;

		_UpdateHeight(node);
		_UpdateHeight(tmp);

		node = tmp;
	}

	// parameter -> ( stNode*& node ) must be reseve by refrance
	void _RotationToLeft(stNode*& node)
	{
		stNode* tmp = node->Right;

		node->Right = node->Right->Left;

		tmp->Left = node;

		_UpdateHeight(node);
		_UpdateHeight(tmp);

		node = tmp;
	}

	// parameter -> ( stNode*& node ) not must be reseve by refrance, we need reduce space in memory only
	int _CalcBalanceFactor(stNode*& node)
	{
		// this condetion for function delete
		if (node == nullptr)
		{
			return -1;
		}

		int LeftSubTree = 0;
		int RightSubTree = 0;

		if (node->Left == nullptr)
		{
			LeftSubTree = -1;
		}
		else
		{
			LeftSubTree = node->Left->Height;
		}

		if (node->Right == nullptr)
		{
			RightSubTree = -1;
		}
		else
		{
			RightSubTree = node->Right->Height;
		}

		return LeftSubTree - RightSubTree;
	}

	// parameter -> ( stNode*& node ) must be reseve by refrance 
	void _FixBalance(stNode*& node)
	{
		if (_CalcBalanceFactor(node) > 1)
		{
			if (_CalcBalanceFactor(node->Left) < 0)
			{
				_RotationToLeft(node->Left);
			}

			_RotationToRight(node);
		}

		else if (_CalcBalanceFactor(node) < -1)
		{
			if (_CalcBalanceFactor(node->Right) > 0)
			{
				_RotationToRight(node->Right);
			}

			_RotationToLeft(node);
		}

	}

	// parameter -> ( stNode*& Root ) must be reseve by refrance 
	// parameter -> ( T& Element ) not must be reseve by refrance, we need reduce space in memory only 
	void _Insert(stNode*& Root, T& Element)
	{
		if (Root == NULL)
		{
			Root = new stNode(Element);

			_CountAll++;

			return;
		}

		if (Element < Root->Data)
		{
			_Insert(Root->Left, Element);
		}

		// else here mean >= 
		else
		{
			_Insert(Root->Right, Element);
		}

		_UpdateHeight(Root);
		_FixBalance(Root);
	}

	// parameter -> ( T& Element ) not must be reseve by refrance, we need reduce space in memory only 
	// parameter -> ( bool& IsDeleted ) must be reseve by refrance 
	// parameter -> ( stNode*& Root ) must be reseve by refrance 
	void _Delete(stNode*& Root, T& Element, bool& IsDeleted)
	{
		if (Root == NULL)
		{
			IsDeleted = false;

			return;
		}

		if (Element < Root->Data)
		{
			_Delete(Root->Left, Element, IsDeleted);
		}

		else if (Element > Root->Data)
		{
			_Delete(Root->Right, Element, IsDeleted);
		}

		else
		{

			// here we must use ( if and else if ) no ( if and if)
			if (Root->Left == NULL && Root->Right == NULL)
			{
				delete Root;

				Root = NULL;

				return;
			}

			else if (Root->Left == NULL && Root->Right != NULL)
			{
				stNode* temp = Root;

				Root = Root->Right;

				delete temp;

				return;
			}

			else if (Root->Left != NULL && Root->Right == NULL)
			{
				stNode* temp = Root;

				Root = Root->Left;

				delete temp;

				return;
			}

			else if (Root->Left != NULL && Root->Right != NULL)
			{
				stNode* MaxElementInLeft = _FindMax(Root->Left);

				Root->Data = MaxElementInLeft->Data;

				_Delete(Root->Left, MaxElementInLeft->Data, IsDeleted);

				// do not write the line ( return true) here

			}

		}

		if (IsDeleted)
		{
			_UpdateHeight(Root);
			_FixBalance(Root);
		}

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

	int _IsBalancedAVLTreeHelper(stNode* Root, bool& IsBalabced)
	{
		if (Root == nullptr)
		{
			return -1;
		}

		// this fanction must be that order    
		int LeftSubTree = _IsBalancedAVLTreeHelper(Root->Left, IsBalabced);
		int RightSubTree = _IsBalancedAVLTreeHelper(Root->Right, IsBalabced);

		int sub = LeftSubTree - RightSubTree;

		if (sub != 1 && sub != -1 && sub != 0)
		{
			IsBalabced = false;
		}

		return 1 + max(LeftSubTree, RightSubTree);
	}


public:

	AVLTree()
	{
		_Root = NULL;
		_CountAll = 0;
	}

	void Insert(T Element)
	{
		if (IsEmpty())
		{
			_Root = new stNode(Element);

			_CountAll++;
		}
		else
		{
			_Insert(_Root, Element);
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
			bool IsDeleted = true;

			_Delete(_Root, Element, IsDeleted);

			if (IsDeleted)
			{
				_CountAll--;
			}
		}

	}

	int GetHeight()
	{
		if (_Root == nullptr)
		{
			return -1;
		}
		else
		{
			return _Root->Height;
		}
	}

	T GetRoot()
	{
		if (_Root == nullptr)
		{
			cout << "\ntree is empty!\n";
		}
		else
		{
			return _Root->Data;
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

	bool IsBalancedAVLTree()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return false;
		}

		bool IsBalabced = true;

		_IsBalancedAVLTreeHelper(_Root, IsBalabced);

		if (IsBalabced == true)
		{
			return true;
		}

		return false;

	}

	int GetNumberOfBrunchs()
	{
		return _CountAll - 1;
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
		_CountAll = 0;
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
		return _CountAll;
	}

	bool IsFound(T Element)
	{
		return _IsFound(_Root, Element);
	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(AVLTree<T>& CopyAVLTree)
	{
		if (!IsEmpty())
		{
			cout << "\nTree Must be Empty!\n";
			return;
		}

		_Copy(CopyAVLTree._Root);
	}

	~AVLTree()
	{
		Clear();
	}



};

