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
		//���� ������ ����, �� ��� ������ ����������� ��������� �� 0;
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
		//1) ������� ������� � ��������� � ���� ����������� ��������:
		Element* New = new Element(Data);

		//2) ����������� �����, ��������� ������� � ������ ������:
		New->pNext = Head;

		//3) ��������� ������ �� ����� �������:
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
		//1) ������� �� ������� �������� (������� ����� �����������)
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;

		//2) ������� ����������� �������
		Element* New = new Element(Data);

		//3) �������������� ����� ������� � ������
		New->pNext = Temp->pNext;

		//4) �������������� ���������� ������� � ������
		Temp->pNext = New;
		count++;
	}

	//			Removing elements
	void pop_front()
	{
		//1) ���������� ����� ���������� ��������:
		Element* Erased = Head;
		//2) ��������� ��������� ������� �� ������:
		Head = Head->pNext;
		//3) ������� ������� �� ������:
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
		//1) ������� �� ������� �������� (������� ����� ���������)
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
		cout << "���������� ��������� ������: " << count << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
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
	cout << "������� ������ ������������ ��������: "; cin >> Index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
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
	cout << "������� ������ ������������ ��������: "; cin >> Index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list1.insert(value, Index);
	list1.print();
	list2.print();*/


	int Index;
	cout << "������� ������ ���������� ��������: "; cin >> Index;
	list1.erased(Index);
	list1.print();
	list2.print();
}