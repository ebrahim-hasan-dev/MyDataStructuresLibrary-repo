#pragma once

#include <iostream>
#include "clsUtil.h";
#include "clsValidate.h";
using namespace std;

template <class X>
class clsInput
{
public:

	static X ReadPositiveNumber(string MasssegeEnterNumber = "\nPlease enter a positive number : ")
	{
		X n = 0;

		do
		{
			cout << MasssegeEnterNumber;
			cin >> n;

			// if user enter input not number
			clsUtil<X>::MakeSureItisNumber(n);

		} while (n < 0);

		return n;

	}

	static X ReadNumber(string MasssegeEnterNumber = "\nPlease enter number : ")
	{
		X n = 0;
		
		cout << MasssegeEnterNumber;
		cin >> n;

		// if user enter input not number
		clsUtil<X>::MakeSureItisNumber(n);

		return n;

	}

	static X ReadNumberBetween(X NumberFrom, X NumberTo, string MasssegeEnterNumber = "\nPlease enter number between ")
	{
		X n = 0;
		
		cout << MasssegeEnterNumber;
		cin >> n;

		// if user enter input not number
		while (cin.fail() || !clsValidate<X>::IsNumberBetween(n, NumberFrom, NumberTo))
		{
			if(cin.fail())
			{
				clsUtil<X>::MakeSureItisNumber(n);
			}
			if (!clsValidate<X>::IsNumberBetween(n, NumberFrom, NumberTo) && !cin.fail())
			{
				cout << "\n" << n << " is not between " << NumberFrom << " and " << NumberTo << ", Please enter again : ";
				cin >> n;
			}
		}

		return n;

	}

	static string Readstring(string MasssegePleaseEnter)
	{
		string str = "";
		cout << MasssegePleaseEnter;
		getline(cin >> ws, str);
		return str;
	}

	static char ReadCharacter(string MasssegePleaseEnter = "\nPlease Enter A Character : ")
	{
		char c;
		cout << MasssegePleaseEnter;
		cin >> c;
		return c;
	}
	
	static void FillArrayOfAnyDataTypeFromUser(X arr[], int len, string MassegePleaseEnter = "\n Please Enter Element Number ")
	{
		clsUtil<X>::FillArrayOfAnyDataTypeFromUser(arr, len, MassegePleaseEnter);
	}

	





	
};

