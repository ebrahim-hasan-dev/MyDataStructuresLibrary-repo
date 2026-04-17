#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <stack>


class GraphUseAdjacencyMatrix
{
private:

	int _NumberOfVertices;

	int** _Matrix;

	// this vector -> ( _MatrixPseudoWeightedGraph ) special for -> ( pseudo weighted graph ) which mean graph have parallel edges and,
	// loop and have -> ( weights are important )

	vector<vector<vector<int>>> _MatrixPseudoWeightedGraph;

	vector <bool> _DeletedVertices;

	void _DepthFirstSearchHelper(int Vertex, vector <bool>& isVisited)
	{
		if (isVisited[Vertex] == false && _DeletedVertices[Vertex] == false)
		{
			cout << "Vertex : " << Vertex << "\n";

			isVisited[Vertex] = true;

			for (int i = 0; i < _NumberOfVertices; i++)
			{
				if (_Matrix[Vertex][i] != 0)
				{
					_DepthFirstSearchHelper(i, isVisited);
				}
			}
		}

	}

	void _DepthFirstSearchPseudoWeightedGraphHelper(int Vertex, vector <bool>& isVisited)
	{
		if (isVisited[Vertex] == false && _DeletedVertices[Vertex] == false)
		{
			cout << "Vertex : " << Vertex << "\n";

			isVisited[Vertex] = true;

			for (int i = 0; i < _NumberOfVertices; i++)
			{
				if (_MatrixPseudoWeightedGraph[Vertex][i].empty() == false)
				{
					_DepthFirstSearchPseudoWeightedGraphHelper(i, isVisited);
				}
			}
		}

	}


public:


	GraphUseAdjacencyMatrix(int NumberOfVertices)
	{
		_NumberOfVertices = NumberOfVertices;

		_DeletedVertices.resize(_NumberOfVertices);

		// ========================================

		// this vector -> ( _MatrixPseudoWeightedGraph ) special for -> ( pseudo weighted graph ) which mean graph have parallel edges and,
		// loop and have -> ( weights are important )

		_MatrixPseudoWeightedGraph.resize(_NumberOfVertices, vector<vector<int>>(_NumberOfVertices));

		// ========================================
	
		_Matrix = new int* [_NumberOfVertices];

		// حجز مكان في الذاكره لجميع المؤشرات التي تمثل القمم
		int i;
		for (i = 0; i < _NumberOfVertices; i++)
		{
			_Matrix[i] = new int[_NumberOfVertices];
		}

		// تهيئة جميع الحواف بصفر
		for (i = 0; i < _NumberOfVertices; i++)
		{
			for (int j = 0; j < _NumberOfVertices; j++)
			{
				_Matrix[i][j] = 0;
			}
		}

	}


	// =========================================================================================================


	void AddEdgeInPseudoWeightedUndirectedGraph(int indexV1, int indexV2, int weight)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		if (indexV1 == indexV2)
		{
			_MatrixPseudoWeightedGraph[indexV1][indexV2].push_back(weight);
		}
		else
		{
			_MatrixPseudoWeightedGraph[indexV1][indexV2].push_back(weight);
			_MatrixPseudoWeightedGraph[indexV2][indexV1].push_back(weight);
		}
	}

	void DeleteEdgeInPseudoWeightedUndirectedGraph(int indexV1, int indexV2, int weight)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		vector <int>::iterator it;

		int i;
		for (i = 0; i < _MatrixPseudoWeightedGraph[indexV1][indexV2].size(); i++)
		{
			if (_MatrixPseudoWeightedGraph[indexV1][indexV2][i] == weight)
			{
				it = _MatrixPseudoWeightedGraph[indexV1][indexV2].begin() + i;
				_MatrixPseudoWeightedGraph[indexV1][indexV2].erase(it);
				break;
			}
		}

		if (indexV1 != indexV2)
		{
			for (i = 0; i < _MatrixPseudoWeightedGraph[indexV2][indexV1].size(); i++)
			{
				if (_MatrixPseudoWeightedGraph[indexV2][indexV1][i] == weight)
				{
					it = _MatrixPseudoWeightedGraph[indexV2][indexV1].begin() + i;
					_MatrixPseudoWeightedGraph[indexV2][indexV1].erase(it);
					return;
				}
			}
		}
		
	}

	void AddEdgeInPseudoWeightedDirectedGraph(int indexV1, int indexV2, int weight)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		_MatrixPseudoWeightedGraph[indexV1][indexV2].push_back(weight);
	}

	void DeleteEdgeInPseudoWeightedDirectedGraph(int indexV1, int indexV2, int weight)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		for (int i = 0; i < _MatrixPseudoWeightedGraph[indexV1][indexV2].size(); i++)
		{
			if (_MatrixPseudoWeightedGraph[indexV1][indexV2][i] == weight)
			{
				vector <int>::iterator it = _MatrixPseudoWeightedGraph[indexV1][indexV2].begin() + i;
				_MatrixPseudoWeightedGraph[indexV1][indexV2].erase(it);
				return;
			}
		}
	}

	bool AreTheseTowVerticesAdjacencyPseudoWeightedGraph(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return false;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return false;
		}

		return _MatrixPseudoWeightedGraph[indexV1][indexV2].empty() == false || _MatrixPseudoWeightedGraph[indexV2][indexV1].empty() == false;
	}

	vector <int> GetAllWeightsBetweenTowVerticesPseudoWeightedGraph(int indexV1, int indexV2)
	{
		vector <int> vec;

		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return vec;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\nno weights between these tow vertices,\nbecause one of these vertices is deleted!\n";
			return vec;
		}

		// here we no need to check if vetor empty or not
		return _MatrixPseudoWeightedGraph[indexV1][indexV2];
	}

	vector <int> GetAllAdjacencyVerticesPseudoWeightedGraph(int indexV)
	{
		vector <int> vec;

		if (indexV >= _NumberOfVertices || indexV < 0)
		{
			cout << "\nOut Of Range!\n";
			return vec;
		}

		if (_DeletedVertices[indexV] == true)
		{
			cout << "\nvertex with index " << indexV << " is deleted!\n";
			return vec;
		}

		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == true)
			{
				continue;
			}

			if (_MatrixPseudoWeightedGraph[indexV][i].empty())
			{
				vec.push_back(0);
			}
			else
			{
				vec.push_back(1);
			}
		}

		return vec;
	}

	void AddVertexPseudoWeightedGraph()
	{
		_NumberOfVertices++;

		// here we are reserve a space in mamory to first vector only
		// second vector must be empty 
		vector<vector<int>> tmp1(_NumberOfVertices);

		_MatrixPseudoWeightedGraph.push_back(tmp1);

		vector<int> tmp2;

		// here we need add vector in every second vector
		for (int i = 0; i < _NumberOfVertices - 1; i++)
		{
			_MatrixPseudoWeightedGraph[i].push_back(tmp2);
		}

		_DeletedVertices.push_back(false);
	}

	void ClearPseudoWeightedGraph()
	{
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			for (int j = 0; j < _NumberOfVertices; j++)
			{
				_MatrixPseudoWeightedGraph[i][j].clear();
			}
		}

		_DeletedVertices.clear();
		_DeletedVertices.resize(_NumberOfVertices);
	}

	void DisplayPseudoWeightedGraph()
	{
		cout << "\n";
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == true)
			{
				continue;
			}

			cout << "Vertex number : " << i << "\n\n";
			for (int j = 0; j < _NumberOfVertices; j++)
			{
				if (_DeletedVertices[j] == true)
				{
					continue;
				}

				cout << "Vertex Adjacency Weights number " << j << " {  ";
				for (int c = 0; c < _MatrixPseudoWeightedGraph[i][j].size(); c++)
				{
					cout << _MatrixPseudoWeightedGraph[i][j][c] << " ";
				}
				cout << " }\n";
			}
			cout << "\n";
		}
		cout << "\n";
	}

	void BreadthFirstSearchPseudoWeightedGraph()
	{
		vector <bool> isVisited(_NumberOfVertices);

		queue <int> q;

		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == false)
			{
				q.push(i);
				isVisited[i] = true;
				break;
			}
		}

		while (!q.empty())
		{
			int Vertex = q.front();

			cout << "Vertex : " << Vertex << "\n";

			for (int j = 0; j < _NumberOfVertices; j++)
			{
				if (_MatrixPseudoWeightedGraph[Vertex][j].empty() == false)
				{
					if (isVisited[j] == false && _DeletedVertices[j] == false)
					{
						q.push(j);
						isVisited[j] = true;
					}
				}
			}

			q.pop();
		}

	}

	void DepthFirstSearchPseudoWeightedGraph()
	{
		vector <bool> isVisited(_NumberOfVertices);

		int i;
		for (i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == false)
			{
				break;
			}
		}

		_DepthFirstSearchPseudoWeightedGraphHelper(i, isVisited);
	}

	void DepthFirstSearchPseudoWeightedGraph2()
	{
		vector <bool> isVisited(_NumberOfVertices);

		stack <int> s;

		int i;
		for (i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == false)
			{
				s.push(i);
				isVisited[i] = true;
				break;
			}
		}

		while (!s.empty())
		{
			int Vertex = s.top();

			cout << "Vertex : " << Vertex << "\n";

			s.pop();

			for (i = 0; i < _NumberOfVertices; i++)
			{
				if (_MatrixPseudoWeightedGraph[Vertex][i].empty() == false)
				{
					if (isVisited[i] == false && _DeletedVertices[i] == false)
					{
						s.push(i);
						isVisited[i] = true;
					}
				}
			}
		}

	}


	// =========================================================================================================


	void AddEdgeInUndirectedGraph(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		_Matrix[indexV1][indexV2]++;
		_Matrix[indexV2][indexV1]++;
	}

	void AddEdgeInDirectedGraph(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		_Matrix[indexV1][indexV2]++;
	}

	void AddEdgeInWeightedUndirectedGraph(int indexV1, int indexV2, int Weight)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		// this condetion special for loop mean edge out from vertex and inside in same vertex
		if (indexV1 == indexV2)
		{
			_Matrix[indexV1][indexV2] = Weight;
		}
		else
		{
			_Matrix[indexV1][indexV2] = Weight;
			_Matrix[indexV2][indexV1] = Weight;
		}
	}

	void AddEdgeInWeightedDirectedGraph(int indexV1, int indexV2, int Weight)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		_Matrix[indexV1][indexV2] = Weight;
	}

	void DeleteEdgeInWeightedUndirectedGraph(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		if (indexV1 == indexV2)
		{
			_Matrix[indexV1][indexV2] = 0;
		}
		else
		{
			_Matrix[indexV1][indexV2] = 0;
			_Matrix[indexV2][indexV1] = 0;
		}
	}

	void DeleteEdgeInWeightedDirectedGraph(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		_Matrix[indexV1][indexV2] = 0;
	}

	void DeleteEdgeInUndirectedGraph(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		if (_Matrix[indexV1][indexV2] > 0)
		{
			_Matrix[indexV1][indexV2]--;
			_Matrix[indexV2][indexV1]--;
		}
	}

	void DeleteEdgeInDirectedGraph(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		if (_Matrix[indexV1][indexV2] > 0)
		{
			_Matrix[indexV1][indexV2]--;
		}
	}

	bool AreTheseTowVerticesAdjacency(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return false;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return false;
		}

		return _Matrix[indexV1][indexV2] != 0 || _Matrix[indexV2][indexV1] != 0;
	}

	int GetWeightBetweenTowVertices(int indexV1, int indexV2)
	{
		if (indexV1 >= _NumberOfVertices || indexV2 >= _NumberOfVertices || indexV1 < 0 || indexV2 < 0)
		{
			cout << "\nOut Of Range!\n";
			return 0;
		}

		if (_DeletedVertices[indexV1] == true || _DeletedVertices[indexV2] == true)
		{
			cout << "\nno weight between these tow vertices,\nbecause one of these vertices is deleted!\n";
			return 0;
		}

		return _Matrix[indexV1][indexV2];
	}

	vector <int> GetAllAdjacencyVertices(int indexV)
	{
		vector <int> vec;

		if (indexV >= _NumberOfVertices || indexV < 0)
		{
			cout << "\nOut Of Range!\n";
			return vec;
		}

		if (_DeletedVertices[indexV] == true)
		{
			cout << "\nvertex with index " << indexV << " is deleted!\n";
			return vec;
		}

		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == true)
			{
				continue;
			}

			vec.push_back(_Matrix[indexV][i]);
		}

		return vec;
	}

	void AddVertex()
	{
		_NumberOfVertices++;
		
		int** tmp = _Matrix;

		_Matrix = new int* [_NumberOfVertices];

		int i;
		for (i = 0; i < _NumberOfVertices; i++)
		{
			_Matrix[i] = new int[_NumberOfVertices];
		}

		int j;

		// نسخ العناصر
		for (i = 0; i < _NumberOfVertices - 1; i++)
		{
			for (j = 0; j < _NumberOfVertices - 1; j++)
			{
				_Matrix[i][j] = tmp[i][j];
			}

			// تهيئة اخر حافه في كل قمه بصفر
			_Matrix[i][_NumberOfVertices - 1] = 0;
		}

		// تهيئة جمع حواف القمه الجديده بصفر
		for (j = 0; j < _NumberOfVertices; j++)
		{
			_Matrix[_NumberOfVertices - 1][j] = 0;
		}

		// مسح جميع المؤشرات من المصفوفه القديمه
		for (i = 0; i < _NumberOfVertices - 1; i++)
		{
			delete[] tmp[i];
		}

		// مسح المصفوفه القديمه نفسها
		delete[] tmp;
		tmp = nullptr;

		_DeletedVertices.push_back(false);
	}

	void DeleteVertex(int indexV)
	{
		if (indexV >= _NumberOfVertices || indexV < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		_DeletedVertices[indexV] = true;

		// ===============================================

		// المسح بهذه الطريقه يتطلب تعديل هياكل البيانات الاخري التي تعتمد علي فهارس القمم وتعديل ايضا الخوارزميات التي تعتمد علي الفهارس

		/*int** tmp_Matrix = new int* [_NumberOfVertices - 1];

		int i;
		for (i = 0; i < _NumberOfVertices - 1; i++)
		{
			tmp_Matrix[i] = new int[_NumberOfVertices - 1];
		}

		int x = 0;
		int c = 0;

		for (i = 0; i < _NumberOfVertices; i++)
		{
			if (i == indexV)
				continue;

			for (int j = 0; j < _NumberOfVertices; j++)
			{
				if (j == indexV)
					continue;

				tmp_Matrix[x][c] = _Matrix[i][j];
				c++;
			}

			x++;
			c = 0;
		}

		for (i = 0; i < _NumberOfVertices; i++)
		{
			delete[] _Matrix[i];
		}

		delete[] _Matrix;
		
		_Matrix = tmp_Matrix;
		_NumberOfVertices--;*/

		// ==================================================

	}

	void Clear()
	{
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			for (int j = 0; j < _NumberOfVertices; j++)
			{
				_Matrix[i][j] = 0;
			}
		}

		_DeletedVertices.clear();
		_DeletedVertices.resize(_NumberOfVertices);
	}

	void Display()
	{
		cout << "\n";
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == true)
			{
				continue;
			}

			cout << "Vertex number : " << i << "\n\n{  ";
			for (int j = 0; j < _NumberOfVertices; j++)
			{
				if (_DeletedVertices[j] == true)
				{
					continue;
				}

				cout << _Matrix[i][j] << " ";
			}
			cout << " }\n\n";
		}
		cout << "\n";
	}

	void BreadthFirstSearch()
	{
		vector <bool> isVisited(_NumberOfVertices);

		queue <int> q;

		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == false)
			{
				q.push(i);
				isVisited[i] = true;
				break;
			}
		}

		while (!q.empty())
		{
			int Vertex = q.front();

			cout << "Vertex : " << Vertex << "\n";

			for (int j = 0; j < _NumberOfVertices; j++)
			{
				if (_Matrix[Vertex][j] != 0)
				{
					if (isVisited[j] == false && _DeletedVertices[j] == false)
					{
						q.push(j);
						isVisited[j] = true;
					}
				}
			}

			q.pop();
		}

	}

	void DepthFirstSearch()
	{
		vector <bool> isVisited(_NumberOfVertices);

		int i;
		for (i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == false)
			{
				break;
			}
		}

		_DepthFirstSearchHelper(i, isVisited);
	}

	void DepthFirstSearch2()
	{
		vector <bool> isVisited(_NumberOfVertices);

		stack <int> s;

		int i;
		for (i = 0; i < _NumberOfVertices; i++)
		{
			if (_DeletedVertices[i] == false)
			{
				s.push(i);
				isVisited[i] = true;
				break;
			}
		}

		while (!s.empty())
		{
			int Vertex = s.top();

			cout << "Vertex : " << Vertex << "\n";

			s.pop();

			for (i = 0; i < _NumberOfVertices; i++)
			{
				if (_Matrix[Vertex][i] != 0)
				{
					if (isVisited[i] == false && _DeletedVertices[i] == false)
					{
						s.push(i);
						isVisited[i] = true;
					}
				}
			}
		}

	}

	private:

		struct WeightedGraph
		{
			int Vertex;

			int Weight;

			WeightedGraph(int indexAdVertex, int weight)
			{
				Vertex = indexAdVertex;
				Weight = weight;
			}
		};

		struct stCompare
		{
			bool operator () (WeightedGraph a, WeightedGraph b)
			{
				return a.Weight > b.Weight;
			}
		};

		vector <int> _vWeights;
		vector <int> _vParints;

		bool _isPseudoWeightedGraph = false;

	public:

		void DijkstraAlgorithmPseudoWeightedGraph(int Vertex, int Vertex2 = -1)
		{
			if (Vertex >= _NumberOfVertices || Vertex2 >= _NumberOfVertices || Vertex < 0)
			{
				cout << "\nOut Of Range!\n";
				return;
			}

			_isPseudoWeightedGraph = true;

			_vWeights.clear();
			_vParints.clear();

			_vWeights.resize(_NumberOfVertices, 2147483647);
			_vParints.resize(_NumberOfVertices);

			vector <bool> isVisited(_NumberOfVertices);

			priority_queue <WeightedGraph, vector <WeightedGraph>, stCompare> pq;

			pq.push(WeightedGraph(Vertex, 0));

			_vWeights[Vertex] = 0;

			while (!pq.empty())
			{
				WeightedGraph CurrentVertex = pq.top();

				if (Vertex2 == CurrentVertex.Vertex)
				{
					return;
				}

				pq.pop();

				if (isVisited[CurrentVertex.Vertex] == false)
				{
					// i = vertices
					for (int i = 0; i < _NumberOfVertices; i++)
					{
						if (_MatrixPseudoWeightedGraph[CurrentVertex.Vertex][i].empty() == false && isVisited[i] == false)
						{
							// j = weights
							for (int j = 0; j < _MatrixPseudoWeightedGraph[CurrentVertex.Vertex][i].size(); j++)
							{
								int weight = _MatrixPseudoWeightedGraph[CurrentVertex.Vertex][i][j];

								int sum = CurrentVertex.Weight + weight;

								if (sum < _vWeights[i])
								{
									weight = sum;
									_vWeights[i] = sum;
									_vParints[i] = CurrentVertex.Vertex;

									pq.push(WeightedGraph(i, weight));
								}
							}
						}
					}

					isVisited[CurrentVertex.Vertex] = true;
				}
			}

		}

		void DijkstraAlgorithm(int Vertex, int Vertex2 = -1)
		{
			if (Vertex >= _NumberOfVertices || Vertex2 >= _NumberOfVertices || Vertex < 0)
			{
				cout << "\nOut Of Range!\n";
				return;
			}

			_vWeights.clear();
			_vParints.clear();

			_vWeights.resize(_NumberOfVertices, 2147483647);
			_vParints.resize(_NumberOfVertices);

			vector <bool> isVisited(_NumberOfVertices);

			priority_queue <WeightedGraph, vector <WeightedGraph>, stCompare> pq;

			pq.push(WeightedGraph(Vertex, 0));

			_vWeights[Vertex] = 0;

			while (!pq.empty())
			{
				WeightedGraph CurrentVertex = pq.top();

				if (Vertex2 == CurrentVertex.Vertex)
				{
					return;
				}

				pq.pop();

				if (isVisited[CurrentVertex.Vertex] == false)
				{
					for (int i = 0; i < _NumberOfVertices; i++)
					{
						if (_Matrix[CurrentVertex.Vertex][i] != 0 && isVisited[i] == false)
						{
							int weight = _Matrix[CurrentVertex.Vertex][i];

							int sum = CurrentVertex.Weight + weight;

							if (sum < _vWeights[i])
							{
								weight = sum;
								_vWeights[i] = sum;
								_vParints[i] = CurrentVertex.Vertex;

								pq.push(WeightedGraph(i, weight));
							}
						}
					}

					isVisited[CurrentVertex.Vertex] = true;
				}
			}

		}

		vector <int> GetWeightsAfterDijkstraAlgorithmWorkedOrAfterBellmanFordAlgorithm()
		{
			return _vWeights;
		}

		vector <int> GetParintsToEveryVertexAfterDijkstraAlgorithmWorkedOrAfterBellmanFordAlgorithm()
		{
			return _vParints;
		}

		vector <int> GetShortestPathBetweenTwoVerticesDijkstraAlgorithm(int Vertex1, int Vertex2)
		{
			vector <int> vec;

			if (Vertex1 >= _NumberOfVertices || Vertex2 >= _NumberOfVertices || Vertex1 < 0 || Vertex2 < 0)
			{
				cout << "\nOut Of Range!\n";
				return vec;
			}

			if (_isPseudoWeightedGraph == true)
			{
				DijkstraAlgorithmPseudoWeightedGraph(Vertex1, Vertex2);
			}
			else
			{
				DijkstraAlgorithm(Vertex1, Vertex2);
			}

			if (_vWeights[Vertex2] != 2147483647 && Vertex1 != Vertex2)
			{
				vec.push_back(Vertex2);

				int i = _NumberOfVertices;

				while (_vParints[Vertex2] != Vertex1 && i != 0)
				{
					Vertex2 = _vParints[Vertex2];
					vec.push_back(Vertex2);
					i--;
				}

				vec.push_back(Vertex1);
			}

			return vec;
		}

		int GetLowestCostBetweenTwoVerticesDijkstraAlgorithm(int Vertex1, int Vertex2)
		{
			if (Vertex1 >= _NumberOfVertices || Vertex2 >= _NumberOfVertices || Vertex1 < 0 || Vertex2 < 0)
			{
				cout << "\nOut Of Range!\n";
				return 0;
			}

			if (_isPseudoWeightedGraph == true)
			{
				DijkstraAlgorithmPseudoWeightedGraph(Vertex1, Vertex2);
			}
			else
			{
				DijkstraAlgorithm(Vertex1, Vertex2);
			}


			return _vWeights[Vertex2];
		}


		// =====================================================================================


		void BellmanFordAlgorithm(int Vertex)
		{
			if (Vertex >= _NumberOfVertices || Vertex < 0)
			{
				cout << "\nOut Of Range!\n";
				return;
			}

			_vWeights.clear();
			_vParints.clear();

			_vWeights.resize(_NumberOfVertices, 2147483647);
			_vParints.resize(_NumberOfVertices);

			_vWeights[Vertex] = 0;

			int weight = 0;
			long long int sum = 0;
			int v = 0;
			int i = 0;

			for (int j = 0; j < _NumberOfVertices - 1; j++)
			{
				int CurrentVertex = Vertex;

				bool HaveWeightsChanged = false;

				// هذه التكرار يضمن ان كل الرؤوس سوف يتم المرور عليها
				for (v = 0; v < _NumberOfVertices; v++)
				{
					for (i = 0; i < _NumberOfVertices; i++)
					{
						if (_Matrix[CurrentVertex][i] != 0)
						{
							weight = _Matrix[CurrentVertex][i];

							sum = _vWeights[CurrentVertex] + weight;

							if (sum < _vWeights[i])
							{
								_vWeights[i] = sum;
								_vParints[i] = CurrentVertex;

								HaveWeightsChanged = true;
							}
						}
					}

					CurrentVertex = (CurrentVertex + 1) % _NumberOfVertices;
				}

				if (HaveWeightsChanged == false)
				{
					return;
				}
			}

			for (v = 0; v < _NumberOfVertices; v++)
			{
				for (i = 0; i < _NumberOfVertices; i++)
				{
					if (_Matrix[v][i] != 0)
					{
						weight = _Matrix[v][i];

						sum = _vWeights[v] + weight;

						if (sum < _vWeights[i])
						{
							_vWeights.clear();
							_vParints.clear();

							cout << "\n\nBellman Algorithm Can not Find Shortest Path To This Graph!\n\n";
							return;
						}
					}
				}
			}

		}

		void BellmanFordAlgorithmPseudoWeightedGraph(int Vertex)
		{
			if (Vertex >= _NumberOfVertices || Vertex < 0)
			{
				cout << "\nOut Of Range!\n";
				return;
			}

			_isPseudoWeightedGraph = true;

			_vWeights.clear();
			_vParints.clear();

			_vWeights.resize(_NumberOfVertices, 2147483647);
			_vParints.resize(_NumberOfVertices);

			_vWeights[Vertex] = 0;

			int weight = 0;
			long long int sum = 0;
			int v = 0;
			int i = 0;
			int j = 0;

			for (int c = 0; c < _NumberOfVertices - 1; c++)
			{
				int CurrentVertex = Vertex;

				bool HaveWeightsChanged = false;

				// هذه التكرار يضمن ان كل الرؤوس سوف يتم المرور عليها
				for (v = 0; v < _NumberOfVertices; v++)
				{
					// i = vertices adjacence
					for (i = 0; i < _NumberOfVertices; i++)
					{
						if (_MatrixPseudoWeightedGraph[CurrentVertex][i].empty() == false)
						{
							// j = weights
							for (j = 0; j < _MatrixPseudoWeightedGraph[CurrentVertex][i].size(); j++)
							{
								weight = _MatrixPseudoWeightedGraph[CurrentVertex][i][j];

								sum = _vWeights[CurrentVertex] + weight;

								if (sum < _vWeights[i])
								{
									_vWeights[i] = sum;
									_vParints[i] = CurrentVertex;

									HaveWeightsChanged = true;
								}
							}
						}
					}

					CurrentVertex = (CurrentVertex + 1) % _NumberOfVertices;
				}

				if (HaveWeightsChanged == false)
				{
					return;
				}
			}

			for (v = 0; v < _NumberOfVertices; v++)
			{
				for (i = 0; i < _NumberOfVertices; i++)
				{
					if (_MatrixPseudoWeightedGraph[v][i].empty() == false)
					{
						// j = weights
						for (j = 0; j < _MatrixPseudoWeightedGraph[v][i].size(); j++)
						{
							weight = _MatrixPseudoWeightedGraph[v][i][j];

							sum = _vWeights[v] + weight;

							if (sum < _vWeights[i])
							{
								_vWeights.clear();
								_vParints.clear();

								cout << "\n\nBellman Algorithm Can not Find Shortest Path To This Graph!\n\n";
								return;
							}
						}
					}
				}
			}

		}

		vector <int> GetShortestPathBetweenTwoVerticesBellmanFordAlgorithm(int Vertex1, int Vertex2)
		{
			vector <int> vec;

			if (Vertex1 >= _NumberOfVertices || Vertex2 >= _NumberOfVertices || Vertex1 < 0 || Vertex2 < 0)
			{
				cout << "\nOut Of Range!\n";
				return vec;
			}

			if (_isPseudoWeightedGraph == true)
			{
				BellmanFordAlgorithmPseudoWeightedGraph(Vertex1);
			}
			else
			{
				BellmanFordAlgorithm(Vertex1);
			}

			if (_vWeights.empty() == false && _vWeights[Vertex2] != 2147483647 && Vertex1 != Vertex2)
			{
				vec.push_back(Vertex2);

				int i = _NumberOfVertices;

				while (_vParints[Vertex2] != Vertex1 && i != 0)
				{
					Vertex2 = _vParints[Vertex2];
					vec.push_back(Vertex2);
					i--;
				}

				vec.push_back(Vertex1);
			}

			return vec;
		}

		int GetLowestCostBetweenTwoVerticesBellmanFordAlgorithm(int Vertex1, int Vertex2)
		{
			if (Vertex1 >= _NumberOfVertices || Vertex2 >= _NumberOfVertices || Vertex1 < 0 || Vertex2 < 0)
			{
				cout << "\nOut Of Range!\n";
				return 0;
			}

			if (_isPseudoWeightedGraph == true)
			{
				BellmanFordAlgorithmPseudoWeightedGraph(Vertex1);
			}
			else
			{
				BellmanFordAlgorithm(Vertex1);
			}

			// this condition because negative cycle is happend this vector -> _vWeights will be empty 
			if (_vWeights.empty() == false)
			{
				return _vWeights[Vertex2];
			}
			else
			{
				return 0;
			}
		}



		~GraphUseAdjacencyMatrix()
		{
			// مسح جميع المؤشرات من المصفوفه القديمه
			for (int i = 0; i < _NumberOfVertices; i++)
			{
				delete[] _Matrix[i];
			}

			// مسح المصفوفه القديمه نفسها
			delete[] _Matrix;
			_Matrix = nullptr;

			_DeletedVertices.clear();
		}




};

