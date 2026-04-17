#pragma once

#include <iostream>
#include <vector>
using namespace std;
#include "..\Linear\Queue.h"


template <class T>
class BTree
{
private:

	class clsNode
	{
	public:

		clsNode* Parent = nullptr;

		vector <T> Keys;
		vector <clsNode*> Children;
	
		bool IsLeaf = false;
		bool IsDeleted = false;

		void ClearKeys()
		{
			Keys.clear();
		}

		void ClearChildren()
		{
			Children.clear();
		}

		void ChildInsertFirst(clsNode* node = nullptr)
		{
			Children.push_back(node);

			for (int i = Children.size() - 1; i > 0; i--)
			{
				Children[i] = Children[i - 1];
			}

			// this condetion must be here
			if (node != nullptr)
			{
				Children[0] = node;
			}
		}

		void ChildPushBack(clsNode* node = nullptr)
		{
			Children.push_back(node);
		}

		void ChildInsertAtPosition(int Index, clsNode* node = nullptr)
		{
			Children.push_back(node);

			for (int i = Children.size() - 1; i > Index; i--)
			{
				Children[i] = Children[i - 1];
			}

			// this condetion must be here
			if (node != nullptr)
			{
				Children[Index] = node;
			}
		}

		void KeyInsertFirst(T key)
		{
			T k;
			Keys.push_back(k);

			for (int i = Keys.size() - 1; i > 0; i--)
			{
				Keys[i] = Keys[i - 1];
			}

			Keys[0] = key;
		}

		void KeyInsertAtPosition(int Index, T key)
		{
			T k;
			Keys.push_back(k);

			for (int i = Keys.size() - 1; i > Index; i--)
			{
				Keys[i] = Keys[i - 1];
			}

			Keys[Index] = key;
		}

		void KeyPushBack(T key)
		{
			Keys.push_back(key);
		}

		int KeysSize()
		{
			return Keys.size();
		}

		int ChildrenSize()
		{
			return Children.size();
		}

		void CreateChildren()
		{
			clsNode* tmp = nullptr;

			for (int i = 0; i < Keys.size() + 1; i++)
			{
				Children.push_back(tmp);
			}
		}

		bool IsLeafNode()
		{
			/*for (int i = 0; i < Children.size(); i++)
			{
				if (Children[i] != nullptr)
				{
					return false;
				}
			}

			return true;*/

			// the leaf node all children == nullptr, and not leaf all children != nullptr  
			if (Children[0] == nullptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		// prameters reseve by refrance & becuase we need reduce space in memory only
		void ChangeParent(clsNode*& parent)
		{
			for (int i = 0; i < Children.size(); i++)
			{
				if ( Children[i] != nullptr)
				{
					Children[i]->Parent = parent;
				}
				else
				{
					return;
				}
			}
		}

		void EraseKey(int Index)
		{
			typename  vector <T>::iterator it = Keys.begin() + Index;
			Keys.erase(it);
		}

		void EraseChildren(int Index)
		{
			typename vector <clsNode*>::iterator it = Children.begin() + Index;
			Children.erase(it);
		}

		void PopBackChildren()
		{
			Children.pop_back();
		}

		int GetIndexChild(clsNode*& node)
		{
			for (int i = 0; i < Children.size(); i++)
			{
				if (Children[i] == node)
				{
					return i;
				}
			}
		}

	};

	int _MaxChildren = 0;
	int _MaxKeys = 0;
	int _MinChildren = 0;
	int _MinKeys = 0;

	int _CountKeys = 0;

	clsNode* _Root;

	enum enCorrectParent { eNoAnswer, eLeft, eRight, eEqualMiddle };

	int _BinarySearch(vector <T>& vKeys, T key)
	{
		int first = 0;
		int last = vKeys.size() - 1;

		while (first <= last)
		{
			int m = (first + last) / 2;

			if (key == vKeys[m])
			{
				return m;
			}

			else if (key > vKeys[m])
			{
				first = m + 1;
			}

			else
			{
				last = m - 1;
			}
		}

		return -1;
	}

	// prameters reseve by refrance & becuase we need reduce space in memory only
	int _GetIndexKey(clsNode*& node, T& key)
	{
		int IndexKey = -1;

		int IndexLastKey = node->KeysSize() - 1;

		if (key >= node->Keys[IndexLastKey])
		{
			IndexKey = IndexLastKey + 1;
		}
		else if (key < node->Keys[0])
		{
			IndexKey = 0;
		}
		else
		{
			// here we must stop befor the end - 1 because not error hapened
			for (int i = 0; i < node->KeysSize() - 1; i++)
			{
				if (key >= node->Keys[i] && key < node->Keys[i + 1])
				{
					IndexKey = i + 1;
					break;
				}
			}
		}

		return IndexKey;
	}

	// prameters reseve by refrance & becuase we need reduce space in memory only
	T _SplitNodeAndGetMiddleKey(clsNode*& node, clsNode*& tempLeft, clsNode*& tempRight)
	{
		int IndexMiddleKey = node->KeysSize() / 2;

		T MiddleKey = node->Keys[IndexMiddleKey];

		// we use tow for loop to transfer the keys
		for (int i = 0; i < IndexMiddleKey; i++)
		{
			tempLeft->KeyPushBack(node->Keys[i]);
		}

		for (int i = IndexMiddleKey + 1; i < node->KeysSize(); i++)
		{
			tempRight->KeyPushBack(node->Keys[i]);
		}

		// =======================================================
		
		// we use tow for loop to transfer the children
		for (int i = IndexMiddleKey + 1; i < node->ChildrenSize(); i++)
		{
			tempRight->ChildPushBack(node->Children[i]);
		}

		tempRight->ChangeParent(tempRight);

		for (int i = 0; i <= IndexMiddleKey; i++)
		{
			tempLeft->ChildPushBack(node->Children[i]);
		}

		tempLeft->ChangeParent(tempLeft);

		return MiddleKey;
	}

	struct stLeftAndRight
	{
		clsNode* eLeft = nullptr;
		clsNode* eRight = nullptr;
	};
	
	// only this parameter -> (clsNode*& parent) reseve by refrance &  
	void _FixParent(clsNode*& node, clsNode*& parent, T& MiddleKey, clsNode*& tempLeft, clsNode*& tempRight)
	{
		enCorrectParent CorrectParent = _InsertHelper2(parent, MiddleKey);

		stLeftAndRight LeftAndRight = _FixNode(parent);

		if (CorrectParent == eEqualMiddle)
		{
			LeftAndRight.eRight->Children[0] = tempRight;
			LeftAndRight.eLeft->Children[LeftAndRight.eLeft->ChildrenSize() - 1] = tempLeft;

			tempLeft->Parent = LeftAndRight.eLeft;
			tempRight->Parent = LeftAndRight.eRight;
		}
		else
		{
			if (CorrectParent == eLeft)
			{
				parent = LeftAndRight.eLeft;
			}
			else if (CorrectParent == eRight)
			{
				parent = LeftAndRight.eRight;
			}

			tempRight->Parent = parent;
			tempLeft->Parent = parent;

			int IndexleftChildren = parent->GetIndexChild(node);

			parent->Children[IndexleftChildren] = tempLeft;
			parent->Children[IndexleftChildren + 1] = tempRight;

		}

		tempLeft->IsLeaf = tempLeft->IsLeafNode();
		tempRight->IsLeaf = tempRight->IsLeafNode();

		delete node;
	}

	// prameter -> ( clsNode*& Root ) must be reseve by refrance 
	stLeftAndRight _FixNode(clsNode*& node)
	{
		clsNode* tempLeft = new clsNode;
		clsNode* tempRight = new clsNode;

		T MiddleKey = _SplitNodeAndGetMiddleKey(node, tempLeft, tempRight);

		if (node->Parent == nullptr)
		{
			node->ClearChildren();
			node->ClearKeys();

			node->KeyPushBack(MiddleKey);

			node->CreateChildren();

			node->Children[0] = tempLeft;
			node->Children[1] = tempRight;

			tempLeft->Parent = node;
			tempRight->Parent = node;

			tempLeft->IsLeaf = tempLeft->IsLeafNode();
			tempRight->IsLeaf = tempRight->IsLeafNode();
			node->IsLeaf = false;
		}
		else
		{
			clsNode* parent = node->Parent;

			if (parent->KeysSize() == _MaxKeys)
			{
				_FixParent(node, parent, MiddleKey, tempLeft, tempRight);
			}
			else // else here mean parent->KeysSize() < _MaxKeys 
			{
				_InsertHelper2(parent, MiddleKey);

				tempRight->Parent = parent;
				tempLeft->Parent = parent;

				int IndexleftChildren = parent->GetIndexChild(node);

				parent->Children[IndexleftChildren] = tempLeft;
				parent->Children[IndexleftChildren + 1] = tempRight;

				delete node;

				tempLeft->IsLeaf = tempLeft->IsLeafNode();
				tempRight->IsLeaf = tempRight->IsLeafNode();
			}
		}

		return  stLeftAndRight{ tempLeft , tempRight };
	}

	// prameter -> ( clsNode*& node ) must be reseve by refrance &
	void _InsertHelper1(clsNode*& node, T& key)
	{
		int IndexCorrectChildren = 0;

		while (node->IsLeaf == false)
		{
			int IndexLastKey = node->KeysSize() - 1;

			if (key >= node->Keys[IndexLastKey])
			{
				IndexCorrectChildren = IndexLastKey + 1;
			}
			// here condition must be <= not < only because if node have one key and new key same key is already excist
			else if (key < node->Keys[0])
			{
				IndexCorrectChildren = 0;
			}
			else
			{
				for (int i = 0; i < node->KeysSize(); i++)
				{
					if (key >= node->Keys[i] && key < node->Keys[i + 1])
					{
						IndexCorrectChildren = i + 1;
						break;
					}
				}
			}

			node = node->Children[IndexCorrectChildren];
		}

	}

	// prameters reseve by refrance & becuase we need reduce space in memory only
	enCorrectParent _InsertHelper2(clsNode*& node, T& key)
	{
		enCorrectParent CorrectParent;

		int IndexLastKey = node->KeysSize() - 1;

		if (key >= node->Keys[IndexLastKey])
		{
			node->KeyPushBack(key);
			node->ChildPushBack();
			CorrectParent = eRight;
		}
		// here condition must be <= not < only because if node have one key and new key same key is already excist
		else if (key < node->Keys[0])
		{
			node->KeyInsertFirst(key);
			node->ChildInsertFirst();
			CorrectParent = eLeft;
		}
		else
		{
			for (int i = 0; i < node->KeysSize(); i++)
			{
				if (key >= node->Keys[i] && key <= node->Keys[i + 1])
				{
					node->KeyInsertAtPosition(i + 1, key);
					node->ChildInsertAtPosition(i + 1);

					int indexMiddle = (_MaxKeys + 1) / 2;

					if (i + 1 == indexMiddle)
					{
						CorrectParent = eEqualMiddle;
					}
					else if (i + 1 > indexMiddle)
					{
						CorrectParent = eRight;
					}
					else if (i + 1 < indexMiddle)
					{
						CorrectParent = eLeft;
					}
					break;
				}
			}
		}

		return CorrectParent;

	}

	// prameters reseve by refrance & becuase we need reduce space in memory only
	void _Insert(clsNode*& Root, T& key)
	{
		clsNode* tmp = Root;

		if (tmp->IsLeaf == false)
		{
			// here tmp will back correct node and it is leaf
			_InsertHelper1(tmp, key);
		}

		_InsertHelper2(tmp, key);

		if (tmp->KeysSize() > _MaxKeys)
		{
			// we used that varible -> (IndexleftChildren) to know place Key Caused The Problem
			_FixNode(tmp);
		}

	}

	bool _BorrowingFromMyBrothers(clsNode*& LeftBrother, clsNode*& RightBrother, clsNode*& parent, clsNode*& curr, int& IndexBrothersAddOrSub, int& IndexKey)
	{
		T SeparatorKey;

		if (LeftBrother != nullptr && LeftBrother->KeysSize() > _MinKeys)
		{
			// here this varible -> (IndexBrothersAddOrSub - 1) point to separator key 
			SeparatorKey = parent->Keys[IndexBrothersAddOrSub - 1];

			int IndexLastKey = LeftBrother->KeysSize() - 1;

			// here this varible -> (IndexBrothersAddOrSub - 1) point to separator key 
			parent->Keys[IndexBrothersAddOrSub - 1] = LeftBrother->Keys[IndexLastKey];

			LeftBrother->EraseKey(IndexLastKey);
			
			if (curr->KeysSize() == 0)
			{
				curr->KeyPushBack(SeparatorKey);
			}
			else
			{
				if (curr->IsLeaf == true)
				{
					// here we need deleted key before insert new key
					curr->EraseKey(IndexKey);
				}

				curr->KeyInsertFirst(SeparatorKey);
			}

			// here we update children before deleted
			if (curr->IsLeaf == false)
			{
				int IndexLastChild = LeftBrother->ChildrenSize() - 1;

				// here we need to make this child -> (curr->Children[0]) point to correct place
				curr->Children[0] = LeftBrother->Children[IndexLastChild];

				curr->ChangeParent(curr);
			}
			
			LeftBrother->PopBackChildren();
			
			return true;
		}

		else if (RightBrother != nullptr && RightBrother->KeysSize() > _MinKeys)
		{
			// here this varible -> (IndexBrothersAddOrSub) point to separator key 
			SeparatorKey = parent->Keys[IndexBrothersAddOrSub];

			// here this varible -> (IndexBrothersAddOrSub) point to separator key 
			parent->Keys[IndexBrothersAddOrSub] = RightBrother->Keys[0];

			RightBrother->EraseKey(0);

			if (curr->IsLeaf == true)
			{
				// here we need deleted key before insert new key
				curr->EraseKey(IndexKey);
			}

			curr->KeyPushBack(SeparatorKey);

			// here we update children and before deleted
			if (curr->IsLeaf == false)
			{
				int IndexLastChild = curr->ChildrenSize() - 1;

				// here we need to make this child -> (curr->Children[IndexLastChild]) point to correct place
				curr->Children[IndexLastChild] = RightBrother->Children[0];

				curr->ChangeParent(curr);

				RightBrother->EraseChildren(0);
			}
			else
			{
				RightBrother->PopBackChildren();
			}

			return true;
		}

		return false;
	}

	void _Merge(clsNode*& LeftBrother, clsNode*& RightBrother, clsNode*& parent, clsNode*& curr, int& IndexBrothersAddOrSub, int& IndexKey)
	{
		if (RightBrother != nullptr)
		{
			// here this varible -> (IndexBrothersAddOrSub) = Index separator key
			curr->KeyPushBack(parent->Keys[IndexBrothersAddOrSub]);

			int IndexLastChildren = curr->ChildrenSize() - 1;

			// here we must udate this child (curr->Children[IndexLastChildren])
			curr->Children[IndexLastChildren] = RightBrother->Children[0];

			for (int i = 0; i < RightBrother->KeysSize(); i++)
			{
				curr->KeyPushBack(RightBrother->Keys[i]);
			}

			for (int i = 1; i < RightBrother->ChildrenSize(); i++)
			{
				curr->ChildPushBack(RightBrother->Children[i]);
			}

			curr->ChangeParent(curr);

			delete RightBrother;

			// here we use this varible -> (IndexBrothersAddOrSub) to know right brother 
			// here make pointer which point to right brother point to me after merge happend 
			parent->Children[IndexBrothersAddOrSub + 1] = curr;
		}

		else if (LeftBrother != nullptr)
		{
			// here this varible -> (--IndexBrothersAddOrSub) = Index separator key 
			curr->KeyInsertFirst(parent->Keys[--IndexBrothersAddOrSub]);

			int lastChild = LeftBrother->ChildrenSize() - 1;

			// here we must udate this child (curr->Children[0])
			curr->Children[0] = LeftBrother->Children[lastChild];

			for (int i = LeftBrother->KeysSize() - 1; i >= 0; i--)
			{
				curr->KeyInsertFirst(LeftBrother->Keys[i]);
			}

			for (int i = LeftBrother->ChildrenSize() - 2; i >= 0; i--)
			{
				curr->ChildInsertFirst(LeftBrother->Children[i]);
			}

			curr->ChangeParent(curr);

			delete LeftBrother;

			// here we use this varible -> (IndexBrothersAddOrSub) to know left brother 
			// here make pointer which point to left brother point to me after merge happend 
			parent->Children[IndexBrothersAddOrSub] = curr;
		}
	}

	void _UpdateCurrentNodeInfo(clsNode*& LeftBrother, clsNode*& RightBrother, clsNode*& parent, clsNode*& curr, int& IndexBrothersAddOrSub, int& IndexKey, T& key)
	{
		parent = curr->Parent;

		// here this varible -> (IndexBrothersAddOrSub) = Index separator key 
		IndexBrothersAddOrSub = parent->GetIndexChild(curr);

		// that is mean curr node have left brother and right brother
		if (IndexBrothersAddOrSub != 0 && IndexBrothersAddOrSub < parent->ChildrenSize() - 1)
		{
			// here we use this varible -> (IndexBrothersAddOrSub) to know left and right brother
			LeftBrother = parent->Children[IndexBrothersAddOrSub - 1];
			RightBrother = parent->Children[IndexBrothersAddOrSub + 1];
		}

		// that is mean curr node have right brother only
		else if (IndexBrothersAddOrSub == 0)
		{
			// here we use this varible -> (IndexBrothersAddOrSub) to know right brother
			RightBrother = parent->Children[IndexBrothersAddOrSub + 1];
		}

		// that is mean curr node have left brother only
		else if (IndexBrothersAddOrSub == parent->ChildrenSize() - 1)
		{
			// here we use this varible -> (IndexBrothersAddOrSub) to know left brother
			LeftBrother = parent->Children[IndexBrothersAddOrSub - 1];
		}
	}

	bool _Delete(clsNode*& Root, T& key)
	{
		clsNode* curr = Root;

		while (curr != nullptr)
		{
			int IndexKey = _BinarySearch(curr->Keys, key);

			// this condetion mean key not found in curr node
			if (IndexKey == -1)
			{
				// here mean key not found in all tree
				if (curr->IsLeaf == true)
				{
					return false;
				}
				else
				{
					// here we use this fanction (_GetIndexKeyWithDeletion(curr, key)) to know where we go 
					int IndexChildren = _GetIndexKey(curr, key);
					curr = curr->Children[IndexChildren];
				}
			}
			else
			{
				if (curr == _Root && curr->KeysSize() > 1 && (curr->Children[0] == nullptr || curr->IsLeaf == true))
				{
					curr->EraseKey(IndexKey);
					curr->PopBackChildren();
					return true;
				}

				if (curr->IsLeaf == true && curr->KeysSize() > _MinKeys)
				{
					curr->EraseKey(IndexKey);
					curr->PopBackChildren();
					return true;
				}

				else if (curr->IsLeaf == true && curr->KeysSize() == _MinKeys)
				{
					while (true)
					{
						clsNode* parent = nullptr;
						clsNode* LeftBrother = nullptr;
						clsNode* RightBrother = nullptr;

						// we get from this variple -> (IndexBrothersAddOrSub) separator key and left brother and right brother
						int IndexBrothersAddOrSub = 0;

						_UpdateCurrentNodeInfo(LeftBrother, RightBrother, parent, curr, IndexBrothersAddOrSub, IndexKey, key);

						if (_BorrowingFromMyBrothers(LeftBrother, RightBrother, parent, curr, IndexBrothersAddOrSub, IndexKey) == true)
						{
							curr->IsDeleted = false;
							return true;
						}
						else
						{
							if (curr->IsDeleted == false)
							{
								curr->EraseKey(IndexKey);
							}
							else
							{
								curr->IsDeleted = false;
							}

							_Merge(LeftBrother, RightBrother, parent, curr, IndexBrothersAddOrSub, IndexKey);

							// here condetion must <= not ==  because _Root possible have less than _MinKeys and bigger than 1
							if (parent->KeysSize() <= _MinKeys)
							{
								if (parent == _Root)
								{
									// this condation mean _Root will be empty after delete separator key
									if (parent->KeysSize() == 1)
									{
										delete parent;
										_Root = curr;
										_Root->Parent = nullptr;
										return true;
									}

									// this condation mean _Root have keys other than separator key
									else if (parent->KeysSize() > 1)
									{
										// this varible -> (IndexBrothersAddOrSub) store index separator key in parent and we now child must deleted
										parent->EraseKey(IndexBrothersAddOrSub);
										parent->EraseChildren(IndexBrothersAddOrSub);
										return true;
									}
								}

								// this varible -> (IndexBrothersAddOrSub) store index separator key in parent
								key = parent->Keys[IndexBrothersAddOrSub];
								curr = parent;
								IndexKey = IndexBrothersAddOrSub;

								curr->EraseKey(IndexBrothersAddOrSub);
								curr->IsDeleted = true;
							}
							else // else here mean parent have keys > _MinKeys
							{
								// this varible -> (IndexBrothersAddOrSub) store index separator key in parent
								parent->EraseKey(IndexBrothersAddOrSub);
								parent->EraseChildren(IndexBrothersAddOrSub);
								return true;
							}
						}
					}
				}
				else if (curr->IsLeaf == false)
				{
					// tmp = max key in left current key
					clsNode* tmp = _FindMax(curr->Children[IndexKey]);

					int IndexLastKey = tmp->KeysSize() - 1;

					curr->Keys[IndexKey] = tmp->Keys[IndexLastKey];

					key = tmp->Keys[IndexLastKey];

					curr = tmp;
				}
			}
		}

	}

	// prameters reseve by refrance & becuase we need reduce space in memory only
	int _IsFind(clsNode*& Root, T& key)
	{
		clsNode* curr = Root;

		while (curr != nullptr)
		{
			int IndexKey = _BinarySearch(curr->Keys, key);

			if (IndexKey == -1)
			{
				if (curr->IsLeaf == true)
				{
					return IndexKey;
				}
				else
				{
					int IndexChildren = _GetIndexKey(curr, key);
					curr = curr->Children[IndexChildren];
				}
			}
			else
			{
				return IndexKey;
			}
		}
	}

	// prameter reseve by refrance & becuase we need reduce space in memory only
	void _Clear(clsNode*& Root)
	{
		Queue <clsNode*> q;

		clsNode* curr = nullptr;

		q.Enqueue(Root);

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			for (int i = 0; i < curr->ChildrenSize(); i++)
			{
				if (curr->Children[i] != nullptr)
				{
					q.Enqueue(curr->Children[i]);
				}
			}

			q.Dequeue();
			delete curr;
		}
	}

	// prameter reseve by refrance & becuase we need reduce space in memory only
	void _Copy(clsNode*& Root)
	{
		Queue <clsNode*> q;

		clsNode* curr = nullptr;

		q.Enqueue(Root);

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			for (int i = 0; i < curr->KeysSize(); i++)
			{
				Insert(curr->Keys[i]);
			}

			for (int i = 0; i < curr->ChildrenSize(); i++)
			{
				if (curr->Children[i] != nullptr)
				{
					q.Enqueue(curr->Children[i]);
				}
			}

			q.Dequeue();
		}
	}

	// prameter reseve by refrance & becuase we need reduce space in memory only
	clsNode* _FindMin(clsNode*& Root)
	{
		clsNode* curr = Root;

		while (curr->IsLeaf == false)
		{
			curr = curr->Children[0];
		}

		return curr;
	}

	// prameter reseve by refrance & becuase we need reduce space in memory only
	clsNode* _FindMax(clsNode*& Root)
	{
		clsNode* curr = Root;

		while (curr->IsLeaf == false)
		{
			int LastChildren = curr->ChildrenSize() - 1;
			curr = curr->Children[LastChildren];
		}

		return curr;
	}

	// prameter reseve by refrance & becuase we need reduce space in memory only
	int _GetHeight(clsNode*& Root)
	{
		clsNode* curr = Root;

		int height = 0;

		while (curr->IsLeaf == false)
		{
			curr = curr->Children[0];

			height++;
		}
		
		return height;
	}

	// prameter reseve by refrance & becuase we need reduce space in memory only
	/*void _DisPlayUsingLevelOrder(clsNode*& Root)
	{
		Queue <clsNode*> q;

		clsNode* curr = nullptr;

		q.Enqueue(Root);

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			for (int i = 0; i < curr->KeysSize(); i++)
			{
				cout << curr->Keys[i] << " ";
			}

			for (int i = 0; i < curr->ChildrenSize(); i++)
			{
				if (curr->Children[i] != nullptr)
				{
					q.Enqueue(curr->Children[i]);
				}
			}

			q.Dequeue();
		}

	}*/

	// prameter reseve by refrance & becuase we need reduce space in memory only
	void _DisPlayUsingLevelOrder(clsNode*& Root)
	{
		Queue <clsNode*> q;

		clsNode* curr = nullptr;

		q.Enqueue(Root);

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			cout << "======================================\n\n";
			cout << " is leaf        : " << curr->IsLeaf << "\n";
			cout << " count keys     : " << curr->KeysSize() << "\n";
			cout << " count children : " << curr->ChildrenSize() << "\n";
			cout << " node -> ";

			for (int i = 0; i < curr->KeysSize(); i++)
			{
				cout << curr->Keys[i] << " ";
			}

			cout << "\n\n======================================\n\n";

			for (int i = 0; i < curr->ChildrenSize(); i++)
			{
				if (curr->Children[i] != nullptr)
				{
					q.Enqueue(curr->Children[i]);
				}
			}

			q.Dequeue();
		}
	}

	// prameter reseve by refrance & becuase we need reduce space in memory only
	int _CountNode(clsNode*& Root)
	{
		int Count = 1;

		Queue <clsNode*> q;

		clsNode* curr = Root;

		q.Enqueue(Root);

		while (curr->IsLeaf == false)
		{
			curr = q.GetFront();

			// here we count children != nullptr in all nodes
			for (int i = 0; i < curr->ChildrenSize() && curr->IsLeaf == false; i++)
			{
				if (curr->Children[i] != nullptr)
				{
					q.Enqueue(curr->Children[i]);

					Count++;
				}
			}

			q.Dequeue();
		}

		return Count;
	}
	

public:


	BTree(float M)
	{
		_MaxChildren = M;
		_MaxKeys = M - 1;
		_MinChildren = ceil(M / 2);
		_MinKeys = ceil(M / 2 - 1);

		_Root = nullptr;
	}

	void  Delete(T key)
	{
		if (_Root == nullptr)
		{
			cout << "\nNo Element Found!\n";
			return;
		}

		if (_Root->KeysSize() == 1 && _Root->Children[0] == nullptr)
		{
			_CountKeys = 0;

			delete _Root;
			_Root = nullptr;
			return;
		}

		if (_Delete(_Root, key) == true)
		{
			_CountKeys--;
		}

	}

	void Insert(T key)
	{
		if (_MaxChildren <= 2)
		{
			cout << "\n\n The Order must be greater than 2!\n\n";
			return;
		}

		_CountKeys++;

		if (_Root == nullptr)
		{
			_Root = new clsNode;

			_Root->KeyPushBack(key);

			_Root->CreateChildren();

			_Root->IsLeaf = true;
		}
		else
		{
			_Insert(_Root, key);
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
			return _GetHeight(_Root);
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
			clsNode* tmp = _FindMax(_Root);
			int IndexLastKey = tmp->KeysSize() - 1;
			return  tmp->Keys[IndexLastKey];
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
			clsNode* tmp = _FindMin(_Root);
			return tmp->Keys[0];
		}
	}

	int GetNumberOfBrunchs()
	{
		if (IsEmpty())
		{
			cout << "\nEmpty Tree!\n";
		}
		else
		{
			return CountNode() - 1;
		}
	}

	bool IsEmpty()
	{
		return _Root == nullptr;
	}

	void DisPlayUsingLevelOrder()
	{
		if (IsEmpty())
		{
			cout << "\nEmpty Tree!\n";
			return;
		}

		cout << "\n\n{ ";
		_DisPlayUsingLevelOrder(_Root);
		cout << "}\n\n";
	}

	int CountNode()
	{
		if (IsEmpty())
		{
			cout << "\nEmpty Tree!\n";
		}
		else
		{
			return  _CountNode(_Root);
		}
	}

	int CountKeys()
	{
		if (IsEmpty())
		{
			cout << "\nEmpty Tree!\n";
		}
		else
		{
			return _CountKeys;
		}
	}

	bool IsFind(T key)
	{
		if (_Root == nullptr)
		{
			cout << "\nEmpty Tree!\n";
			return -1;
		}

		return _IsFind(_Root, key) == -1 ? false : true;
	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction (main) 
	void Copy(BTree <T>& CopyBTree)
	{
		if (!IsEmpty())
		{
			cout << "\nMy Tree Must be Empty!\n";
			return;
		}

		if (_MaxChildren != CopyBTree._MaxChildren)
		{
			cout << "M must be the same in tow B_Trees!\n";
			return;
		}

		if (CopyBTree._Root == nullptr)
		{
			cout << "\nEmpty Tree!\n";
			return;
		}

		_Copy(CopyBTree._Root);
	}

	void Clear()
	{
		if (_Root == nullptr)
		{
			return;
		}

		_Clear(_Root);

		_Root = nullptr;
	}

	~BTree()
	{
		Clear();
	}


	void _DisPlayUsingLevelOrder2(clsNode* Root)
	{
		Queue <clsNode*> q;

		q.Enqueue(Root);

		clsNode* curr;

		int i;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			cout << "\n Node -> ";
			for (i = 0; i < curr->Keys.size(); i++)
			{
				cout << curr->Keys[i] << " ";
			}
			if (curr->Parent != nullptr)
			{
				cout << " Parent -> ";
				for (i = 0; i < curr->Parent->Keys.size(); i++)
				{
					cout << curr->Parent->Keys[i] << " ";
				}
			}
			cout << " it is have " << curr->Children.size() << " children";
			cout << "\n";

			for (i = 0; i < curr->Children.size(); i++)
			{
				if (curr->Children[i] != nullptr)
				{
					q.Enqueue(curr->Children[i]);
				}
			}

			q.Dequeue();
		}

	}
	void DisPlayUsingLevelOrder2()
	{
		if (IsEmpty())
		{
			cout << "\nNo item Found!\n";
			return;
		}

		cout << "\n\n";
		_DisPlayUsingLevelOrder2(_Root);
		cout << "\n\n";
	}
};

