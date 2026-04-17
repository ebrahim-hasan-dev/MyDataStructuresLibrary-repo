#pragma once

#include <iostream>
using namespace std;
#include "..\MyLibrary\clsValidate.h"


// This class is specific to the cuckoo hashing method
template <class K, class V>
class HashTableCuckooHashing
{
private:

	struct stKeyAndValue
	{
		K key;
		V value;

		bool IsDeleted = true;
	};

	int _TableSize;

	int _Length;

	int _LoadFactorThreshold;

	stKeyAndValue* FirstHashTable;
	stKeyAndValue* SecondHashTable;

	bool _IsRemainderMethodOfDivisionUsed = false;

	bool _IsChangeHashFunctions = false;


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

	void _ResizingOrRehashingCuckooHashingMethod()
	{
		int OldTapleSize = _TableSize;

		_TableSize = _TableSize + _TableSize;

		_TableSize = _GetPrimeNumberBigger(_TableSize);

		_IsChangeHashFunctions = _IsChangeHashFunctions == false ? true : false;

		_LoadFactorThreshold = (_TableSize + _TableSize) * 0.50f;

		_Length = 0;

		// here we must use two varaibles not one because not error occured
		stKeyAndValue* OldHashTable1 = FirstHashTable;
		stKeyAndValue* OldHashTable2 = SecondHashTable;

		FirstHashTable = new stKeyAndValue[_TableSize];
		SecondHashTable = new stKeyAndValue[_TableSize];

		for (int i = 0; i < OldTapleSize; i++)
		{
			if (OldHashTable1[i].IsDeleted == false)
			{
				Insert(OldHashTable1[i].key, OldHashTable1[i].value);
			}
		}

		delete[] OldHashTable1;

		for (int i = 0; i < OldTapleSize; i++)
		{
			if (OldHashTable2[i].IsDeleted == false)
			{
				Insert(OldHashTable2[i].key, OldHashTable2[i].value);
			}
		}

		delete[] OldHashTable2;
	}

	bool _InsertInFirstTable(stKeyAndValue& item)
	{
		int index = _HashFunctionDivisionMethod(item.key, _TableSize);

		if (FirstHashTable[index].IsDeleted == true)
		{
			FirstHashTable[index] = item;

			return true;
		}
		else
		{
			stKeyAndValue tmp = FirstHashTable[index];

			FirstHashTable[index] = item;

			item = tmp;

			return false;
		}
	}

	bool _InsertInSecondTable(stKeyAndValue& item)
	{
		int index = 0;

		if (_IsChangeHashFunctions == false)
		{
			index = _HashFunctionFoldingMethod(item.key, _TableSize);
		}
		else
		{
			index = _HashFunctionMultiplicationMethod(item.key, _TableSize);
		}

		if (SecondHashTable[index].IsDeleted == true)
		{
			SecondHashTable[index] = item;
			return true;
		}
		else
		{
			stKeyAndValue tmp = SecondHashTable[index];

			SecondHashTable[index] = item;

			item = tmp;

			return false;
		}

	}

	void _Eviction(K key, V value, int index1)
	{
		_Length++;

		stKeyAndValue tmp = FirstHashTable[index1];

		FirstHashTable[index1] = stKeyAndValue{ key ,value ,false };

		int i = 0;

		int Log2 = log2(_TableSize) * 2;

		while (i < Log2)
		{
			if (_InsertInSecondTable(tmp) == true)
			{
				return;
			}

			if (_InsertInFirstTable(tmp) == true)
			{
				return;
			}

			i++;
		}

		_ResizingOrRehashingCuckooHashingMethod();

		Insert(tmp.key, tmp.value);
	}

	void _InsertCuckooHashingMethod2(K key, V value, int index1)
	{
		int index = 0;

		if (_IsChangeHashFunctions == false)
		{
			index = _HashFunctionFoldingMethod(key, _TableSize);
		}
		else
		{
			index = _HashFunctionMultiplicationMethod(key, _TableSize);
		}

		if (SecondHashTable[index].IsDeleted == true)
		{
			SecondHashTable[index] = stKeyAndValue{ key ,value ,false };
			_Length++;
		}
		else
		{
			// هذا الشرط خاص بالتعديل وعشان ميبقاش فيه مفتاحيين زي بعض
			if (SecondHashTable[index].key == key)
			{
				SecondHashTable[index].value = value;
			}
			else
			{
				_Eviction(key, value, index1);
			}
		}

	}

	void _InsertCuckooHashingMethod1(K key, V value)
	{
		int index = _HashFunctionDivisionMethod(key, _TableSize);

		if (FirstHashTable[index].IsDeleted == true)
		{
			FirstHashTable[index] = stKeyAndValue{ key ,value ,false };
			_Length++;
		}
		else
		{
			// هذا الشرط خاص بالتعديل وعشان ميبقاش فيه مفتاحيين زي بعض
			if (FirstHashTable[index].key == key)
			{
				FirstHashTable[index].value = value;
				return;
			}

			// this function must be inside else scope
			_InsertCuckooHashingMethod2(key, value, index);
		}

		if (_Length > _LoadFactorThreshold)
		{
			_ResizingOrRehashingCuckooHashingMethod();
		}

	}

	bool _IsFindCuckooHashingMethod(K key)
	{
		int index = _HashFunctionDivisionMethod(key, _TableSize);

		if (FirstHashTable[index].key == key && FirstHashTable[index].IsDeleted == false)
		{
			return true;
		}
		else
		{
			if (_IsChangeHashFunctions == false)
			{
				index = _HashFunctionFoldingMethod(key, _TableSize);
			}
			else
			{
				index = _HashFunctionMultiplicationMethod(key, _TableSize);
			}

			if (SecondHashTable[index].key == key && SecondHashTable[index].IsDeleted == false)
			{
				return true;
			}
		}

		return false;
	}

	void _DisplayCuckooHashingMethod()
	{
		cout << "\n\n";

		for (int i = 0; i < _TableSize; i++)
		{
			if (FirstHashTable[i].IsDeleted == false)
			{
				cout << FirstHashTable[i].key << " : " << FirstHashTable[i].value << "\n";
			}

			if (SecondHashTable[i].IsDeleted == false)
			{
				cout << SecondHashTable[i].key << " : " << SecondHashTable[i].value << "\n";
			}
		}

		cout << "\n\n";
	}

	void _ClearCuckooHashingMethod()
	{
		delete[] FirstHashTable;

		FirstHashTable = new stKeyAndValue[_TableSize];

		delete[] SecondHashTable;

		SecondHashTable = new stKeyAndValue[_TableSize];

		_Length = 0;
	}

	
public:


	HashTableCuckooHashing(int TableSize = 503)
	{
		_TableSize = _GetPrimeNumberBigger(TableSize);

		_Length = 0;

		FirstHashTable = new stKeyAndValue[_TableSize];
		SecondHashTable = new stKeyAndValue[_TableSize];

		_LoadFactorThreshold = (_TableSize + _TableSize) * 0.50f;
	}

	void Insert(K key, V value)
	{
		if (_TableSize < 1)
		{
			cout << "\n\nTable Size must bigger than 0\n\n";
			return;
		}

		_InsertCuckooHashingMethod1(key, value);
	}

	void Delete(K key)
	{
		if (_Length == 0)
		{
			cout << "\n\nHash Table is empty\n\n";
			return;
		}

		int index = _HashFunctionDivisionMethod(key, _TableSize);


		if (FirstHashTable[index].key == key && FirstHashTable[index].IsDeleted == false)
		{
			FirstHashTable[index].IsDeleted = true;
			_Length--;
		}
		else
		{
			if (_IsChangeHashFunctions == false)
			{
				index = _HashFunctionFoldingMethod(key, _TableSize);
			}
			else
			{
				index = _HashFunctionMultiplicationMethod(key, _TableSize);
			}


			if (SecondHashTable[index].key == key && SecondHashTable[index].IsDeleted == false)
			{
				SecondHashTable[index].IsDeleted = true;
				_Length--;
			}
		}

	}

	bool IsFind(K key)
	{
		if (_Length == 0)
		{
			cout << "\n\nHash Table is empty\n\n";
			return false;
		}

		return _IsFindCuckooHashingMethod(key);
	}

	void Display()
	{
		if (_Length == 0)
		{
			cout << "\n\nHash Table is empty\n\n";
			return;
		}

		_DisplayCuckooHashingMethod();
	}

	void Clear()
	{
		_ClearCuckooHashingMethod();
	}

	int GetLength()
	{
		return _Length;
	}

	int GetTableSize()
	{
		return _TableSize;
	}

	~HashTableCuckooHashing()
	{
		Clear();

		delete[] FirstHashTable;
		FirstHashTable = nullptr;
		delete[] SecondHashTable;
		SecondHashTable = nullptr;
	}


};

