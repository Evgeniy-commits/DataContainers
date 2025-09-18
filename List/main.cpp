#include "ListClasswork.h"
#include "ListClasswork.cpp"

//#define BASE_CHECK
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
		list.push_back((double)(rand() % 100) / 10);
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
	for (List<int>::ConstIterator it = list1.begin(); it != list1.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 100;
		cout << *it << tab;
	}
	cout << endl;
	for (List<int>::ConstReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;


	List <std::string> s_list = { "Hello", "World" };
	for (std::string i : s_list)cout << i << tab; cout << endl;

	for (List<std::string>::ConstReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // CHECK_CODE
	
}
