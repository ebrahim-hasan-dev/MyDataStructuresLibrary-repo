#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include "clsString.h";
using namespace std;

template <class T>
class clsUtil
{
public:

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int GetRangeRandomNumber(int from = 1, int to = 100)
	{
		int n = rand() % (to - from + 1) + from;

		return n;
	}

	static char GetRandomCapitalCharacter()
	{
		return char(GetRangeRandomNumber(65, 90));
	}

	static char GetRandomSmallCharacter()
	{
		return char(GetRangeRandomNumber(97, 122));
	}

	static char GetRandomDigitCharacter() 
	{
		return char(GetRangeRandomNumber(48, 57));
	}

	static char GetRandomSpecialCharacter() 
	{
		return char(GetRangeRandomNumber(32, 47));
	}

	enum enChoiceCharacter { CapitalCharacter = 1, SmallCharacter, Digit, SpecialCharacter, Mix };

	static char GetRandomCharacter(enChoiceCharacter ChoiceCharacter)
	{
		if (ChoiceCharacter == enChoiceCharacter::Mix)
		{
			ChoiceCharacter = (enChoiceCharacter)GetRangeRandomNumber(1, 3);
		}

		switch (ChoiceCharacter)
		{

		case enChoiceCharacter::CapitalCharacter:
		{
			return GetRandomCapitalCharacter();
		}
		case enChoiceCharacter::SmallCharacter:
		{
			return GetRandomSmallCharacter();
		}
		case enChoiceCharacter::Digit:
		{
			return GetRandomDigitCharacter();
		}
		case enChoiceCharacter::SpecialCharacter:
		{
			return GetRandomSpecialCharacter();
		}

		}
	}
	
	static string GetRandomWord(enChoiceCharacter ChoiceCharacters = enChoiceCharacter::CapitalCharacter, short LengthOfWord = 4)
	{
		if (ChoiceCharacters == enChoiceCharacter::SpecialCharacter || ChoiceCharacters == enChoiceCharacter::Digit)
		{
			return "\nYou Must Choice Any Characters Unless Special And Digit";
		}

		string word = "";

		for (short i = 0; i < LengthOfWord; i++)
		{
			word += GetRandomCharacter(ChoiceCharacters);
		}
		
		return word;

	}
	
	static string GenerateKey(enChoiceCharacter ChoiceCharacters = enChoiceCharacter::Mix, short HowManyWord = 4, short LengthOfWord = 4)
	{
		string key = "";

		for (int i = 0; i < HowManyWord; i++)
		{
			key += GetRandomWord(ChoiceCharacters, LengthOfWord);

			if (i != (HowManyWord - 1))
			{
				key += '-';
			}
		}

		return key;

	}
	
	static void GenerateKeys(short HowManyKeys, enChoiceCharacter ChoiceCharacters = enChoiceCharacter::Mix, short HowManyWord = 4, short LengthOfWord = 4)
	{

		cout << endl;

		for (short i = 0; i < HowManyKeys; i++)
		{
			cout << "Key [" << i + 1 << "] : " << GenerateKey(ChoiceCharacters, HowManyWord, LengthOfWord) << endl;
		}

	}
	
	static void FillArrayWithRandomWords(string arr[], int LengthOfArray, enChoiceCharacter ChoiceCharacters = enChoiceCharacter::CapitalCharacter, short LengthOfWord = 4)
	{
		for (int i = 0; i < LengthOfArray; i++)
		{
			arr[i] = GetRandomWord(ChoiceCharacters, LengthOfWord);
		}
	}
	
	static void FillArrayWithRandomKeys(string arr[], int LengthOfArray, enChoiceCharacter ChoiceCharacters = enChoiceCharacter::CapitalCharacter, short LengthOfWord = 4, short HowManyWord = 4)
	{
		for (int i = 0; i < LengthOfArray; i++)
		{
			arr[i] = GenerateKey(ChoiceCharacters, HowManyWord, LengthOfWord);
		}
	}

	static void FillSortedArray(int arr[], int from, int to)
	{
		for (int i = 0; i < to; i++)
		{
			arr[i] = from + i;
		}
	}

	/*static void CheckIsNumbeOrNot(double& Number)
	{
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "\nInvalid Input, Please Enter a valid one : ";
			cin >> Number;
		}
	}*/

	static void MakeSureItisNumber(T& Number)
	{
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Input, Please Enter a valid one : ";
			cin >> Number;
		}
	}

	static void MakeSureItisNumber2(T& Number)
	{
		do
		{
			if (cin.fail())
			{
				cout << "Invalid Input, Please Enter a valid one : ";
			}

			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cin >> Number;

		} while (cin.fail());
	}

	/*static void CheckIsNumbeOrNot(short& Number)
	{
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "\nInvalid Input, Please Enter a valid one : ";
			cin >> Number;
		}
	}*/

	static void FillArrayOfAnyDataTypeFromUser(T arr[], int len, string MassegePleaseEnter = "\n Please Enter Element Number ")
	{
		
		for (int i = 0; i < len; i++)
		{
			cout << MassegePleaseEnter << i + 1 << " : ";
			cin >> arr[i];

			MakeSureItisNumber(arr[i]);
			
		}
	}

	static void PrintArrayOfAnyDataType(T array[], int length)
	{

		cout << endl;

		for (int i = 0; i < length; i++)
		{
			cout << array[i];

			if (i != (length - 1))
			{
				cout << ", ";
			}
		}

		cout << endl;

	}

	static void FillArrayWithRandomNumbers(int arr[], int LengthOfArray, int RandomNumbeStartFrom, int RandomNumberEndAt)
	{
		for (int i = 0; i < LengthOfArray; i++)
		{
			arr[i] = GetRangeRandomNumber(RandomNumbeStartFrom, RandomNumberEndAt);
		}
	}

	static short CountTheNumberInArray(T arr[], T TheNumber, int LengthOfArray)
	{
		short c = 0;

		for (int i = 0; i < LengthOfArray; i++)
		{
			if (arr[i] == TheNumber)
				c++;
		}

		return c;

	}

	static T MaxNumberInArray(T arr[], int LengthOfArray)
	{
		T max = arr[0];

		for (int i = 1; i < LengthOfArray; i++)
		{
			if (arr[i] > max)
				max = arr[i];
		}

		return max;

	}

	static T MinNumberInArray(T arr[], int LengthOfArray)
	{
		T min = arr[0];

		for (int i = 1; i < LengthOfArray; i++)
		{
			if (arr[i] < min)
				min = arr[i];
		}

		return min;

	}

	static T SumAllElmentsOfArray(T arr[], int LengthOfArray)
	{
		T sum = 0;

		for (int i = 0; i < LengthOfArray; i++)
		{
			sum += arr[i];
		}

		return sum;

	}

	static void CopyArray(T SourceArray[], T CopyArray[], int LengthOfSourceArray)
	{
		for (int i = 0; i < LengthOfSourceArray; i++)
		{
			CopyArray[i] = SourceArray[i];
		}
	}

	static short FindPositionNumberInArray(T arr[], int LengthOfArray, T Number)
	{
		for (short i = 0; i < LengthOfArray; i++)
		{
			if (arr[i] == Number)
			{
				return i;
			}
		}

		return -1;
	}

	static bool IsFound(T arr[], int LengthOfArray, T Number)
	{
		return FindPositionNumberInArray(arr, LengthOfArray, Number) != -1;
	}

	static void CopyReverseArray(T arr[], T CopyArray[], int LengthOfArray)
	{
		for (short i = 0; i < LengthOfArray; i++)
		{
			CopyArray[i] = arr[LengthOfArray - (1 + i)];
		}
	}

	static bool IsPrime(int number)
	{
		if (number == 1 || number == 0)
		{
			return false;
		}

		int m = number / 2;

		for (int i = 2; i <= m; i++)
		{
			if (number % i == 0)
				return false;
		}

		return true;

	}

	static void CopyArrayOnlyPrimeNumber(T SourceArray[], T CopyArray[], int LengthOfSourceArray, int& LengthOfCopyArray)
	{

		// LengthOfCopyArray must be = 0

		for (int i = 0; i < LengthOfSourceArray; i++)
		{
			if (IsPrime(SourceArray[i]))
			{
				CopyArray[LengthOfCopyArray] = SourceArray[i];

				LengthOfCopyArray++;

			}
		}

	}

	static void Sum2Arrays(T Array1[], T Array2[], T SumArray[], int LengthOfArray)
	{
		for (int i = 0; i < LengthOfArray; i++)
		{
			SumArray[i] = Array1[i] + Array2[i];
		}
	}

	static short IsFoundMoreThanOnce(T Array[], int LengthOfArray, T number)
	{
		int c = 0;

		for (int i = 0; i < LengthOfArray; i++)
		{
			if (Array[i] == number)
				c++;
		}

		return c == 0 ? -1 : c == 1 ? 0 : 1;

	}

	static void SwapAnyDataType(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	static void shuffle_array_better_algorithm(T Array[], int length)
	{
		for (int i = 0; i < length; i++)
		{
			SwapAnyDataType(Array[GetRangeRandomNumber(1, length) - 1], Array[GetRangeRandomNumber(1, length) - 1]);
		}
	}

	static int CountOddNumbersInArray(int arr[], int len) 
	{
		int c = 0;

		for (short i = 0; i < len; i++)
		{
			if (arr[i] % 2 != 0)
				c++;
		}

		return c;

	}

	static int CountEvenNumbersInArray(int arr[], int len) 
	{
		int c = 0;

		for (short i = 0; i < len; i++)
		{
			if (arr[i] % 2 == 0)
				c++;
		}

		return c;

	}

	static int CountPositiveNumbersInArray(int arr[], int len) 
	{
		int c = 0;

		for (short i = 0; i < len; i++)
		{
			if (arr[i] >= 0)
			{
				c++;
			}
		}

		return c;

	}

	static int CountNegativeNumbersInArray(int arr[], int len)
	{
		int c = 0;

		for (short i = 0; i < len; i++)
		{
			if (arr[i] < 0)
			{
				c++;
			}
		}

		return c;

	}

	static bool IsPalindrom(T arr[], int len)
	{

		for (short i = 0; i < len/2; i++)
		{
			if (arr[i] != arr[len - (1 + i)]) 
			{
				return false; 
			}
		}

		return true;
	}

	static void AddElementInArray(T Element, T Array[], int& PositionElementinArray)
	{
		Array[PositionElementinArray] = Element;

		PositionElementinArray++;

	}

	static void CopyDistinctArray(T SourceArray[], T CopyArray[], int lengthOfSourceArray, int& lengthOfCopyArray)
	{
		// lengthOfCopyArray must be = 0

		for (int i = 0; i < lengthOfSourceArray; i++)
		{
			if (!IsFound(CopyArray, lengthOfCopyArray, SourceArray[i]))
			{
				AddElementInArray(SourceArray[i], CopyArray, lengthOfCopyArray);
			}
		}
	}

	static void FillTowDimantionalArrayWithRangeRandomNumbers(int matrix[3][3], int row, int col, int RandomNumberStartFrom, int RandomNumberEndAt)
	{
		// row = number sub array  in big array
		// col = number of elements in sub array

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				matrix[i][j] = GetRangeRandomNumber(RandomNumberStartFrom, RandomNumberEndAt);
			}
		}
	}

	static void FillTowDimantionalArrayWithOrderedNumbers(int matrix[3][3], int row, int col, int SatrtFrom)
	{
		// row = number sub array  in big array
		// col = number of elements in sub array

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				matrix[i][j] = SatrtFrom;

				SatrtFrom++;
			}
		}
	}

	static void PrintTowDimantionalArray(T matrix[3][3], int row, int col)
	{
		// row = number sub array in big array
		// col = number of elements in sub array

		for (int i = 0; i < row; i++)
		{
			cout << "  ";

			for (short j = 0; j < col; j++)
			{
				cout << setw(3) << matrix[i][j] << "   ";
			}

			cout << endl;
		}
	}

	static T SumColinTowDimantionalArray(T matrix[3][3], int row, int col)
	{
		// row = number sub array  in big array
		// col = number of elements in sub array

		T sum = 0;

		for (short j = 0; j < row; j++)
		{
			sum += matrix[j][col];
		}

		return sum;
	}

	static void PrintEachColSum(T matrix[3][3], int row, int col)
	{
		// row = number sub array  in big array
		// col = number of elements in sub array

		for (int i = 0; i < col; i++)
		{
			cout << " Col " << i + 1 << " = " << SumColinTowDimantionalArray(matrix, row, i) << endl;
		}

	}

	static T SumRowinTowDimantionalArray(T matrix[3][3], int row, int col)
	{
		T sum = 0;
		
		for (short j = 0; j < col; j++)
		{
			sum += matrix[row][j];
		}
		
		return sum;
	
	}

	static void PrintEachRowSum(T matrix[3][3], int row, int col)
	{
		for (int i = 0; i < row; i++)
		{
			cout << " Row " << i + 1 << " = " << SumRowinTowDimantionalArray(matrix, i, col) << endl;
		}
	}

	static void SumMatrixRowsInArray(T matrix[3][3], T arr[], int row, int col)
	{
		for (short i = 0; i < row; i++)
		{
			arr[i] = SumRowinTowDimantionalArray(matrix, i, col);
		}
	}

	static void SumMatrixColsInlArray(T matrix[3][3], T arr[], int row, int col)
	{
		for (short i = 0; i < col; i++)
		{
			arr[i] = SumColinTowDimantionalArray(matrix, row, i);
		}
	}

	static void PrintResultOfMultiplyTowDimantionalArray(T matrix[3][3], T matrix2[3][3], int row, int col)
	{
		for (int i = 0; i < row; i++)
		{
			cout << "  ";

			for (short j = 0; j < col; j++)
			{
				printf("%0*d  ", 2, matrix[i][j] * matrix2[i][j]);
			}

			cout << endl;
		}
	}

	static void PrintTowDimantionalArrayUsingPrintf(T matrix[3][3], int row, int col)
	{
		for (short i = 0; i < row; i++)
		{
			cout << "  ";

			for (short j = 0; j < col; j++)
			{
				printf(" %0*d  ", 2, matrix[i][j]);
			}

			cout << endl;
		}
	}

	static void GenerateMatrixContentOnResultMultiplyTowMatrix(T matrix[3][3], T matrix2[3][3], T ResultMatrix[3][3], int row, int col)
	{
		for (short i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				ResultMatrix[i][j] = matrix[i][j] * matrix2[i][j];
			}
		}
	}

	static void PrintMiddleRowInTowDimantionalArrayUsingPrintf(T matrix[3][3], int row, int col)
	{
		short MiddleRow = row / 2;

		cout << "  ";

		for (short j = 0; j < col; j++)
		{
			printf(" %0*d  ", 2, matrix[MiddleRow][j]);
		}

		cout << endl;

	}

	static void PrintMiddleColInTowDimantionalArrayUsingPrintf(T matrix[3][3], int row, int col)
	{
		short MiddleCol = col / 2;

		cout << "  ";

		for (short j = 0; j < row; j++)
		{
			printf(" %0*d  ", 2, matrix[j][MiddleCol]);
		}

		cout << endl;

	}

	static T SumMatrix(T matrix[3][3], int row, int col)
	{
		T sum = 0;

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				sum += matrix[i][j];
			}
		}

		return sum;

	}

	static bool AreSumOf_2_MatricesEqual(T matrix[3][3], T matrix2[3][3], int row, int col)
	{
		return (SumMatrix(matrix, row, col) == SumMatrix(matrix2, row, col));
	}

	static bool AreTypicalMatrices(T matrix[3][3], T matrix2[3][3], int row, int col)
	{

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (matrix[i][j] != matrix2[i][j])
				{
					return false;
				}
			}
		}

		return true;

	}

	static bool IsidentityMatrix(int matrix[3][3], int row, int col)
	{

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (i == j && matrix[i][j] != 1)
				{
					return false;
				}
				if (i != j && matrix[i][j] != 0)
				{
					return false;
				}
			}
		}

		return true;

	}

	static bool IsScalarMatrix(T matrix[3][3], int row, int col)
	{

		T scalar = matrix[0][0];

		for (short i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (i == j && matrix[i][j] != scalar)
				{
					return false;
				}
				if (i != j && matrix[i][j] != 0)
				{
					return false;
				}
			}
		}

		return true;

	}

	static short CountElementInMatrix(T matrix[3][3], int row, int col, T Element)
	{
		T count = 0;

		for (short i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (matrix[i][j] == Element)
				{
					count++;
				}
			}
		}

		return count;

	}

	static bool IsSparceMatrix(int matrix[3][3], int row, int col)
	{
		return CountElementInMatrix(matrix, row, col, 0) > row * col / 2;
	}

	static bool IsFoundInMatrix(T matrix[3][3], int row, int col, T Element)
	{
		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (matrix[i][j] == Element)
				{
					return true;
				}
			}
		}

		return false;

	}

	static void PrintIntersectedNumberInTowMatrices(T matrix[3][3], T matrix2[3][3], int row, int col)
	{
		cout << "  ";

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (IsFoundInMatrix(matrix2, row, col, matrix[i][j]))
				{
					cout << matrix[i][j] << "  ";
				}
			}
		}
	}

	static T MaxNumberInMatrix(T matrix[3][3], int row, int col)
	{
		T MaxNumber = matrix[0][0];

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (matrix[i][j] > MaxNumber)
				{
					MaxNumber = matrix[i][j];
				}
			}
		}

		return MaxNumber;

	}

	static T MinNumberInMatrix(T matrix[3][3], int row, int col)
	{
		T MinNumber = matrix[0][0];

		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col; j++)
			{
				if (matrix[i][j] < MinNumber)
				{
					MinNumber = matrix[i][j];
				}
			}
		}

		return MinNumber;

	}

	static bool IsPalindromMatrix(T matrix[3][3], int row, int col)
	{
		for (int i = 0; i < row; i++)
		{
			for (short j = 0; j < col / 2; j++)
			{
				if (matrix[i][j] != matrix[i][col - (1 + j)])
				{
					return false;
				}
			}
		}

		return true;

	}

	static void FibonacciSeriesArray(int arr[], int len)
	{
		// 1 1 2 3 5 8 13 21 

		arr[0] = 1;

		arr[1] = 1;

		for (short i = 2; i < len; i++)
		{
			arr[i] = arr[i - 1] + arr[i - 2];
		}

	}

	static void PrintFibonacciSeriesUsingloop(int num)
	{
		int febnumber = 0;

		int prev1 = 1;

		int prev2 = 1;

		cout << "1  1  ";

		for (short i = 2; i < num; i++)
		{
			// 1 1 2 3 5 8 13 21 

			febnumber = prev1 + prev2;
			cout << febnumber << "  ";
			prev2 = prev1;
			prev1 = febnumber;

		}

	}

	static void PrintFibonacciSeriesUsingRecursion(int num, int prev2, int prev1)
	{
		if (num == 2)
		{
			return;
		}

		if (prev1 == 1)
		{
			cout << "1  1  ";
		}

		// 1 1 2 3 5 8 13 21

		int febnumber = prev2 + prev1;
		cout << febnumber << "  ";
		prev2 = prev1;
		prev1 = febnumber;

		PrintFibonacciSeriesUsingRecursion(num - 1 , prev2, prev1);

	}

	static string EncryptText(string Text, short EncryptionKey = 2) // 1234
	{
		for (short i = 0; i < Text.length(); i++)
		{
			short ch = Text[i];

			if (ch % 2 == 0)
			{
				Text[i] = char(ch - EncryptionKey);
			}
			else
			{
				Text[i] = char(ch + EncryptionKey);
			}
		}

		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 2)
	{
		for (short i = 0; i < Text.length(); i++)
		{
			short ch = Text[i];

			// if ch here = odd number
			// ch += EncryptionKey = odd number / or / ch -= EncryptionKey = odd number
			// same if ch = even number 
			ch += EncryptionKey;

			if (ch % 2 == 0)
			{
				Text[i] = char(ch);
			}
			else
			{
				ch = ch - (EncryptionKey + EncryptionKey);

				Text[i] = char(ch);
			}
		}

		return Text;
	}

	/*static string EncryptText(string Text, short EncryptionKey = 2)
	{
		for (short i = 0; i < Text.length(); i++)
		{
			short ch = Text[i];

			Text[i] = char(ch ^ EncryptionKey);
		}

		return Text;
	}

	static string DecryptText(string Text, short EncryptionKey = 2)
	{
		return EncryptText(Text, EncryptionKey);
	}*/

	static string ConvertNumberToText(long long int number)
	{
		return clsString::ConvertNumberToTextUsingRecursion(number);
	}





};

