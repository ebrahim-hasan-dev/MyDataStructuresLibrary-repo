#pragma once

#include "../Linear/StackUsingArray.h";


namespace PracticalOnStack
{
	namespace Internal
	{
		bool ArePair(char open, char close)
		{
			if (open == '(' && close == ')')
			{
				return true;
			}

			else if (open == '[' && close == ']')
			{
				return true;
			}

			else if (open == '{' && close == '}')
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}

	bool AreBalanced(string Exp)
	{
		StackUsingArray<char> stack;

		for (short i = 0; i < Exp.length(); i++)
		{
			if (Exp[i] == '{' || Exp[i] == '[' || Exp[i] == '(')
			{
				stack.push(Exp[i]);
			}

			else if (Exp[i] == '}' || Exp[i] == ']' || Exp[i] == ')')
			{
				if (stack.IsEmpty() || Internal::ArePair(stack.GetTop(), Exp[i]) == false)
				{
					return false;
				}
				else
				{
					stack.pop();
				}

			}
		}

		return stack.IsEmpty();

	}

}