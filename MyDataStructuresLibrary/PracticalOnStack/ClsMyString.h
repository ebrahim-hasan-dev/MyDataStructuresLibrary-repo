#pragma once

#include <iostream>
using namespace std;

#include "../Linear/ClsMyStackArr.h";


namespace PracticalOnStack
{
	class ClsMyString
	{
	private:

		string _Value;

		ClsMyStackArr <string> sUndo;
		ClsMyStackArr <string> sRedo;

	public:

		ClsMyString()
		{
			_Value = "";
		}


		string GetValue()
		{
			return _Value;
		}

		void SetValue(string Value)
		{
			sUndo.Push(_Value);
			_Value = Value;
		}

		__declspec(property(get = GetValue, put = SetValue)) string Value;


		void Undo()
		{
			if (!sUndo.IsEmpty())
			{
				sRedo.Push(_Value);
				_Value = sUndo.GetTop();
				sUndo.Pop();
			}
		}

		void Redo()
		{
			if (!sRedo.IsEmpty())
			{
				sUndo.Push(_Value);
				_Value = sRedo.GetTop();
				sRedo.Pop();
			}
		}


	};

}

// This is an example of how to test this class in the main function 

//int main()
//{
//	ClsMyString s;
//
//	cout << "s1  = " << s.Value << "\n";
//
//	s.Value = "Mohammed";
//
//	cout << "s1  = " << s.Value << "\n";
//
//	s.Value = "Mohammed2";
//
//	cout << "s1  = " << s.Value << "\n";
//
//	s.Value = "Mohammed3";
//
//	cout << "s1  = " << s.Value << "\n";
//
//	cout << "\n\nUndo:\n";
//	cout << "\n-----------\n";
//
//	s.Undo();
//	cout << "s1 after Undo  = " << s.Value << "\n";
//
//	s.Undo();
//	cout << "s1 after Undo  = " << s.Value << "\n";
//
//	s.Undo();
//	cout << "s1 after Undo  = " << s.Value << "\n";
//
//
//	cout << "\n\nRedo:\n";
//	cout << "\n-----------\n";
//
//	s.Redo();
//	cout << "s1 after Redo  = " << s.Value << "\n";
//
//	s.Redo();
//	cout << "s1 after Redo  = " << s.Value << "\n";
//
//	s.Redo();
//	cout << "s1 after Redo  = " << s.Value << "\n";
//
// 
//	return 0;
//}
