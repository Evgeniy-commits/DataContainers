#include<iostream>
#include<Windows.h>
#include <time.h>

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
			Data(Data), pLeft(pLeft), pRight(pRight) {
		}
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
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int i : il) insert(i);
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
	void balance()
	{
		balance(Root);
	}
	int minValue()const
	{
		/*clock_t t_start = clock();
		int min = minValue(Root);
		clock_t t_end = clock();
		cout << "MIN complete for: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
		return min;*/
		return minValue(Root);
	}
	int maxValue()const
	{
		/*clock_t t_start = clock();
		int max =  maxValue(Root);
		clock_t t_end = clock();
		cout << "MAX complete for: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
		return max;*/
		return maxValue(Root);
	}
	int count()const
	{
		clock_t t_start = clock();
		int rcount = count(Root);
		clock_t t_end = clock();
		cout << "COUNT complete for: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
		return rcount;
	}
	int depth()const
	{
		clock_t t_start = clock();
		int rdepth = depth(Root);
		clock_t t_end = clock();
		cout << "DEPTH complete for: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
		return rdepth;
	}
	unsigned long long Sum()const
	{
		clock_t t_start = clock();
		unsigned long long rSum = Sum(Root);
		clock_t t_end = clock();
		cout << "SUM complete for: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
		return rSum;
	}
	double Avg() const
	{
		clock_t t_start = clock();
		double rAvg = Sum(Root) / count(Root);
		clock_t t_end = clock();
		cout << "AVG complete for: " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. " << endl;
		return rAvg;
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void treePrint()const
	{
		treePrint(Root);
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
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(maxValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	void balance(Element*& Root)
	{
		if (Root == nullptr) return;
		if (count(Root->pLeft) - count(Root->pRight) < -1 || count(Root->pLeft) - count(Root->pRight) > 1)
		{
			Element* buffer = this->Root;
			erase(Root->Data);
			insert(buffer->Data);
		}
		//balance(Root->pRight);
		//balance(Root->pLeft);
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
	int depth(Element* Root)const
	{
		if(Root == nullptr) return 0;
		int leftdepth = depth(Root->pLeft);
		int rightdepth = depth(Root->pRight);
		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
		//return Root ? depth(Root->pLeft) > depth(Root->pRight) ? depth(Root->pLeft) + 1 : depth(Root->pRight) + 1 : 0;
	}
	unsigned long long Sum(Element* Root)const
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
	
	void printLevel(Element* Root, int level)const
	{
		if (Root == nullptr) 
		{
			cout << tab << tab;
			return;
		}
		if (level == 1)
		{
			//if (Root->Data != 0) cout << Root->Data; cout << tab << tab;
			cout << Root->Data << tab << tab;
			//if (Root->pRight == nullptr)  cout << tab << tab;
		}
		else if (level > 1)
		{
			printLevel(Root->pLeft, level - 1);
			printLevel(Root->pRight, level - 1);
		}
		//if (Root->pLeft == nullptr || Root->pRight == nullptr) cout << tab << tab;
	}

	void treePrint(Element* Root)const
	{
		for (int tabCount = depth(Root), i = 1; i <= depth(Root); i++, tabCount--)
		{
			for (int j = 0; j <= tabCount; j++) cout << tab;
			printLevel(Root, i);
			cout << endl;
		}
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

#define ERASE_CHECK
//#define BASE_CHECK
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
	tree.erase(58);
	cout << delimiter << delimiter;
	tree.print();
	/*cout << delimiter << delimiter;
	tree.balance();
	tree.print();
	cout << delimiter << delimiter;
	tree.treePrint();
	cout << endl;
	cout << delimiter;*/
	/*cout << "MIN " << tree.minValue();
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
	cout << "DEPTH " << tree.depth();
	cout << endl;
	cout << delimiter;
	cout<< tree.find(34);
	cout << delimiter;*/

	//UniqueTree utree;
	//for (;utree.count() < n;)
	//{
	//	utree.insert(rand() % 100);
	//}
	//utree.print();
	//cout << endl;
	//cout << "COUNT " << utree.count();
	//cout << endl;
	//cout << delimiter;
	////cout << utree.find(18);
	//cout << delimiter;
	//utree.erase(27);
	//utree.print();
	//cout << endl;
	//cout << "COUNT " << utree.count();
	//cout << delimiter;
#endif // BASE_CHECK

#ifdef ERASE_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 58, 85 };
	tree.print();
	cout << delimiter;
	tree.erase(50);
	tree.print();
	cout << delimiter;
	cout << "DEPTH " << tree.depth();
	cout << endl;
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
