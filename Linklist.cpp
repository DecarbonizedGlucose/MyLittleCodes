#include <iostream>

using namespace std;

// 链表分8类，是否循环，是否双向，是否有头

// 结点
class Node
{
public:
	int value;
	Node* next;
	Node(int v, Node* n) : value(v), next(n) {}
};

template<typename T>
void swapElem(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

// 非循环有头单链表
class LinkList
{
public:
	Node* head = new Node(0, nullptr); // 头
	int length = 0;

	LinkList() {} // 默认构造

	LinkList(int* a, int len) // 有参构造
	{
		for (int i = 0; i < len; ++i)
		{
			addBack(a[i]);
		}
	}
	
	LinkList(LinkList& _L) // 复制一个相同的链表
	{
		Node* cur = _L.head->next;
		while (cur)
		{
			addBack(cur->value);
			cur = cur->next;
		}
	}

	LinkList(LinkList& _L1, LinkList& _L2) // 融合两个有序链表
	{
		if (_L1.empty() || _L2.empty())
		{
			head = _L1.empty() ? _L2.head : _L1.head;
			(_L1.empty() ? _L2 : _L1).head->next = nullptr;
			return;
		}
		Node* pre = _L1.head->next->value <= _L2.head->next->value ? _L1.head->next : _L2.head->next;
		head->next = pre;
		Node* cur1 = pre->next;
		Node* cur2 = pre == _L1.head->next ? _L2.head->next : _L1.head->next;

		while (cur1 != nullptr && cur2 != nullptr)
		{
			if (cur1->value <= cur2->value)
			{
				pre->next = cur1;
				pre = cur1;
				cur1 = cur1->next;
			}
			else
			{
				pre->next = cur2;
				pre = cur2;
				cur2 = cur2->next;
			}
		}
		pre->next = cur1 == nullptr ? cur2 : cur1;
		_L1.head = nullptr;
		_L2.head = nullptr;
	}

	/*--------------------------   插入   ----------------------------*/

	void addBack(int value) // 尾插
	{
		Node* newElement = new Node(value, nullptr);
		if (empty()) head->next = newElement;
		else tail()->next = newElement;
		++length;
	}

	void addFront(int value) // 头插
	{
		Node* newFirstElem = new Node(value, head->next);
		head->next = newFirstElem;
		++length;
	}

	void add(int idx, int value) // 任意位置插入
	{
		if (idx > length - 1) throw "Linklist is not so long.";
		if (idx == 0)
		{
			addFront(value);
			return;
		}
		Node* former = ptrOf(idx - 1);
		Node* newElement = new Node(value, former->next);
		former->next = newElement;
		++length;
	}

	/*--------------------------   删改   ----------------------------*/

	void modify(int idx, int newv) // 修改
	{
		ptrOf(idx)->value = newv;
	}

	void popFront() // 头删
	{
		if (empty()) throw "Linklist is empty.";
		Node* toDel = head->next;
		head->next = toDel->next;
		delete toDel;
		toDel = nullptr;
		--length;
	}

	void popBack() // 尾删
	{
		if (empty()) throw "Linklist is empty.";
		if (length == 1) { popFront(); return; }
		Node* Lsub2 = ptrOf(length - 2);
		delete Lsub2->next;
		Lsub2->next = nullptr;
		--length;
	}

	void pop(int idx) // 任意位置删
	{
		if (idx == 0) { popFront(); return; }
		if (idx == length - 1) { popBack(); return; }
		Node* former = ptrOf(idx - 1);
		Node* toDel = former->next;
		Node* latter = toDel->next;
		delete toDel;
		toDel = nullptr;
		former->next = latter;
		--length;
	}

	/*--------------------------   查   ----------------------------*/

	bool empty() // 判断是否为空
	{
		return head->next == nullptr;
	}

	Node* tail() // 返回指向末元素的指针
	{
		if (empty()) return nullptr;
		Node* nextptr = head->next;
		while (nextptr->next) nextptr = nextptr->next;
		return nextptr;
	}

	Node* ptrOf(int idx) // 根据序号索引结点位置
	{
		if (empty()) throw "Linklist is empty!";
		if (idx + 1 > length) throw "Linklist is not so long.";
		Node* nptr = head->next;
		for (int i = 0; i < idx; ++i)
		{
			nptr = nptr->next;
		}
		return nptr;
	}

	int valueOf(int idx) // 根据序号索引结点数据
	{
		return ptrOf(idx)->value;
	}

	int operator[](int idx)
	{
		return ptrOf(idx)->value;
	}

	int front()
	{
		if (empty()) throw "Linklist is empty.";
		return head->next->value;
	}

	int back()
	{
		if (empty()) throw "Linklist is empty.";
		return tail()->value;
	}

	/*--------------------------   调整顺序   ----------------------------*/

	void reverse() // 逆置
	{
		Node* pre = nullptr;
		Node* temp = head->next;
		Node* nextptr = temp;
		while (temp)
		{
			nextptr = nextptr->next;
			temp->next = pre;
			pre = temp;
			temp = nextptr;
		}
		head->next = pre;
	}

	void bubble() // 排序，采用冒泡，只交换数据域
	{
		if (length < 2) return;
		for (int i = 0; i < length; ++i)
		{
			for (Node* i = head->next; i->next; i = i->next)
			{
				if (i->value > i->next->value)
					swapElem(i->value, i->next->value);
			}
		}
	}

	void Bubble() // 冒泡，但是重新组织结点关系
	{
		if (length < 2) return;
		for (int end = length - 1; end > 0; --end)
		{
			Node* pre = head;
			Node* temp = head->next;
			Node* nextptr = temp;
			while (nextptr->next)
			{
				nextptr = nextptr->next;
				/*-----------*/
				if (temp->value > nextptr->value)
				{
					temp->next = nextptr->next;
					nextptr->next = temp;
					pre->next = nextptr;
					swapElem(temp, nextptr);
				}
				/*-----------*/
				pre = temp;
				temp = nextptr;
			}
		}
	}
};

ostream& operator<<(ostream& cout, LinkList& l)
{
	Node* nptr = l.head->next;
	while (nptr) // 遍历输出
	{
		cout << nptr->value << " ";
		nptr = nptr->next;
	}
	return cout;
}

int main()
{
	int arr1[] = { 1, 3, 5, 7, 9 };
	int arr2[] = { 2, 4, 6, 8, 10 };
	LinkList t1(arr1, sizeof(arr1) / sizeof(arr1[0]));
	LinkList t2(arr2, sizeof(arr2) / sizeof(arr2[0]));
	t1.bubble();
	t2.bubble();
	cout << t1 << endl;
	cout << t2 << endl;
	LinkList t3(t1, t2);
	cout << t3 << endl;
	return 0;
}