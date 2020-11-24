#ifndef __TURN_H__
#define __TURN_H__

const int MaxTurnSize = 10000;

template <class T>
class Turn
{
	T *p_mem;//– указатель на память, выделенную для кольцевого буфера
	int size;//размер памяти
	int data_count;//кол-во запомненых в оцереди значений
	int first_index;
	int last_index;
	int GetNextIndex(int index);
public:
	Turn();
	Turn(int _size);
	~Turn();
	bool IsEmpty();
	bool IsFull();
	void Put(T & elem);
	T Get();
	int Cardinality();
	int GetSize();
	T ViewTheFirst();
};

template <class T>
Turn<T>::Turn() : size(10), first_index(0), data_count(0), last_index(-1)
{
	p_mem = new T[size];
}


template <class T>
Turn<T>::Turn(int _size) : size(_size), first_index(0), data_count(0), last_index(-1)
{
	if ((size < 1) || (size > MaxTurnSize))
		throw size;
	p_mem = new T[size];
}

template <class T>
Turn<T>::~Turn()
{
	delete[] p_mem;
	p_mem = nullptr;
}

template <class T>
bool Turn<T>::IsEmpty()
{
	if (data_count == 0) return 1;
	return 0;
}

template <class T>
bool Turn<T>::IsFull()
{
	if (data_count == size) return 1;
	return 0;
}

template <class T>
int Turn<T>::GetNextIndex(int index)
{
	if (index == size - 1)
		return 0;
	else
		return ++index;
}


template <class T>
void Turn<T>::Put(T & elem)
{
	if (IsFull())
		throw - 1;
	data_count++;
	last_index = GetNextIndex(last_index);
	p_mem[last_index] = elem;
}

template <class T>
T Turn<T>::Get()
{
	if (IsEmpty())
		throw - 1;
	T res = p_mem[first_index];
	first_index = GetNextIndex(first_index);
	data_count--;
	return res;
}

template <class T>
int Turn<T>::Cardinality()
{
	return data_count;
}

template <class T>
int Turn<T>::GetSize()
{
	return size;
}

template <class T>
T Turn<T>::ViewTheFirst()
{
	if (IsEmpty())
		throw - 1;
	return p_mem[first_index];
}

#endif 
