#pragma once

#include <iostream>
#include <string>
#include "clsDate.h";
#include "clsUtil.h";
#include "clsString.h";
using namespace std;

template <class C>
class clsValidate
{
public:


	static bool IsNumberBetween(C Number, C NumberFrom, C NumberTo)
	{	
		if (NumberFrom == NumberTo)
		{
			return NumberFrom == Number;
		}

		if (NumberFrom > NumberTo)
		{
			clsUtil<C>::SwapAnyDataType(NumberFrom, NumberTo);
		}

		return Number >= NumberFrom && Number <= NumberTo;

	}

	static bool IsDateBetween(clsDate Date, clsDate DateStart, clsDate DateEnd)
	{
		if (clsDate::IsDate1EqualDate2(DateStart, DateEnd))
		{
			return clsDate::IsDate1EqualDate2(Date, DateEnd);
		}

		if (!clsDate::IsDate1LessThanDate2(DateStart, DateEnd))
		{
			clsDate::SwapDate(DateStart, DateEnd);
		}

		return !(clsDate::CompareDates(Date, DateStart) == clsDate::Results::Before || clsDate::CompareDates(Date, DateEnd) == clsDate::Results::After);
	}

	static bool IsValideDate(clsDate Date)
	{
		return Date.IsValide();
	}

	static bool IsFound(C arr[], int LengthOfArray, C Number)
	{
		return clsUtil<C>::IsFound(arr, LengthOfArray, Number);
	}

	static bool IsPrime(int number)
	{
		return clsUtil<int>::IsPrime(number);
	}

	static short IsFoundMoreThanOnce(C Array[], int LengthOfArray, C number)
	{
		return clsUtil<C>::IsFoundMoreThanOnce(Array, LengthOfArray, number);
	}

	static bool IsPalindrom(C arr[], int len)
	{
		return clsUtil<C>::IsPalindrom(arr, len);
	}

	static bool AreSumOf_2_MatricesEqual(C matrix[3][3], C matrix2[3][3], int row, int col)
	{
		return clsUtil<C>::AreSumOf_2_MatricesEqual(matrix, matrix2, row, col);
	}

	static bool IsidentityMatrix(int matrix[3][3], int row, int col)
	{
		return clsUtil<int>::IsidentityMatrix(matrix, row, col);
	}

	static bool IsScalarMatrix(C matrix[3][3], int row, int col)
	{
		return clsUtil<C>::IsScalarMatrix(matrix, row, col);
	}

	static bool IsSparceMatrix(int matrix[3][3], int row, int col)
	{
		return clsUtil<int>::IsScalarMatrix(matrix, row, col);
	}

	static bool IsFoundInMatrix(C matrix[3][3], int row, int col, C Element)
	{
		return clsUtil<C>::IsFoundInMatrix(matrix, row, col, Element);
	}

	static bool IsPalindromMatrix(C matrix[3][3], int row, int col)
	{
		return clsUtil<C>::IsPalindromMatrix(matrix, row, col);
	}

	static bool IsLeapYear(short year)
	{
		return clsDate::IsLeapYear(year);
	}

	static bool IsDate1LessThanDate2(clsDate Date1, clsDate Date2)
	{
		return clsDate::IsDate1LessThanDate2(Date1, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return clsDate::IsDate1EqualDate2(Date1, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return clsDate::IsLastDayInMonth(Date);
	}

	static bool IsLastMonthInYear(short month)
	{
		return clsDate::IsLastMonthInYear(month);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return clsDate::IsDate1AfterDate2(Date1, Date2);
	}

	static bool IsVowel(char ch)
	{
		return clsString::IsVowel(ch);
	}

	static bool ItIsPhoneNumber(string PhoneNumber)
	{
		if (PhoneNumber[0] != '0')
		{
			return false;
		}

		for (short i = 1; i < PhoneNumber.length(); i++)
		{
			if (!isdigit(PhoneNumber[i]))
			{
				return false;
			}
		}

		return true;
	}

	static bool IsStrongePassWord(string PassWord)
	{
		short Digits = 0;
		short SpecielChar = 0;
		short Char = 0;

		for (short i = 0; i < PassWord.length(); i++)
		{
			if (isdigit(PassWord[i]))
			{
				Digits++;
			}
			else if (ispunct(PassWord[i]))
			{
				SpecielChar++;
			}
			else if (PassWord[i] >= 'A' && PassWord[i] <= 'Z' || PassWord[i] >= 'a' && PassWord[i] <= 'z')
			{
				Char++;
			}
		}

		if (Digits == 0 || SpecielChar == 0 || Char == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}



};

