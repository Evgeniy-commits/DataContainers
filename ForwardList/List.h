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

template<typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev) {
}
template<typename T> List<T>::Element::~Element() {}

///////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) : Temp(Temp) {}
template<typename T> List<T>::ConstBaseIterator::~ConstBaseIterator() {}
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

///////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ConstIterator:: ConstIterator(Element* Temp) : ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstIterator:: ~ConstIterator() {}

template<typename T> auto List<T>::ConstIterator:: operator++() -> List<T>::ConstIterator&
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> auto List<T>::ConstIterator:: operator++(int) -> List<T>::ConstIterator
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> auto List<T>::ConstIterator:: operator--() -> List<T>::ConstIterator&
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> auto List<T>::ConstIterator:: operator--(int) -> List<T>::ConstIterator
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp) {}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator() {}
template<typename T> auto List<T>::ConstReverseIterator:: operator++() -> List<T>::ConstReverseIterator&
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> auto List<T>::ConstReverseIterator:: operator++(int) -> List<T>::ConstReverseIterator
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> auto List<T>::ConstReverseIterator:: operator--() -> List<T>::ConstReverseIterator&
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> auto List<T>::ConstReverseIterator:: operator--(int) -> List<T>::ConstReverseIterator
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//template<typename T> List<T>::Iterator::Iterator(Element* Temp) : ConstIterator(Temp) {}
template<typename T> List<T>::Iterator::~Iterator() {}
template<typename T> T& List<T>::Iterator:: operator*()
{
	return ConstBaseIterator::Temp->Data;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

//template<typename T> List<T>::ReverseIterator::ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
template<typename T> List<T>::ReverseIterator::~ReverseIterator() {}
template<typename T> T& List<T>::ReverseIterator:: operator*()
{
	return ConstBaseIterator::Temp->Data;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> auto List<T>::begin() const -> List<T>::ConstIterator
{
	return Head;
}
template<typename T> auto List<T>::end() const -> List<T>::ConstIterator
{
	return nullptr;
}
template<typename T>  auto List<T>::rbegin() const -> List<T>::ConstReverseIterator
{
	return Tail;
}
template<typename T>  auto List<T>::rend() const -> List<T>::ConstReverseIterator
{
	return nullptr;
}
template<typename T> auto List<T>::begin() -> List<T>::Iterator
{
	return Head;
}
template<typename T>  auto List<T>::end() -> List<T>::Iterator
{
	return nullptr;
}
template<typename T>  auto List<T>::rbegin() -> List<T>::ReverseIterator
{
	return Tail;
}
template<typename T> auto List<T>::rend() -> List<T>::ReverseIterator
{
	return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
}
template<typename T> List<T>::List(int size) : List()
{
	while (size--) push_front(0);
	cout << "LSizeConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) : List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
	cout << "LItConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(List<T>&& other) noexcept : List()
{
	*this = std::move(other);
	cout << "LMoveConstructor:\t" << this << endl;
}
template<typename T> List<T>::~List()
{
	clock_t t_start = clock();
	while (Head) pop_front();
	clock_t t_end = clock();
	cout << "LDestructor:\t" << this << "\tcomplete for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
}
template<typename T>  List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other) return *this;
	while (Head) pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);

	cout << "FLCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T> List<T>& List<T>::operator=(List<T>&& other) noexcept
{
	if (this == &other) return *this;
	while (Head) pop_front();
	this->Head = other.Head;
	this->Tail = other.Tail;
	this->size = other.size;
	other.Head = nullptr;
	other.Tail = nullptr;
	other.size = 0;
	cout << "FLMoveAssignment:\t" << this << endl;
	return *this;
}
template<typename T> T List<T>::operator[] (int index) const
{
	Element* Temp = Head;
	for (int i = 0; i < index; i++) Temp = Temp->pNext;
	return Temp->Data;
}
template<typename T> T& List<T>::operator[] (int index)
{
	Element* Temp = Head;
	for (int i = 0; i < index; i++) Temp = Temp->pNext;
	return Temp->Data;
}
template<typename T> void List<T>::push_front(T Data)
{
	if (Head == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Head = Head->pPrev = new Element(Data, Head, nullptr);
	size++;
}
template<typename T> void List<T>::push_back(T Data)
{

	if (Head == nullptr && Tail == nullptr) return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
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
template<typename T> void List<T>::pop_front()
{
	if (Head == nullptr) return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T> void List<T>::pop_back()
{
	if (Head == Tail) return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
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
template<typename T>void List<T>::reverse_print()const
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