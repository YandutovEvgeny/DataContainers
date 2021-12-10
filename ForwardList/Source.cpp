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
public:
	ForwardList()
	{
		this->Head = nullptr; //Если голова указывает на 0, значит список пуст
		cout << "FLConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "FLDestructor:\t" << this << endl;
	}

	//           Adding elements:
	void push_front(int Data)
	{
		//1)Создаём элемент:
		Element* New = new Element(Data);
		//2)Присоединяем новый элемент к списку:
		New->pNext = Head;
		//3)Переносим Голову на новый элемент:
		Head = New;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
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
		Element* New = new Element(Data);
		//Осуществляем вставку нового элемента в список:
		//2)Привязываем новый элемент к списку:
		New->pNext = Temp->pNext;
		//3)Включаем элемент в список:
		Temp->pNext = New;
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
	}

	//           Methods:
	void Print()const
	{
		Element* Temp = Head;  //Temp - итератор.
		//Итератор - это указатель при помощи которого можно получить доступ к 
		//элементам структуры данных.
		while (Temp!=nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;  //Переход на следующий элемент
		}
		cout << "Количество элементов списка: " << Head->count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;   //Размер списка
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
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
	/*int index, value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.Print();*/
	int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.Print();
 
	/*list.push_back(123);
	list.Print();
	list.pop_back();
	list.Print();*/
}