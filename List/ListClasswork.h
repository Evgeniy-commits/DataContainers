#pragma once

#include "ListClasswork.cpp"
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

#define tab  "\t"
#define delimiter "\n-------------------------------------------------------\n"


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
	}*Head, * Tail;

	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		T operator*() const;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		T& operator*();
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp);
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
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	List<T>& operator=(const List<T>& other);

	// Adding Elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	// Removing Elements
	void pop_front();
	void pop_back();
	void erase(int Index);

	//    Methods
	void print()const;
	void reverse_print()const;
};

template<typename T> List<T> operator+ (const List<T>& left, const List<T>& right);

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) : Data(Data), pNext(pNext), pPrev(pPrev) {}
template<typename T> List<T>::Element:: ~Element() {}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) : Temp(Temp) {}
template<typename T> List<T>::ConstBaseIterator:: ~ConstBaseIterator() {}
template<typename T> bool List<T>::ConstBaseIterator:: operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator:: operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> T List<T>::ConstBaseIterator:: operator*() const
{
	return Temp->Data;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ConstIterator::ConstIterator(Element* Temp) : ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstIterator:: ~ConstIterator() {}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator:: operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator:: operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator:: operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator:: operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstReverseIterator:: ~ConstReverseIterator() {}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::Iterator::Iterator(Element* Temp) : ConstIterator(Temp) {}
template<typename T> List<T>::Iterator:: ~Iterator() {}
template<typename T> T& List<T>::Iterator:: operator*()
{
	return ConstBaseIterator::Temp->Data;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ReverseIterator::ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
template<typename T> List<T>::ReverseIterator:: ~ReverseIterator() {}
template<typename T> T& List<T>::ReverseIterator:: operator*()
{
	return ConstBaseIterator::Temp->Data;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> typename List<T>::ConstIterator List<T>::begin() const
{
	return Head;
}
template<typename T> typename List<T>::ConstIterator List<T>::end() const
{
	return nullptr;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::rbegin() const
{
	return Tail;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::rend() const
{
	return nullptr;
}
template<typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) : List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}
	cout << "ILConstructor:\t " << endl;
}

template<typename T> List<T>::List(const List<T>& other)
{
	*this = other;
}
template<typename T> List<T>:: ~List()
{
	while (Head) pop_front();
	cout << "LDestructor:\t" << this << endl;
}

template<typename T> List<T>& List<T>:: operator=(const List<T>& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////

// Adding Elements:

template<typename T> void List<T>::push_front(T Data)
{
	Element* New = new Element(Data);
	if (Head == nullptr)
	{
		Head = Tail = New;
		size++;
		return;
	}
	else
	{
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
	}
	//Head = Head->pPrev = new Element(Data, Head, nullptr);
	size++;
}

template<typename T> void List<T>::push_back(T Data)
{
	Element* New = new Element(Data);
	if (Tail == nullptr)
	{
		Head = Tail = New;
		size++;
		return;
	}
	else
	{
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
	}
	//Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}

template<typename T> void List<T>::insert(T Data, int Index)
{
	if (Index < 0) return;
	if (Index == 0 || size == 0) return push_front(Data);
	if (Index >= size) return push_back(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
	}
	Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}


///////////////////////////////////////////////////////////////////////////////////////

// Removing Elements

template<typename T> void List<T>::pop_front()
{
	if (Head == nullptr) return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}

template<typename T> void List<T>::pop_back()
{
	if (Tail == nullptr) return;
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}

template<typename T> void List<T>::erase(int Index)
{
	if (Index < 0) return;
	if (Index == 0 || size == 0) return pop_front();
	if (Index >= size) return pop_back();
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
	}
	Element* Erase = Temp;
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Erase;
	size--;
}

///////////////////////////////////////////////////////////////////////////////////////

//    Methods
template<typename T> void List<T>::print()const
{
	cout << delimiter << endl;
	cout << Head << endl;
	cout << delimiter << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << delimiter << endl;
	cout << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << delimiter << endl;
}

template<typename T> void List<T>::reverse_print()const
{
	cout << delimiter << endl;
	cout << Tail << endl;
	cout << delimiter << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << delimiter << endl;
	cout << Head << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << delimiter << endl;
}

///////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T> operator+ (const List<T>& left, const List<T>& right)
{
	List<T> fusion = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		fusion.push_back(*it);
	}
	return fusion;
}
