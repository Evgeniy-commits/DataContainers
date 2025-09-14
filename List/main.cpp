#include <iostream>
#include <time.h>
using namespace std;

#define tab  "\t"
#define delimiter "\n-------------------------------------------------------\n"


class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() 
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;

	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	// Adding Elements:
	void push_front(int Data)
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
	void push_back(int Data)
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

	void insert(int Data, int Index)
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


#define BASE_CHECK

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
}
