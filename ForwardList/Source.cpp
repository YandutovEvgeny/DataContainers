//ForwardList
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab '\t'

class Element
{
	int Data;          //�������� ��������
	Element* pNext;    //����� ���������� ��������
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
	Element* Head;      //��������� �� ��������� ������� ������. �������� ������ ����� � ������.
public:
	ForwardList()
	{
		this->Head = nullptr; //���� ������ ��������� �� 0, ������ ������ ����
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//           Adding elements:
	void push_front(int Data)
	{
		//1)������ �������:
		Element* New = new Element(Data);
		//2)������������ ����� ������� � ������:
		New->pNext = Head;
		//3)��������� ������ �� ����� �������:
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
		Element* Temp = Head;
		delete Temp->pNext;
		Head = Temp->pNext;
	}

	//           Methods:
	void Print()const
	{
		Element* Temp = Head;  //Temp - ��������.
		//�������� - ��� ��������� ��� ������ �������� ����� �������� ������ � 
		//��������� ��������� ������.
		while (Temp!=nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;  //������� �� ��������� �������
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;   //������ ������
	cout << "������� ������ ������: "; cin >> n;
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