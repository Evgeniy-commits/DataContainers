//ForwardList
#include <iostream>
#include <time.h>
using namespace std;

#define tab  "\t"
#define delimiter "\n-------------------------------------------------------------\n"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}

	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	size_t size;
public:
	Element* get_Head() const
	{
		return Head;
	}
	size_t get_size() const
	{
		return size;
	}

	ForwardList()
	{
		Head = nullptr;
		size = 0;
		Element::count = 0;
		//если список пуст, то его Голова обязательно указывает на 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		//Deep copy (побитовое копирование)
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clock_t t_start = clock();
		while (Head) pop_front();
		clock_t t_end = clock();
		cout << "FLDestructor:\t" << this << "\tcomplete for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
	}

	//      Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this; //0) Проверить, что This и Other разные объекты
		while (Head) pop_front();         //1) Очистить данные
		//2)Deep copy (побитовое копирование)
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	//		Adding elements
	void push_front(int Data)
	{
		////1) Создаем элемент и сохраняем в него добавляемое значение:
		//Element* New = new Element(Data);

		////2) Привязываем новый, созданный элемент к началу списка:
		//New->pNext = Head;

		////3) Переносим Голову на новый элемент:
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{

		if (Head == nullptr) return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		if (Index >= size) return push_back(Data);
		//1) Доходим до нужного элемента (элемент перед добавляемым)
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;

		////2) Создаем добавляемый элемент
		//Element* New = new Element(Data);

		////3) Пристыковываем новый элемент к списку
		//New->pNext = Temp->pNext;

		////4) Пристыковываем предыдущий элемент к новому
		//Temp->pNext = New;

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//			Removing elements
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти:
		delete Erased;
		size--;
	}

	void pop_back()
	{
		if (!Head || Head->pNext == nullptr) return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}


	//		Methods:
	void print()const
	{
		/*Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/

		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList fusion;
	for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);
	return fusion;
}

//#define BASE_CHECK
#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK


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
	list1.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	/*int Index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.print();
	list2.print();
	list1.insert(value, Index);*/

	//ForwardList fusion = list1 + list2;  //CopyConstructor
	ForwardList fusion;
	cout << delimiter << endl;
	fusion = list1 + list2;   //CopyAssignment
	cout << delimiter << endl;
	fusion.print();
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

}
