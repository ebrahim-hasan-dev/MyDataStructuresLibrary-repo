#pragma once


#include <iostream>
using namespace std;
#include <vector>

#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";
#include "..\Linear\Queue.h";


template <class T>
class BTree_Correct_Update
{
private:

	class NodeOfKeyAndData
	{
	public:

		double key;
		T data;

		NodeOfKeyAndData(double Key, T Data)
		{
			key = Key;
			data = Data;
		}

		NodeOfKeyAndData()
		{

		}
	};


	class Node
	{
	public:

		Node* Parent = nullptr;

		vector <Node*> vChildren;

		vector <NodeOfKeyAndData> vKeysAndData;

		bool isLeaf = true;
		bool isDeleted = false;
	};

	Node* _Root;

	int _MaxChildren;
	int _MinChildren;
	int _MaxKeys;
	int _MinKeys;

	int _CountKeys;


	// parameters not must be reseve by refrance, we need reduce space in momry only
	void _DisPlayUsingLevelOrder(Node*& Root)
	{
		Queue <Node*> q;

		q.Push(Root);

		Node* curr;

		int i;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			cout << "\nNode -> ";
			for (i = 0; i < curr->vKeysAndData.size(); i++)
			{
				cout << curr->vKeysAndData[i].key << " : " << curr->vKeysAndData[i].data;

				if (i != curr->vKeysAndData.size() - 1)
				{
					cout << " | ";
				}
			}
			if (curr->Parent != nullptr)
			{
				cout << "\nParent -> ";
				for (i = 0; i < curr->Parent->vKeysAndData.size(); i++)
				{
					cout << curr->Parent->vKeysAndData[i].key << " : " << curr->Parent->vKeysAndData[i].data;

					if (i != curr->Parent->vKeysAndData.size() - 1)
					{
						cout << " | ";
					}
				}
			}
			cout << "\nit is have " << curr->vChildren.size() << " children";
			cout << "\n";

			for (i = 0; i < curr->vChildren.size(); i++)
			{
				if (curr->vChildren[i] != nullptr)
				{
					q.Push(curr->vChildren[i]);
				}
			}

			q.Pop();
		}

	}

	// This parameter -> (T& key) not must reseve by refrance
	// This parameter -> (Node* node) must reseve by refrance
	int _BinarySearch(Node*& node, double& key)
	{
		int first = 0;
		int last = node->vKeysAndData.size() - 1;

		Node* tmp = node;

		while (first <= last)
		{
			int m = (first + last) / 2; // 48 49 70 

			if (key == node->vKeysAndData[m].key)
			{
				return m;
			}

			else if (key > node->vKeysAndData[m].key)
			{
				first = m + 1;

				if (node->vChildren.empty() == false)
				{
					tmp = node->vChildren[m + 1];
				}
			}

			else
			{
				last = m - 1;

				if (node->vChildren.empty() == false)
				{
					tmp = node->vChildren[m];
				}
			}
		}

		node = tmp;

		return -1;
	}

	// This parameter -> (Node* Root) must reseve by refrance, because Function_Delete Depend on this
	int _IsFind(Node*& Root, double& key)
	{
		int index = _BinarySearch(Root, key);

		if (index == -1)
		{
			while (Root->isLeaf == false)
			{
				index = _BinarySearch(Root, key);

				if (index != -1)
				{
					return index;
				}
			}

			index = _BinarySearch(Root, key);

			if (index != -1)
			{
				return index;
			}

			Root = nullptr;
			return -1;
		}
		else
		{
			return index;
		}

	}

	// parameters not must be reseve by refrance, we need reduce space in momry only
	void _Copy(Node*& Root)
	{
		Queue <Node*> q;

		q.Push(Root);

		Node* curr;

		int i;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			for (i = 0; i < curr->vKeysAndData.size(); i++)
			{
				this->Insert(curr->vKeysAndData[i].key, curr->vKeysAndData[i].data);
			}

			for (i = 0; i < curr->vChildren.size(); i++)
			{
				if (curr->vChildren[i] != nullptr)
				{
					q.Push(curr->vChildren[i]);
				}
			}

			q.Pop();
		}


	}

	// parameters never reseve by refrance
	Node* _FindMin(Node* Root)
	{
		while (Root->isLeaf == false)
		{
			Root = Root->vChildren[0];
		}

		return Root;
	}

	// parameters never reseve by refrance
	Node* _FindMax(Node* Root)
	{
		while (Root->isLeaf == false)
		{
			Root = Root->vChildren.back();
		}

		return Root;
	}

	int _GetIndexNode(Node* parent, Node* node)
	{
		for (int i = 0; i < parent->vChildren.size(); i++)
		{
			if (node == parent->vChildren[i])
				return i;
		}
	}

	// this parameter -> ( Node*& RightBrother ) and this parameter -> ( Node*& LeftBrother ),
	// and this parameter -> ( int& indexNode ) must reseve by refrance
	bool _Borrowing(Node* node, int indexItem, Node*& RightBrother, Node*& LeftBrother, int& indexNode)
	{
		typename vector <NodeOfKeyAndData>::iterator it;
		typename vector <Node*>::iterator itNode;

		if (node == node->Parent->vChildren.front())
		{
			RightBrother = node->Parent->vChildren[1];
		}
		else if (node == node->Parent->vChildren.back())
		{
			LeftBrother = node->Parent->vChildren[node->Parent->vChildren.size() - 2];
		}
		else
		{
			RightBrother = node->Parent->vChildren[indexNode + 1];
			LeftBrother = node->Parent->vChildren[indexNode - 1];
		}

		if (RightBrother != nullptr && RightBrother->vKeysAndData.size() > _MinKeys)
		{
			if (node->isDeleted == false)
			{
				it = node->vKeysAndData.begin() + indexItem;
				node->vKeysAndData.erase(it);
			}
			else
			{
				node->isDeleted = false;
			}

			if (node->isLeaf == false)
			{
				RightBrother->vChildren.front()->Parent = node;
				node->vChildren.push_back(RightBrother->vChildren.front());

				itNode = RightBrother->vChildren.begin();
				RightBrother->vChildren.erase(itNode);
			}

			NodeOfKeyAndData x = node->Parent->vKeysAndData[indexNode];
			node->vKeysAndData.push_back(x);

			x = RightBrother->vKeysAndData[0];

			node->Parent->vKeysAndData[indexNode] = x;

			it = RightBrother->vKeysAndData.begin();
			RightBrother->vKeysAndData.erase(it);

			return true;
		}

		if (LeftBrother != nullptr && LeftBrother->vKeysAndData.size() > _MinKeys)
		{
			if (node->isDeleted == false)
			{
				it = node->vKeysAndData.begin() + indexItem;
				node->vKeysAndData.erase(it);
			}
			else
			{
				node->isDeleted = false;
			}

			if (node->isLeaf == false)
			{
				LeftBrother->vChildren.back()->Parent = node;
				itNode = node->vChildren.begin();

				node->vChildren.insert(itNode, LeftBrother->vChildren.back());
				LeftBrother->vChildren.pop_back();
			}

			NodeOfKeyAndData x = node->Parent->vKeysAndData[indexNode - 1];

			if (node->vKeysAndData.empty())
			{
				node->vKeysAndData.push_back(x);
			}
			else
			{
				it = node->vKeysAndData.begin();
				node->vKeysAndData.insert(it, x);
			}

			x = LeftBrother->vKeysAndData.back();

			node->Parent->vKeysAndData[indexNode - 1] = x;

			LeftBrother->vKeysAndData.pop_back();

			return true;
		}

		return false;
	}

	void _Merge(Node* node, Node* RightBrother, Node* LeftBrother, int indexItem, int& indexNode)
	{
		typename vector <NodeOfKeyAndData>::iterator it;
		typename vector <Node*>::iterator itNode;
		int i = 0;

		if (RightBrother != nullptr)
		{
			if (node->isDeleted == false)
			{
				it = node->vKeysAndData.begin() + indexItem;
				node->vKeysAndData.erase(it);
			}
			else
			{
				node->isDeleted = false;
			}

			node->vKeysAndData.push_back(node->Parent->vKeysAndData[indexNode]);

			it = node->Parent->vKeysAndData.begin() + indexNode;
			node->Parent->vKeysAndData.erase(it);
			indexItem = indexNode;

			for (i = 0; i < RightBrother->vKeysAndData.size(); i++)
			{
				node->vKeysAndData.push_back(RightBrother->vKeysAndData[i]);
			}

			if (RightBrother->vChildren.empty() == false)
			{
				for (i = 0; i < RightBrother->vChildren.size(); i++)
				{
					node->vChildren.push_back(RightBrother->vChildren[i]);
				}

				_UpdateParent(node);
			}

			int indexRightBrother = _GetIndexNode(RightBrother->Parent, RightBrother);
			itNode = RightBrother->Parent->vChildren.begin() + indexRightBrother;
			RightBrother->Parent->vChildren.erase(itNode);

			delete RightBrother;
			RightBrother = nullptr;
		}

		else if (LeftBrother != nullptr)
		{
			if (node->isDeleted == false)
			{
				it = node->vKeysAndData.begin() + indexItem;
				node->vKeysAndData.erase(it);
			}
			else
			{
				node->isDeleted = false;
			}

			it = node->vKeysAndData.begin();
			NodeOfKeyAndData n = node->Parent->vKeysAndData[indexNode - 1];

			if (node->vKeysAndData.empty())
			{
				node->vKeysAndData.push_back(n);
			}
			else
			{
				node->vKeysAndData.insert(it, n);
			}

			it = node->Parent->vKeysAndData.begin() + (indexNode - 1);
			node->Parent->vKeysAndData.erase(it);
			indexItem = (indexNode - 1);

			for (i = LeftBrother->vKeysAndData.size() - 1; i >= 0; i--)
			{
				it = node->vKeysAndData.begin();
				n = LeftBrother->vKeysAndData[i];
				node->vKeysAndData.insert(it, n);
			}

			if (LeftBrother->vChildren.empty() == false)
			{
				int size = LeftBrother->vChildren.size();
				int Lastindex = LeftBrother->vChildren.size() - 1;

				for (i = 0; i < size; i++)
				{
					itNode = node->vChildren.begin();
					Node* tmp = LeftBrother->vChildren[Lastindex];
					node->vChildren.insert(itNode, tmp);
					Lastindex--;
				}

				_UpdateParent(node);
			}

			int indexLeftBrother = _GetIndexNode(LeftBrother->Parent, LeftBrother);
			itNode = LeftBrother->Parent->vChildren.begin() + indexLeftBrother;
			LeftBrother->Parent->vChildren.erase(itNode);

			delete LeftBrother;
			LeftBrother = nullptr;
		}

	}

	// parameters not must be reseve by refrance, we need reduce space in momry only
	void _Delete(Node*& Root, double& key)
	{
		Node* node = Root;

		int indexItem = _IsFind(node, key);

		if (node != nullptr)
		{
			_CountKeys--;

			typename vector <NodeOfKeyAndData>::iterator it;

			if (node == _Root && node->isLeaf == true)
			{
				it = node->vKeysAndData.begin() + indexItem;
				node->vKeysAndData.erase(it);

				if (node->vKeysAndData.empty())
				{
					delete _Root;
					_Root = nullptr;
				}

				return;
			}

			if (node->isLeaf == false)
			{
				Node* Predecessor = _FindMax(node->vChildren[indexItem]);

				node->vKeysAndData[indexItem] = Predecessor->vKeysAndData.back();

				node = Predecessor;

				indexItem = Predecessor->vKeysAndData.size() - 1;
			}

			while (node != _Root)
			{
				if (node->vKeysAndData.size() > _MinKeys)
				{
					it = node->vKeysAndData.begin() + indexItem;
					node->vKeysAndData.erase(it);
					return;
				}

				Node* RightBrother = nullptr;
				Node* LeftBrother = nullptr;

				int indexNode = _GetIndexNode(node->Parent, node);

				if (_Borrowing(node, indexItem, RightBrother, LeftBrother, indexNode) == true)
				{
					return;
				}
				else
				{
					_Merge(node, RightBrother, LeftBrother, indexItem, indexNode);

					if (node->Parent == _Root)
					{
						if (node->Parent->vKeysAndData.empty())
						{
							delete _Root;
							_Root = node;
							_Root->Parent = nullptr;
						}

						return;
					}

					if (node->Parent->vKeysAndData.size() < _MinKeys)
					{
						node = node->Parent;
						node->isDeleted = true;
						continue;
					}
					else
					{
						return;
					}

				}


			}

		}

	}

	// parameter -> ( Node*& node ) not must be reseve by refrance, we need reduce space in momry only
	bool _IsLeaf(Node*& node)
	{
		return !node->vChildren.empty() && node->vChildren[0] != nullptr ? false : true;
	}

	// parameters not must be reseve by refrance, we need reduce space in momry only
	int _GetIndex(Node*& node, double& key)
	{
		return _BinarySearch(node, key);
	}


	struct LeftAndRightChildren
	{
		Node* Leftnode;
		Node* Rightnode;
	};


	LeftAndRightChildren _Insert3(Node* node, NodeOfKeyAndData Middleitem, int& pos)
	{
		int i = _BinarySearchInKeys(node, Middleitem.key);

		typename vector <NodeOfKeyAndData>::iterator it = node->vKeysAndData.begin() + i;
		typename vector <Node*>::iterator it2 = node->vChildren.begin() + i;

		pos = i;

		node->vKeysAndData.insert(it, Middleitem);
		node->vChildren.insert(it2, node->vChildren[i]);

		LeftAndRightChildren x = _Split(node);

		return x;
	}

	int _Insert2(Node* node, NodeOfKeyAndData Middleitem)
	{
		int i = _BinarySearchInKeys(node, Middleitem.key);

		typename vector <NodeOfKeyAndData>::iterator it = node->vKeysAndData.begin() + i;
		typename vector <Node*>::iterator it2 = node->vChildren.begin() + i;

		node->vKeysAndData.insert(it, Middleitem);
		node->vChildren.insert(it2, node->vChildren[i]);

		return i;
	}

	void _UpdateParent(Node* node)
	{
		for (int i = 0; i < node->vChildren.size(); i++)
		{
			if (node->vChildren[i] != nullptr)
			{
				node->vChildren[i]->Parent = node;
			}
		}
	}

	void _SplitHelper(Node* Leftnode, Node* Rightnode, Node* node, int IndexMiddleitem)
	{
		NodeOfKeyAndData n;
		int i;

		// copy keys
		for (i = 0; i < IndexMiddleitem; i++)
		{
			n = node->vKeysAndData[i];
			Leftnode->vKeysAndData.push_back(n);
		}

		for (i = IndexMiddleitem + 1; i < _MaxChildren; i++)
		{
			n = node->vKeysAndData[i];
			Rightnode->vKeysAndData.push_back(n);
		}

		if (_IsLeaf(node) == false)
		{
			// copy children
			for (i = 0; i <= IndexMiddleitem; i++)
			{
				Leftnode->vChildren.push_back(node->vChildren[i]);
			}


			for (i = IndexMiddleitem + 1; i < node->vChildren.size(); i++)
			{
				Rightnode->vChildren.push_back(node->vChildren[i]);
			}

			_UpdateParent(Leftnode);
			_UpdateParent(Rightnode);
		}
	}

	LeftAndRightChildren _Split(Node* node)
	{
		int IndexMiddleitem = _MaxChildren / 2;
		NodeOfKeyAndData Middleitem = node->vKeysAndData[IndexMiddleitem];

		Node* Leftnode = new Node;
		Node* Rightnode = new Node;

		_SplitHelper(Leftnode, Rightnode, node, IndexMiddleitem);

		if (node->Parent == nullptr)
		{
			node->isLeaf = false;
			node->vKeysAndData.clear();

			if (node->vChildren.empty() == false)
			{
				node->vChildren.clear();
			}

			node->vKeysAndData.push_back(Middleitem);

			node->vChildren.resize(node->vKeysAndData.size() + 1);

			node->vChildren[0] = Leftnode;
			node->vChildren[1] = Rightnode;

			Leftnode->Parent = node;
			Rightnode->Parent = node;
		}
		else
		{
			if (node->Parent->vKeysAndData.size() == _MaxKeys)
			{
				int pos = 0;

				LeftAndRightChildren x = _Insert3(node->Parent, Middleitem, pos);

				int i = 0;

				if (pos < IndexMiddleitem)
				{
					Leftnode->Parent = x.Leftnode;
					Rightnode->Parent = x.Leftnode;

					i = _GetIndex(x.Leftnode, Middleitem.key);

					x.Leftnode->vChildren[i] = Leftnode;
					x.Leftnode->vChildren[i + 1] = Rightnode;
				}
				else if (pos > IndexMiddleitem)
				{
					Leftnode->Parent = x.Rightnode;
					Rightnode->Parent = x.Rightnode;

					i = _GetIndex(x.Rightnode, Middleitem.key);

					x.Rightnode->vChildren[i] = Leftnode;
					x.Rightnode->vChildren[i + 1] = Rightnode;
				}
				else if (pos == IndexMiddleitem)
				{
					Leftnode->Parent = x.Leftnode;
					Rightnode->Parent = x.Rightnode;

					x.Leftnode->vChildren.back() = Leftnode;
					x.Rightnode->vChildren[0] = Rightnode;
				}

				delete node;
			}
			else if (node->Parent->vKeysAndData.size() < _MaxKeys)
			{
				int Indexitem = _Insert2(node->Parent, Middleitem);

				Leftnode->Parent = node->Parent;
				Rightnode->Parent = node->Parent;

				node->Parent->vChildren[Indexitem] = Leftnode;
				node->Parent->vChildren[Indexitem + 1] = Rightnode;

				delete node;
			}
		}

		Leftnode->isLeaf = _IsLeaf(Leftnode);
		Rightnode->isLeaf = _IsLeaf(Rightnode);

		return LeftAndRightChildren{ Leftnode , Rightnode };
	}

	int _BinarySearchInKeys(Node* node, double key)
	{
		int first = 0;
		int last;

		last = node->vKeysAndData.size() - 1;

		int CorrectIndex = 0;

		while (first <= last)
		{
			int m = (first + last) / 2;

			if (key >= node->vKeysAndData[m].key)
			{
				first = m + 1;
				CorrectIndex = m + 1;
			}
			else
			{
				last = m - 1;
				CorrectIndex = m;
			}
		}

		return CorrectIndex;
	}

	Node* _InsertHelper(Node* node, double key)
	{
		while (node->isLeaf == false)
		{
			int i = _BinarySearchInKeys(node, key);
					
			node = node->vChildren[i];
		}

		return node;
	}

	// parameter -> ( Node* node ) never reseve by refrance 
	void _Insert(Node* node, double key, T Data)
	{
		if (node->isLeaf)
		{
			int i = _BinarySearchInKeys(node, key);

			class vector <NodeOfKeyAndData>::iterator it = node->vKeysAndData.begin() + i;

			node->vKeysAndData.insert(it, NodeOfKeyAndData(key, Data));
				
			if (node->vKeysAndData.size() == _MaxChildren)
			{
				_Split(node);
			}
		}
		else
		{
			node = _InsertHelper(node, key);
			_Insert(node, key, Data);
		}

	}

	int _CountNode(Node*& Root)
	{
		int Count = 1;

		Queue <Node*> q;

		Node* curr = Root;

		q.Push(Root);

		while (curr->isLeaf == false)
		{
			curr = q.GetFront();

			// here we count children != nullptr in all nodes
			for (int i = 0; i < curr->vChildren.size() && curr->isLeaf == false; i++)
			{
				if (curr->vChildren[i] != nullptr)
				{
					q.Push(curr->vChildren[i]);

					Count++;
				}
			}

			q.Pop();
		}

		return Count;
	}

	// parameters not must be reseve by refrance, we need reduce space in momry only
	void _Clear(Node*& Root)
	{
		Queue <Node*> q;

		q.Push(Root);

		Node* curr;

		int i;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();

			for (i = 0; i < curr->vChildren.size(); i++)
			{
				if (curr->vChildren[i] != nullptr)
				{
					q.Push(curr->vChildren[i]);
				}
			}

			delete curr;

			q.Pop();
		}

	}

	// parameters never reseve by refrance
	int _GetHeight(Node* Root)
	{
		int height = 0;

		while (Root->isLeaf == false)
		{
			Root = Root->vChildren[0];
			height++;
		}

		return height;
	}


public:


	BTree_Correct_Update(int Order)
	{
		float m = Order;

		_MaxChildren = m;
		_MinChildren = ceil(m / 2);
		_MaxKeys = m - 1;
		_MinKeys = ceil(m / 2 - 1);

		_Root = nullptr;
		_CountKeys = 0;
	}

	void Insert(double key, T Data)
	{
		if (_MaxChildren <= 2)
		{
			cout << "\n\n The Order must be greater than 2!\n\n";
			return;
		}

		if (IsEmpty())
		{
			_Root = new Node;

			_Root->vKeysAndData.push_back(NodeOfKeyAndData(key, Data));
		}
		else
		{
			if (IsFind(key) == true)
			{
				cout << "\n\n this key is already found!\n\n";
				return;
			}

			_Insert(_Root, key, Data);
		}

		_CountKeys++;
	}

	void Delete(double key)
	{
		if (IsEmpty())
		{
			cout << "\nTree is Empty!\n";
			return;
		}

		_Delete(_Root, key);
	}

	int GetHeight()
	{
		if (IsEmpty())
		{
			cout << "\nTree is Empty!\n";
			return -1;
		}

		return _GetHeight(_Root);
	}

	double FindMax()
	{
		if (IsEmpty())
		{
			cout << "\nTree is Empty!\n";
			return -1;
		}
		else
		{
			return _FindMax(_Root)->vKeysAndData.back().key;
		}
	}

	double FindMin()
	{
		if (IsEmpty())
		{
			cout << "\nTree is Empty!\n";
			return -1;
		}
		else
		{
			return _FindMin(_Root)->vKeysAndData[0].key;
		}
	}

	int CountNode()
	{
		if (IsEmpty())
		{
			cout << "\nEmpty Tree!\n";
			return -1;
		}
		else
		{
			return  _CountNode(_Root);
		}
	}

	int GetNumberOfBrunchs()
	{
		if (IsEmpty())
		{
			cout << "\nEmpty Tree!\n";
			return -1;
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
			cout << "\nNo key Found!\n";
			return;
		}

		cout << "\n\n";
		_DisPlayUsingLevelOrder(_Root);
		cout << "\n\n";
	}

	int Count()
	{
		return _CountKeys;
	}

	bool IsFind(double key)
	{
		if (IsEmpty())
		{
			cout << "\nTree is Empty!\n";
			return false;
		}

		Node* tmp = _Root;

		if (_IsFind(tmp, key) == -1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(BTree_Correct_Update& CopyBTree_Correct_Update)
	{
		if (!IsEmpty())
		{
			cout << "\nTree Must be Empty!\n";
			return;
		}

		if (CopyBTree_Correct_Update.IsEmpty())
		{
			cout << "\nCopy Tree is Empty!\n";
			return;
		}

		if (CopyBTree_Correct_Update._MaxChildren != _MaxChildren)
		{
			cout << "\nThe Order in two Btree must be the same!\n";
			return;
		}

		_Copy(CopyBTree_Correct_Update._Root);
	}

	void Clear()
	{
		if (IsEmpty())
		{
			cout << "\nTree is Empty!\n";
			return;
		}

		_Clear(_Root);

		_Root = nullptr;
	}

	~BTree_Correct_Update()
	{
		Clear();
	}



};




