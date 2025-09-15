#include <iostream>
#include <time.h>
using namespace std;

#define tab  "\t"
#define delimiter "\n-------------------------------------------------------------\n"

template<typename T> class List
{
	class Element
	{	T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
		friend class Iterator;
		friend class ReverseIterator;
		friend List<T> operator+(const List<T>& left, const List<T>& right);
	} *Head, * Tail;

private:
	size_t size;
public:
	class Iterator
	{
	protected:
		Element* Temp;
	public:

		Iterator(Element* Temp = nullptr);
		~Iterator();
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		bool operator==(const Iterator& other)const;
		bool operator!=(const Iterator& other)const;
		T operator*() const;
		T& operator*();
		friend class List;
		friend List<T> operator+(const List<T>& left, const List<T>& right);
	};

	class ReverseIterator
	{
	protected:
		Element* Temp;
	public:
		ReverseIterator(Element* Temp);
		~ReverseIterator();
		ReverseIterator& operator++();
		ReverseIterator operator++(int);
		ReverseIterator& operator--();
		ReverseIterator operator--(int);
		bool operator==(const ReverseIterator& other)const;
		bool operator!=(const ReverseIterator& other)const;
		T operator*()const;		
		T& operator*();
		friend class List;
		friend List<T> operator+(const List<T>& left, const List<T>& right);
	};
public:
	Element* get_Head() const;	
	Element* get_Tail() const;
	size_t get_size() const;
	Iterator begin() const;
	Iterator end() const;
	ReverseIterator rbegin() const;
	ReverseIterator rend() const;
	
	List(Element* Head = nullptr, Element* Tail = nullptr, int size = 0);
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
	void revers();
	friend Element;
	friend Iterator;
	friend ReverseIterator;
	friend List<T> operator+(const List<T>& left, const List<T>& right);
};

template <typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
	List fusion;
	for (List::Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	for (List::Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	fusion.revers();
	return fusion;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define CHECK_CODE

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List<double> list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back((double)(rand() % 100)/10);
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
	//int value;
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.erase(Index);
	list.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	List list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	//list1.print();
	for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab; cout << endl;

	List list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	//list2.print();
	for (int i = 0; i < list2.get_size(); i++) cout << list2[i] << tab; cout << endl;

	/*int Index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.print();
	list2.print();
	list1.insert(value, Index);*/

	//List fusion = list1 + list2;  //CopyConstructor
	List list3;
	cout << delimiter << endl;
	list3 = list1 + list2;   //CopyAssignment
	cout << delimiter << endl;
	for (int i = 0; i < list3.get_size(); i++) cout << list3[i] << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "List filled. " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK

#ifdef SUBSCRIPT_OPERATOR_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list(n);
	clock_t t_start = clock();
	for (int i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;
	clock_t t_end = clock();
	cout << "List filled. " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("Pause");
	//for (int i = 0; i < list.get_size(); i++) cout << list[i] << tab;
	//cout << endl;  
#endif // SUBSCRIPT_OPERATOR_CHECK

#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	clock_t t_start, t_end;
	List list1;
	t_start = clock();
	for (int i = 0; i < n; i++)
		list1.push_front(rand() % 100);
	t_end = clock();
	cout << "List filled. " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("Pause");
	t_start = clock();
	List list2 = list1;
	t_end = clock();
	cout << "Copying complete for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	cout << endl;
	/*for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab;
	cout << endl;
	for (int i = 0; i < list2.get_size(); i++) cout << list2[i] << tab;
	cout << endl;*/
#endif // COPY_SEMANTIC_PERFORMANCE_CHECK

#ifdef MOVE_SEMANTIC_CHECK
	List list1;
	List list2;
	clock_t t_start, t_end;

	t_start = clock();
	for (int i = 0; i < 1500000; i++) list1.push_front(rand());
	for (int i = 0; i < 1500000; i++) list2.push_front(rand());
	t_end = clock();
	cout << "List12 filled " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("Pause");

	t_start = clock();
	List list3 = list1 + list2;
	t_end = clock();
	cout << "List3 filled " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	t_start = clock();
	List list4 = list3;
	t_end = clock();
	cout << "List4 filled " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for - for для диапазонаю Под диапазоном понимается контейнер
	//(какой-то набор элементов)

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << typeid(arr).name() << endl;
	print(arr);
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list) cout << i << tab; cout << endl;
	cout << delimiter << endl;
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

#ifdef CHECK_CODE
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	//List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	//for (int i : list3)cout << i << tab; cout << endl;
#endif // CHECK_CODE
}

template<typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev): 
	Data(Data), pNext(pNext), pPrev(pPrev) {}
template<typename T> List<T>::Element::~Element() {}
template<typename T> List<T>::Iterator::Iterator(Element* Temp)
{
	this->Temp = Temp;
	cout << "ITConstructor:\t" << this << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::Iterator::~Iterator()
{
	cout << "ITDestructor:\t" << this << endl;
}
template<typename T> List<T>::Iterator& List<T>::Iterator:: operator++()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T> List<T>::Iterator List<T>::Iterator:: operator++(int)
{
	Iterator old = *this;
	Temp = Temp->pNext;
	return old;
}
template<typename T> List<T>::Iterator& List<T>::Iterator:: operator--()
{
	Temp = Temp->pPrev;
	return *this;
}
template<typename T> List<T>::Iterator List<T>::Iterator:: operator--(int)
{
	Iterator old = *this;
	Temp = Temp->pPrev;
	return old;
}
template<typename T> bool List<T>::Iterator::operator==(const Iterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::Iterator::operator!=(const Iterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> T List<T>::Iterator::operator*() const
{
	return Temp->Data;
}
template<typename T> T& List<T>::Iterator:: operator*()
{
	return Temp->Data;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::ReverseIterator::ReverseIterator(Element* Temp)
{
	this->Temp = Temp;
	cout << "RItConstructor:\t" << this << endl;
}
template<typename T> List<T>::ReverseIterator::~ReverseIterator()
{
	cout << "RItDestructor:\t" << this << endl;
}
template<typename T> List<T>::ReverseIterator& List<T>::ReverseIterator::operator++()
{
	Temp = Temp->pPrev;
	return *this;
}
template<typename T> List<T>::ReverseIterator List<T>::ReverseIterator::operator++(int)
{
	ReverseIterator old = *this;
	Temp = Temp->pPrev;
	return old;
}
template<typename T> List<T>::ReverseIterator& List<T>::ReverseIterator::operator--()
{
	Temp = Temp->pNext;
	return *this;
}
template<typename T> List<T>::ReverseIterator List<T>::ReverseIterator::operator--(int)
{
	ReverseIterator old = *this;
	Temp = Temp->pNext;
	return old;
}
template<typename T> bool List<T>::ReverseIterator::operator==(const ReverseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ReverseIterator::operator!=(const ReverseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> T List<T>::ReverseIterator::operator*() const
{
	return Temp->Data;
}
template<typename T> T& List<T>::ReverseIterator::operator*()
{
	return Temp->Data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T>::Element* List<T>::get_Head() const
{
	return Head;
}
template<typename T> List<T>::Element* List<T>:: get_Tail() const
{
	return Tail;
}
template<typename T> size_t List<T>:: get_size() const
{
	return size;
}
template<typename T> List<T>::Iterator List<T>::begin() const
{
	return Head;
}
template<typename T> List<T>::Iterator List<T>::end() const
{
	return nullptr;
}
template<typename T> List<T>::ReverseIterator List<T>::rbegin() const
{
	return Tail;
}
template<typename T> List<T>::ReverseIterator List<T>::rend() const
{
	return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
 
template<typename T> List<T>::List(Element* Head, Element* Tail, int size) 
{
	this->Head = Head;
	this->Tail = Tail;
	this->size = size;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(int size) : List()
{
	while (size--) push_front(0);
	cout << "LSizeConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	//cout << typeid(il.begin()).name() << endl;
	for (int const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
	cout << "LItConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const List<T>& other) : List()
{
	//Deep copy (побитовое копирование)
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(List<T>&& other) noexcept: List()
{
	//Shallow copy (поверхностное копирование)
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
	if (this == &other) return *this; //0) Проверить, что This и Other разные объекты
	while (Head) pop_front();         //1) Очистить данные
	//2)Deep copy (побитовое копирование)
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_front(Temp->Data);
	revers();
	cout << "FLCopyAssignment:\t" << this << endl;
	return *this;
}
template<typename T> List<T>&  List<T>::operator=(List<T>&& other) noexcept
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
template<typename T>void List<T>::revers()
{
	List revers;
	while (Head)
	{
		revers.push_front(Head->Data); //добавляем Головной элемент в реверсный список
		pop_front(); //удаляем начальный элемент списка
	}
	/*Head = revers.Head;
	size = revers.size;*/
	*this = std::move(revers); //встроенная функция, которая явным образом вызывает 
	//moveAssignment если он есть
	revers.Head = nullptr; //Поскольку реверсный список является локальной переменной ,
	// для него будет вызван деструктор, который полностью его очистит, а он указывает на ту же
	//память, что и наш объект, поэтому деструктор очистит полностью, чтобы этого не произошло
	//зануляем список.
}
