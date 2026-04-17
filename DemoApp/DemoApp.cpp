
using namespace std;
#include <iostream>


// Graphs

#include "../MyDataStructuresLibrary/Graphs/GraphUseAdjacencyList.h";
#include "../MyDataStructuresLibrary/Graphs/GraphUseAdjacencyMatrix.h";
#include "../MyDataStructuresLibrary/Graphs/GraphUseIncidenceMatrix.h";

//========================================================================

// Hash Tables

#include "../MyDataStructuresLibrary/HashTables/HashTableOpenHashing.h";
#include "../MyDataStructuresLibrary/HashTables/HashTableCloseHashing.h";
#include "../MyDataStructuresLibrary/HashTables/HashTableRobinHoodHashing.h";
#include "../MyDataStructuresLibrary/HashTables/HashTableCuckooHashing.h";
#include "../MyDataStructuresLibrary/HashTables/HashTableCoalescedHashing.h";
#include "../MyDataStructuresLibrary/HashTables/HashTablePerfectHashing.h";

//========================================================================

// Linear

#include "../MyDataStructuresLibrary/Linear/ArrayBasedList.h";
#include "../MyDataStructuresLibrary/Linear/ClsMyQueue.h";
#include "../MyDataStructuresLibrary/Linear/ClsMyQueueArr.h";
#include "../MyDataStructuresLibrary/Linear/ClsMyStack.h";
#include "../MyDataStructuresLibrary/Linear/ClsMyStackArr.h";
#include "../MyDataStructuresLibrary/Linear/DoublyLinkedList.h";
#include "../MyDataStructuresLibrary/Linear/LinkedList.h";
#include "../MyDataStructuresLibrary/Linear/PriorityQueue.h";
#include "../MyDataStructuresLibrary/Linear/Queue.h";
#include "../MyDataStructuresLibrary/Linear/QueueUsingArray.h";
#include "../MyDataStructuresLibrary/Linear/Stack.h";
#include "../MyDataStructuresLibrary/Linear/StackUsingArray.h";

//========================================================================

// Trees

#include "../MyDataStructuresLibrary/Trees/BinarySearchTree.h";
#include "../MyDataStructuresLibrary/Trees/AVLTree.h";
#include "../MyDataStructuresLibrary/Trees/RedBlackTree.h";
#include "../MyDataStructuresLibrary/Trees/BPlusTree.h";
#include "../MyDataStructuresLibrary/Trees/BPlusTree_Correct.h";
#include "../MyDataStructuresLibrary/Trees/BPlusTree_Correct_Update.h";
#include "../MyDataStructuresLibrary/Trees/BTree.h";
#include "../MyDataStructuresLibrary/Trees/BTree_Correct.h";
#include "../MyDataStructuresLibrary/Trees/BTree_Correct_Update.h";
#include "../MyDataStructuresLibrary/Trees/HuffmanTree.h";


int main()
{
	// demo here any class from my data structures library

	return 0;
}




// this function main specified is for testing all hash tables

/*int main()
{
	// this demo for open hashing method ( close addressing, separate chaining )

	HashTableOpenHashing<int, int> HTOpenHashingObject(HashTableOpenHashing<int, int>::DivisionMethod, 7);
	//HashTableOpenHashing<int, int> HTOpenHashingObject(HashTableOpenHashing<int, int>::MultiplicationMethod, 7);
	//HashTableOpenHashing<int, int> HTOpenHashingObject(HashTableOpenHashing<int, int>::FoldingMethod, 7);

	HTOpenHashingObject.Insert(1, 10);
	HTOpenHashingObject.Insert(2, 20);
	HTOpenHashingObject.Insert(3, 30);

	cout << "item key = 2 and value = 20 is deleted.\n\n";
	HTOpenHashingObject.Delete(2);

	cout << "Is Find (4) : " << HTOpenHashingObject.IsFind(4) << "\n";
	cout << "Is Find (3) : " << HTOpenHashingObject.IsFind(3) << "\n";
	cout << "Get Length : " << HTOpenHashingObject.GetLength() << "\n";
	cout << "Get Table Size : " << HTOpenHashingObject.GetTableSize() << "\n";

	cout << "\n\nview all items :";

	HTOpenHashingObject.Display();

	// ==========================================================================================================================

	// this demo for close hashing method ( open addressing ), ( linear probing, quadratic probing, double hashing )

	//HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::DivisionMethod, HashTableCloseHashing<int, int>::LinearProbing, 7);
	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::DivisionMethod, HashTableCloseHashing<int, int>::QuadraticProbing, 7);
	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::DivisionMethod, HashTableCloseHashing<int, int>::DoubleHashing, 7);

	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::MultiplicationMethod, HashTableCloseHashing<int, int>::LinearProbing, 7);
	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::MultiplicationMethod, HashTableCloseHashing<int, int>::QuadraticProbing, 7);
	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::MultiplicationMethod, HashTableCloseHashing<int, int>::DoubleHashing, 7);

	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::FoldingMethod, HashTableCloseHashing<int, int>::LinearProbing, 7);
	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::FoldingMethod, HashTableCloseHashing<int, int>::QuadraticProbing, 7);
	////HashTableCloseHashing<int, int> HTCloseHashingObject(HashTableCloseHashing<int, int>::FoldingMethod, HashTableCloseHashing<int, int>::DoubleHashing, 7);


	//HTCloseHashingObject.Insert(1, 10);
	//HTCloseHashingObject.Insert(2, 20);
	//HTCloseHashingObject.Insert(3, 30);
	//
	//cout << "item key = 2 and value = 20 is deleted.\n\n";
	//HTCloseHashingObject.Delete(2);
	////HTCloseHashingObject.Delete(4);

	//cout << "Is Find (4) : " << HTCloseHashingObject.IsFind(4) << "\n";
	//cout << "Is Find (3) : " << HTCloseHashingObject.IsFind(3) << "\n";
	//cout << "Get Length : " << HTCloseHashingObject.GetLength() << "\n";
	//cout << "Get Table Size : " << HTCloseHashingObject.GetTableSize() << "\n";

	//cout << "\n\nview all items :";

	//HTCloseHashingObject.Display();

	// ==========================================================================================================================

	// this demo for robin hood hashing method

	//HashTableRobinHoodHashing<int, int> HTRobinHoodHashingObject(HashTableRobinHoodHashing<int, int>::DivisionMethod, 7);
	////HashTableRobinHoodHashing<int, int> HTRobinHoodHashingObject(HashTableRobinHoodHashing<int, int>::MultiplicationMethod, 7);
	////HashTableRobinHoodHashing<int, int> HTRobinHoodHashingObject(HashTableRobinHoodHashing<int, int>::FoldingMethod, 7);

	//HTRobinHoodHashingObject.Insert(1, 10);
	//HTRobinHoodHashingObject.Insert(2, 20);
	//HTRobinHoodHashingObject.Insert(3, 30);

	//cout << "item key = 2 and value = 20 is deleted.\n\n";
	//HTRobinHoodHashingObject.Delete(2);

	//cout << "Is Find (4) : " << HTRobinHoodHashingObject.IsFind(4) << "\n";
	//cout << "Is Find (3) : " << HTRobinHoodHashingObject.IsFind(3) << "\n";
	//cout << "Get Length : " << HTRobinHoodHashingObject.GetLength() << "\n";
	//cout << "Get Table Size : " << HTRobinHoodHashingObject.GetTableSize() << "\n";

	//cout << "\n\nview all items :";

	//HTRobinHoodHashingObject.Display();

	// ==========================================================================================================================

	// this demo for cuckoo hashing method

	//HashTableCuckooHashing<int, int> HTCuckooHashingObject(7);
	////HashTableCuckooHashing<int, int> HTCuckooHashingObject(7);
	////HashTableCuckooHashing<int, int> HTCuckooHashingObject(7);

	//HTCuckooHashingObject.Insert(1, 10);
	//HTCuckooHashingObject.Insert(2, 20);
	//HTCuckooHashingObject.Insert(3, 30);

	//cout << "item key = 2 and value = 20 is deleted.\n\n";
	//HTCuckooHashingObject.Delete(2);

	//cout << "Is Find (4) : " << HTCuckooHashingObject.IsFind(4) << "\n";
	//cout << "Is Find (3) : " << HTCuckooHashingObject.IsFind(3) << "\n";
	//cout << "Get Length : " << HTCuckooHashingObject.GetLength() << "\n";
	//cout << "Get Table Size : " << HTCuckooHashingObject.GetTableSize() << "\n";

	//cout << "\n\nview all items :";

	//HTCuckooHashingObject.Display();

	// ==========================================================================================================================

	// this demo for coalesced hashing method

	////HashTableCoalescedHashing<int, int> HTCoalescedHashingObject(HashTableCoalescedHashing<int, int>::DivisionMethod, 7);
	////HashTableCoalescedHashing<int, int> HTCoalescedHashingObject(HashTableCoalescedHashing<int, int>::MultiplicationMethod, 7);
	//HashTableCoalescedHashing<int, int> HTCoalescedHashingObject(HashTableCoalescedHashing<int, int>::FoldingMethod, 7);

	//HTCoalescedHashingObject.Insert(1, 10);
	//HTCoalescedHashingObject.Insert(2, 20);
	//HTCoalescedHashingObject.Insert(3, 30);

	//cout << "item key = 2 and value = 20 is deleted.\n\n";
	//HTCoalescedHashingObject.Delete(2);

	//cout << "Is Find (4) : " << HTCoalescedHashingObject.IsFind(4) << "\n";
	//cout << "Is Find (3) : " << HTCoalescedHashingObject.IsFind(3) << "\n";
	//cout << "Get Length : " << HTCoalescedHashingObject.GetLength() << "\n";
	//cout << "Get Table Size : " << HTCoalescedHashingObject.GetTableSize() << "\n";

	//cout << "\n\nview all items :";

	//HTCoalescedHashingObject.Display();

	// ==========================================================================================================================

	// this demo for perfect hashing method

	////HashTablePerfectHashing<int, int> HTPerfectHashingObject(HashTablePerfectHashing<int, int>::DivisionMethod, 7);
	////HashTablePerfectHashing<int, int> HTPerfectHashingObject(HashTablePerfectHashing<int, int>::MultiplicationMethod, 7);
	//HashTablePerfectHashing<int, int> HTPerfectHashingObject(HashTablePerfectHashing<int, int>::FoldingMethod, 7);

	//HTPerfectHashingObject.Insert(1, 10, false);
	//HTPerfectHashingObject.Insert(2, 20, false);

	//HTPerfectHashingObject.DeleteBeforeBuildingStructurePerfectHashing(2);
	//HTPerfectHashingObject.Insert(3, 30, true);


	//HTPerfectHashingObject.PrintItem(4);
	//HTPerfectHashingObject.PrintItem(3);

	//cout << "\nGet Length : " << HTPerfectHashingObject.GetLength() << "\n";
	//cout << "Get Table Size : " << HTPerfectHashingObject.GetTableSize() << "\n";

	//cout << "\n\nview all items :";

	//HTPerfectHashingObject.Display();



	return 0;
}*/




// this function main specified is for testing Huffman Tree 

/*int main()
{
	HuffmanTree h;

	string str = "aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff";

	string HuffmanCode = h.CreateHuffmanCode(str);

	cout << "\n\n   " << HuffmanCode << "\n\n";



	string strAfterDeCompression = h.DeCompression(HuffmanCode);

	cout << "\n\n   " << strAfterDeCompression << "\n\n";


	return 0;
}*/