//:AVLTree.h
//function:
//	AVL Tree realizes INSERT DELETE FIND
//program:
//	guo 2016/12/31 released
#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <malloc.h>
#include "../queue/Queue.h"

struct AVLNode;
typedef struct AVLNode *Position;
typedef Position AVLTree;

AVLTree MakeEmpty(AVLTree T);

Position Find(int x,AVLTree T);

Position FindMin(AVLTree T);

Position FindMax(AVLTree T);

AVLTree Insert(int x,AVLTree T);
AVLTree SingleRotateWithLeft(AVLTree T);
AVLTree SingleRotateWithRight(AVLTree T);
AVLTree DoubleRotateWithLeft(AVLTree T);
AVLTree DoubleRotateWithRight(AVLTree T);

AVLTree Delete(int x,AVLTree T);
AVLTree CheckAVLTree(AVLTree T);

void Print(AVLTree T);
void PrintWithLevelOrder(AVLTree T);

static int Height(Position P);
int CountNodes(AVLTree T);
int CountLeaves(AVLTree T);
int CountFull(AVLTree T);

int Max(int a,int b);

#endif//AVLTree.h
