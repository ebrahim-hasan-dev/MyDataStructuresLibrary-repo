#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsValidate.h"


// This class is specific to the perfect hashing method
template <class K, class V>
class HashTablePerfectHashing
{
private:

	struct stKeyAndValue
	{
		K key;
		V value;

		bool IsDeleted = true;

		stKeyAndValue* next = nullptr;

		int NumberCollisions = 1;
	};


	enum enHashFunction { Folding, Division, Multiplication };

	struct StructForPerfectHashing
	{
		K key;
		V value;

		bool IsEmpty = true;

		enHashFunction HashFunction = Division;
	};

	stKeyAndValue* ptrHashTable;

	int* SecondryTablesSize;

	bool IsAllowedInsert = true;

	int _TableSize;

	int _Length;

	int _LoadFactorThreshold;

	StructForPerfectHashing** PrimaryHashTable;

	bool _IsRemainderMethodOfDivisionUsed = false;


	int _HashFunctionDivisionMethod(int key, int TableSize)
	{
		// في هذه الطريقه يجب ان يكون حجم جدول التجزئه رقم اولي ويجب ايضا ان لا يكون من مضاعفات الرقم 2

		int index = key % TableSize;

		_IsRemainderMethodOfDivisionUsed = true;

		return index;
	}

	int _HashFunctionDivisionMethod(string key, int TableSize)
	{
		// في هذه الطريقه يجب ان يكون حجم جدول التجزئه رقم اولي ويجب ايضا ان لا يكون من مضاعفات الرقم 2

		long long index = 0;

		// we here choice this prime number because it is bigger than any asci value to any letter and it is middle not big and not small  
		int p = 131;

		long long power = 1; // القوة الأولية للأساس هي p^0 = 1

		for (int i = 0; i < key.size(); i++)
		{
			index = (index + (key[i] * power)) % TableSize;
			power = (power * p) % TableSize;
		}

		_IsRemainderMethodOfDivisionUsed = true;

		return int(index);
	}

	int _HashFunctionMultiplicationMethod(int key, int TableSize)
	{
		// تتميز هذه الطريقه في ان حجم جدول التجزئه يمكن ان يكون من مضاعفات 2 عادي

		// تم حساب هذا الثابت بواسطة هذه المعادله (sqrt(5) - 1) / 2
		// ثابت عشري اكبر من 0 واصغر من الواحد 
		double a = 0.618033;

		a = a * key;

		// اخذنا الرقم الصحيح من نتيجة ضرب المفتاح في الثابت العشري 
		int b = a;

		// استخرجنا الجزء العشري من الرقم الناتج من ضرب الثابت العشري في المفتاح
		a = a - b;

		a = floor(a * TableSize);

		return int(a);
	}

	int _HashFunctionMultiplicationMethod(string key, int TableSize)
	{
		// تتميز هذه الطريقه في ان حجم جدول التجزئه يمكن ان يكون من مضاعفات 2 عادي

		// تم حساب هذا الثابت بواسطة هذه المعادله (sqrt(5) - 1) / 2
		// ثابت عشري اكبر من 0 واصغر من الواحد 
		double a = 0.618033;

		a = a * _HashFunctionDivisionMethod(key, TableSize);

		_IsRemainderMethodOfDivisionUsed = false;

		// اخذنا الرقم الصحيح من نتيجة ضرب المفتاح في الثابت العشري 
		int b = a;

		// استخرجنا الجزء العشري من الرقم الناتج من ضرب الثابت العشري في المفتاح
		a = a - b;

		a = floor(a * TableSize);

		return int(a);
	}

	int _HashFunctionFoldingMethod(long long key, int TableSize)
	{
		// احنا بنتعامل مع ثلاث ارقام في الخوارزميه لاننا بنقسم علي 1000

		int num = 0;
		int tmp = 0;

		while (key > 0)
		{
			tmp = key % 1000;
			num += tmp;
			key = key / 1000;
		}

		_IsRemainderMethodOfDivisionUsed = true;

		return  num % TableSize;
	}

	int _HashFunctionFoldingMethod(string key, int TableSize)
	{
		short x = 0;
		string tmp = "";

		for (int i = 0; i < key.size(); i++)
		{
			x = key[i];

			while (x > 0)
			{
				short n = x % 10;
				tmp = char(n + 48) + tmp;
				x = x / 10;
			}
		}

		long long num = 0;

		for (int i = 0; i < tmp.size(); i++)
		{
			num = num * 10 + (tmp[i] - 48);
		}

		return  _HashFunctionFoldingMethod(num, TableSize);
	}

	int _GetPrimeNumberBigger(int begin)
	{
		while (clsValidate<int>::IsPrime(begin) == false)
		{
			begin++;
		}

		return begin;
	}

	int _GetPrimeNumberSmuller(int begin)
	{
		begin = begin - 2;

		while (clsValidate<int>::IsPrime(begin) == false)
		{
			begin--;
		}

		return begin;
	}

	void _ResizingOrRehashing()
	{
		int OldTapleSize = _TableSize;

		_TableSize = _TableSize + _TableSize;

		if (_IsRemainderMethodOfDivisionUsed == true)
		{
			_TableSize = _GetPrimeNumberBigger(_TableSize);
		}

		_LoadFactorThreshold = _TableSize * 0.75f;

		_Length = 0;

		stKeyAndValue* OldHashTable = ptrHashTable;

		ptrHashTable = new stKeyAndValue[_TableSize];

		delete[] PrimaryHashTable;

		PrimaryHashTable = new StructForPerfectHashing * [_TableSize];

		_InitializedPrimaryHashTable();

		delete[] SecondryTablesSize;

		SecondryTablesSize = new int[_TableSize];


		for (int i = 0; i < OldTapleSize; i++)
		{
			if (OldHashTable[i].IsDeleted == false)
			{
				Insert(OldHashTable[i].key, OldHashTable[i].value, false);

				// this condetion special for open hashing and perfect hashing only
				if (OldHashTable[i].next != nullptr)
				{
					stKeyAndValue* tmp = OldHashTable[i].next;

					while (tmp != nullptr)
					{
						Insert(tmp->key, tmp->value, false);

						tmp = tmp->next;
					}
				}
			}
		}

		delete[] OldHashTable;
	}


	stKeyAndValue& operator[] (int i)
	{
		return ptrHashTable[i];
	}


	void _InitializedPrimaryHashTable()
	{
		for (int i = 0; i < _TableSize; i++)
		{
			PrimaryHashTable[i] = nullptr;
		}
	}

	void _ClearPrefectHashing()
	{
		if (ptrHashTable != nullptr)
		{
			for (int i = 0; i < _TableSize; i++)
			{
				if (ptrHashTable[i].next != nullptr)
				{
					stKeyAndValue* tmp = ptrHashTable[i].next;

					while (tmp != nullptr)
					{
						stKeyAndValue* tmp2 = tmp->next;
						delete tmp;
						tmp = tmp2;
					}
				}
			}

			delete[] ptrHashTable;
		}

		ptrHashTable = new stKeyAndValue[_TableSize];

		for (int i = 0; i < _TableSize; i++)
		{
			if (PrimaryHashTable[i] != nullptr)
			{
				delete[] PrimaryHashTable[i];
			}
		}

		delete[] PrimaryHashTable;
		PrimaryHashTable = new StructForPerfectHashing * [_TableSize];

		_InitializedPrimaryHashTable();

		_Length = 0;

		IsAllowedInsert = true;

	}

	void _DeleteHelperTable()
	{
		for (int i = 0; i < _TableSize; i++)
		{
			if (ptrHashTable[i].next != nullptr)
			{
				stKeyAndValue* tmp = ptrHashTable[i].next;

				while (tmp != nullptr)
				{
					stKeyAndValue* tmp2 = tmp->next;
					delete tmp;
					tmp = tmp2;
				}
			}
		}

		delete[] ptrHashTable;
		ptrHashTable = nullptr;
	}

	int _GetIndexItemInSecondryHashTable(K key, enHashFunction HashFunction, int SecondryTableSize)
	{
		switch (HashFunction)
		{
		case enHashFunction::Division:
		{
			return _HashFunctionDivisionMethod(key, SecondryTableSize);
		}
		case enHashFunction::Folding:
		{
			return _HashFunctionFoldingMethod(key, SecondryTableSize);
		}
		case enHashFunction::Multiplication:
		{
			return _HashFunctionMultiplicationMethod(key, SecondryTableSize);
		}
		}
	}

	bool _IsFindInArray(int arr[], int len, int number)
	{
		for (int i = 0; i < len; i++)
		{
			if (arr[i] == number)
			{
				return true;
			}
		}

		return false;
	}

	void _ChoiceHashingFuction(int NumberCollisions, int ItemIndex, StructForPerfectHashing* SecondryHashTable, short count)
	{
		if (count > 3)
		{
			cout << "\n\nwe need more Hash Functions!\n\n";
			return;
		}

		int* indexes = new int[NumberCollisions];

		int index = _GetIndexItemInSecondryHashTable(ptrHashTable[ItemIndex].key, SecondryHashTable->HashFunction, SecondryTablesSize[ItemIndex]);

		indexes[0] = index;

		if (NumberCollisions > 1)
		{
			stKeyAndValue* tmp = ptrHashTable[ItemIndex].next;

			for (int i = 1; i < NumberCollisions; i++)
			{
				index = _GetIndexItemInSecondryHashTable(tmp->key, SecondryHashTable->HashFunction, SecondryTablesSize[ItemIndex]);

				tmp = tmp->next;

				if (_IsFindInArray(indexes, NumberCollisions, index) == true)
				{
					if (SecondryHashTable->HashFunction == Division)
					{
						SecondryHashTable->HashFunction = Multiplication;
					}
					else if (SecondryHashTable->HashFunction == Multiplication)
					{
						SecondryHashTable->HashFunction = Folding;
					}
					else
					{
						SecondryHashTable->HashFunction = Division;
					}

					_ChoiceHashingFuction(NumberCollisions, ItemIndex, SecondryHashTable, count + 1);
					break;
				}
				else
				{
					indexes[i] = index;
				}
			}
		}

		delete[] indexes;
	}

	void _InsertPerfectHashingHelper(StructForPerfectHashing* SecondryHashTable, int NumberCollisions, int ItemIndex)
	{
		int index = _GetIndexItemInSecondryHashTable(ptrHashTable[ItemIndex].key, SecondryHashTable->HashFunction, SecondryTablesSize[ItemIndex]);

		SecondryHashTable[index] = StructForPerfectHashing{ ptrHashTable[ItemIndex].key , ptrHashTable[ItemIndex].value , false , SecondryHashTable->HashFunction };

		if (NumberCollisions > 1)
		{
			stKeyAndValue* tmp = ptrHashTable[ItemIndex].next;

			for (int i = 1; i < NumberCollisions; i++)
			{
				index = _GetIndexItemInSecondryHashTable(tmp->key, SecondryHashTable->HashFunction, SecondryTablesSize[ItemIndex]);

				SecondryHashTable[index] = StructForPerfectHashing{ tmp->key , tmp->value , false , SecondryHashTable->HashFunction };

				tmp = tmp->next;
			}
		}

	}

	void _InsertPerfectHashing()
	{
		for (int i = 0; i < _TableSize; i++)
		{
			if (ptrHashTable[i].IsDeleted == false)
			{
				int QuadraticNumberCollisions = pow(ptrHashTable[i].NumberCollisions, 2);

				SecondryTablesSize[i] = QuadraticNumberCollisions;

				// create secondry hash table
				PrimaryHashTable[i] = new StructForPerfectHashing[QuadraticNumberCollisions];

				_ChoiceHashingFuction(ptrHashTable[i].NumberCollisions, i, PrimaryHashTable[i], 1);

				_InsertPerfectHashingHelper(PrimaryHashTable[i], ptrHashTable[i].NumberCollisions, i);
			}
		}

		_DeleteHelperTable();

		IsAllowedInsert = false;
	}

	void _InsertOpenHashingOrSeparateChaining(int index, K key, V value)
	{
		if (ptrHashTable[index].next == nullptr)
		{
			ptrHashTable[index].next = new stKeyAndValue{ key ,value ,false };
			_Length++;

			// this line special for Perfect Hashing Method only
			ptrHashTable[index].NumberCollisions++;
		}
		else
		{
			stKeyAndValue* tmp = ptrHashTable[index].next;

			// هذا الشرط خاص بالتعديل
			if (tmp->key == key)
			{
				tmp->value = value;
				return;
			}

			while (tmp->next != nullptr)
			{
				tmp = tmp->next;

				// هذا الشرط خاص بالتعديل
				if (tmp->key == key)
				{
					tmp->value = value;
					return;
				}
			}

			tmp->next = new stKeyAndValue{ key ,value ,false };
			_Length++;

			ptrHashTable[index].NumberCollisions++;
		}

	}

	void _DeleteOpenHashingOrSeparateChaining(int index, K key)
	{
		stKeyAndValue* tmp = ptrHashTable[index].next;

		if (tmp->key == key)
		{
			_Length--;
			ptrHashTable[index].next = tmp->next;
			delete tmp;

			// this line special for Perfect Hashing Method only
			ptrHashTable[index].NumberCollisions--;
			return;
		}

		while (tmp->next != nullptr)
		{
			stKeyAndValue* prev = tmp;
			tmp = tmp->next;

			if (tmp->key == key)
			{
				_Length--;
				prev->next = tmp->next;
				delete tmp;

				// this line special for Perfect Hashing Method only
				ptrHashTable[index].NumberCollisions--;
				return;
			}
		}
	}


public:

	enum enTypesOfHashFunctions { DivisionMethod, MultiplicationMethod, FoldingMethod };

private:

	enTypesOfHashFunctions _TypeOfHashFunction;

	int _PerformCorrectTypeOfHashFunction(K key)
	{
		if (_TypeOfHashFunction == enTypesOfHashFunctions::DivisionMethod)
		{
			return _HashFunctionDivisionMethod(key, _TableSize);
		}
		else if (_TypeOfHashFunction == enTypesOfHashFunctions::MultiplicationMethod)
		{
			return _HashFunctionMultiplicationMethod(key, _TableSize);
		}
		else
		{
			return _HashFunctionFoldingMethod(key, _TableSize);
		}
	}


public:


	HashTablePerfectHashing(enTypesOfHashFunctions TypeOfHashFunction, int TableSize = 503)
	{
		_TypeOfHashFunction = TypeOfHashFunction;

		_TableSize = _GetPrimeNumberBigger(TableSize);

		ptrHashTable = new stKeyAndValue[_TableSize];

		PrimaryHashTable = new StructForPerfectHashing * [_TableSize];

		_InitializedPrimaryHashTable();

		SecondryTablesSize = new int[_TableSize];

		_Length = 0;

		// this is default load factor -> 0.75f
	   _LoadFactorThreshold = _TableSize * 0.75f;
	}

	void Insert(K key, V value, bool IsThisLastItem)
	{
		if (_TableSize < 1)
		{
			cout << "\n\nTable Size must bigger than 0\n\n";
			return;
		}

		if (IsAllowedInsert == false)
		{
			cout << "\n\nnot allowed insert more items,\nif you want insert more you must clear all items and insert from begining.\n\n";
			return;
		}

		int index = _PerformCorrectTypeOfHashFunction(key);

		if (ptrHashTable[index].IsDeleted == true)
		{
			ptrHashTable[index] = stKeyAndValue{ key ,value ,false };
			_Length++;
		}

		// هذا الشرط خاص بالتعديل وعشان ميبقاش فيه مفتاحيين زي بعض
		else if (ptrHashTable[index].key == key)
		{
			ptrHashTable[index].value = value;
		}

		else
		{
			_InsertOpenHashingOrSeparateChaining(index, key, value);
		}

		if (_Length > _LoadFactorThreshold)
		{
			_ResizingOrRehashing();
		}

		if (IsThisLastItem == true)
		{
			_InsertPerfectHashing();
		}

	}

	void DeleteBeforeBuildingStructurePerfectHashing(K key)
	{
		if (ptrHashTable == nullptr)
		{
			cout << "\n\nyou must use this function delete before building structure perfect hashing or before insert last item!\n\n";
			return;
		}

		if (_Length == 0)
		{
			cout << "\n\nHash Table is empty\n\n";
			return;
		}

		int index = _PerformCorrectTypeOfHashFunction(key);

		if (ptrHashTable[index].IsDeleted == false && ptrHashTable[index].key == key)
		{
			_Length--;

			if (ptrHashTable[index].next == nullptr)
			{
				ptrHashTable[index].IsDeleted = true;
			}
			else
			{
				stKeyAndValue* tmp = ptrHashTable[index].next;

				ptrHashTable[index] = stKeyAndValue{ tmp->key, tmp->value, tmp->IsDeleted, tmp->next };

				delete tmp;
			}
		}
		else if (ptrHashTable[index].IsDeleted == false && ptrHashTable[index].key != key && ptrHashTable[index].next != nullptr)
		{
			_DeleteOpenHashingOrSeparateChaining(index, key);
		}
	}

	void PrintItem(K key)
	{
		if (IsAllowedInsert == true)
		{
			cout << "\n\nyou must use function PrintItem after insert all items!\n\n";
		}
		else
		{
			int index = _PerformCorrectTypeOfHashFunction(key);

			StructForPerfectHashing* tmp = PrimaryHashTable[index];

			if (tmp == nullptr)
			{
				cout << "\n\nitem with key { " << key << " } not found!\n\n";
			}
			else
			{
				index = _GetIndexItemInSecondryHashTable(key, tmp->HashFunction, SecondryTablesSize[index]);

				if (tmp[index].key == key)
				{
					cout << "\n " << tmp[index].key << " : " << tmp[index].value << " \n";
				}
				else
				{
					cout << "\n\nitem with key { " << key << " } not found!\n\n";
				}
			}
		}

	}

	void Display()
	{
		if (IsAllowedInsert == true)
		{
			cout << "\n\nyou must use function Display after insert all items!\n\n";
			return;
		}

		cout << "\n\n";

		for (int i = 0; i < _TableSize; i++)
		{
			if (PrimaryHashTable[i] != nullptr)
			{
				StructForPerfectHashing* tmp = PrimaryHashTable[i];

				int SecondryTableSize = SecondryTablesSize[i];

				for (int i = 0; i < SecondryTableSize; i++)
				{
					if (tmp[i].IsEmpty == false)
					{
						cout << tmp[i].key << " : " << tmp[i].value << "\n";
					}
				}
			}
		}

		cout << "\n\n";
	}

	void Clear()
	{
		_ClearPrefectHashing();
	}
	
	int GetLength()
	{
		return _Length;
	}

	int GetTableSize()
	{
		return _TableSize;
	}


	~HashTablePerfectHashing()
	{
		Clear();

		delete[] PrimaryHashTable;
		PrimaryHashTable = nullptr;

		delete[] SecondryTablesSize;
		SecondryTablesSize = nullptr;

		delete[] ptrHashTable;
		ptrHashTable = nullptr;
	}


};


