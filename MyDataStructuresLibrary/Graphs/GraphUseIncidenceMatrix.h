#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <stack>


class GraphUseIncidenceMatrix
{
private:

	int _NumberOfVertices;
	int _NumberOfEdges;

	int** _Matrix;


	int* _MatrixForWeights;


	vector <bool> _DeletedVertices;

	void _DepthFirstSearchHelper(int Vertex, vector <bool>& isVisited)
	{
		if (isVisited[Vertex] == false && _DeletedVertices[Vertex] == false)
		{
			cout << "Vertex : " << Vertex << "\n";

			isVisited[Vertex] = true;

			// edges = j
			for (int j = 0; j < _NumberOfEdges; j++)
			{
				if (_Matrix[Vertex][j] == 1)
				{
					// vertices = i
					for (int i = 0; i < _NumberOfVertices; i++)
					{
						if (_DeletedVertices[i] == false && i != Vertex)
						{
							if (_Matrix[i][j] != 0)
							{
								if (isVisited[i] == false)
								{
									_DepthFirstSearchHelper(i, isVisited);
									break;
								}
							}
						}
					}
					
				}
			}
		}
		
	}


public:


	GraphUseIncidenceMatrix(int NumberOfVertices, int NumberOfEdges)
	{
		_NumberOfVertices = NumberOfVertices;
		_NumberOfEdges = NumberOfEdges;

		_DeletedVertices.resize(_NumberOfVertices);

		_Matrix = new int* [_NumberOfVertices];

		int i;
		// حجز مكان في الذاكره لجميع المؤشرات التي تمثل القمم
		for (i = 0; i < _NumberOfVertices; i++)
		{
			_Matrix[i] = new int[_NumberOfEdges];
		}

		// تهيئة جميع الحواف بصفر
		for (i = 0; i < _NumberOfVertices; i++)
		{
			for (int j = 0; j < _NumberOfEdges; j++)
			{
				_Matrix[i][j] = 0;
			}
		}

		_MatrixForWeights = new int[_NumberOfEdges];

		// تهيئة مصفوفة الاوزان بصفار
		for (i = 0; i < _NumberOfEdges; i++)
		{
			_MatrixForWeights[i] = 0;
		}
	}


	void UpdateEdge(int SourceVertex, int DestinationVertex, int Edge, bool isDirectedGraph, int Weight = 0)
	{
		if (SourceVertex >= _NumberOfVertices || DestinationVertex >= _NumberOfVertices || Edge >= _NumberOfEdges || SourceVertex < 0 || DestinationVertex < 0 || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[SourceVertex] == true || _DeletedVertices[DestinationVertex] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		_Matrix[SourceVertex][Edge] = 1;
		_Matrix[DestinationVertex][Edge] = isDirectedGraph == true ? -1 : 1;

		_MatrixForWeights[Edge] = Weight;
	}

	void DeleteEdge(int SourceVertex, int DestinationVertex, int Edge)
	{
		if (SourceVertex >= _NumberOfVertices || DestinationVertex >= _NumberOfVertices || Edge >= _NumberOfEdges || SourceVertex < 0 || DestinationVertex < 0 || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		if (_DeletedVertices[SourceVertex] == true || _DeletedVertices[DestinationVertex] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return;
		}

		_Matrix[SourceVertex][Edge] = 0;
		_Matrix[DestinationVertex][Edge] = 0;
	
		_MatrixForWeights[Edge] = 0;
	}

	bool AreTheseTowVerticesAdjacency(int SourceVertex, int DestinationVertex, int Edge)
	{
		if (SourceVertex >= _NumberOfVertices || DestinationVertex >= _NumberOfVertices || Edge >= _NumberOfEdges || SourceVertex < 0 || DestinationVertex < 0 || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return false;
		}

		if (_DeletedVertices[SourceVertex] == true || _DeletedVertices[DestinationVertex] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return false;
		}

		return _Matrix[SourceVertex][Edge] != 0 && _Matrix[DestinationVertex][Edge] != 0;
	}

	bool IsEdgeIncidenceVertex(int Vertex, int Edge)
	{
		if (Vertex >= _NumberOfVertices || Edge >= _NumberOfEdges || Vertex < 0 || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return false;
		}

		if (_DeletedVertices[Vertex] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return false;
		}

		return _Matrix[Vertex][Edge] != 0;
	}

	bool IsVertexFinalAtEdge(int Vertex, int Edge)
	{
		if (Vertex >= _NumberOfVertices || Edge >= _NumberOfEdges || Vertex < 0 || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return false;
		}

		if (_DeletedVertices[Vertex] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return false;
		}

		return _Matrix[Vertex][Edge] == -1;
	}

	bool IsVertexStartFromEdge(int Vertex, int Edge)
	{
		if (Vertex >= _NumberOfVertices || Edge >= _NumberOfEdges || Vertex < 0 || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return false;
		}

		if (_DeletedVertices[Vertex] == true)
		{
			cout << "\none of these vertices is deleted!\n";
			return false;
		}

		return _Matrix[Vertex][Edge] == 1;
	}

	int GetEdgeWeight(int Edge)
	{
		if (Edge >= _NumberOfEdges || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return 0;
		}

		return _MatrixForWeights[Edge];
	}

	int GetEdgeDirection(int Vertex, int Edge)
	{
		if (Edge >= _NumberOfEdges || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return 0;
		}

		if (_DeletedVertices[Vertex] == true)
		{
			cout << "\nthis vertex is deleted!\n";
			return 0;
		}

		return _Matrix[Vertex][Edge];
	}

	vector <int> GetAllAdjacencyVertices(int Vertex)
	{
		vector <int> vec;

		if (Vertex >= _NumberOfVertices || Vertex < 0)
		{
			cout << "\nOut Of Range!\n";
			return vec;
		}

		if (_DeletedVertices[Vertex] == true)
		{
			cout << "\nvertex with index " << Vertex << " is deleted!\n";
			return vec;
		}

		// i = edges
		for (int i = 0; i < _NumberOfEdges; i++)
		{
			if (_Matrix[Vertex][i] != 0)
			{
				// j = vertices
				for (int j = 0; j < _NumberOfVertices; j++)
				{
					if (_DeletedVertices[j] == false && j != Vertex)
					{
						if (_Matrix[j][i] != 0)
						{
							vec.push_back(j);
						}
					}
				}
			}
		}

		return vec;
	}

	void AddVertex()
	{
		_NumberOfVertices++;

		int** tmp = _Matrix;

		_Matrix = new int* [_NumberOfVertices];

		for (int i = 0; i < _NumberOfVertices - 1; i++)
		{
			_Matrix[i] = tmp[i];
		}

		_Matrix[_NumberOfVertices - 1] = new int[_NumberOfEdges];

		/*for (int i = 0; i < _NumberOfVertices; i++)
		{
			_Matrix[i] = new int[_NumberOfEdges];
		}*/

		//// نسخ العناصر
		//for (int i = 0; i < _NumberOfVertices - 1; i++)
		//{
		//	for (int j = 0; j < _NumberOfEdges; j++)
		//	{
		//		_Matrix[i][j] = tmp[i][j];
		//	}
		//}

		// تهيئة جمع حواف القمه الجديده بصفر
		for (int j = 0; j < _NumberOfEdges; j++)
		{
			_Matrix[_NumberOfVertices - 1][j] = 0;
		}

		//// مسح جميع المؤشرات من المصفوفه القديمه
		//for (int i = 0; i < _NumberOfVertices - 1; i++)
		//{
		//	delete[] tmp[i];
		//}

		// مسح المصفوفه القديمه نفسها
		delete[] tmp;
		tmp = nullptr;

		_DeletedVertices.push_back(false);
	}

	void AddNewEdge()
	{
		_NumberOfEdges++;

		int** tmp = _Matrix;

		_Matrix = new int* [_NumberOfVertices];

		for (int i = 0; i < _NumberOfVertices; i++)
		{
			_Matrix[i] = new int[_NumberOfEdges];
		}

		// نسخ العناصر
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			for (int j = 0; j < _NumberOfEdges - 1; j++)
			{
				_Matrix[i][j] = tmp[i][j];
			}

			// تهيئة الحافه الجديده الاخيره بصفر في كل رأس
			_Matrix[i][_NumberOfEdges - 1] = 0;
		}

		// مسح جميع المؤشرات من المصفوفه القديمه
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			delete[] tmp[i];
		}

		// مسح المصفوفه القديمه نفسها
		delete[] tmp;
		tmp = nullptr;


		int* tmpMatrixForWeights = _MatrixForWeights;

		_MatrixForWeights = new int[_NumberOfEdges];

		for (int i = 0; i < _NumberOfEdges - 1; i++)
		{
			_MatrixForWeights[i] = tmpMatrixForWeights[i];
		}

		_MatrixForWeights[_NumberOfEdges - 1] = 0;

		delete[] tmpMatrixForWeights;
		tmpMatrixForWeights = nullptr;
	}

	void DeleteEdge(int Edge)
	{
		if (Edge >= _NumberOfEdges || Edge < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}


		for (int i = 0; i < _NumberOfVertices; i++)
		{
			_Matrix[i][Edge] = 0;
		}

		_MatrixForWeights[Edge] = 0;
	}

	void DeleteVertex(int Vertex)
	{
		if (Vertex >= _NumberOfVertices || Vertex < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		_DeletedVertices[Vertex] = true;


		for (int i = 0; i < _NumberOfEdges; i++)
		{
			if (_Matrix[Vertex][i] != 0)
			{
				DeleteEdge(i);
			}
		}
	}

	void Clear()
	{
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			for (int j = 0; j < _NumberOfEdges; j++)
			{
				_Matrix[i][j] = 0;
			}
		}

		for (int j = 0; j < _NumberOfEdges; j++)
		{
			_MatrixForWeights[j] = 0;
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
				continue;

			cout << "Edges Vertex number : " << i << "\n\n{  ";
			for (int j = 0; j < _NumberOfEdges; j++)
			{
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

			// edges = j
			for (int j = 0; j < _NumberOfEdges; j++)
			{
				if (_Matrix[Vertex][j] == 1)
				{
					// vertices = i
					for (int i = 0; i < _NumberOfVertices; i++)
					{
						if (_DeletedVertices[i] == false && i != Vertex)
						{
							if (_Matrix[i][j] != 0)
							{
								if (isVisited[i] == false)
								{
									q.push(i);
									isVisited[i] = true;
									break;
								}
							}
						}
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

		int j;
		for (j = 0; j < _NumberOfVertices; j++)
		{
			if (_DeletedVertices[j] == false)
			{
				s.push(j);
				isVisited[j] = true;
				break;
			}
		}

		while (!s.empty())
		{
			int Vertex = s.top();

			cout << "Vertex : " << Vertex << "\n";

			s.pop();

			// edges = j
			for (j = 0; j < _NumberOfEdges; j++)
			{
				if (_Matrix[Vertex][j] == 1)
				{
					// vertices = i
					for (int i = 0; i < _NumberOfVertices; i++)
					{
						if (_DeletedVertices[i] == false && i != Vertex)
						{
							if (_Matrix[i][j] != 0)
							{
								if (isVisited[i] == false)
								{
									s.push(i);
									isVisited[i] = true;
									break;
								}
							}
						}
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

	public:

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
					// i = Edges
					for (int i = 0; i < _NumberOfEdges; i++)
					{
						if (_Matrix[CurrentVertex.Vertex][i] == 1)
						{
							// j = Vertices
							for (int j = 0; j < _NumberOfVertices; j++)
							{
								if (_Matrix[j][i] != 0 && j != CurrentVertex.Vertex && isVisited[j] == false)
								{
									int weight = _MatrixForWeights[i];

									int sum = CurrentVertex.Weight + weight;

									if (sum < _vWeights[j])
									{
										weight = sum;
										_vWeights[j] = sum;
										_vParints[j] = CurrentVertex.Vertex;

										pq.push(WeightedGraph(j, weight));
									}

									break;
								}
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

			DijkstraAlgorithm(Vertex1, Vertex2);

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

			DijkstraAlgorithm(Vertex1, Vertex2);

			return _vWeights[Vertex2];
		}


		// ================================================================================================


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
			int e = 0;
			int x = 0;

			for (int j = 0; j < _NumberOfVertices - 1; j++)
			{
				int CurrentVertex = Vertex;

				bool HaveWeightsChanged = false;

				// هذه التكرار يضمن ان كل الرؤوس سوف يتم المرور عليها
				for (v = 0; v < _NumberOfVertices; v++)
				{
					// i = edges
					for (e = 0; e < _NumberOfEdges; e++)
					{
						if (_Matrix[CurrentVertex][e] == 1)
						{
							// x = adjancency vertices
							for (x = 0; x < _NumberOfVertices; x++)
							{
								if (_Matrix[x][e] != 0 && x != CurrentVertex)
								{
									weight = _MatrixForWeights[e];

									sum = _vWeights[CurrentVertex] + weight;

									if (sum < _vWeights[x])
									{
										_vWeights[x] = sum;
										_vParints[x] = CurrentVertex;

										HaveWeightsChanged = true;
									}
									break;
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
				// e = edges
				for (e = 0; e < _NumberOfEdges; e++)
				{
					if (_Matrix[v][e] == 1)
					{
						// x = adjancency vertices
						for (x = 0; x < _NumberOfVertices; x++)
						{
							if (_Matrix[x][e] != 0 && x != v)
							{
								weight = _MatrixForWeights[e];

								sum = _vWeights[v] + weight;

								if (sum < _vWeights[x])
								{
									_vWeights.clear();
									_vParints.clear();

									cout << "\n\nBellman Algorithm Can not Find Shortest Path To This Graph!\n\n";
									return;
								}

								break;
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

			BellmanFordAlgorithm(Vertex1);
			
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

			BellmanFordAlgorithm(Vertex1);

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



		~GraphUseIncidenceMatrix()
		{
			// مسح جميع المؤشرات من المصفوفه القديمه
			for (int i = 0; i < _NumberOfVertices; i++)
			{
				delete[] _Matrix[i];
			}

			// مسح المصفوفه القديمه نفسها
			delete[] _Matrix;
			_Matrix = nullptr;

			delete[] _MatrixForWeights;
			_MatrixForWeights = nullptr;

			_DeletedVertices.clear();
		}



};

