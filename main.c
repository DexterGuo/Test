
#include "AVLTree.h"

int main()
{
    AVLTree tree=NULL;
    tree = Insert(2,tree);    
    tree = Insert(1,tree);    
    tree = Insert(4,tree);    
    tree = Insert(5,tree);    
    tree = Insert(9,tree);    
    tree = Insert(3,tree);    
    tree = Insert(6,tree);    
    tree = Insert(7,tree);    
    printf("=========Insert=========\n");
    Print(tree);
    printf("=========Find=========\n");
    Position Pf=Find(6,tree);
    Position Pmin=FindMin(tree);
    Position Pmax=FindMax(tree);
    Print(Pf);
    Print(Pmin);
    Print(Pmax);
    printf("=========Insert 8=========\n");
    tree = Insert(8,tree);    
    Print(tree);
    printf("=========Delete 2 and 3=========\n");
    tree = Delete(2,tree);
    tree = Delete(3,tree);
    Print(tree);
    printf("==================\n");
    printf("the Nodes:%d ,the Leaves:%d ,the Fullnodes:%d \n",CountNodes(tree),CountLeaves(tree),CountFull(tree));
    printf("==================\n");
    PrintWithLevelOrder(tree);
    printf("==================\n");
    return 0;
}
