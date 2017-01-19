//:AVLTree.c
//
#include "AVLTree.h"

//Construct AVLNode
struct AVLNode
{
    int Element;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

AVLTree MakeEmpty(AVLTree T)
{
    if(T != NULL)
    {
	MakeEmpty(T->Left);
	MakeEmpty(T->Right);
	free(T);
    }
    return NULL;
}

Position Find(int x,AVLTree T)
{
    if(T == NULL)
	return NULL;
    if(x < T->Element)
    	return Find(x,T->Left);
    else if(x > T->Element)
	return Find(x,T->Right);
    else return T;
}

Position FindMin(AVLTree T)
{
    if(T == NULL)
	return NULL;
    else if(T->Left == NULL)
	return T;
    else FindMin(T->Left);
}

Position FindMax(AVLTree T)
{
    if(T != NULL)
	while(T->Right != NULL)
	    T = T->Right;
    return T;
}

AVLTree Insert(int x,AVLTree T)
{
    if(T == NULL)
    {
	//create one Node tree
	T=malloc(sizeof(struct AVLNode));
	T->Element=x;
	T->Left=NULL;
	T->Right=NULL;
	T->Height=0;
    }
    else if(x<T->Element)
    {
	T->Left=Insert(x,T->Left);
	if(Height(T->Left) - Height(T->Right) == 2)
	    if(x<T->Left->Element)
		T = SingleRotateWithLeft(T);
	    else
		T = DoubleRotateWithLeft(T);
    }
    else if(x>T->Element)
    {
	T->Right=Insert(x,T->Right);
	if(Height(T->Left) - Height(T->Right) == -2)
	    if(x>T->Right->Element)
		T = SingleRotateWithRight(T);
	    else
		T = DoubleRotateWithRight(T);
    }
    //ELSE the value is in the tree, so we do nothing
    T->Height = Max(Height(T->Left),Height(T->Right))+1;
    return T;
}
/*
void InsertWithoutRecursive(int x,AVLTree T)
{
    Position P=T;
    if(T == NULL)
    {
	//create one Node tree
	T=malloc(sizeof(struct AVLNode));
	T->Element=x;
	T->Left=NULL;
	T->Right=NULL;
	T->Height=0;
    }
    else
    while(P != NULL)
    {
	++P->Height;
	if(x<T->Element)
	{
	    if(P->Left == NULL)
	    {
		
	    }
	    P=P->Left;
	}
    }
}
*/
AVLTree SingleRotateWithLeft(AVLTree T)
{
    Position P=T;
    T = T->Left;
    P->Left = T->Right;
    T->Right = P;
    P->Height = Max(Height(P->Left),Height(P->Right))+1;
    T->Height = Max(Height(T->Left),P->Height)+1;
    return T;
}

AVLTree SingleRotateWithRight(AVLTree T)
{
    Position P=T;
    T = T->Right;
    P->Right = T->Left;
    T->Left = P;
    P->Height = Max(Height(P->Left),Height(P->Right))+1;
    T->Height = Max(Height(T->Right),P->Height)+1;
    return T;
}

AVLTree DoubleRotateWithLeft(AVLTree T)
{
    Position P=T;
    T=T->Left->Right;
    P->Left->Right=T->Left;
    P->Left->Height=Max(Height(P->Left->Left),Height(P->Left->Right))+1; 
    T->Left=P->Left;
    P->Left=T->Right;
    T->Right=P;
    P->Height = Max(Height(P->Left),Height(P->Right))+1;
    T->Height = Max(Height(T->Right),P->Height)+1;
    return T;
}

AVLTree DoubleRotateWithRight(AVLTree T)
{
    Position P=T;
    T=T->Right->Left;
    P->Right->Left=T->Right;
    P->Right->Height=Max(Height(P->Right->Left),Height(P->Right->Right))+1; 
    T->Right=P->Right;
    P->Right=T->Left;
    T->Left=P;
    P->Height = Max(Height(P->Left),Height(P->Right))+1;
    T->Height = Max(Height(T->Left),P->Height)+1;
    return T;
}

AVLTree CheckAVLTree(AVLTree T)
{
    if(Height(T->Left) - Height(T->Right) == 2)
    {
	if(T->Left->Left->Height >= T->Left->Right->Height)
	    T = SingleRotateWithLeft(T);
   	else
	    T = DoubleRotateWithLeft(T);
    }
    if(Height(T->Left) - Height(T->Right) == -2)
    {
	if(T->Right->Right->Height >= T->Right->Left->Height)
	    T = SingleRotateWithRight(T);
   	else
	    T = DoubleRotateWithRight(T);
    }
    return T;
}

AVLTree Delete(int x,AVLTree T)
{
    Position TmpCell;
    if(x < T->Element)
    {
	T->Left = Delete(x,T->Left);
    	T->Height = Max(Height(T->Left),Height(T->Right))+1;
	T = CheckAVLTree(T);
    }
    else if(x > T->Element)
    {
	T->Right = Delete(x,T->Right);
    	T->Height = Max(Height(T->Left),Height(T->Right))+1;
	T = CheckAVLTree(T);
    }
    else
    {
    	if(T->Left && T->Right)
    	{
	    TmpCell = FindMin(T->Right);
	    T->Element = TmpCell->Element;
	    T->Right = Delete(T->Element,T->Right);
    	    T->Height = Max(Height(T->Left),Height(T->Right))+1;
	    T = CheckAVLTree(T);
    	}
	else if(T->Left)
	{
	    TmpCell = T->Left;
	    T->Element = TmpCell->Element;
	    T->Left = NULL;
	    T->Height = 0;
	    free(TmpCell);
	}
	else if(T->Right)
	{
	    TmpCell = T->Right;
	    T->Element = TmpCell->Element;
	    T->Right = NULL;
	    T->Height = 0;
	    free(TmpCell);
	}
	else
	{
	    TmpCell = T;
	    T = NULL;
	    free(TmpCell);
    	}
    	//T->Height = Max(Height(T->Left),Height(T->Right))+1;
    }
    return T;
}

void Print(AVLTree T)
{
    if(T != NULL)
    {
	printf("the element is: %d and the height is: %d\n",T->Element,T->Height);
	Print(T->Left);
	Print(T->Right);
    }
}

void PrintWithLevelOrder(AVLTree T)
{
    Queue Q = CreateQueue();
    Position tmp = T;
    Q = Enqueue(tmp,Q);
    while(Q->Front != NULL)
    {
	tmp = Q->Front->Element;
	printf("the element is: %d and the Height is: %d\n",tmp->Element,tmp->Height);
	if(tmp->Left != NULL)
	    Q = Enqueue(tmp->Left,Q);
	if(tmp->Right != NULL)
	    Q = Enqueue(tmp->Right,Q);
	Q = Dequeue(Q);
    }
}

int CountNodes(AVLTree T)
{
    if(T == NULL) 
	return 0;
    return 1+CountNodes(T->Left)+CountNodes(T->Right);
}

int CountLeaves(AVLTree T)
{
    if(T == NULL)
	return 0;
    else if(T->Left == NULL && T->Right == NULL)
	return 1;
    return CountLeaves(T->Left)+CountLeaves(T->Right);
}

int CountFull(AVLTree T)
{
    if(T == NULL)
	return 0;
    return (T->Left != NULL && T->Right != NULL)+CountFull(T->Left)+CountFull(T->Right);
}

static int Height(Position P)
{
    if(P == NULL)
	return -1;
    else
	return P->Height;
}

int Max(int a,int b)
{
    return a>=b?a:b;
}
