#include "List.h"
#include "List.cpp"
#include <string>

#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define SUBSCRIPT_OPERATOR_CHECK
//#define COPY_SEMANTIC_PERFORMANCE_CHECK
//#define MOVE_SEMANTIC_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
//#define CHECK_CODE
//#define CHECK_CODE_A

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List<int> list;
	list.filling(n);
	//list.pop_front();
	//list.print();
	//list.reverse_print();
	//list.pop_back();
	//list.print();
	//int Index;
	//int value;
	//cout << "Введите индекс удаляемого элемента: "; cin >> Index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.erase(Index);
	//list.print();
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

#ifdef CHECK_CODE_A
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	list1.print();
	list2.print();
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	//for (int i : list3)cout << i << tab; cout << endl;
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
#endif // CHECK_CODE_A
}




