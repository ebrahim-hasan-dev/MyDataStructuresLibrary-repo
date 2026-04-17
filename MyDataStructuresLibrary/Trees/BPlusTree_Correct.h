#pragma once

#include <iostream>
using namespace std;
#include <vector>

#include "..\MyLibrary\clsInput.h";
#include "..\MyLibrary\clsUtil.h";
#include "..\Linear\Queue.h";


template <class K, class T>
class BPlusTree_Correct
{
private:

	class NodeOfKeysAndData
	{
	public:

		K key;
		T data;

		NodeOfKeysAndData(K Key, T Data)
		{
			key = Key;
			data = Data;
		}

		NodeOfKeysAndData()
		{

		}
	};

	class Node
	{
	public:

		Node* Parent = nullptr;
		Node* Right = nullptr;

		vector <Node*> vChildren;

		vector <K> vKeys;
		vector <NodeOfKeysAndData> vKeysAndData;

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
			if (curr->vKeysAndData.empty() == false)
			{
				for (i = 0; i < curr->vKeysAndData.size(); i++)
				{
					cout << curr->vKeysAndData[i].key << " : " << curr->vKeysAndData[i].data;

					if (i != curr->vKeysAndData.size() - 1)
					{
						cout << " | ";
					}
				}
			}
			else
			{
				for (i = 0; i < curr->vKeys.size(); i++)
				{
					cout << curr->vKeys[i] << " ";
				}
			}

			
			if (curr->Parent != nullptr && curr->Parent->vKeysAndData.empty() == true)
			{
				cout << "  Parent -> ";
				for (i = 0; i < curr->Parent->vKeys.size(); i++)
				{
					cout << curr->Parent->vKeys[i] << " ";
				}
			}
			cout << " it is have " << curr->vChildren.size() << " children";
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
	int _BinarySearch(Node* node, K& key)
	{
		int first = 0;
		int last;

		if (node->isLeaf == true)
		{
			last = node->vKeysAndData.size() - 1;
		}
		else
		{
			last = node->vKeys.size() - 1;
		}


		while (first <= last)
		{
			int m = (first + last) / 2;

			if (key == (node->isLeaf ? node->vKeysAndData[m].key : node->vKeys[m]))
			{
				return m;
			}

			else if (key > (node->isLeaf ? node->vKeysAndData[m].key : node->vKeys[m]))
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

	// This parameter -> (Node* Root) must reseve by refrance, because Function_Delete Depend on this
	int _IsFind(Node*& Root, K& key)
	{
		Root = _InsertHelper(Root, key);

		int index = _BinarySearch(Root, key);

		if (index == -1)
		{
			return -1;
		}
		else
		{
			return index;
		}

	}

	// parameters not must be reseve by refrance, we need reduce space in momry only
	void _Copy(Node* Root)
	{
		Root = _FindMin(Root);

		while (Root != nullptr)
		{
			for (int i = 0; i < Root->vKeysAndData.size(); i++)
			{
				this->Insert(Root->vKeysAndData[i].key, Root->vKeysAndData[i].data);
			}

			Root = Root->Right;
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

	int _GetIndexNode(Node* parent, Node* Node)
	{
		for (int i = 0; i < parent->vChildren.size(); i++)
		{
			if (Node == parent->vChildren[i])
				return i;
		}
	}

	// this parameter -> ( Node*& RightBrother ) and this parameter -> ( Node*& LeftBrother ),
	// and this parameter -> ( int& indexNode ) must reseve by refrance
	bool _Borrowing(Node* node, int indexItem, Node*& RightBrother, Node*& LeftBrother, int& indexNode, K key)
	{
		typename vector <K>::iterator itk;
		typename vector <NodeOfKeysAndData>::iterator it;
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

		if (RightBrother != nullptr && (node->isLeaf ? RightBrother->vKeysAndData.size() > _MinKeys : RightBrother->vKeys.size() > _MinKeys))
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

			NodeOfKeysAndData x;
			K k;

			if (node->isLeaf == false)
			{
				k = node->Parent->vKeys[indexNode];
				node->vKeys.push_back(k);
			}
			else
			{
				node->Parent->vKeys[indexNode] = RightBrother->vKeysAndData[1].key;
			}
			
			if (node->isLeaf == false)
			{
				k = RightBrother->vKeys[0];
			}
			else
			{
				x = RightBrother->vKeysAndData[0];
			}

			if (node->isLeaf == false)
			{
				node->Parent->vKeys[indexNode] = k;
			}
			else
			{
				node->vKeysAndData.push_back(x);
			}

			if (node->isLeaf == true && indexItem == 0 && indexNode > 0)
			{
				node->Parent->vKeys[indexNode - 1] = node->vKeysAndData[0].key;
			}
			else if (node->isLeaf == true && indexItem == 0 && indexNode == 0)
			{
				if (node->Parent != nullptr)
				{
					Node* tmp = node->Parent->Parent;

					if (tmp != nullptr)
					{
						int index = _BinarySearch(tmp, key);

						while (index == -1 && tmp != _Root)
						{
							tmp = tmp->Parent;
							index = _BinarySearch(tmp, key);
						}

						if (index != -1)
						{
							tmp->vKeys[index] = node->vKeysAndData[0].key;
						}
					}
				}
			}

			if (node->isLeaf == false)
			{
				itk = RightBrother->vKeys.begin();
				RightBrother->vKeys.erase(itk);
			}
			else
			{
				it = RightBrother->vKeysAndData.begin();
				RightBrother->vKeysAndData.erase(it);
			}
			
			return true;
		}

		if (LeftBrother != nullptr && (node->isLeaf ? LeftBrother->vKeysAndData.size() > _MinKeys :  LeftBrother->vKeys.size() > _MinKeys))
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

			NodeOfKeysAndData x;
			K k;

			if (node->isLeaf == false)
			{
				k = node->Parent->vKeys[indexNode - 1];
			}
			else
			{
				x = LeftBrother->vKeysAndData.back();
			}

			if (node->isLeaf == false)
			{
				if (node->vKeys.empty())
				{
					node->vKeys.push_back(k);
				}
				else
				{
					itk = node->vKeys.begin();
					node->vKeys.insert(itk, k);
				}
			}
			else
			{
				if (node->vKeysAndData.empty())
				{
					node->vKeysAndData.push_back(x);
				}
				else
				{
					it = node->vKeysAndData.begin();
					node->vKeysAndData.insert(it, x);
				}
			}

			if (node->isLeaf)
			{
				k = LeftBrother->vKeysAndData.back().key;
			}
			else
			{
				k = LeftBrother->vKeys.back();
			}

			node->Parent->vKeys[indexNode - 1] = k;

			if (node->isLeaf)
			{
				LeftBrother->vKeysAndData.pop_back();
			}
			else
			{
				LeftBrother->vKeys.pop_back();
			}

			return true;
		}

		return false;
	}

	void _Merge(Node* node, Node* RightBrother, Node* LeftBrother, int indexItem, int& indexNode)
	{
		typename vector <K>::iterator itk;
		typename vector <NodeOfKeysAndData>::iterator it;
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

			if (node->isLeaf == false)
			{
				node->vKeys.push_back(node->Parent->vKeys[indexNode]);
			}
			
			itk = node->Parent->vKeys.begin() + indexNode;
			node->Parent->vKeys.erase(itk);
			
			indexItem = indexNode;

			if (node->isLeaf)
			{
				for (i = 0; i < RightBrother->vKeysAndData.size(); i++)
				{
					node->vKeysAndData.push_back(RightBrother->vKeysAndData[i]);
				}
			}
			else
			{
				for (i = 0; i < RightBrother->vKeys.size(); i++)
				{
					node->vKeys.push_back(RightBrother->vKeys[i]);
				}
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

			if (RightBrother->Right == nullptr)
			{
				node->Right = nullptr;
			}

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

			NodeOfKeysAndData n;
			K k;

			if (node->isLeaf == false)
			{
				itk = node->vKeys.begin();
				k = node->Parent->vKeys[indexNode - 1];

				if (node->vKeys.empty())
				{
					node->vKeys.push_back(k);
				}
				else
				{
					node->vKeys.insert(itk, k);
				}
			}

			itk = node->Parent->vKeys.begin() + (indexNode - 1);
			node->Parent->vKeys.erase(itk);

			indexItem = (indexNode - 1);

			if (node->isLeaf)
			{
				for (i = LeftBrother->vKeysAndData.size() - 1; i >= 0; i--)
				{
					it = node->vKeysAndData.begin();
					n = LeftBrother->vKeysAndData[i];
					node->vKeysAndData.insert(it, n);
				}
			}
			else
			{
				for (i = LeftBrother->vKeys.size() - 1; i >= 0; i--)
				{
					itk = node->vKeys.begin();
					k = LeftBrother->vKeys[i];
					node->vKeys.insert(itk, k);
				}
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
	void _Delete(Node*& Root, K& key)
	{
		Node* node = Root;

		int indexItem = _IsFind(node, key);

		if (indexItem != -1)
		{
			_CountKeys--;

			typename vector <NodeOfKeysAndData>::iterator it;

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

			Node* OriginalNode = node;
			int OriginalIndexItem = indexItem;

			while (node != _Root)
			{
				if (node->vKeysAndData.size() > _MinKeys)
				{
					it = node->vKeysAndData.begin() + indexItem;
					node->vKeysAndData.erase(it);
					break;
				}

				Node* RightBrother = nullptr;
				Node* LeftBrother = nullptr;

				int indexNode = _GetIndexNode(node->Parent, node);

				if (_Borrowing(node, indexItem, RightBrother, LeftBrother, indexNode, key) == true)
				{
					break;
				}
				else
				{
					_Merge(node, RightBrother, LeftBrother, indexItem, indexNode);
					
					if (node->Parent == _Root)
					{
						if (node->Parent->vKeys.empty())
						{
							delete _Root;
							_Root = node;
							_Root->Parent = nullptr;
						}

						break;
					}

					if (node->Parent->vKeys.size() < _MinKeys)
					{
						node = node->Parent;
						node->isDeleted = true;
						continue;
					}
					else
					{
						break;
					}
				}
			}

			if (OriginalNode->Parent != nullptr)
			{
				int index = _GetIndexNode(OriginalNode->Parent, OriginalNode);

				if (index > 0)
				{
					OriginalNode->Parent->vKeys[index - 1] = OriginalNode->vKeysAndData[0].key;
				}
				else if (OriginalIndexItem == 0 && index == 0)
				{
					Node* Grandba = OriginalNode->Parent->Parent;

					if (Grandba != nullptr)
					{
						int index = _BinarySearch(Grandba, key);

						while (index == -1 && Grandba != _Root)
						{
							Grandba = Grandba->Parent;
							index = _BinarySearch(Grandba, key);
						}

						if (index != -1)
						{
							Grandba->vKeys[index] = OriginalNode->vKeysAndData[0].key;
						}
					}
				}
			}
		}

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

	// parameter -> ( Node*& Node ) not must be reseve by refrance, we need reduce space in momry only
	bool _IsLeaf(Node*& node)
	{
		return !node->vChildren.empty() && node->vChildren[0] != nullptr ? false : true;
	}

	// parameters not must be reseve by refrance, we need reduce space in momry only
	int _GetIndex(Node*& node, K& key)
	{
		return _BinarySearch(node, key);
	}


	struct LeftAndRightChildren
	{
		Node* Leftnode;
		Node* Rightnode;
	};


	LeftAndRightChildren _Insert3(Node* node, K MiddleKey, int& pos)
	{
		typename vector <K>::iterator it;
		typename vector <Node*>::iterator it2;

		if (MiddleKey < node->vKeys[0])
		{
			it = node->vKeys.begin();
			it2 = node->vChildren.begin();

			node->vKeys.insert(it, MiddleKey);
			node->vChildren.insert(it2, node->vChildren[0]);

			pos = 0;
		}
		else if (MiddleKey >= node->vKeys.back())
		{
			Node* tmp = nullptr;
			pos = node->vKeys.size();
			node->vKeys.push_back(MiddleKey);
			node->vChildren.push_back(tmp);
		}
		else
		{
			for (int i = 0; i < node->vKeys.size() - 1; i++)
			{
				if (MiddleKey >= node->vKeys[i] && MiddleKey < node->vKeys[i + 1])
				{
					it = node->vKeys.begin() + (i + 1);
					it2 = node->vChildren.begin() + (i + 1);

					node->vKeys.insert(it, MiddleKey);
					node->vChildren.insert(it2, node->vChildren[i + 1]);
					pos = i + 1;
					break;
				}
			}
		}

		LeftAndRightChildren x = _Split(node);

		return x;
	}

	int _Insert2(Node* node, K MiddleKey)
	{
		int Indexitem = 0;

		typename vector <K>::iterator it;
		typename vector <Node*>::iterator it2;

		if (MiddleKey < node->vKeys[0])
		{
			it = node->vKeys.begin();
			it2 = node->vChildren.begin();

			node->vKeys.insert(it, MiddleKey);
			node->vChildren.insert(it2, node->vChildren[0]);

			Indexitem = 0;
		}
		else if (MiddleKey >= node->vKeys.back())
		{
			int indexLastItem = node->vKeys.size();
			Node* tmp = nullptr;

			node->vKeys.push_back(MiddleKey);
			node->vChildren.push_back(tmp);
			
			Indexitem = indexLastItem;
		}
		else
		{
			for (int i = 0; i < node->vKeys.size() - 1; i++)
			{
				if (MiddleKey >= node->vKeys[i] && MiddleKey < node->vKeys[i + 1])
				{
					it = node->vKeys.begin() + (i + 1);
					it2 = node->vChildren.begin() + (i + 1);

					node->vKeys.insert(it, MiddleKey);
					node->vChildren.insert(it2, node->vChildren[i + 1]);

					Indexitem = i + 1;
					break;
				}
			}
		}

		return Indexitem;
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

	void _SplitHelperLeaf(Node* Leftnode, Node* Rightnode, Node* node, int IndexMiddleitem)
	{
		NodeOfKeysAndData n;
		int i;

		// copy keys
		for (i = 0; i < IndexMiddleitem; i++)
		{
			n = node->vKeysAndData[i];
			Leftnode->vKeysAndData.push_back(n);
		}

		for (i = IndexMiddleitem ; i < _MaxChildren; i++)
		{
			n = node->vKeysAndData[i];
			Rightnode->vKeysAndData.push_back(n);
		}

	}

	void _SplitHelperInternal(Node* Leftnode, Node* Rightnode, Node* node, int IndexMiddleitem)
	{
		int i;

		// copy keys
		for (i = 0; i < IndexMiddleitem; i++)
		{
			Leftnode->vKeys.push_back(node->vKeys[i]);
		}

		for (i = IndexMiddleitem + 1; i < _MaxChildren; i++)
		{
			Rightnode->vKeys.push_back(node->vKeys[i]);
		}

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

	LeftAndRightChildren _Split(Node* node)
	{
		Node* Leftnode = new Node;
		Node* Rightnode = new Node;

		int IndexMiddleKey = _MaxChildren / 2;
		K MiddleKey;

		if (node->isLeaf == true)
		{
			MiddleKey = node->vKeysAndData[IndexMiddleKey].key;

			_SplitHelperLeaf(Leftnode, Rightnode, node, IndexMiddleKey);
		}
		else
		{
			MiddleKey = node->vKeys[IndexMiddleKey];

			_SplitHelperInternal(Leftnode, Rightnode, node, IndexMiddleKey);
		}
	

		if (node->Parent == nullptr)
		{
			if (node->isLeaf == true)
			{
				node->vKeysAndData.clear();
				node->isLeaf = false;
			}
			else
			{
				node->vKeys.clear();
				node->vChildren.clear();
			}

			node->vKeys.push_back(MiddleKey);

			node->vChildren.resize(node->vKeys.size() + 1);

			node->vChildren[0] = Leftnode;
			node->vChildren[1] = Rightnode;

			Leftnode->Parent = node;
			Rightnode->Parent = node;
		}
		else
		{
			if (node->Parent->vKeys.size() == _MaxKeys)
			{
				int pos = 0;

				LeftAndRightChildren x = _Insert3(node->Parent, MiddleKey, pos);

				int i = 0;

				if (pos < IndexMiddleKey)
				{
					Leftnode->Parent = x.Leftnode;
					Rightnode->Parent = x.Leftnode;

					i = _GetIndex(x.Leftnode, MiddleKey);

					x.Leftnode->vChildren[i] = Leftnode;
					x.Leftnode->vChildren[i + 1] = Rightnode;
				}
				else if (pos > IndexMiddleKey)
				{
					Leftnode->Parent = x.Rightnode;
					Rightnode->Parent = x.Rightnode;

					i = _GetIndex(x.Rightnode, MiddleKey);

					x.Rightnode->vChildren[i] = Leftnode;
					x.Rightnode->vChildren[i + 1] = Rightnode;
				}
				else if (pos == IndexMiddleKey)
				{
					Leftnode->Parent = x.Leftnode;
					Rightnode->Parent = x.Rightnode;

					x.Leftnode->vChildren.back() = Leftnode;
					x.Rightnode->vChildren[0] = Rightnode;
				}

				delete node;
			}
			else if (node->Parent->vKeys.size() < _MaxKeys)
			{
				int Indexitem = _Insert2(node->Parent, MiddleKey);

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

	Node* _InsertHelper(Node* node, K key)
	{
		while (node->isLeaf == false)
		{
			if (key < node->vKeys[0])
			{
				node = node->vChildren[0];
			}
			else if (key >= node->vKeys.back())
			{
				node = node->vChildren.back();
			}
			else
			{
				for (int i = 0; i < node->vKeys.size() - 1; i++)
				{
					if (key >= node->vKeys[i] && key < node->vKeys[i + 1])
					{
						node = node->vChildren[i + 1];
						break;
					}
				}
			}
		}

		return node;
	}

	// parameter -> ( Node* Node ) never reseve by refrance 
	void _Insert(Node* node, K key, T Data)
	{
		if (node->isLeaf)
		{
			class vector <NodeOfKeysAndData>::iterator it;

			if (key <= node->vKeysAndData[0].key)
			{
				it = node->vKeysAndData.begin();
				node->vKeysAndData.insert(it, NodeOfKeysAndData(key, Data));
			}
			else if (key > node->vKeysAndData.back().key)
			{
				node->vKeysAndData.push_back(NodeOfKeysAndData(key, Data));
			}
			else
			{
				for (int i = 0; i < node->vKeysAndData.size() - 1; i++)
				{
					if (key > node->vKeysAndData[i].key && key <= node->vKeysAndData[i + 1].key)
					{
						it = node->vKeysAndData.begin() + (i + 1);
						node->vKeysAndData.insert(it, NodeOfKeysAndData(key, Data));
						break;
					}
				}
			}

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
	void _LinkLeafNodeTogeither(Node*& Root)
	{
		Queue <Node*> q;

		q.Push(Root);

		Node* curr;
		Node* lastChild = nullptr;

		int i;

		while (!q.IsEmpty())
		{
			curr = q.GetFront();
		
			if (curr->vChildren.empty() == false)
			{
				if (curr->vChildren[0]->isLeaf == true)
				{
					for (i = 0; i < curr->vChildren.size() - 1; i++)
					{
						curr->vChildren[i]->Right = curr->vChildren[i + 1];
					}

					if (lastChild == nullptr)
					{
						lastChild = curr->vChildren.back();
					}
					else
					{
						lastChild->Right = curr->vChildren[0];
						lastChild = curr->vChildren.back();
					}
				}
				else
				{
					for (i = 0; i < curr->vChildren.size(); i++)
					{
						if (curr->vChildren[i] != nullptr)
						{
							q.Push(curr->vChildren[i]);
						}
					}
				}
			}

			q.Pop();
		}

	}

	void _DisPlayUsingLinkRight(Node* Root)
	{
		Root = _FindMin(Root);

		while (Root != nullptr)
		{
			for (int i = 0; i < Root->vKeysAndData.size(); i++)
			{
				cout << Root->vKeysAndData[i].key << " : " << Root->vKeysAndData[i].data << " | ";
			}

			Root = Root->Right;
		}
	}


public:


	BPlusTree_Correct(int Order)
	{
		float m = Order;

		_MaxChildren = m;
		_MinChildren = ceil(m / 2);
		_MaxKeys = m - 1;
		_MinKeys = ceil(m / 2 - 1);

		_Root = nullptr;
		_CountKeys = 0;
	}

	void Insert(K key, T Data)
	{
		if (_MaxChildren <= 2)
		{
			cout << "\n\n The Order must be greater than 2!\n\n";
			return;
		}

		if (IsEmpty())
		{
			_Root = new Node;

			_Root->vKeysAndData.push_back(NodeOfKeysAndData(key, Data));
		}
		else
		{
			_Insert(_Root, key, Data);
			_LinkLeafNodeTogeither(_Root);
		}

		_CountKeys++;
	}

	void Delete(K key)
	{
		if (IsEmpty())
		{
			cout << "\nTree is Empty!\n";
			return;
		}

		_Delete(_Root, key);

		if (_Root != nullptr)
		{
			_LinkLeafNodeTogeither(_Root);
		}
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

	K FindMax()
	{
		if (!IsEmpty())
		{
			return _FindMax(_Root)->vKeysAndData.back().key;
		}
	}

	K FindMin()
	{
		if (!IsEmpty())
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

	void DisPlayUsingLinkRight()
	{
		if (IsEmpty())
		{
			cout << "\nNo key Found!\n";
			return;
		}

		cout << "\n\n";
		_DisPlayUsingLinkRight(_Root);
		cout << "\n\n";
	}

	int Count()
	{
		return _CountKeys;
	}

	bool IsFind(K key)
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
	void Copy(BPlusTree_Correct& CopyBPlusTree_Correct)
	{
		if (!IsEmpty())
		{
			cout << "\nTree Must be Empty!\n";
			return;
		}

		if (CopyBPlusTree_Correct.IsEmpty())
		{
			cout << "\nCopy Tree is Empty!\n";
			return;
		}

		if (CopyBPlusTree_Correct._MaxChildren != _MaxChildren)
		{
			cout << "\nThe Order in two Btree must be the same!\n";
			return;
		}

		_Copy(CopyBPlusTree_Correct._Root);
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

	~BPlusTree_Correct()
	{
		Clear();
	}



};

