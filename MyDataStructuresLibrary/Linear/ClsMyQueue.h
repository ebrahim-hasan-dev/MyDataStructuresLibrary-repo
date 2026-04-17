#pragma once

#include <iostream>
using namespace std;

#include "DoublyLinkedList.h"



template <class T>
class ClsMyQueue
{
protected:

	DoublyLinkedList<T> _queue;
	
public:

	void Push(T Element)
	{
		_queue.InsertInLast(Element);
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
		return _queue.GetHead();	
	}

	T GetBack()
	{
		return _queue.GetTail();
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
		return _queue.Size();
	}

	bool IsFound(T Element)
	{
		return _queue.IsFound(Element);
	}

	// here we must use & because not destractor call towice and delete same places towice, one here and one in fanction main  
	void Copy(ClsMyQueue<T>& CopyQueue)
	{
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



	~ClsMyQueue()
	{
		Clear();
	}



};

