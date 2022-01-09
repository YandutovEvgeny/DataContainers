#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;  //Корень дерева
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const Tree& other):Tree()
	{
		cout << "TCopyConstructor:\t" << this << endl;
		*this = other;
	}
	Tree(Tree&& other)
	{
		this->Root = other.Root;
		cout << "TMoveConstructor:\t" << this << endl;
		other.Root = nullptr;
	}
	~Tree()
	{
		Clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}

	//                Operators:
	Tree& operator=(const Tree& other)
	{
		if (this != &other)
		{
			this->Clear();
			Element* Root = other.Root;
			RecursionFunction(Root);
		}
		cout << "TCopyAssignment:\t" << this << endl;
		return *this;
	}

	Tree& operator=(Tree&& other)
	{
		this->Root = other.Root;
		other.Root = nullptr;
		cout << "TMoveAssignment:\t" << this << endl;
		return *this;
	}

	void RecursionFunction(Element* Root)    //Рекурсивная функция для оператора присваивания
	{
		if (Root != nullptr)
		{
			this->insert(Root->Data);
			RecursionFunction(Root->pLeft);
			RecursionFunction(Root->pRight);
		}
	}

	//                Methods:
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
	int Count()const
	{
		return Count(this->Root);
	}
	int Sum()const
	{
		return Sum(this->Root);
	}
	double Avg()const
	{
		return Avg(this->Root);
	}
	void erease(int Data)
	{
		erease(Data, this->Root);
	}
	void Clear()
	{
		return Clear(this->Root);
	}
	void print()const  
	{
		print(this->Root);
		cout << endl;
	}

private:
	void insert(int Data, Element* Root)
	{
		//Root - корень поддерева
		//this->Root - корень всего дерева
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;		
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)  //Если есть место для добавления элемента,
				Root->pLeft = new Element(Data);  //Добавляем элемент прямо сюда.
			else  //В противном случае
				insert(Data, Root->pLeft);   //идём налево и ищем место куда добавить элемент.
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}

	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else maxValue(Root->pRight);*/
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)const
	{
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root)const
	{
		int sum = 0;
		if (Root != nullptr)
		{
			sum += Sum(Root->pLeft);
			sum += Root->Data;
			sum += Sum(Root->pRight);
		}
		return sum;
	}

	double Avg(Element* Root)const
	{
		return double(Sum(Root)) / Count(Root);
	}

	void erease(int Data, Element* Root)
	{
		if (Root == nullptr)return;
		if (Data == Root->Data)
		{
			cout << "Вы сломали программу, та в принципе ничего нового!" << endl;
			delete Root;
			return;
		}
		if (Data < Root->Data)
		{
			if (Data == Root->pLeft->Data)
			{
				Element* Erased = Root->pLeft;
				Root->pLeft = Root->pLeft->pLeft;
				delete Erased;
			}
			else erease(Data, Root->pLeft);
		}
		else
		{
			if (Data == Root->pRight->Data)
			{
				Element* Erased = Root->pRight;
				Root->pRight = Root->pRight->pRight;
				delete Erased;
			}
			else erease(Data, Root->pRight);
		}
	}

	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

#define BASE_CHECK
//#define COPY_METHODS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int erease_number;
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.Count() << endl;
	cout << "Сумма элементов в дереве: " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов в дереве: " << tree.Avg() << endl;
	cout << "Укажите, какой элемент хотите удалить из дерева: "; cin >> erease_number;
	tree.erease(erease_number);
	//cout << "Указанный элемент удалён!" << endl;
	tree.print();
	tree.Clear();
	cout << "Дерево полностью очищено!" << endl;
#endif // BASE_CHECK

#ifdef COPY_METHODS_CHECK
	Tree tree1;
	for (int i = 0; i < 5; i++)
	{
		tree1.insert(rand() % 100);
	}
	tree1.print();
	Tree tree2 = tree1;        //Copy constructor
	tree2.print();
	Tree tree3;                
	tree3 = tree2;             //Shallow copy
	tree3.print();             
#endif // COPY_METHODS_CHECK
	main();
}