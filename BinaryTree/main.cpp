#include<iostream>
#include<Windows.h>

using namespace std;

#define tab				"\t"
#define delimiter		"\n--------------------------------------------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight) {}
		~Element() {}
		
		friend class Tree;
		friend class UniqueTree;
	} *Root;
public:
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il): Tree()
	{
		for(int i : il) insert(i);		
		cout << "ILConstructor:\t" << this << endl;
	}
	Tree(const Tree& other) : Tree()
	{
		copy(other.Root);
		cout << "CopyConstructor:\t" << this << endl;
	}
	Tree(Tree&& other) noexcept
	{
		this->Root = other.Root;
		other.Root = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	Element* getRoot() const
	{
		return Root;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg() const
	{
		return Sum(Root) / count(Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void copy()
	{
		copy(Root);
	}
	void clear()
	{	
		clear(Root);	
		Root = nullptr;
	}
	/*bool find(int Data)
	{
		return find(Data, Root);
	}*/

private:
	///// operators
	Tree& operator=(const Tree& other)
	{
		if (this == &other) return *this; 
		this->~Tree();
		/*clear(Root);*/
		copy(other.Root);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	Tree& operator=(Tree&& other) noexcept
	{
		if (this == &other) return *this;
		this->~Tree();
		/*clear(Root);*/
		this->Root = other.Root;
		other.Root = nullptr;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root ->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(maxValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		return !Root ? 0 : Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int Sum(Element* Root)const
	{
		return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
	}
	
	void copy(Element* Root)
	{
		if (Root == nullptr) return;
		insert(Root->Data);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
	void clear(Element*& Root)
	{
		if (Root == nullptr) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
				Root->pLeft = new Element(Data);
			else
				insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
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
#define ERASE_CHECK
//#define MOVE_SEMANTIC

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << delimiter;
	cout << "MIN " << tree.minValue();
	cout << endl;
	cout << "MAX " << tree.maxValue();
	cout << endl;
	cout << "COUNT " << tree.count();
	cout << endl;
	cout << "SUM " << tree.Sum();
	cout << endl;
	cout << "AVG " << tree.Avg();
	cout << endl;
	cout << delimiter;
	//cout<< tree.find(34);
	cout << delimiter;

	UniqueTree utree;
	for (;utree.count() < n;)
	{
		utree.insert(rand() % 100);
	}
	utree.print();
	cout << endl;
	cout << "COUNT " << utree.count();
	cout << endl;
	cout << delimiter;
	//cout << utree.find(18);
	cout << delimiter;
	utree.erase(27);
	utree.print();
	cout << endl;
	cout << "COUNT " << utree.count();
	cout << delimiter;
#endif // BASE_CHECK

#ifdef ERASE_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 58, 85};
	tree.print();
	cout << delimiter;
	tree.erase(50);
	tree.print();
	cout << delimiter;
#endif // ERASE_CHECK

#ifdef MOVE_SEMANTIC

	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << delimiter;
	cout << tree.find(15) << endl;
	cout << delimiter;
	int value;
	cout << "Введите удавляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print(tree.getRoot());
	cout << delimiter;
	UniqueTree unqtree;
	for (;unqtree.count(unqtree.getRoot()) < n;)
	{
		unqtree.insert(rand() % 100, unqtree.getRoot());
	}
	unqtree.print(unqtree.getRoot());
	cout << delimiter;
	Tree example;
	example = tree;
	example.print(example.getRoot());
	cout << delimiter;
#endif // MOVE_SEMANTIC
}
