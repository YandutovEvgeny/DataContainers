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
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;      //Указывает на начальный элемент списка. Является точкой входа в список.
public:
	ForwardList()
	{
		this->Head = nullptr; //Если голова указывает на 0, значит список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
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
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (true)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
	}

	void pop_front()
	{
		Element* Temp = Head->pNext;  //Присваеваем итератору указатель на 2 элемент
		delete Head;                  //Удаляем Голову
		Head = Temp;                  //Назначаем новый головной элемент
	}

	void pop_back()
	{
		Element* Temp = Head;          
		while (Temp->pNext->pNext!=nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	void insert(int Data, int n)
	{
		Element* Temp = Head;
		int i = 0;
		while (Temp != nullptr)
		{
			Temp = Temp->pNext;
			i++;
		}
		if (n > i)
		{
			cout << "Вы вышли за пределы списка!" << endl;
			return;
		}
		else
		{
			Element* New = new Element(Data);
			New->pNext = Temp->pNext;
			Temp->pNext = New;
		}

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
		list.push_front(rand() % 100);
	}
	list.Print();
	cout << delimiter << endl;
	list.push_back(8);
	list.Print();
	cout << delimiter << endl;
	list.pop_front();
	list.Print();
	cout << delimiter << endl;
	list.pop_back();
	list.Print();
	cout << delimiter << endl;
	list.insert(100, 3);
	list.Print();
}