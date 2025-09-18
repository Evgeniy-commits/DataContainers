#include <iostream>
#include <time.h>
using namespace std;

#define tab  "\t"
#define delimiter "\n-------------------------------------------------------------\n"

template<typename T> class ForwardList;
template<typename T> class Element;
template<typename T> class Iterator;

template<typename T> class Element
{
	T Data;
	Element* pNext;
public:
	Element(T Data, Element* pNext = nullptr);
	~Element();	
	friend class Iterator<T>;
	friend class ForwardList<T>;
};

template<typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr); 
	~Iterator();
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator& other)const;
	bool operator!=(const Iterator& other)const;
	T operator*() const;
	T& operator*();
};

template<typename T> class ForwardList
{
	Element<T>* Head;
	size_t size;
public:
	Element<T>* get_Head() const;
	size_t get_size() const;
	Iterator<T> begin() const;
	Iterator<T> end() const;
	ForwardList();
	explicit ForwardList(int size);
	ForwardList(const std::initializer_list<T>& il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other) noexcept;
	~ForwardList();
	
	//      Operators
	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other) noexcept;
	T operator[] (int index) const;
	T& operator[] (int index);
	
	//		Adding elements
	void push_front(T Data);	
	void push_back(T Data);
	void insert(T Data, int Index);
	
	//			Removing elements
	void pop_front();
	void pop_back();

	//		Methods:
	void print() const;
	void revers();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

	template<typename T> Element<T>:: Element(T Data, Element* pNext)
	{
		this->Data = Data;
		this->pNext = pNext;
	}
	template<typename T> Element<T>::~Element() {}
	
///////////////////////////////////////////////////////////////////////////////

	template<typename T> Iterator<T>:: Iterator(Element<T>* Temp) : Temp(Temp) {}
	template<typename T> Iterator<T>:: ~Iterator() {}
	template<typename T> typename Iterator<T>& Iterator<T>:: operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	template<typename T> typename Iterator<T> Iterator<T>:: operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	template<typename T> bool Iterator<T>:: operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	template<typename T> bool Iterator<T>:: operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	template<typename T> T Iterator<T>:: operator*() const
	{
		return Temp->Data;
	}
	template<typename T> T& Iterator<T>:: operator*()
	{
		return Temp->Data;
	}

	///////////////////////////////////////////////////////////////////////////////

	template <typename T> Element<T>* ForwardList<T>:: get_Head() const
	{
		return Head;
	}
	template <typename T> size_t ForwardList<T>:: get_size() const
	{
		return size;
	}
	template <typename T> Iterator<T> ForwardList<T>:: begin() const
	{
		return Head;
	}
	template <typename T> Iterator<T> ForwardList<T>:: end() const
	{
		return nullptr;
	}
	template <typename T> ForwardList<T>::ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	template <typename T> ForwardList<T>:: ForwardList(int size) :ForwardList()
	{
		while (size--) push_front(0);
		cout << "FLSizeConstructor:\t" << this << endl;
	}
	template <typename T> ForwardList<T>:: ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		cout << "FLItConstructor:\t" << this << endl;
	}
	template <typename T> ForwardList<T>:: ForwardList(const ForwardList<T>& other) : ForwardList()
	{
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	template <typename T> ForwardList<T>:: ForwardList(ForwardList<T>&& other) noexcept : ForwardList()
	{
		*this = std::move(other);
		cout << "FLMoveConstructor:\t" << this << endl;
	}
	template <typename T> ForwardList<T>:: ~ForwardList()
	{
		clock_t t_start = clock();
		while (Head) pop_front();
		clock_t t_end = clock();
		cout << "FLDestructor:\t" << this << "\tcomplete for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
	}

///////////////////////////////////////////////////////////////////////////////

	template <typename T> ForwardList<T>& ForwardList<T>:: operator=(const ForwardList<T>& other)
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		revers();
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}
	template <typename T> ForwardList<T>& ForwardList<T>:: operator=(ForwardList<T>&& other) noexcept
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "FLMoveAssignment:\t" << this << endl;
		return *this;
	}

	template <typename T> T ForwardList<T>:: operator[] (int index) const
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
		return Temp->Data;
	}

	template <typename T> T& ForwardList<T>:: operator[] (int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
		return Temp->Data;
	}

	//		Adding elements
	template <typename T> void ForwardList<T>:: push_front(T Data)
	{
		Head = new Element<T>(Data, Head);
		size++;
	}
	template <typename T> void ForwardList<T>:: push_back(T Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element<T>* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	template <typename T> void ForwardList<T>:: insert(T Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		if (Index >= size) return push_back(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//			Removing elements
	template <typename T> void ForwardList<T>::pop_front()
	{
		Element<T>* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}

	template <typename T> void ForwardList<T>::pop_back()
	{
		if (!Head || Head->pNext == nullptr) return pop_front();
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}


	//		Methods:
	template <typename T> void ForwardList<T>:: print()const
	{
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}

	template <typename T> void ForwardList<T>:: revers()
	{
		ForwardList<T> revers;
		while (Head)
		{
			revers.push_front(Head->Data);
			pop_front();
		}
		*this = std::move(revers);
		revers.Head = nullptr;
	}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> fusion = left;
	for (Iterator<T> it = right.begin(); it != right.end(); ++it)
	{
		fusion.push_back(*it);
	}
	//fusion.revers();
	return fusion;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
#define CHECK_CODE

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	list.print();
	/*int Index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, Index);
	list.print();*/
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	//list1.print();
	for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab; cout << endl;

	ForwardList list2;
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

	//ForwardList fusion = list1 + list2;  //CopyConstructor
	ForwardList list3;
	cout << delimiter << endl;
	list3 = list1 + list2;   //CopyAssignment
	cout << delimiter << endl;
	for (int i = 0; i < list3.get_size(); i++) cout << list3[i] << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();

	cout << "ForwardList filled. " << double(t_end - t_start)/CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif // PERFORMANCE_CHECK

#ifdef SUBSCRIPT_OPERATOR_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list(n);
	clock_t t_start = clock();
	for (int i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;
	clock_t t_end = clock();
	cout << "ForwardList filled. " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("Pause");
	//for (int i = 0; i < list.get_size(); i++) cout << list[i] << tab;
	//cout << endl;  
#endif // SUBSCRIPT_OPERATOR_CHECK

#ifdef COPY_SEMANTIC_PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	clock_t t_start, t_end;
	ForwardList list1;
	t_start = clock();
	for (int i = 0; i < n; i++)
		list1.push_front(rand() % 100);
	t_end = clock();
	cout << "ForwardList filled. " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("Pause");
	t_start = clock();
	ForwardList list2 = list1;
	t_end = clock();
	cout << "Copying complete for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	cout << endl;
	/*for (int i = 0; i < list1.get_size(); i++) cout << list1[i] << tab;
	cout << endl;
	for (int i = 0; i < list2.get_size(); i++) cout << list2[i] << tab;
	cout << endl;*/
#endif // COPY_SEMANTIC_PERFORMANCE_CHECK

#ifdef MOVE_SEMANTIC_CHECK
	ForwardList list1;
	ForwardList list2;
	clock_t t_start, t_end;

	t_start = clock();
	for (int i = 0; i < 30000000; i++) list1.push_front(rand());
	for (int i = 0; i < 30000000; i++) list2.push_front(rand());
	t_end = clock();
	cout << "ForwardList12 filled " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("Pause");

	t_start = clock();
	ForwardList list3 = list1 + list2;
	t_end = clock();
	cout << "ForwardList3 filled " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	t_start = clock();
	ForwardList list4 = list3;
	t_end = clock();
	cout << "ForwardList4 filled " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
#endif // MOVE_SEMANTIC_CHECK

#ifdef CHECK_CODE
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	for (int i : list) cout << i << tab; cout << endl;
	cout << delimiter << endl;
	for (Iterator<int> it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << delimiter << endl;
	ForwardList<int> list1 = { 3, 5, 8, 13, 21 };
	ForwardList<int> list2 = { 34, 55, 89 };
	list1.print();
	list2.print();
	cout << delimiter << endl;
	ForwardList<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	cout << delimiter << endl;
	for (Iterator<int> it = list1.begin(); it != list1.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (Iterator<int> it = list2.begin(); it != list2.end(); ++it)
	{
		//*it *= 100;
		cout << *it << tab;
	}
	cout << endl;
	for (Iterator<int> it = list3.begin(); it != list3.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // CHECK_CODE
}
