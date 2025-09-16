#pragma once

#include <iostream>
#include <time.h>
using namespace std;

#define tab  "\t"
#define delimiter "\n-------------------------------------------------------------\n"

template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		 Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	} *Head, * Tail;

	size_t size;
public:
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		T operator*() const;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp) : ConstIterator(Temp) {}
		~Iterator();
		T& operator*();
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
		~ReverseIterator();
		T& operator*();
	};

	ConstIterator begin() const;
	ConstIterator end() const;
	ConstReverseIterator rbegin() const;
	ConstReverseIterator rend() const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	explicit List(int size);
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	List(List<T>&& other) noexcept;
	~List();


	//      Operators
	List<T>& operator=(const List<T>& other);
	List<T>& operator=(List<T>&& other) noexcept;
	T operator[] (int index) const;
	T& operator[] (int index);

	//		Adding elements
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);
	void filling(int size);

	//			Removing elements
	void pop_front();
	void pop_back();
	void erase(int Index);


	//		Methods:

	void print()const;
	void reverse_print()const;

	friend const List<T> operator+(const List<T>& left, const List<T>& right)
	{
		List<T> fusion = left;
		for (List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
		{
			fusion.push_back(*it);
		}
		return fusion;
	}
};

