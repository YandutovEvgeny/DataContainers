//List2
#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;            //�������� ��������
	Element* pNext;      //��������� �� ��������� �������
	Element* pPrev;      //��������� �� ���������� �������
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		:Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List;
};

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
		Element* New = new Element(Data, Head, Tail);
		New->pNext = Head;
		Element* Temp = Tail;
		while (Tail != nullptr)Temp = Temp->pPrev;
		Temp->pPrev = New;
		Head = new Element(Data, Head, Tail);
		New->pPrev = nullptr;
	}

	//             Methods:
	void Print()const
	{
		Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->pPrev << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
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
		list.push_front(rand() % 100);
	}
	list.Print();
}