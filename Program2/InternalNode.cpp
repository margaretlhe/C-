//Margaret He, Jordan Schultz
#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize, InternalNode *p, BTreeNode *left, BTreeNode *right) :
BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


void InternalNode::addChildren(BTreeNode *c)
{
  update();//see if necessary! (is your smallest key == the smallest number?)
 // cout << "addCHildren first line " << c->getMinimum() << keys[count-1] <<endl;
  if(count == 0) //if there are no current children
  {
    children[0] = c;
    keys[0] = c->getMinimum(); 
    //count++;
   // cout << "first one" << endl;
  }
  else if(c->getMinimum() > keys[count-1])//smallest child is > than current max
  {
     // cout << "second one" << endl;
      children[count] = c;
      keys[count] = c->getMinimum();  
  }//if
  else if(c->getMinimum() < getMinimum())//if smallest
  { 
   // cout << "Third one " << endl; 
    for(int i = count ; i > 0 ; i--)
    {
      keys[count] = keys[count -1];//move everything to the right
      children[count]=children[count-1]; 
    }//for
    keys[0] = c->getMinimum();
    children[0] = c;
  }//if
  else //if in between, place in correct place, update child accordingly.
  {
    int i;
    for(i = count-1 ; i >= 0 && keys[i] > c->getMinimum(); i--){
      keys[i+1] = keys[i];
      children[i+1] = children[i];
    }
    keys[i+1] = c->getMinimum();
    children[i+1] = c;
    //count++;
  }//else 
  count++;
  c->setParent(this);
  update();//necessary?!
}//addChildren

void InternalNode::update()
{
  int check = 0;
  while(check < count)
  { 
    keys[check] = children[check]->getMinimum();
    check++;
  }//while
//check if this is really necessary! 
}//update 

InternalNode* InternalNode::insert(int value)
{
  int i,f;
  /*
  for(f = count -1; f > 0; f--)
    if(keys[f] > value) //starting with the largest key
      break;

  BTreeNode *first = children[f]->insert(value);
  BTreeNode *second = children[f]->insert(value);
  if(!second)
    return NULL;
  
  if(count < internalSize)
  {
   addElement(value);
   return NULL;
   count++;
  }//add regularly
  
  if(leftSibling && leftSibling->getCount() < internalSize)
  {
    giveleft(value);
  }//if
  
  else
    if(rightSibling && rightSibling->getCount() < internalSize)
    {
      giveright(value);
      return NULL;
    }//if
    else
		return split(value);
	*/


bool found = false;

BTreeNode* node = NULL;
InternalNode* split = NULL; 

for(int i = 0 ; i < count; i++){
  if(value < keys[i]){  // if it's the smallest value
    if(i ==0) 
      node = children[i]->insert(value);
    else
      node = children[i-1]->insert(value);
    found = true;
    break;
  }
}
if(!found)
  node = children[count-1]->insert(value); // insert into the last child node if the value is largest

if(node){ // if there was a split
  if(count < internalSize){  // and if there's room to add another internal node
    cout<< "hello" << endl;
    insert(node);
  }  
else //try to give to everyone else
  {
    if(leftSibling && leftSibling->getCount() < internalSize)  //if there exists a leftSibling and if it's not full
    {
      ((InternalNode*)leftSibling)->insert(children[0]);
      addChildren(node);
      for(int i = 0;i < count; i++){
        keys[i] = keys[i+1];
        children[i] = children[i+1];
      }
      count--;
    }//if


  }//else
   // split = insertWhenFull(node);
}
  
  update();
cout << "finally" << endl;
/*

  for(i = count -1 ; i > 0 ; i--)
  {
    if(value > keys[i])
      break; 
  }
   children[i]->insert(value);
*/
  return NULL;

 // }//for


/*//change this remember that you don't have to manipulate leaf node with this class, 
 * only internal node, split left right/ etc update pointers.
  int i;
*/
} // InternalNode::insert()

InternalNode* InternalNode::Split(int value)
{
  InternalNode *newInt = new InternalNode(internalSize,leafSize,parent,this,rightSibling);
  if(rightSibling != NULL)
    rightSibling->setLeftSibling(newInt);
  rightSibling = newInt;

  for(int i = (internalSize+1)/2; i <= internalSize; i++)
  {
    newInt->keys[newInt->count] = keys[i];
    newInt->count++;
//    newInt->children[newInt->count] = 

  } 
  
  return NULL;
  
  
}


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  addChildren(oldRoot);
  addChildren(node2);
 

} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
	if ((rightSibling) && (rightSibling->getCount() < leafSize))
	  cout << "count < internalsize"<< count << internalSize<< endl;
	  if(count < internalSize)
		addChildren(newNode);
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()




