#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;


class HuffmanTree
{
private:

	struct Node
	{
		char ch = ' ';
		int count;

		Node* left = nullptr;
		Node* right = nullptr;
	};

	struct LetterAndHisCode
	{
		char letter;
		string code;
	};

	Node* _Root = nullptr;

	vector <LetterAndHisCode> _vLettersAndHisCode;

	map <char, int> _GetRepetitionForEachLetter(string str)
	{
		map <char, int> Letters;

		for (int i = 0; i < str.length(); i++)
		{
			Letters[str[i]]++;
		}

		return Letters;
	}

	struct com
	{
		bool operator () (Node* a, Node* b)
		{
			return a->count > b->count;
		}
	};

	Node* _CreateHuffmanTree(string str)
	{
		map <char, int> letters = _GetRepetitionForEachLetter(str);

		priority_queue <Node*, vector<Node*>, com> pq;

		for (auto pair : letters)
		{
			Node* node = new Node;

			node->ch = pair.first;
			node->count = pair.second;

			pq.push(node);
		}


		while (pq.size() >= 2)
		{
			Node* left = pq.top();
			pq.pop();

			Node* right = pq.top();
			pq.pop();

			Node* parent = new Node;

			parent->count = right->count + left->count;
			parent->left = left;
			parent->right = right;

			pq.push(parent);
		}

		return pq.top();
	}

	void _CreateHuffmanCodeHelper2(Node* node, string code, vector <LetterAndHisCode>& vec)
	{
		if (node->left != nullptr)
		{
			_CreateHuffmanCodeHelper2(node->left, code + "0", vec);
		}

		if (node->right != nullptr)
		{
			_CreateHuffmanCodeHelper2(node->right, code + "1", vec);
		}

		if (node->left == nullptr && node->right == nullptr)
		{
			LetterAndHisCode charAndHisCode;

			charAndHisCode.letter = node->ch;
			charAndHisCode.code = code;

			vec.push_back(charAndHisCode);
		}

	}

	vector <LetterAndHisCode> _CreateHuffmanCodeHelper1(string str)
	{
		_Root = _CreateHuffmanTree(str);

		_CreateHuffmanCodeHelper2(_Root, "", _vLettersAndHisCode);

		return _vLettersAndHisCode;
	}


	struct stNode
	{
		char ch = ' ';

		stNode* left = nullptr;
		stNode* right = nullptr;
	};


	stNode* _DeCompressionHelper()
	{
		stNode* root = new stNode;

		stNode* tmp = root;

		// here we use the vector which stor each letter and his code to create tree again

		for (int i = 0; i < _vLettersAndHisCode.size(); i++)
		{
			for (int j = 0; j < _vLettersAndHisCode[i].code.size(); j++)
			{
				if (_vLettersAndHisCode[i].code[j] == '0')
				{
					if (tmp->left == nullptr)
					{
						tmp->left = new stNode;
						tmp = tmp->left;
					}
					else
					{
						tmp = tmp->left;
					}
				}

				else if (_vLettersAndHisCode[i].code[j] == '1')
				{
					if (tmp->right == nullptr)
					{
						tmp->right = new stNode;
						tmp = tmp->right;
					}
					else
					{
						tmp = tmp->right;
					}
				}
			}

			tmp->ch = _vLettersAndHisCode[i].letter;
			tmp = root;
		}

		return root;
	}
	

public:


	string CreateHuffmanCode(string str)
	{
		vector <LetterAndHisCode> vec = _CreateHuffmanCodeHelper1(str);

		string HuffmanCode = "";

		for (int i = 0; i < str.length(); i++)
		{
			for (int j = 0; j < vec.size(); j++)
			{
				if (str[i] == vec[j].letter)
				{
					HuffmanCode += vec[j].code;
					break;
				}
			}
		}

		return HuffmanCode;
	}

	string DeCompression(string HuffmanCode)
	{
		if (_Root == nullptr && _vLettersAndHisCode.empty())
		{
			cout << "\n\nnot happend any create huffman code!\n\n";
			return "";
		}

		stNode* root = _DeCompressionHelper();

		stNode* tmp = root;

		string str = "";

		for (int i = 0; i < HuffmanCode.length(); i++)
		{
			if (HuffmanCode[i] == '0')
			{
				tmp = tmp->left;
			}

			else if (HuffmanCode[i] == '1')
			{
				tmp = tmp->right;
			}

			if (tmp->left == nullptr && tmp->right == nullptr)
			{
				str += tmp->ch;

				tmp = root;
			}
		}

		return str;
	}



};

