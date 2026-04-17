#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class clsString
{
private: 

	string _Value = "";

public:

	clsString() : _Value("") {}

	clsString(string Value) : _Value (Value) {}


	void SetValue(string Value) 
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}

	_declspec(property(get = GetValue, put = SetValue)) string Value;


	static void PrintFirstLetterOfEachWordInThisString(string st) {
		
		bool isFirstLetter = true;

		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ' && isFirstLetter)
				cout << st[i] << "\n";


			isFirstLetter = st[i] == ' ' ? true : false;

		}

	}
	void PrintFirstLetterOfEachWordInThisString()
	{
		PrintFirstLetterOfEachWordInThisString(_Value);
	}

	static void PrintFirstLetterOfEachWordInThisStringMyAlgorithm(string st) {
		
		for (short i = 0; i < st.length(); i++)
		{

			if (i == 0 && st[i] != ' ')
				cout << st[i] << endl;


			if (st[i] == ' ' && st[i + 1] != ' ')
				cout << st[i + 1] << endl;

		}

	}
	void PrintFirstLetterOfEachWordInThisStringMyAlgorithm()
	{
		PrintFirstLetterOfEachWordInThisStringMyAlgorithm(_Value);
	}

	static string ConvertionFirstLetterOfEachWordToUpper(string st) {

		bool isFirstLetter = true;

		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ' && isFirstLetter)
				st[i] = toupper(st[i]);


			isFirstLetter = st[i] == ' ' ? true : false;

		}

		return st;

	}
	void ConvertionFirstLetterOfEachWordToUpper()
	{
		_Value = ConvertionFirstLetterOfEachWordToUpper(_Value);
	}

	static string ConvertionFirstLetterOfEachWordToLower(string st) {

		bool isFirstLetter = true;

		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ' && isFirstLetter)
				st[i] = tolower(st[i]);


			isFirstLetter = st[i] == ' ' ? true : false;

		}

		return st;

	}
	void ConvertionFirstLetterOfEachWordToLower()
	{
		_Value = ConvertionFirstLetterOfEachWordToLower(_Value);
	}


	static string ConvertionAllStringToLower(string st) {

		for (short i = 0; i < st.length(); i++)
		{
			//if (isupper(st[i]))
		   //if ((st[i] >= 65 && st[i] <= 90))
		   
			//tolower() -> if we pass any argument not letter return it same like Space and digit,
			// it change only upper letters  
			st[i] = tolower(st[i]);

		}

		return st;

	}
	void ConvertionAllStringToLower()
	{
		_Value = ConvertionAllStringToLower(_Value);
	}

	static string ConvertionAllStringToUpper(string st) {

		for (short i = 0; i < st.length(); i++)
		{
			//if (islower(st[i]))
		   //if ((st[i] >= 97 && st[i] <= 122))

			//toupper() -> if we pass any argument not letter return it same like Space and digit,
			// it change only lower letters 
			st[i] = toupper(st[i]);

		}

		return st;

	}
	void ConvertionAllStringToUpper()
	{
		_Value = ConvertionAllStringToUpper(_Value);
	}


	static char ConvertionCharacter(char ch) 
	{
		return isupper(ch) ? char(tolower(ch)) : char(toupper(ch));
	}


	static string ConvertionAllString(string st) {

			for (short i = 0; i < st.length(); i++)
			{
				st[i] = ConvertionCharacter(st[i]);
			}

			return st;
	
		}
	void ConvertionAllString()
		{
			_Value = ConvertionAllString(_Value);
		}

	static short CountSmallLetter(string st) {

			short c = 0;

			for (size_t i = 0; i < st.length(); i++)
			{
				if (islower(st[i]))
					c++;
			}
	
			return c;

		}
	short CountSmallLetter()
	{
		return CountSmallLetter(_Value);
	}

	static short CountCapitalLetter(string st) {

		short c = 0;

		for (size_t i = 0; i < st.length(); i++)
		{
			if (isupper(st[i]))
				c++;
		}

		return c;

	}
	short CountCapitalLetter()
	{
		return CountCapitalLetter(_Value);
	}

	static short CountSpecialLetter(string st) {

		short c = 0;

		for (size_t i = 0; i < st.length(); i++)
		{
			if (ispunct(st[i]))
				c++;
		}

		return c;

	}
	short CountSpecialLetter()
	{
		return CountSpecialLetter(_Value);
	}

	static vector <string> SplitStringinVector(string st, string delimit = " ") 
	{
		
		vector <string> vec;

		string word = "";

		short pos = 0;

		while ((pos = st.find(delimit)) != std::string::npos)
		{

			word = st.substr(0, pos);

			if (word != "")
				vec.push_back(word);


			st.erase(0, pos + delimit.length());

		}

		if (st != "")
			vec.push_back(st);


		return vec;

	}
	vector <string> SplitStringinVector(string delimit = " ")
	{
		return SplitStringinVector(_Value, delimit);
	}

	static short CountSpecificLetterInString(string st, char ch, bool isSensitive = true) {

		short c = 0;

		for (short i = 0; i < st.length(); i++)
		{
			if (isSensitive)
			{
				if (st[i] == ch)
					c++;
			}
			else
			{
				if (tolower(st[i]) == tolower(ch))
					c++;
			}
		}

		return c;

	}
	short CountSpecificLetterInString(char ch, bool isSensitive = true)
	{
		return CountSpecificLetterInString(_Value, ch, isSensitive);
	}


	static bool IsVowel(char ch) {

		char Array[5] = { 'a','e','o','u','i' };

		for (short j = 0; j < 5; j++)
		{
			if (Array[j] == tolower(ch))
				return true;
		}

		return false;

	}


	static short CountVowelLetterInString(string st) {

		short c = 0;

		for (short i = 0; i < st.length(); i++)
		{
			if (IsVowel(st[i]))
				c++;

		}

		return c;

	}
	short CountVowelLetterInString()
	{
		return CountVowelLetterInString(_Value);
	}

	static void PrintallVowelLetterInString(string st) {
		
		for (short i = 0; i < st.length(); i++)
		{
			if (IsVowel(st[i]))
				cout << st[i] << endl;
		}
	}
	void PrintallVowelLetterInString()
	{
		PrintallVowelLetterInString(_Value);
	}

	static void PrintEachWordInStringUsingBuiltinFunction(string st, string Seprator = " ") {

		string word = "";

		short pos = 0;

		while ((pos = st.find(Seprator)) != std::string::npos)
		{

			word = st.substr(0, pos);

			if (word != "")
			{
				cout << word << endl;
			}

			st.erase(0, pos + Seprator.length());

		}

		if (st != "")
			cout << st << endl;

	}
	void PrintEachWordInStringUsingBuiltinFunction(string Seprator = " ")
	{
		PrintEachWordInStringUsingBuiltinFunction(_Value, Seprator);
	}

	static void PrintEachWordInString(string st) {

		string str = "";

		bool inWord = true;

		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ')
			{
				inWord = true;
				str += st[i];
			}
			else
			{
				inWord = false;
				if (str != "")
					cout << str << endl;

				str = "";
			}
		}

		if (inWord)
			cout << str << endl;

	}
	void PrintEachWordInString()
	{
		PrintEachWordInString(_Value);
	}

	static short CountEachWordInString(string st, string Seprator = " ") {

		short c = 0;

		string word = "";

		short pos = 0;

		while ((pos = st.find(Seprator)) != std::string::npos)
		{

			word = st.substr(0, pos);

			if (word != "")
				c++;


			st.erase(0, pos + Seprator.length());

		}

		if (st != "")
			c++;


		return c;

	}
	short CountEachWordInString(string Seprator = " ")
	{
		return CountEachWordInString(_Value, Seprator);
	}

	static string TrimLift(string st, char Seprator = ' ') {

		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != Seprator)
			{
				return st = st.substr(i, st.length() - i);
			}
		}

		return "";

	}
	void TrimLift(char Seprator = ' ')
	{
		_Value = TrimLift(_Value, Seprator);
	}

	static string TrimRight(string st, char Seprator = ' ') {

		for (short i = st.length() - 1; i > 0; i--)
		{
			if (st[i] != Seprator)
				return st = st.substr(0, i + 1);
		}

		return "";

	}
	void TrimRight(char Seprator = ' ')
	{
		_Value = TrimRight(_Value, Seprator);
	}

	static string TrimAll(string st, char Seprator = ' ') 
	{

		st = TrimRight(st, Seprator);

		return TrimLift(st, Seprator);

	}
	void TrimAll(char Seprator = ' ')
	{
		_Value = TrimAll(_Value, Seprator);
	}

	static string JoinString(string st, vector <string>& vec, string sep = " ") {

		for (string& s : vec)
		{
			st += s + sep;
		}

		return st = st.substr(0, st.length() - sep.length());

	}
	void JoinString(vector <string>& vec, string sep = " ")
	{
		_Value = JoinString(_Value, vec, sep);
	}

	static string JoinString(string st, string arr[3], int len, string sep = " ") {

		for (short i = 0; i < len; i++)
		{

			st += arr[i];

			if (i != len - 1)
				st += sep;
		}

		return st;

	}
	void JoinString(string arr[3], int len, string sep = " ") 
	{
		_Value = JoinString(_Value, arr, len, sep);
	}

	static string ReverseWordinString(string st, string sep = " ") {

		string str = "";

		vector <string> vec;

		vec = SplitStringinVector(st, sep);

		vector <string>::iterator it = vec.end();

		while (it != vec.begin())
		{
			it--;
			str += *it + sep;
		}

		return st = str.substr(0, str.length() - sep.length());

	}
	void ReverseWordinString(string sep = " ")
	{
		_Value = ReverseWordinString(_Value, sep);
	}

	static string ReplaceWordinString(string st, string ReplaceTo, string ReplaceFrom, string sep = " ", bool isSensitive = true) {
		
		vector <string> vec = SplitStringinVector(st, sep);

		vector <string>::iterator it = vec.begin();
		
		while (it != vec.end())
		{
			if (isSensitive)
			{
				if (*it == ReplaceFrom)
				{
					*it = ReplaceTo;
				}
			}
			else
			{
				if (ConvertionAllStringToLower(*it) == ConvertionAllStringToLower(ReplaceFrom))
				{
					*it = ReplaceTo;
				}
			}

			it++;

		}

		string str = "";

		return st = JoinString(str, vec, sep);

	}
	void ReplaceWordinString(string ReplaceTo, string ReplaceFrom, string sep = " ", bool isSensitive = true)
	{
		_Value = ReplaceWordinString(_Value, ReplaceTo, ReplaceFrom, sep, isSensitive);
	}

	static string ReplaceWordinStringUsingBuiltinFanction(string st, string ReplaceTo, string ReplaceFrom) {
		
		short pos = st.find(ReplaceFrom);

		while (pos != std::string::npos)
		{

			st.replace(pos, ReplaceFrom.length(), ReplaceTo);

			pos = st.find(ReplaceFrom);

		}

		return st;

	}
	void ReplaceWordinStringUsingBuiltinFanction(string ReplaceTo, string ReplaceFrom)
	{
		_Value = ReplaceWordinStringUsingBuiltinFanction(_Value, ReplaceTo, ReplaceFrom);
	}

	static string RemovePunctuationsFromString(string st) {

		string str = "";

		for (short i = 0; i < st.length(); i++)
		{

			if (!ispunct(st[i]))
				str += st[i];

		}

		st = str;

		return st;

	}
	void RemovePunctuationsFromString()
	{
		_Value = RemovePunctuationsFromString(_Value);
	}

	static string ConvertNumberToTextUsingRecursion(long long int number)
	{
		string NumberAsString = "";

		if (number < 0)
		{
			number *= -1;

			NumberAsString += "Negative ";
		}

		if (number == 0)
		{
			return "";
		}

		if (number >= 1 && number <= 19)
		{
			string arr[] = { "One", "Two", "Three", "Four", "Five",
				"Six", "Seven", "Eight", "Nine",
			"Ten", "Eleven", "Twelve", "Thirteen",
				"Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };


			NumberAsString += arr[number - 1];
		}

		if (number >= 20 && number <= 99)
		{

			string arr[] = { "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

			NumberAsString += arr[number / 10 - 2] + " " + ConvertNumberToTextUsingRecursion(number % 10);

		}

		if (number >= 100 && number <= 999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 100) + " Hundred " + ConvertNumberToTextUsingRecursion(number % 100);
		}

		if (number >= 1000 && number <= 9999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 1000) + " Thousand " + ConvertNumberToTextUsingRecursion(number % 1000);
		}

		if (number >= 10000 && number <= 99999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 1000) + " Thousand " + ConvertNumberToTextUsingRecursion(number % 1000);
		}

		if (number >= 100000 && number <= 999999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 1000) + " Thousand " + ConvertNumberToTextUsingRecursion(number % 1000);
		}

		if (number >= 1000000 && number <= 9999999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 1000000) + " Million " + ConvertNumberToTextUsingRecursion(number % 1000000);
		}

		if (number >= 10000000 && number <= 99999999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 1000000) + " Million " + ConvertNumberToTextUsingRecursion(number % 1000000);
		}

		if (number >= 100000000 && number <= 999999999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 1000000) + " Million " + ConvertNumberToTextUsingRecursion(number % 1000000);
		}

		if (number >= 1000000000 && number <= 9999999999)
		{
			NumberAsString += ConvertNumberToTextUsingRecursion(number / 1000000000) + " Billion " + ConvertNumberToTextUsingRecursion(number % 1000000000);
		}

		return NumberAsString;

	}
	void ConvertNumberToText(long long int number)
	{
		_Value = ConvertNumberToTextUsingRecursion(number);
	}




};

