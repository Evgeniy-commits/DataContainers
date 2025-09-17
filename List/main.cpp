#include <iostream>
#include <time.h>
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
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;

	size_t size;
	class ConstBaseIterator 
	{
		//Этот класс обобщает свойсва разных итераторов
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr): Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		int operator*() const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator: public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp) {};
		~ConstIterator() {};
		ConstIterator operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp) {};
		~ConstReverseIterator() {};
		ConstReverseIterator operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp): ConstIterator(Temp) {}
		~Iterator(){}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	ConstIterator begin() const
	{
		return Head;
	}
	ConstIterator end() const
	{
		return nullptr;
	}
	ConstReverseIterator rbegin() const
	{
		return Tail;
	}
	ConstReverseIterator rend() const
	{
		return nullptr;
	}
	Iterator begin() 
	{
		return Head;
	}
	Iterator end() 
	{
		return nullptr;
	}
	ReverseIterator rbegin() 
	{
		return Tail;
	}
	ReverseIterator rend() 
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) : List()
	{
		for (T const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
		cout << "ILConstructor:\t " << endl;
	}

	List(const List<T>& other)
	{
		*this = other;
	}
	~List()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	List<T>& operator=(const List<T>& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
	}
	// Adding Elements:
	void push_front(T Data)
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
	void push_back(T Data)
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

	void insert(T Data, int Index)
	{
		if (Index < 0) return;
		if (Index == 0 || size == 0) return push_front(Data);
		if (Index >= size) return push_back(Data);
		//1) Доходим до нужного элемента
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
		//2) Создаем добавляемый элемент
		Element* New = new Element(Data);
		//3) Пристыковываем новый элемент к списку
		New->pNext = Temp;
		//4) Пристыковываем предыдущий элемент к новому
		New->pPrev = Temp->pPrev;
		//5) Говорим списку, где новый элемент
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	// Removing Elements

	void pop_front()
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

	void pop_back()
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

	void erase(int Index)
	{
		if (Index < 0) return;
		if (Index == 0 || size == 0) return pop_front();
		if (Index >= size) return pop_back();
		//1) Доходим до нужного элемента
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
		//2) Создаем удаляемый элемент
		Element* Erase = Temp;
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Erase;
		size--;
	}

	//    Methods
	void print()const
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

	void reverse_print()const
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
};

template<typename> List operator+ (const List<T>& left, const List<T>& right)
{
	List fusion = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		fusion.push_back(*it);
	}
	return fusion;
}


//#define BASE_CHECK
#define CHECK_CODE

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "List filled. " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
	//list.pop_front();
	list.print();
	//list.reverse_print();
	//list.pop_back();
	//list.print();
	int Index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.erase(Index);
	list.print();
#endif // BASE_CHECK
#ifdef CHECK_CODE
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	list1.print();
	list2.print();
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	for (List::ConstIterator it = list1.begin(); it != list1.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (List::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 100;
		cout << *it << tab;
	}
	cout << endl;
	for (List::ConstReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // CHECK_CODE

}
