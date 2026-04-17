#pragma once

#include <iostream>
#include <cmath>
using namespace std;
#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";
#include "..\Linear\Queue.h";


template <class T>
class RedBlackTree
{
private:

	enum enColor { Red, Black };

	struct stNode
	{
		T Data;
		stNode* Left;
		stNode* Right;
		stNode* Parent;
		enColor Color;

		stNode(T data)
		{
			Data = data;
			Left = nullptr;
			Right = nullptr;
			Parent = nullptr;
			Color = enColor::Red;
		}

		/*stNode()
		{
			
		}*/
	};

	stNode* _Root;

	int _CountAll;


	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	int _GetHeight(stNode*& Root)
	{
		if (Root == nullptr)
		{
			return -1;
		}

		// this fanction must be that order
		int LeftSubTree = _GetHeight(Root->Left);
		int RightSubTree = _GetHeight(Root->Right);

		return 1 + max(LeftSubTree, RightSubTree);
	}

	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	bool _ShouldRebalance(stNode*& node)
	{
		// this condetion for function delete
		if (node == nullptr)
		{
			return false;
		}
		else
		{
			// this line must be that order (1 + _GetHeight(node->Left);), mean not like this (_GetHeight(node->Left) + 1;) 
			short HeightLeft = 1 + _GetHeight(node->Left);
			short HeightRight = 1 + _GetHeight(node->Right);

			int Min = min(HeightLeft, HeightRight);
			int Max = max(HeightLeft, HeightRight);

			if (Min == 0)
			{
				if (Max > 2)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			Min = Min * 2;

			if (Max > Min)
			{
				return true;
			}
			else // else here mean Max <= Min
			{
				return false;
			}

			

		}

	}
	
	// parameter -> ( stNode* node ) never reseve by refrance
	void _RotationToRight(stNode* node)
	{
		stNode* tmp = node->Left;

		node->Left = tmp->Right;

		tmp->Right = node;

		tmp->Parent = node->Parent;

		if (tmp->Parent == nullptr)
		{
			_Root = tmp;
		}
		else
		{
			bool nodeisLeft = node->Parent->Left == node ? true : false;

			if (nodeisLeft == true)
			{
				node->Parent->Left = tmp;
			}
			else
			{
				node->Parent->Right = tmp;
			}
		}

		if (tmp->Right != nullptr)
		{
			tmp->Right->Parent = node;
		}

		node->Parent = tmp;

	}

	// parameter -> ( stNode* node ) never reseve by refrance
	void _RotationToLeft(stNode* node)
	{
		stNode* tmp = node->Right;

		node->Right = tmp->Left;

		tmp->Left = node;

		tmp->Parent = node->Parent;

		if (tmp->Parent == nullptr)
		{
			_Root = tmp;
		}
		else
		{
			bool nodeisLeft = node->Parent->Left == node ? true : false;

			if (nodeisLeft == true)
			{
				node->Parent->Left = tmp;
			}
			else
			{
				node->Parent->Right = tmp;
			}
		}

		if (tmp->Left != nullptr)
		{
			tmp->Left->Parent = node;
		}

		node->Parent = tmp;
	}

	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	void _FixInsert(stNode* node)
	{
		stNode* Parent = node->Parent;

		if (Parent->Color == enColor::Black)
		{
			return;
		}

		stNode* GrandFather = Parent->Parent;
		stNode* Uncel = nullptr;

		if (GrandFather != nullptr)
		{
			Uncel = GrandFather->Left == Parent ? GrandFather->Right : GrandFather->Left;
		}

		if (Uncel != nullptr && Uncel->Color == enColor::Red && Parent->Color == enColor::Red)
		{
			Parent->Color = enColor::Black;
			Uncel->Color = enColor::Black;

			if (GrandFather != _Root)
			{
				GrandFather->Color = enColor::Red;
				_FixInsert(GrandFather);
			}
		}
			
		else if (Parent->Color == enColor::Red && (Uncel == nullptr || Uncel->Color == enColor::Black))
		{
			bool ParentisLeft = GrandFather->Left == Parent ? true : false;

			bool MeisLeft = Parent->Left == node ? true : false;

			// GrandFather is red in all cases
			GrandFather->Color = enColor::Red;

			// case LL
			if (ParentisLeft == true && MeisLeft == true)
			{
				Parent->Color = enColor::Black;

				_RotationToRight(GrandFather);

				/*if (Parent->Parent != nullptr)
				{
					_FixInsert(Parent);
				}*/
			}

			// case LR
			else if (ParentisLeft == true && MeisLeft == false)
			{
				node->Color = enColor::Black;

				_RotationToLeft(Parent);
				_RotationToRight(GrandFather);

				/*if (node->Parent != nullptr)
				{
					_FixInsert(node);
				}*/
			}

			// case RR
			else if (ParentisLeft == false && MeisLeft == false)
			{
				Parent->Color = enColor::Black;

				_RotationToLeft(GrandFather);

				/*if (Parent->Parent != nullptr)
				{
					_FixInsert(Parent);
				}*/
			}

			// case RL
			else if (ParentisLeft == false && MeisLeft == true)
			{
				node->Color = enColor::Black;

				_RotationToRight(Parent);
				_RotationToLeft(GrandFather);

				/*if (node->Parent != nullptr)
				{
					_FixInsert(node);
				}*/
			}	
		}

		// _Root never change his color to red but this reserve line 
		_Root->Color = enColor::Black;
	}

	// parameter -> ( stNode* node ) never reseve by refrance
	void _FixDelete(stNode* node)
	{
		// remmeber that this function will work with two cases,
		// node have one child and this case node must be black because red node never have one child or not have any child 


		// here the color of node will be red that is mean the node is leaf because red node never have one child
		if (node->Color == Red || node == _Root)
		{
			return;
		}

		else if (node->Color == Black)
		{
			if (node->Left != nullptr && node->Left->Color == Red)
			{
				node->Left->Color = Black;
			}

			else if (node->Right != nullptr && node->Right->Color == Red)
			{
				node->Right->Color = Black;
			}

			else
			{
				// here Double Black happend and,
				// else here mean node not have any child or have one child black


				while (node != _Root)
				{
					// here (parent) never == nullptr becuase condetion in while loop
					stNode* brother = node == node->Parent->Left ? node->Parent->Right : node->Parent->Left;
					stNode* LeftNephew = nullptr;
					stNode* RightNephew = nullptr;

					// here we do not need check from pointer brother if = nullptr or not because black node always have brother
					LeftNephew = brother->Left;
					RightNephew = brother->Right;


					// case 1 to douple black
					// case 1 we always not finished
					if (brother->Color == Red)
					{
						// here parent color will be black becuase parent have child color red -> brother 
						// swap color between parent and brother
						brother->Color = Black;
						brother->Parent->Color = Red;

						if (brother->Parent->Left == brother)
						{
							_RotationToRight(brother->Parent);
						}
						else
						{
							_RotationToLeft(brother->Parent);
						}

						continue;
					}

					// case 2 to douple black
					// case 2 mype we done mype not
					else if (brother->Color == Black &&
						(LeftNephew == nullptr || LeftNephew->Color == Black) && (RightNephew == nullptr || RightNephew->Color == Black))
					{
						brother->Color = Red;

						if (node->Parent->Color == Red)
						{
							node->Parent->Color = Black;
							// here we are finished must do (return)
							return;
						}
						else
						{
							node = node->Parent;
							// here we are not finished must do( temp == parent) and must do (continue) 
							continue;
						}
					}

					// case 3 and 4
					// case 3 and 4 we always finished
					else if (brother->Color == Black &&
						(LeftNephew != nullptr && LeftNephew->Color == Red) || (RightNephew != nullptr && RightNephew->Color == Red))
					{
						bool nodeinLeft = node == node->Parent->Left ? true : false;

						// case 3
						if (nodeinLeft == true && LeftNephew != nullptr && LeftNephew->Color == Red)
						{
							LeftNephew->Color = node->Parent->Color;
							node->Parent->Color = Black;

							_RotationToRight(brother);
							_RotationToLeft(node->Parent);
							// here we are finished must do (return)
							return;
						}

						// case 3
						if (nodeinLeft == false && RightNephew != nullptr && RightNephew->Color == Red)
						{
							RightNephew->Color = node->Parent->Color;
							node->Parent->Color = Black;

							_RotationToLeft(brother);
							_RotationToRight(node->Parent);
							// here we are finished must do (return)
							return;
						}

						// case 4
						if (nodeinLeft == true && RightNephew != nullptr && RightNephew->Color == Red)
						{
							brother->Color = node->Parent->Color;
							RightNephew->Color = Black;
							node->Parent->Color = Black;

							_RotationToLeft(node->Parent);
							// here we are finished must do (return)
							return;
						}

						// case 4
						if (nodeinLeft == false && LeftNephew != nullptr && LeftNephew->Color == Red)
						{
							brother->Color = node->Parent->Color;
							LeftNephew->Color = Black;
							node->Parent->Color = Black;

							_RotationToRight(node->Parent);
							// here we are finished must do (return)
							return;
						}
					}

				}

			}
		}
	}

	// parameter -> ( stNode*& Root ) must be reseve by refrance
	/*void _DeleteHelper(stNode*& Root)
	 {
		// here we must use ( if and else if ) no ( if and if)
		if (Root->Left == nullptr && Root->Right == nullptr)
		{
			_FixDelete(Root);

			delete Root;

			Root = nullptr;
		}

		else if (Root->Left == nullptr && Root->Right != nullptr)
		{
			_FixDelete(Root);

			stNode* temp = Root;

			Root = Root->Right;

			Root->Parent = temp->Parent;

			delete temp;
		}

		else if (Root->Left != nullptr && Root->Right == nullptr)
		{
			_FixDelete(Root);

			stNode* temp = Root;

			Root = Root->Left;

			Root->Parent = temp->Parent;

			delete temp;
		}

		else if (Root->Left != nullptr && Root->Right != nullptr)
		{
			stNode* MaxElementInLeft = _FindMax(Root->Left);

			Root->Data = MaxElementInLeft->Data;

			_Delete(Root->Left, MaxElementInLeft->Data);
		}
	}*/

	// parameter -> ( stNode*& Root ) must be reseve by refrance
	bool _Delete(stNode*& Root, T& Element)
	{
		if (Root == nullptr)
		{
			return false;
		}

		if (Element < Root->Data)
		{
			_Delete(Root->Left, Element);
		}

		else if (Element > Root->Data)
		{
			_Delete(Root->Right, Element);
		}

		else
		{
			// here we must use ( if and else if ) no ( if and if)
			if (Root->Left == nullptr && Root->Right == nullptr)
			{
				_FixDelete(Root);

				delete Root;

				Root = nullptr;

				return true;
			}

			else if (Root->Left == nullptr && Root->Right != nullptr)
			{
				_FixDelete(Root);

				stNode* temp = Root;

				Root = Root->Right;

				Root->Parent = temp->Parent;

				delete temp;

				return true;
			}

			else if (Root->Left != nullptr && Root->Right == nullptr)
			{
				_FixDelete(Root);

				stNode* temp = Root;

				Root = Root->Left;

				Root->Parent = temp->Parent;

				delete temp;

				return true;
			}

			else if (Root->Left != nullptr && Root->Right != nullptr)
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


	// parameter -> ( stNode*& Root ) must be reseve by refrance
	// parameter -> ( stNode*& Parent ) must be reseve by refrance
	// parameter -> ( T& Element ) not must be reseve by refrance, we need reduce space in memory only
	/*void _Insert(stNode*& Root, T& Element, stNode*& Parent)
	{
		if (Root == nullptr)
		{
			Root = new stNode(Element);

			Root->Parent = Parent;

			_CountAll++;

			_FixInsert(Root);
		}

		else if (Element < Root->Data)
		{
			Parent = Root;

			_Insert(Root->Left, Element, Parent);
		}

		// else here mean >=
		else
		{
			Parent = Root;

			_Insert(Root->Right, Element, Parent);
		}
	}*/


	// parameter reseve by refrance & becuase every time do recarcion not copy parameter and create new pointer in memory
	// we need reduce space in momry
	bool _IsFound(stNode*& Root, T& Element)
	{
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
		if (Root == nullptr)
		{
			return;
		}

		_DisPlayUsingINOrder(Root->Left);

		cout << Root->Data << " ";

		_DisPlayUsingINOrder(Root->Right);

	}

	void _DisPlayUsingPreOrder(stNode*& Root)
	{
		if (Root == nullptr)
		{
			return;
		}

		cout << Root->Data << " ";

		_DisPlayUsingPreOrder(Root->Left);

		_DisPlayUsingPreOrder(Root->Right);

	}

	void _DisPlayUsingPostOrder(stNode*& Root)
	{
		if (Root == nullptr)
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
		if (Root->Left == nullptr)
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
		if (Root->Right == nullptr)
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

	void _IsBalancedRedBlackTreeHelper(stNode* Root, bool& IsBalabced)
	{
		if (Root == nullptr)
		{
			return;
		}

		// this fanction must be that order    
		_IsBalancedRedBlackTreeHelper(Root->Left, IsBalabced);
		_IsBalancedRedBlackTreeHelper(Root->Right, IsBalabced);

		if (_ShouldRebalance(Root))
		{
			IsBalabced = false;
		}
	}

	void _Print(stNode* Root)
	{
		Queue <stNode*> q;

		q.Enqueue(Root);

		stNode* curr;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			if (curr->Left != nullptr || curr->Right != nullptr)
			{
				cout << "\n=======================================\n\n  ";
				cout << curr->Data << " : ";

				if (curr->Color == Red)
				{
					cout << "Red" << "\n     ";
				}
				else if (curr->Color == Black)
				{
					cout << "Black" << "\n     ";
				}
			}

			if (curr->Left != nullptr)
			{
				cout << "L | " << curr->Left->Data << " : ";

				if (curr->Left->Color == Red)
				{
					cout << "Red" << "\n     ";
				}
				else if (curr->Left->Color == Black)
				{
					cout << "Black" << "\n     ";
				}

				q.Enqueue(curr->Left);
			}

			if (curr->Right != nullptr)
			{
				cout << "R | " << curr->Right->Data << " : ";

				if (curr->Right->Color == Red)
				{
					cout << "Red" << "\n     ";
				}
				else if (curr->Right->Color == Black)
				{
					cout << "Black" << "\n     ";
				}

				q.Enqueue(curr->Right);
			}

			q.Dequeue();
		}
	}


public:


	RedBlackTree()
	{
		_Root = nullptr;
		_CountAll = 0;
	}

	void Insert(T Element)
	{
		if (_Root == nullptr)
		{
			_Root = new stNode(Element);
			_Root->Color = enColor::Black;

			_CountAll++;
		}
		else
		{
			//stNode* Parent;

			//_Insert(_Root, Element, Parent);

			//===================================

			stNode* NewNode = new stNode(Element);
			stNode* parent = nullptr;

			// here _Root must not = nullptr
			stNode* temp = _Root;

			while (temp != nullptr)
			{
				parent = temp;

				// here _Root must not = nullptr
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

			NewNode->Parent = parent;

			_FixInsert(NewNode);

			_CountAll++;
		}

	}

	void Delete(T Element)
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

		if (_Root != nullptr)
		{
			_Root->Color = Black;
		}

		_CountAll--;
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
		if (_Root == nullptr)
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
		if (_Root == nullptr)
		{
			cout << "\n\nEmpty Tree, No Element Found\n\n";
		}
		else
		{
			stNode* MinElement = _FindMin(_Root);

			return MinElement->Data;
		}
	}

	bool IsBalancedRedBlackTree()
	{
		if (IsEmpty())
		{
			cout << "\nNo Element Found!\n";
			return false;
		}

		bool IsBalabced = true;

		_IsBalancedRedBlackTreeHelper(_Root, IsBalabced);

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
		return _Root == nullptr;
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
	void Copy(RedBlackTree<T>& CopyRedBlackTree)
	{
		if (_Root != nullptr)
		{
			cout << "\nTree Must be Empty!\n";
			return;
		}

		_Copy(CopyRedBlackTree._Root);
	}
	
	void Print()
	{
		if (_Root == nullptr)
		{
			cout << "Tree is empty." << endl;
		}
		else 
		{
			_Print(_Root);
		}
	}

	~RedBlackTree()
	{
		Clear();
	}


};

