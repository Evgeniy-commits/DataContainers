//ForwardList
#include <iostream>
using namespace std;

#define tab  "\t"

class Element
{
	int Data;
	Element* pNext;
	//static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}

	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

//int Element::count = 0;

class ForwardList
{
	Element* Head;
	int count;
public:
	ForwardList()
	{
		Head = nullptr;
		count = 0;
		//если список пуст, то его Голова обязательно указывает на 0;
		cout << "FLConstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		while (Head) pop_front();

		cout << "FLDestructor:\t" << this << endl;
	}

	//		Adding elements
	void push_front(int Data)
	{
		//1) Создаем элемент и сохраняем в него добавляемое значение:
		Element* New = new Element(Data);

		//2) Привязываем новый, созданный элемент к началу списка:
		New->pNext = Head;

		//3) Переносим Голову на новый элемент:
		Head = New;
		count++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext) Temp = Temp->pNext;
		Temp->pNext = New;
		count++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		if (Index >= count) return push_back(Data);
		//1) Доходим до нужного элемента (элемент перед добавляемым)
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;

		//2) Создаем добавляемый элемент
		Element* New = new Element(Data);

		//3) Пристыковываем новый элемент к списку
		New->pNext = Temp->pNext;

		//4) Пристыковываем предыдущий элемент к новому
		Temp->pNext = New;
		count++;
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
		count--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		count--;
	}

	void erased(int Index)
	{
		if (Index == 0) return pop_front();
		if (Index >= count) return pop_back();
		//1) Доходим до нужного элемента (элемент перед удаляемым)
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		count--;
	}

	//		Methods:
	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << count << endl;
	}
};

ForwardList operator+(const ForwardList left, const ForwardList right)
{

}

//#define BASE_CHECK

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
	int Index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, Index);
	list.print();
#endif // BASE_CHECK

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
	list1.insert(value, Index);
	list1.print();
	list2.print();*/
	
	
	int Index;
	cout << "Введите индекс удаляемого элемента: "; cin >> Index;
	list1.erased(Index);
	list1.print();
	list2.print();
}










//
//String operator+(const String& left, const String& right)
//{
//	int length = strlen(left.str) + strlen(right.str);
//	char* buffer = new char[length + 1];
//	for (int i = 0; i < strlen(left.str); i++)
//		buffer[i] = left.str[i];
//	for (int i = 0; i < length; i++)
//		buffer[i + strlen(left.str)] = right.str[i];
//	return buffer;
//}

////ForwardList
//#include <iostream>
//using namespace std;
//
//#define tab  "\t"
//
//
//class Element
//{
//	int Data;
//	Element* pNext;
//	static int count;
//public:
//	Element(int Data, Element* pNext = nullptr)
//	{
//		this->Data = Data;
//		this->pNext = pNext;
//		count++;
//		cout << "EConstructor:\t" << this << endl;
//	}
//
//	~Element()
//	{
//		count--;
//		cout << "EDestructor:\t" << this << endl;
//	}
//	friend class ForwardList;
//};
//
//int Element::count = 0;
//
//class ForwardList
//{
//	Element* Head;
//public:
//	ForwardList()
//	{
//		Head = nullptr;
//		Element::count = 0;
//		//если список пуст, то его Голова обязательно указывает на 0;
//		cout << "FLConstructor:\t" << this << endl;
//	}
//
//	~ForwardList()
//	{
//		while (Head) pop_front();
//
//		cout << "FLDestructor:\t" << this << endl;
//	}
//
//	//		Adding elements
//	void push_front(int Data)
//	{
//		//1) Создаем элемент и сохраняем в него добавляемое значение:
//		Element* New = new Element(Data);
//
//		//2) Привязываем новый, созданный элемент к началу списка:
//		New->pNext = Head;
//
//		//3) Переносим Голову на новый элемент:
//		Head = New;
//	}
//	void push_back(int Data)
//	{
//		if (Head == nullptr) return push_front(Data);
//		Element* New = new Element(Data);
//		Element* Temp = Head;
//		while (Temp->pNext) Temp = Temp->pNext;
//		Temp->pNext = New;
//	}
//	void insert(int Data, int Index)
//	{
//		if (Index == 0) return push_front(Data);
//		if (Index >= Element::count) return push_back(Data);
//		//1) Доходим до нужного элемента (элемент перед добавляемым)
//		Element* Temp = Head;
//		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
//
//		//2) Создаем добавляемый элемент
//		Element* New = new Element(Data);
//
//		//3) Пристыковываем новый элемент к списку
//		New->pNext = Temp->pNext;
//
//		//4) Пристыковываем предыдущий элемент к новому
//		Temp->pNext = New;
//	}
//
//	//			Removing elements
//	void pop_front()
//	{
//		//1) Запоминаем адрес удаляемого элемента:
//		Element* Erased = Head;
//		//2) Исключаем удаляемый элемент из списка:
//		Head = Head->pNext;
//		//3) Удаляем элемент из памяти:
//		delete Erased;
//		Element::count--;
//	}
//
//	void pop_back()
//	{
//		Element* Temp = Head;
//		while (Temp->pNext->pNext != nullptr) Temp = Temp->pNext;
//		delete Temp->pNext;
//		Temp->pNext = nullptr;
//		Element::count--;
//	}
//
//
//	//		Methods:
//	void print()const
//	{
//		Element* Temp = Head;
//		while (Temp)
//		{
//			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
//			Temp = Temp->pNext;
//		}
//		cout << "Количество элементов списка: " << Element::count << endl;
//	}
//};
//
////#define BASE_CHECK
//
//void main()
//{
//	setlocale(LC_ALL, "");
//
//#ifdef BASE_CHECK
//	int n;
//	cout << "Введите размер списка: "; cin >> n;
//	ForwardList list;
//	for (int i = 0; i < n; i++)
//	{
//		list.push_back(rand() % 100);
//		//list.push_front(rand() % 100);
//	}
//	//list.push_back(123);
//	//list.pop_front();
//	//list.pop_back();
//	list.print();
//	int Index;
//	int value;
//	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
//	cout << "Введите значение добавляемого элемента: "; cin >> value;
//	list.insert(value, Index);
//	list.print();
//#endif // BASE_CHECK
//
//	ForwardList list1;
//	list1.push_back(0);
//	list1.push_back(1);
//	list1.push_back(1);
//	list1.push_back(2);
//	list1.print();
//
//	ForwardList list2;
//	list2.push_back(3);
//	list2.push_back(5);
//	list2.push_back(8);
//	list2.push_back(13);
//	list2.push_back(21);
//	list2.push_back(34);
//	list2.push_back(55);
//	list2.push_back(89);
//	list2.print();
//
//	int Index;
//	int value;
//	cout << "Введите индекс добавляемого элемента: "; cin >> Index;
//	cout << "Введите значение добавляемого элемента: "; cin >> value;
//	list1.insert(value, Index);
//	list1.print();
//	list2.print();
//}
