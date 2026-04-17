#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <stack>



class GraphUseAdjacencyList
{
private:

	// this struct special for -> ( weighted graph )
	struct WeightedGraph
	{
		int indexAdjacencyVertex;

		int Weight;

		WeightedGraph(int indexAdVertex, int weight)
		{
			indexAdjacencyVertex = indexAdVertex;
			Weight = weight;
		}
	};


	int _NumberOfVertices;

	vector <vector <int>> _List;

	vector <vector <WeightedGraph>> _ListWeightedGraph;

	vector <bool> _DeletedVertices;


	void _DepthFirstSearchHelper(int Vertex, vector <bool>& isVisited)
	{
		if (isVisited[Vertex] == false && _DeletedVertices[Vertex] == false)
		{
			cout << "Vertex : " << Vertex << "\n";

			isVisited[Vertex] = true;

			if (_List[Vertex].size() > 0)
			{
				int indexFirstVertex = 0;

				_DepthFirstSearchHelper(_List[Vertex][indexFirstVertex], isVisited);

				while (indexFirstVertex < _List[Vertex].size() - 1)
				{
					indexFirstVertex++;
					_DepthFirstSearchHelper(_List[Vertex][indexFirstVertex], isVisited);
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

			if (_ListWeightedGraph[Vertex].size() > 0)
			{
				int indexFirstVertex = 0;

				_DepthFirstSearchPseudoWeightedGraphHelper(_ListWeightedGraph[Vertex][indexFirstVertex].indexAdjacencyVertex, isVisited);

				while (indexFirstVertex < _ListWeightedGraph[Vertex].size() - 1)
				{
					indexFirstVertex++;
					_DepthFirstSearchPseudoWeightedGraphHelper(_ListWeightedGraph[Vertex][indexFirstVertex].indexAdjacencyVertex, isVisited);
				}
			}
		}
	}


public:


	GraphUseAdjacencyList(int NumberOfVertices)
	{
		_NumberOfVertices = NumberOfVertices;

		_DeletedVertices.resize(_NumberOfVertices);

		_List.resize(_NumberOfVertices);

		// this line special for -> ( weighted graph )
		_ListWeightedGraph.resize(_NumberOfVertices);
	}

	// =========================================================================================================

	void AddEdgeInPseudoWeightedUndirectedGraph(int indexV1, int indexV2, int Weight)
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
			_ListWeightedGraph[indexV1].push_back(WeightedGraph(indexV2, Weight));
		}
		else
		{
			_ListWeightedGraph[indexV1].push_back(WeightedGraph(indexV2, Weight));
			_ListWeightedGraph[indexV2].push_back(WeightedGraph(indexV1, Weight));
		}
	}

	void AddEdgeInPseudoWeightedDirectedGraph(int indexV1, int indexV2, int Weight)
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

		_ListWeightedGraph[indexV1].push_back(WeightedGraph(indexV2, Weight));
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

		vector <WeightedGraph>::iterator it;

		int i;
		for (i = 0; i < _ListWeightedGraph[indexV1].size(); i++)
		{
			if (_ListWeightedGraph[indexV1][i].indexAdjacencyVertex == indexV2 && _ListWeightedGraph[indexV1][i].Weight == weight)
			{
				it = _ListWeightedGraph[indexV1].begin() + i;
				_ListWeightedGraph[indexV1].erase(it);
				break;
			}
		}

		if (indexV1 != indexV2)
		{
			for (i = 0; i < _ListWeightedGraph[indexV2].size(); i++)
			{
				if (_ListWeightedGraph[indexV2][i].indexAdjacencyVertex == indexV1 && _ListWeightedGraph[indexV2][i].Weight == weight)
				{
					it = _ListWeightedGraph[indexV2].begin() + i;
					_ListWeightedGraph[indexV2].erase(it);
					return;
				}
			}
		}
		
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

		for (int i = 0; i < _ListWeightedGraph[indexV1].size(); i++)
		{
			if (_ListWeightedGraph[indexV1][i].indexAdjacencyVertex == indexV2 && _ListWeightedGraph[indexV1][i].Weight == weight)
			{
				vector <WeightedGraph>::iterator it = _ListWeightedGraph[indexV1].begin() + i;
				_ListWeightedGraph[indexV1].erase(it);
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

		for (int i = 0; i < _ListWeightedGraph[indexV1].size(); i++)
		{
			if (_ListWeightedGraph[indexV1][i].indexAdjacencyVertex == indexV2)
			{
				return true;
			}
		}

		for (int i = 0; i < _ListWeightedGraph[indexV2].size(); i++)
		{
			if (_ListWeightedGraph[indexV2][i].indexAdjacencyVertex == indexV1)
			{
				return true;
			}
		}

		return false;
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
			cout << "\nno weight between these tow vertices,\nbecause one of these vertices is deleted!\n";
			return vec;
		}

		for (int i = 0; i < _ListWeightedGraph[indexV1].size(); i++)
		{
			if (_ListWeightedGraph[indexV1][i].indexAdjacencyVertex == indexV2)
			{
				vec.push_back(_ListWeightedGraph[indexV1][i].Weight);
			}
		}

		return vec;
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

		for (int i = 0; i < _ListWeightedGraph[indexV].size(); i++)
		{
			vec.push_back(_ListWeightedGraph[indexV][i].indexAdjacencyVertex);
		}

		return vec;
	}

	void AddVertexPseudoWeightedGraph()
	{
		_NumberOfVertices++;

		vector<WeightedGraph> tmp;

		_ListWeightedGraph.push_back(tmp);

		_DeletedVertices.push_back(false);
	}

	void DeleteVertexFromUndirectedPseudoWeightedGraph(int indexV)
	{
		if (indexV >= _NumberOfVertices || indexV < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		_DeletedVertices[indexV] = true;

		for (int i = 0; i < _ListWeightedGraph[indexV].size(); i++)
		{
			int indexAdjancecyVertex = _ListWeightedGraph[indexV][i].indexAdjacencyVertex;

			for (int j = 0; j < _ListWeightedGraph[indexAdjancecyVertex].size(); j++)
			{
				if (_ListWeightedGraph[indexAdjancecyVertex][j].indexAdjacencyVertex == indexV)
				{
					vector <WeightedGraph>::iterator it = _ListWeightedGraph[indexAdjancecyVertex].begin() + j;
					_ListWeightedGraph[indexAdjancecyVertex].erase(it);

					// this line because check from same index after deletion and it is special for parallel edges
					j--;
				}
			}
		}

	}

	void DeleteVertexFromDirectedPseudoWeightedGraph(int indexV)
	{
		if (indexV >= _NumberOfVertices || indexV < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		_DeletedVertices[indexV] = true;

		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (i == indexV)
				continue;

			for (int j = 0; j < _ListWeightedGraph[i].size(); j++)
			{
				if (_ListWeightedGraph[i][j].indexAdjacencyVertex == indexV)
				{
					vector <WeightedGraph>::iterator it = _ListWeightedGraph[i].begin() + j;
					_ListWeightedGraph[i].erase(it);

					// this line because check from same index after deletion and it is special for parallel edges
					j--;
				}
			}
		}

	}

	void ClearPseudoWeightedGraph()
	{
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			_ListWeightedGraph[i].clear();
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
				continue;
			
			cout << "Vertex number : " << i << "\n\n{  ";
			for (int j = 0; j < _ListWeightedGraph[i].size(); j++)
			{
				cout << _ListWeightedGraph[i][j].Weight << " ";
			}
			cout << " }\n\n";
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

			for (int j = 0; j < _ListWeightedGraph[Vertex].size(); j++)
			{
				int AdjacencyVertex = _ListWeightedGraph[Vertex][j].indexAdjacencyVertex;

				if (isVisited[AdjacencyVertex] == false && _DeletedVertices[AdjacencyVertex] == false)
				{
					q.push(AdjacencyVertex);
					isVisited[AdjacencyVertex] = true;
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

			for (i = 0; i < _ListWeightedGraph[Vertex].size(); i++)
			{
				int AdjacencyVertex = _ListWeightedGraph[Vertex][i].indexAdjacencyVertex;

				if (isVisited[AdjacencyVertex] == false && _DeletedVertices[AdjacencyVertex] == false)
				{
					s.push(AdjacencyVertex);
					isVisited[AdjacencyVertex] = true;
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

		if (indexV1 == indexV2)
		{
			_List[indexV1].push_back(indexV2);
		}
		else
		{
			_List[indexV1].push_back(indexV2);
			_List[indexV2].push_back(indexV1);
		}
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

		_List[indexV1].push_back(indexV2);
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

		vector <int>::iterator it;

		int i;
		for (i = 0; i < _List[indexV1].size(); i++)
		{
			if (_List[indexV1][i] == indexV2)
			{
				it = _List[indexV1].begin() + i;
				_List[indexV1].erase(it);
				break;
			}
		}

		if (indexV1 != indexV2)
		{
			for (i = 0; i < _List[indexV2].size(); i++)
			{
				if (_List[indexV2][i] == indexV1)
				{
					it = _List[indexV2].begin() + i;
					_List[indexV2].erase(it);
					return;
				}
			}
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

		for (int i = 0; i < _List[indexV1].size(); i++)
		{
			if (_List[indexV1][i] == indexV2)
			{
				vector <int>::iterator it = _List[indexV1].begin() + i;
				_List[indexV1].erase(it);
				return;
			}
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

		for (int i = 0; i < _List[indexV1].size(); i++)
		{
			if (_List[indexV1][i] == indexV2)
			{
				return true;
			}
		}

		for (int i = 0; i < _List[indexV2].size(); i++)
		{
			if (_List[indexV2][i] == indexV1)
			{
				return true;
			}
		}

		return false;
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

		return _List[indexV];
	}

	void AddVertex()
	{
		_NumberOfVertices++;

		vector <int> tmp;

		_List.push_back(tmp);

		_DeletedVertices.push_back(false);
	}

	void DeleteVertexFromUndirectedGraph(int indexV)
	{
		if (indexV >= _NumberOfVertices || indexV < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		_DeletedVertices[indexV] = true;

		for (int i = 0; i < _List[indexV].size(); i++)
		{
			int indexAdjancecyVertex = _List[indexV][i];

			for (int j = 0; j < _List[indexAdjancecyVertex].size(); j++)
			{
				if (_List[indexAdjancecyVertex][j] == indexV)
				{
					vector <int>::iterator it = _List[indexAdjancecyVertex].begin() + j;
					_List[indexAdjancecyVertex].erase(it);

					// this line because check from same index after deletion and it is special for parallel edges
					j--;
				}
			}
			
		}
	}

	void DeleteVertexFromDirectedGraph(int indexV)
	{
		if (indexV >= _NumberOfVertices || indexV < 0)
		{
			cout << "\nOut Of Range!\n";
			return;
		}

		_DeletedVertices[indexV] = true;

		for (int i = 0; i < _NumberOfVertices; i++)
		{
			if (i == indexV)
				continue;
			
			for (int j = 0; j < _List[i].size(); j++)
			{
				if (_List[i][j] == indexV)
				{
					vector <int>::iterator it = _List[i].begin() + j;
					_List[i].erase(it);

					// this line because check from same index after deletion and it is special for parallel edges
					j--;
				}
			}
		}

	}

	void Clear()
	{
		for (int i = 0; i < _NumberOfVertices; i++)
		{
			_List[i].clear();
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
			for (int j = 0; j < _List[i].size(); j++)
			{
				cout << _List[i][j] << " ";
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

			for (int j = 0; j < _List[Vertex].size(); j++)
			{
				int AdjacencyVertex = _List[Vertex][j];

				if (isVisited[AdjacencyVertex] == false && _DeletedVertices[AdjacencyVertex] == false)
				{
					q.push(AdjacencyVertex);
					isVisited[AdjacencyVertex] = true;
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

			for (i = 0; i < _List[Vertex].size(); i++)
			{
				int AdjacencyVertex = _List[Vertex][i];

				if (isVisited[AdjacencyVertex] == false && _DeletedVertices[AdjacencyVertex] == false)
				{
					s.push(AdjacencyVertex);
					isVisited[AdjacencyVertex] = true;
				}
			}
		}

	}


	private:


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
		if (Vertex >= _NumberOfVertices || Vertex < 0 || Vertex2 >= _NumberOfVertices)
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

		int AdjacencyVertex = 0;
		
		pq.push(WeightedGraph(Vertex, 0));

		_vWeights[Vertex] = 0;

		while (!pq.empty())
		{
			WeightedGraph CurrentVertex = pq.top();

			if (Vertex2 == CurrentVertex.indexAdjacencyVertex)
			{
				return;
			}

			pq.pop();

			if (isVisited[CurrentVertex.indexAdjacencyVertex] == false)
			{
				for (int i = 0; i < _ListWeightedGraph[CurrentVertex.indexAdjacencyVertex].size(); i++)
				{
					AdjacencyVertex = _ListWeightedGraph[CurrentVertex.indexAdjacencyVertex][i].indexAdjacencyVertex;

					if (isVisited[AdjacencyVertex] == false)
					{
						int weight = _ListWeightedGraph[CurrentVertex.indexAdjacencyVertex][i].Weight;

						int sum = CurrentVertex.Weight + weight;

						if (sum < _vWeights[AdjacencyVertex])
						{
							weight = sum;
							_vWeights[AdjacencyVertex] = sum;
							_vParints[AdjacencyVertex] = CurrentVertex.indexAdjacencyVertex;
							
							pq.push(WeightedGraph(AdjacencyVertex, weight));
						}
						
					}
				}

				isVisited[CurrentVertex.indexAdjacencyVertex] = true;
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


	// =============================================================================================


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

		int AdjacencyVertex = 0;
		int weight = 0;
		long long int sum = 0;
		int v = 0;
		int i = 0;

		for (int j = 0; j < _NumberOfVertices - 1; j++)
		{
			int CurrentVertex = Vertex;

			bool HaveWeightsChanged = false;

			for (v = 0; v < _NumberOfVertices; v++)
			{
				for (i = 0; i < _ListWeightedGraph[CurrentVertex].size(); i++)
				{
					AdjacencyVertex = _ListWeightedGraph[CurrentVertex][i].indexAdjacencyVertex;

					weight = _ListWeightedGraph[CurrentVertex][i].Weight;

					sum = _vWeights[CurrentVertex] + weight;

					if (sum < _vWeights[AdjacencyVertex])
					{
						_vWeights[AdjacencyVertex] = sum;
						_vParints[AdjacencyVertex] = CurrentVertex;

						HaveWeightsChanged = true;
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
			for (i = 0; i < _ListWeightedGraph[v].size(); i++)
			{
				AdjacencyVertex = _ListWeightedGraph[v][i].indexAdjacencyVertex;

				weight = _ListWeightedGraph[v][i].Weight;

				sum = _vWeights[v] + weight;

				if (sum < _vWeights[AdjacencyVertex])
				{
					_vWeights.clear();
					_vParints.clear();

					cout << "\n\nBellman Algorithm Can not Find Shortest Path To This Graph!\n\n";
					return;
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





};

