//ForwardList
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab '\t'

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
	list.push_back(4);
	list.Print();
	list.pop_front();
	list.Print();
}