#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree
{
protected:
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
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
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
	Tree(const std::initializer_list<int>& il): Tree()
	{
		for (int i : il)insert(i, Root);
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
		Root = nullptr;
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
		return (double)Sum(Root) / Count(Root);
	}
	void erase(int Data)
	{
		erase(Data, this->Root);
	}
	void Clear()
	{
		return Clear(this->Root);
		Root = nullptr;
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
		else //if(Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else minValue(Root->pLeft);*/
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
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
		//return Root ? Count(Root->pLeft) + Count(Root->pRight) + 1 : 0;
		return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root)const
	{
		/*int sum = 0;
		if (Root != nullptr)
		{
			sum += Sum(Root->pLeft);
			sum += Root->Data;
			sum += Sum(Root->pRight);
		}
		return sum;*/
		return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
	}

	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())         //Если элемент является листком
			{
				//то его можно удалять 
				delete Root;
				Root=nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight)) //Если в левой ветке больше элементов чем в правой ветке
				{
					Root->Data = maxValue(Root->pLeft);  //Заменяем значение удаляемого элемента максимальным значением в левой ветке
                    erase(maxValue(Root->pLeft), Root->pLeft);
				
				}
				else //В противном случае 
				{
					Root->Data = minValue(Root->pRight);  //заменяем значение удаляемого элемента минимальным значением в правой ветке
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
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

class UniqueTree : public Tree
{
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
		else if(Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK
//#define COPY_METHODS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int erase_number;
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
	/*cout << "Укажите, какой элемент хотите удалить из дерева: "; cin >> erase_number;
	tree.erase(erase_number);
	//cout << "Указанный элемент удалён!" << endl;*/
	tree.Clear();
	tree.print();
	//cout << "Дерево полностью очищено!" << endl;
	
	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << u_tree.Count() << endl;
	cout << "Сумма элементов в дереве: " << u_tree.Sum() << endl;
	cout << "Среднее арифметическое элементов в дереве: " << u_tree.Avg() << endl;
	/*cout << "Укажите, какой элемент хотите удалить из дерева: "; cin >> erase_number;
	u_tree.erase(erase_number);
	//cout << "Указанный элемент удалён!" << endl;*/
	u_tree.Clear();
	u_tree.print();
	//cout << "Дерево полностью очищено!" << endl;
#endif // BASE_CHECK

	Tree tree = { 50, 25, 75, 16, 32, 64, 80, 8, 11, 48, 77, 85 };
	tree.print();
	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();

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
	
}