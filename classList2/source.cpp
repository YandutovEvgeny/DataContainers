#include"classList2.h"
#include"classList2.cpp"

#include<string>

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.Print();
	list.Print_reverse();
	cout << delimiter;
	/*list.pop_front();
	list.pop_back();*/
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	/*cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);*/
	list.Print();
	list.Print_reverse();
#endif // BASE_CHECK

	List<int> list = { 3,5,8,13,21 };
	list.Print();

	List<int> list1;
	list1 = list;
	//list1.Print();
	for (int i : list1)cout << i << tab; cout << endl;

	reverse_print_list(list1);
	print_list(list1);

	List<double> d_list = { 2.7, 3.14, 5.2, 8.7 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "Happy", "New", "Year!" };
	for (std::string i : s_list)cout << i << " "; cout << endl;
}