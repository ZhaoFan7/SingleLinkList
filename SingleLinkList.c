#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int DataType;

typedef struct SListNode {
	DataType data;  // 值 
	struct SListNode *Next;  // 指向下一个结点 
} SListNode;


void SListInit(SListNode **First)// 初始化 
{
	assert(First);
	*First= NULL;
}


SListNode * CreateNode(DataType data)//创建结点
{
	SListNode * NewNode = (SListNode *)malloc(sizeof(SListNode));
	assert(NewNode);
	NewNode->Next = NULL;
	NewNode->data = data;
	return NewNode;
}


void SListPushBack(SListNode** First, DataType data)// 尾部插入 
{
	assert(First);
	SListNode * NewNode = CreateNode(data);
	if (*First == NULL)
	{
		*First = NewNode;
		return;
	}
	else
	{
		SListNode * Node = *First;
		for (Node; Node->Next != NULL; Node = Node->Next)
		{}
		Node->Next = NewNode;
	}
}


void SListPushFront(SListNode **First, DataType data)// 头部插入 
{
	assert(First);
	SListNode * NewNode = CreateNode(data);
	NewNode->Next = *First;
	*First = NewNode;
}


void SListPopBack(SListNode **First)// 尾部删除
{
	assert(First);
	assert(*First);
	SListNode * Node = *First;
	if (Node->Next == NULL)
	{
		free(Node);
		*First = NULL;
		return;
	}
	for (Node; Node->Next->Next != NULL; Node = Node->Next)
	{}
	free(Node->Next);
	Node->Next = NULL;
}

void SListPopFront(SListNode **First)// 头部删除 
{
	assert(First);
	assert(*First);
	SListNode *Node = *First;
	*First = (*First)->Next;
	free(Node);
}


void SListInsert(SListNode **First, SListNode *Pos, DataType data)// 给定结点插入，插入到结点前 
{
	assert(First);
	assert(Pos);
	SListNode * NewNode = CreateNode(data);
	SListNode * Node = *First;
	if (*First == NULL)
	{
		*First = NewNode;
		return ;
	}
	for (Node; Node->Next != Pos; Node = Node->Next)
	{}
	Node->Next = NewNode;
	NewNode->Next = Pos;
}


void SListErase(SListNode **First, SListNode *Pos)// 给定结点删除
{
	assert(First);
	assert(*First);
	assert(Pos);
	SListNode * Node = *First;
	if (Pos == *First)
	{
		(*First)= Pos->Next;
		free(Pos);
		return ;
	}
	for (Node; Node->Next != Pos; Node = Node->Next)
	{}
	Node->Next = Pos->Next;
	free(Pos);
}

 
void SListRemove(SListNode **First, DataType data)// 按值删除，只删遇到的第一个
{
	assert(First);
	assert(*First);
	SListNode * Node = *First;
	SListNode * NNode = Node->Next;
	if ((*First)->data == data)
	{
		*First = (*First)->Next;
		free(Node);
		return ;
	}
	for (Node; (NNode->data != data) && (Node != NULL); Node = Node->Next,NNode = Node->Next)
	{}
	if (NNode->data == data)
	{
		Node->Next = NNode->Next;
		free(NNode);
	}
	else
	  printf("没找到\n");
}


void SListRemoveAll(SListNode **First, DataType data)// 按值删除，删除所有的data
{
	assert(First);
	assert(*First);
	SListNode * cur = *First;
	SListNode * per= NULL;
	while (cur)
	{
		if (cur->data == data)
		{
			if (*First == cur)
			{
				*First = cur->Next;
				free(cur);
				cur = *First;
			}
			else
			{
				per->Next = cur->Next;
				free(cur);
				cur = per->Next;
			}
		}
		else
		{
			per = cur;
			cur = cur->Next;
		}
	}
}


void SListDestroy(SListNode **First)// 销毁 
{
	assert(First);
	SListNode * Node = *First;
	SListNode * NNode = (*First)->Next;
	if (NNode == NULL)
	  free(NNode);
	for (Node; Node != NULL; Node = Node->Next, NNode = NNode->Next)
	{
		free(Node);
		(*First)->Next = NNode;
	}
}


SListNode * SListFind(SListNode *First, DataType data)// 按值查找，返回第一个找到的结点指针，如果没找到，返回 NULL 
{
	assert(First);
	SListNode * Node = First;
	for (Node; Node->data != data&&Node != NULL; Node = Node->Next)
	{}
	if (Node->data == data)
	{
		return Node;
	}
	else
	  return NULL;
}


void Pirntf(SListNode *First)//打印
{
	assert(First);
	SListNode * Node;
	for (Node = First; Node != NULL; Node = Node->Next)
	{
		printf("%d->", Node->data);
	}
	printf("\n");
}

void test()
{
	SListNode *A;
	SListInit(&A);
	SListPushBack(&A, 3);
	SListPushBack(&A, 3);
	SListPushBack(&A, 4);
	SListPushBack(&A, 3);
	SListPushBack(&A, 4);
	SListPushBack(&A, 3);
	SListPushBack(&A, 5);
	SListPushBack(&A, 4);
	SListPushBack(&A, 6);
	SListPushFront(&A, 2);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	SListPushFront(&A, 1);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	SListPushFront(&A, 3);
	printf("初始状态为：");
	Pirntf(A);
	printf("尾删：");
	SListPopBack(&A);
	Pirntf(A);
	printf("头删：");
	SListPopFront(&A);
	Pirntf(A);
	printf("按位置插入第二个：");
	SListInsert(&A, A->Next, 7);
	Pirntf(A);
	printf("按位置删除第三个：");
	SListErase(&A, A->Next->Next);											
	Pirntf(A);							
	printf("按位置删除第 二个：");
	SListErase(&A, A->Next);
	Pirntf(A);
	printf("按位置删除第一个：");
	SListErase(&A, A);
	Pirntf(A);
	printf("删第一个4：");
	SListRemove(&A, 4);
	Pirntf(A);
	printf("删所有的3：");
	SListRemoveAll(&A, 3);
	Pirntf(A);
	printf("找到4：");
	SListFind(A, 4);
	SListDestroy(&A);
}

int main()
{
		test();
}
