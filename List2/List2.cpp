//List2
#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;            //�������� ��������
	Element* pNext;      //��������� �� ��������� �������
	Element* pPrev;      //��������� �� ���������� �������
	static int count;    //���������� ���������
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		:Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t" << this << endl;
		count++;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
		count--;
	}
	friend class List;
};

int Element::count = 0;

class List
{
	Element* Head;    //��������� �� ��������� ������� ������. �������� ������ ����� � ������.
	Element* Tail;    //��������� �� ��������� ������� ������. �������� ������ ����� � ������.
	size_t size;      //���������� ��������� � ������
public:
	List()
	{
		this->Head = nullptr;     //���� ������ ��������� �� ����, ������ ����
		this->Tail = nullptr;     //���� ����� ��������� �� ����, ������ ����
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//            Adding elements:
	void push_front(int Data)
	{
		if (Head != nullptr)
		{
			Element* New = new Element(Data, Head, Tail);
			New->pNext = Head;
			Head = New;
			New->pPrev = nullptr;
		}
		else Head = Tail = new Element(Data, Head, Tail);
		size++;
	}

	void push_back(int Data)
	{
		Element* New = new Element(Data, Head, Tail);
		New->pPrev = Tail;
		Tail = New;
		New->pNext = nullptr;
		size++;
	}

	void insert(int Data, int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* New = new Element(Data);

	}

	//           Erasing elements:
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		Element* Erased = Tail;
		Tail = Tail->pPrev;
		delete Erased;
		Tail->pNext = nullptr;
		size--;
	}
	
	//             Methods:
	void Print()const
	{
		//������� �������� � �����:
		Element* Temp = Tail;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
			Temp = Temp->pPrev;
		}

		//������� �������� � ������:
		/*Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.Print();
	/*list.pop_front();
	list.Print();*/
	list.pop_back();
	list.Print();
}