#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsValidate.h"


// This class is specific to the open hashing method ( close addressing, separate chaining )
template <class K, class V>
class HashTableOpenHashing
{
private:

	struct stKeyAndValue
	{
		K key;
		V value;

		bool IsDeleted = true;

		stKeyAndValue* next = nullptr;
	};

	int _TableSize;

	int _Length;

	int _LoadFactorThreshold;

	stKeyAndValue* ptrHashTable;

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

		for (int i = 0; i < OldTapleSize; i++)
		{
			if (OldHashTable[i].IsDeleted == false)
			{
				Insert(OldHashTable[i].key, OldHashTable[i].value);
				
				if (OldHashTable[i].next != nullptr)
				{
					stKeyAndValue* tmp = OldHashTable[i].next;

					while (tmp != nullptr)
					{
						Insert(tmp->key, tmp->value);

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


	void _InsertOpenHashingOrSeparateChaining(int index, K key, V value)
	{
		if (ptrHashTable[index].next == nullptr)
		{
			ptrHashTable[index].next = new stKeyAndValue{ key ,value ,false };
			_Length++;
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
				return;
			}
		}
	}

	bool _IsFindOpenHashingOrSeparateChaining(int index, K key)
	{
		stKeyAndValue* tmp = ptrHashTable[index].next;

		while (tmp != nullptr)
		{
			 //here we do not check from IsDeleted or not because all items in linked list IsDeleted = false
			if (tmp->key == key)
			{
				return true;
			}

			tmp = tmp->next;
		}

		return false;
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


	HashTableOpenHashing(enTypesOfHashFunctions TypeOfHashFunction, int TableSize = 503)
	{
		_TypeOfHashFunction = TypeOfHashFunction;

		_TableSize = _GetPrimeNumberBigger(TableSize);

		ptrHashTable = new stKeyAndValue[_TableSize];

		_Length = 0;

		// this is default load factor -> 0.75f
	   _LoadFactorThreshold = _TableSize * 0.75f;
	}


	void Insert(K key, V value)
	{
		if (_TableSize < 1)
		{
			cout << "\n\nTable Size must bigger than 0\n\n";
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

	}

	void Delete(K key)
	{
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

	bool IsFind(K key)
	{
		if (_Length == 0)
		{
			cout << "\n\nHash Table is empty\n\n";
			return false;
		}

		int index = _PerformCorrectTypeOfHashFunction(key);

		if (ptrHashTable[index].IsDeleted == false)
		{
			if (ptrHashTable[index].key == key)
			{
				return true;
			}
			else
			{
				if (ptrHashTable[index].next != nullptr)
				{
					return _IsFindOpenHashingOrSeparateChaining(index, key);
				}
				else
				{
					return false;
				}
			}

		}
		else
		{
			return false;
		}
	}

	void Clear()
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

		_Length = 0;

		ptrHashTable = new stKeyAndValue[_TableSize];
	}

	
	
	void Display()
	{
		if (_Length == 0)
		{
			cout << "\n\nHash Table is empty\n\n";
			return;
		}

		cout << "\n\n";

		for (int i = 0; i < _TableSize; i++)
		{
			if (ptrHashTable[i].IsDeleted == false)
			{
				cout << ptrHashTable[i].key << " : " << ptrHashTable[i].value << "\n";

				if (ptrHashTable[i].next != nullptr)
				{
					stKeyAndValue* tmp = ptrHashTable[i].next;

					while (tmp != nullptr)
					{
						cout << tmp->key << " : " << tmp->value << "\n";
						tmp = tmp->next;
					}
				}
			}
		}

		cout << "\n\n";
	}


	int GetLength()
	{
		return _Length;
	}

	int GetTableSize()
	{
		return _TableSize;
	}

	
	~HashTableOpenHashing()
	{
		Clear();

		delete[] ptrHashTable;
		ptrHashTable = nullptr;
	}


};


