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
	Element* getRoot() const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
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
		clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
	}

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

	void insert(int Data)
	{
		insert(Data, this->Root);
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
	Element* _find(int Data, Element* Root)
	{
		if (Root == nullptr) return nullptr;
		if (Data == Root->Data)	return Root;
		else if (Data < Root->Data)	return _find(Data, Root->pLeft);
		else return _find(Data, Root->pRight);
	}

	bool find(int Data)
	{
		if (this->Root == nullptr) return false;
		if (_find(Data, Root) != nullptr) return true;	
	}
		
	void erase(int Data) 
	{
		if (this->Root != nullptr) this->Root = _erase(Data, Root);
	}
	Element* _erase(int Data, Element* Root)
	{
		if (Root == nullptr) return nullptr;
		if (Data < Root->Data) Root->pLeft = _erase(Data, Root->pLeft);
		else if (Data > Root->Data) Root->pRight = _erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else if (Root->pLeft == nullptr)	return Root->pRight;
			else if (Root->pRight == nullptr) return Root->pLeft;
			else
			{
				/*Element* replace_root = Root->pRight;
				while (replace_root->pLeft) replace_root = replace_root->pLeft;
				Root->Data = replace_root->Data;*/
				Root->Data = minValue(Root->pRight);
				Root->pRight = _erase(minValue(Root->pRight), Root->pRight);
			}
		}
		return Root;
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
	int Avg() const
	{
		return (double)Sum(Root) / count(Root);
	}
	void copy(Element* Root)
	{
		if (Root == nullptr) return;
		insert(Root->Data);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr) return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
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
public:
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
};

#define BASE_CHECK
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
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << delimiter;
	cout << "MIN " << tree.minValue(tree.getRoot());
	cout << endl;
	cout << "MAX " << tree.maxValue(tree.getRoot());
	cout << endl;
	cout << "COUNT " << tree.count(tree.getRoot());
	cout << endl;
	cout << "SUM " << tree.Sum(tree.getRoot());
	cout << endl;
	cout << "AVG " << tree.Avg();
	cout << endl;
	cout << delimiter;
	cout<< tree.find(34);
	cout << delimiter;
	UniqueTree utree;
	for (;utree.count(utree.getRoot()) < n;)
	{
		utree.insert(rand() % 100, utree.getRoot());
	}
	utree.print(utree.getRoot());
	cout << endl;
	cout << "COUNT " << utree.count(utree.getRoot());
	cout << endl;
	cout << delimiter;
	cout << utree.find(18);
	cout << delimiter;
	utree.erase(27);
	utree.print(utree.getRoot());
	cout << endl;
	cout << "COUNT " << utree.count(utree.getRoot());
	cout << delimiter;
#endif // BASE_CHECK

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
