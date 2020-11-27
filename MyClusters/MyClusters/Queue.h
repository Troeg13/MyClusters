#ifndef __Queue_H__
#define __Queue_H__

const int MaxQueueSize = 10000;

template <class T>
class Queue
{
	T *p_mem;// указатель на память, выделенную для кольцевого буфера
	int size;//размер памяти
	int data_count;//кол-во запомненных в очереди значений
	int first_index;
	int last_index;
	int GetNextIndex(int index);
public:
	Queue();
	Queue(int _size);
	~Queue();
	bool IsEmpty();
	bool IsFull();
	void Put(T & elem);
	T Get();
	int Cardinality();
	int GetSize();
	T ViewTheFirst();
};


template <class T>
Queue<T>::Queue() : size(10), first_index(0), data_count(0), last_index(-1)
{
	p_mem = new T[size];
}

template <class T>
Queue<T>::Queue(int _size) : size(_size), first_index(0), data_count(0), last_index(-1)
{
	if ((size < 1) || (size > MaxQueueSize))
		throw size;
	p_mem = new T[size];
}

template <class T>
Queue<T>::~Queue()
{
	delete[] p_mem;
	p_mem = nullptr;
}

template <class T>
bool Queue<T>::IsEmpty()
{
	if (data_count == 0) return 1;
	return 0;
}

template <class T>
bool Queue<T>::IsFull()
{
	if (data_count == size) return 1;
	return 0;
}

template <class T>
int Queue<T>::GetNextIndex(int index)
{
	if (index == size - 1)
		return 0;
	else
		return ++index;
}

template <class T>
void Queue<T>::Put(T & elem)
{
	if (IsFull())
		throw - 1;
	data_count++;
	last_index = GetNextIndex(last_index);
	p_mem[last_index] = elem;
}

template <class T>
T Queue<T>::Get()
{
	if (IsEmpty())
		throw - 1;
	T res = p_mem[first_index];
	first_index = GetNextIndex(first_index);
	data_count--;
	return res;
}

template <class T>
int Queue<T>::Cardinality()
{
	return data_count;
}

template <class T>
int Queue<T>::GetSize()
{
	return size;
}

template <class T>
T Queue<T>::ViewTheFirst()
{
	if (IsEmpty())
		throw - 1;
	return p_mem[first_index];
}

#endif 
