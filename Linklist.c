#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

typedef struct LinkNode
{
	int value;
	struct LinkNode* next;
} Node ;

// 非循环有头单链表
typedef struct LinkList
{
	Node *head;
	int length;
} Link ;


/*-----------------------------------------------*/
// 增
int addBack(Link* ll, int value);
int addFront(Link* ll, int value);
int add(Link* ll, int idx, int value);
// 删改
void modify(Link* ll, int idx, int newv);
int popFront(Link* ll);
int popBack(Link* ll);
int pop(Link* ll, int idx);
// 查
int empty(Link* ll);
Node* tail(Link* ll);
Node* ptrOf(Link* ll, int idx);
int front(Link* ll);
int back(Link* ll);
// 调
void reverse(Link* ll);
void bubble(Link* ll);
int Bubble(Link* ll);
/*-----------------------------------------------*/


int linkInit(Link* ll)
{
	ll->head = (Node*)malloc(sizeof(Node));
	if (ll->head) ll->head->next = 0;
	else return 0;
	ll->head->next = NULL;
	ll->length = 0;
	return 1;
}

void cpArray(Link* ll, int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		addBack(ll, a[i]);
	}
}

int addBack(Link* ll, int value)
{
	Node* newElement = (Node*)malloc(sizeof(Node));
	if (newElement) newElement->next = NULL;
	else return 0;
	newElement->value = value;
	tail(ll)->next = newElement;
	++ll->length;
	return 1;
}

int addFront(Link* ll, int value)
{
	Node* newElement = (Node*)malloc(sizeof(Node));
	if (newElement) newElement->value = value;
	else return 0;
	newElement->next = ll->head->next;
	ll->head->next = newElement;
	return 1;
}

int add(Link* ll, int idx, int value)
{
	if (idx > ll->length - 1) return 0;
	if (idx == 0)
	{
		addFront(ll, value);
		return 1;
	}
	Node* former = ptrOf(ll, idx - 1);
	Node* newElement = (Node*)malloc(sizeof(Node));
	if (newElement) newElement->next = former->next;
	else return 0;
	newElement->value = value;
	former->next = newElement;
	++ll->length;
	return 1;
}

void modify(Link* ll, int idx, int newv)
{
	ptrOf(ll, idx)->value = newv;
}

int popFront(Link* ll)
{
	if (empty(ll)) return 0;
	Node* toDel = ll->head->next;
	ll->head->next = toDel->next;
	free(toDel);
	toDel = NULL;
	--ll->length;
	return 1;
}

int popBack(Link* ll)
{
	if (empty(ll)) return 0;
	if (ll->length == 1)
	{
		popFront(ll);
		return 1;
	}
	Node* Lsub2 = ptrOf(ll, ll->length - 2);
	free(Lsub2->next);
	Lsub2->next = NULL;
	--ll->length;
	return 1;
}

int pop(Link* ll, int idx)
{
	if (idx == 0)
	{
		popFront(ll);
		return 1;
	}
	if (idx == ll->length - 1)
	{
		popBack(ll);
		return 1;
	}
	Node* former = ptrOf(ll, idx - 1);
	Node* toDel = former->next;
	Node* latter = toDel->next;
	free(toDel);
	toDel = NULL;
	former->next = latter;
	--ll->length;
	return 1;
}

int empty(Link* ll)
{
	return ll->head->next == NULL;
}

Node* tail(Link* ll)
{
	if (empty(ll)) return NULL;
	Node* nextptr = ll->head->next;
	while (nextptr->next) nextptr = nextptr->next;
	return nextptr;
}

Node* ptrOf(Link* ll, int idx)
{
	if (empty(ll)) return NULL;
	if (idx + 1 > ll->length) return NULL;
	Node* nptr = ll->head->next;
	for (int i = 0; i < idx; ++i)
	{
		nptr = nptr->next;
	}
	return nptr;
}

int valueOf(Link* ll, int idx)
{
	return ptrOf(ll, idx)->value;
}

int front(Link* ll)
{
	return ll->head->value;
}

int back(Link* ll)
{
	return tail(ll)->value;
}

int reserve(Link* ll)
{
	if (empty(ll)) return 0;
	Node* pre = NULL;
	Node* temp = ll->head->next;
	Node* nextptr = temp;
	while (temp)
	{
		nextptr = nextptr->next;
		temp->next = pre;
		pre = temp;
		temp = nextptr;
	}
	ll->head->next = pre;
	return 1;
}

void bubble(Link* ll) // 排序，采用冒泡，只交换数据域
{
	if (ll->length < 2) return;
	for (int i = 0; i < ll->length; ++i)
	{
		for (Node* i = ll->head->next; i->next; i = i->next)
		{
			if (i->value > i->next->value)
				swap(&(i->value), &(i->next->value));
		}
	}
}

int Bubble(Link* ll) // 冒泡，但是重新组织结点关系
{
	if (ll->length < 1) return 0;
	if (ll->length < 2) return 1;
	for (int end = ll->length - 1; end > 0; --end)
	{
		Node* pre = ll->head;
		Node* temp = ll->head->next;
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
				//swapElem(temp, nextptr);
				Node* p = temp;
				temp = nextptr;
				nextptr = p;
			}
			/*-----------*/
			pre = temp;
			temp = nextptr;
		}
	}
	return 1;
}

int main()
{
	return 0;
}