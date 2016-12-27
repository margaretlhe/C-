#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  int getMinimum() const;
  void addElement(int value);//if room, add to values
  void giveleft(int value);//look to the left, check if can pass elements
  void giveRight(int value);//look right, check if can pass elements
  LeafNode* split(int value);
  LeafNode* insert(int value); // returns pointer to new Leaf if splits
  // else NULL
  void print(Queue <BTreeNode*> &queue);
}; //LeafNode class

#endif