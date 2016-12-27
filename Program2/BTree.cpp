#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;

BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  root = new LeafNode(LSize, NULL, NULL, NULL); //create root
} // BTree::BTree()


void BTree::insert(const int value)
{ // students must write this 
  BTreeNode *bt = root->insert(value);
  //cout << "BTREE"<<endl;
  if(bt != NULL)
  {
    InternalNode *in = new InternalNode(internalSize, leafSize, NULL, NULL, NULL);
    in->insert(root, bt);
    root = in;
  }//REMEMBER TO UPDATE THIS WHEN FINISHED. FOR TESTING ONLY

} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);

  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()