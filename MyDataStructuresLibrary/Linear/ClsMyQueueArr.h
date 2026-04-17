#pragma once

#include <iostream>
using namespace std;

#include "ArrayBasedList.h"


template <class T>
class ClsMyQueueArr
{
protected:

	ArrayBasedList<T> _queue;

public:

	void Push(T Element)
	{
		_queue.Push_Back(Element);
	}

	void Pop()
	{
		_queue.DeleteFirst();
	}

	bool IsEmpty()
	{
		return _queue.IsEmpty();
	}

	T GetFront()
	{
		return _queue.GetItem(0);
	}

	T GetBack()
	{
		return _queue.GetLastItem();
	}

	bool IsFull()
	{
		return _queue.IsFull();
	}

	void Fill()
	{
		_queue.Fill();
	}

	void DisPlay()
	{
		_queue.DisPlay();
	}

	int Size()
	{
		return _queue.GetLength();
	}

	bool IsFound(T Element)
	{
		return _queue.Find(Element) != -1;
	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(ClsMyQueueArr<T>& CopyQueue)
	{
		_queue.Resize(CopyQueue._queue.GetSize());

		_queue.Copy(CopyQueue._queue);
	}

	T GetItem(int index)
	{
		return _queue.GetItem(index);
	}

	void UpdateItem(int index, T item)
	{
		_queue.UpdateItem(index, item);
	}

	void Clear()
	{
		_queue.Clear();
	}



	~ClsMyQueueArr()
	{
		_queue.~ArrayBasedList();
	}



};

