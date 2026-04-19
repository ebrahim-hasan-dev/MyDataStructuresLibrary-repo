#pragma once

#include "../Linear/Stack.h";


namespace PracticalOnStack
{
	namespace Internal
	{
		short GetPriorityOperator(char Operator)
		{
			enum Operators { openbracket = 0, add = 1, sub = 1, multi = 2, div = 2 };

			switch (Operator)
			{
			case '+':
			{
				return add;
			}
			case '-':
			{
				return sub;
			}
			case '/':
			{
				return div;
			}
			case '*':
			{
				return multi;
			}
			case '(':
			{
				return openbracket;
			}
			}
		}

		bool DoesOperator_1HavePriorityOverOperator_2(char Operator1, char Operator2)
		{
			short op1 = GetPriorityOperator(Operator1);
			short op2 = GetPriorityOperator(Operator2);

			return op1 > op2;
		}

		bool ItIsCharacterIDoNotNeed(char ch)
		{
			if (!isdigit(ch) && ch != '/' && ch != '*' && ch != '-' && ch != '+' && ch != '(' && ch != ')')
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		// ============================================================================================
		
		double Calc(char ch, double num1, double num2)
		{
			switch (ch)
			{
			case '+':
			{
				return num1 + num2;
			}
			case '-':
			{
				return num1 - num2;
			}
			case '/':
			{
				return num1 / num2;
			}
			case '*':
			{
				return num1 * num2;
			}

			}

		}
		
		double ConvertToDouble(string str)
		{
			double n = 0;

			for (short i = 0; i < str.length(); i++)
			{
				n = n * 10 + (str[i] - 48);
			}

			return n;
		}

		double MakeSureWeAreGetFullNumberPrefix(string str, short& index)
		{
			double num = 0;

			short n = 1;

			for (short i = index - 1; i >= 0; i--)
			{
				if (!isdigit(str[i]))
				{
					string NumAsString = str.substr(i + 1, n);
					num = ConvertToDouble(NumAsString);
					index = i;
					break;
				}

				n++;
			}

			return num;
		}		
	}


	string ConvertInfixToPrefix(string Exp)
	{
		string PreFix = "";

		Stack<char> s;

		for (short j = 0; j < Exp.length(); j++)
		{
			if (Internal::ItIsCharacterIDoNotNeed(Exp[j]))
				continue;

			else if (isdigit(Exp[j]))
			{
				if (!isdigit(Exp[j + 1]))
				{
					PreFix = Exp[j] + PreFix;

					// this -> ' ' must be here, becuase this function -> MakeSureWeAreGetFullNumber depend on excist space after number 
					PreFix = ' ' + PreFix;
				}
				else
				{
					string tmp = "";

					tmp += Exp[j];

					while (isdigit(Exp[j + 1]))
					{
						++j;

						tmp += Exp[j];
					}

					PreFix = tmp + PreFix;

					// this -> ' ' must be here, becuase this function -> MakeSureWeAreGetFullNumber depend on excist space after number 
					PreFix = ' ' + PreFix;
				}
			}

			else if (Exp[j] == '/' || Exp[j] == '*' || Exp[j] == '-' || Exp[j] == '+' || Exp[j] == '(')
			{
				if (s.IsEmpty() || Exp[j] == '(')
				{
					s.Push(Exp[j]);
				}
				else
				{
					while (!Internal::DoesOperator_1HavePriorityOverOperator_2(Exp[j], s.GetTop()))
					{
						PreFix = s.GetTop() + PreFix;
						PreFix = ' ' + PreFix;

						s.Pop();

						if (s.IsEmpty())
							break;
					}

					s.Push(Exp[j]);
				}
			}

			else if (Exp[j] == ')')
			{
				while (s.GetTop() != '(')
				{
					PreFix = s.GetTop() + PreFix;
					PreFix = ' ' + PreFix;
					s.Pop();
				}

				s.Pop();
			}

		}

		while (!s.IsEmpty())
		{
			PreFix = s.GetTop() + PreFix;
			s.Pop();
		}

		return PreFix;
	}

	double PerformExpressionEvaluationPrefix(string Exp)
	{
		Exp = ConvertInfixToPrefix(Exp);

		Stack<double> s;

		for (short i = Exp.length() - 1; i >= 0; i--)
		{
			if (isdigit(Exp[i]))
			{
				s.Push(Internal::MakeSureWeAreGetFullNumberPrefix(Exp, i));
			}

			else if (Exp[i] == '/' || Exp[i] == '*' || Exp[i] == '-' || Exp[i] == '+')
			{
				double SecondOperand = s.GetTop();
				s.Pop();

				double FirstOperand = s.GetTop();
				s.Pop();

				s.Push(Internal::Calc(Exp[i], FirstOperand, SecondOperand));
			}
		}

		return s.GetTop();
	}


}