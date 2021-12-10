//ForwardList
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "--------------------------------------------------"

class Element
{
	int Data;          //Значение элемента
	Element* pNext;    //Адрес следующего элемента
	static int count;  //Количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;    //Статические переменные могут быть проинициализированны только за классом

class ForwardList
{
	Element* Head;      //Указывает на начальный элемент списка. Является точкой входа в список.
	size_t size;
public:
	ForwardList()
	{
		this->Head = nullptr; //Если голова указывает на 0, значит список пуст
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}

	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			//it - итератор для прохождения по il(initializer_list)
			push_back(*it);
		}
	}

	ForwardList(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "FLCopyConstructor: " << this << endl;
		cout << delimiter << endl;
	}

	~ForwardList()
	{
		while (Head!=nullptr)pop_front();
		cout << "FLDestructor:\t" << this << endl;
	}

	//             Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;		
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "FLCopyAssignment: " << this << endl;
		return *this;
	}

	//           Adding elements:
	void push_front(int Data)
	{
		//1)Создаём элемент:
		//Element* New = new Element(Data, Head);
		//2)Присоединяем новый элемент к списку:
		//New->pNext = Head;
		//3)Переносим Голову на новый элемент:
		//Head = New; 
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error 404: Выход за пределы списка!" << endl;
			return;
		}
		if (Index == 0 || Head == nullptr)return push_front(Data);
		//0)Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//1)Создаём новый элемент:
		//Element* New = new Element(Data);
		//Осуществляем вставку нового элемента в список:
		//2)Привязываем новый элемент к списку:
		//New->pNext = Temp->pNext;
		//3)Включаем элемент в список:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//             Erasing elements:
	void pop_front()
	{
		/*Element* Temp = Head->pNext;  //Присваеваем итератору указатель на 2 элемент
		delete Head;                    //Удаляем Голову
		Head = Temp;                    //Назначаем новый головной элемент*/
		//1)Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;
		//2)Исключаем элемент из списка:
		Head = Head->pNext;
		//3)Удаляем элемент из списка:
		delete Erased;
		size--;
	}

	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		//1)Доходим до предпоследнего элемента:
		Element* Temp = Head;                                                          
		while (Temp->pNext->pNext)Temp = Temp->pNext;   //Мы оказываемся в предпоследнем элементе
		//2)Удаляем последний элемент из памяти:
		delete Temp->pNext;
		//3)"Забываем" об удалённом элементе, то есть затираемего адрес нулём:
		Temp->pNext = nullptr;
		//Теперь Temp является последним элементом списка. 
		size--;
	}

	void erase(int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error 404: Выход за пределы списка!";
			return;
		}
		if (Index == 0 || Head == nullptr)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}

	//           Methods:
	void Print()const
	{
		/*Element* Temp = Head;  //Temp - итератор.
		//Итератор - это указатель при помощи которого можно получить доступ к 
		//элементам структуры данных.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;  //Переход на следующий элемент
		}*/
		for(Element* Temp = Head; Temp; Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов: " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define COUNT_CHECK
//#define COPY_METHODS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;   //Размер списка
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.Print();
	/*cout << delimiter << endl;
	list.push_back(8);
	list.Print();
	cout << delimiter << endl;
	list.pop_front();
	list.Print();
	cout << delimiter << endl;
	list.pop_back();
	list.Print();
	cout << delimiter << endl;*/
	int index, value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.Print();
	/*int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.Print();*/

	/*list.push_back(123);
	list.Print();
	list.pop_back();
	list.Print();*/
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.Print();
	list2.Print();
#endif // COUNT_CHECK

#ifdef COPY_METHODS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1 = list1;
	list1.Print();

	//ForwardList list2 = list1;   //CopyConstructor
	ForwardList list2;
	list2 = list1;                 //CopyAssignment
	list2.Print();
#endif // COPY_METHODS_CHECK

	/*int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << tab;
	cout << endl;*/

	ForwardList list = { 3,5,8,13,21 };
	list.Print();
}