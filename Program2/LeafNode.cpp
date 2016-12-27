#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


void LeafNode::addElement(int value)
{
  int i;
    for(i = count-1 ; i >= 0 && values[i] > value; i--)  
      values[i+1] = values[i];

    values[i+1] = value;
    count++;
 
//if(parent && value == values[0])
 // parent->update();

}//addElement

void LeafNode::giveleft(int value)
{
  leftSibling->insert(value);

}//giveleft

void LeafNode::giveRight(int value)
{
  rightSibling->insert(value);

}//giveRight

LeafNode* LeafNode::split(int value)
{
  LeafNode *newLeaf= new LeafNode(leafSize, parent, this, rightSibling);
 
  if(rightSibling != NULL) 
    rightSibling->setLeftSibling(newLeaf);  //rightSibling points to leftSibling
  
  // if leaf size is not full
  // value > this max of left leaf
	rightSibling = newLeaf;//current's right sibling = new || rightSibling = newLeaf;

  cout<<"splitting"<< value << endl;
  int last = values[count-1];//last element within values
  if(value > last)//stored for split, can go either way (if the value is greater than the maximum)
    last = value;
  else
  {
    count--;
    addElement(value);
  }//else
    
  //put correct number of elements
  //into each leaf
  for(int i = (leafSize+1)/2; i <= leafSize; i++)  //while leafSize is odd
  {
    newLeaf->values[newLeaf->count] = values[i];
    newLeaf->count++;
    //count--;
  }//for
  newLeaf->count--;
  newLeaf->addElement(last);
  count = (leafSize+1)/2;
  //update parents
  

  if(parent && value == values[0])  
    parent->update();  //update the internal node
  
  return newLeaf;

}//split


LeafNode* LeafNode::insert(int value)
{
 int last;
 if(count < leafSize)
  {
    addElement(value);
    return NULL;
  }//if space available
  else
  {
    //if(leftSibling->getCount() < leafSize)
    if(leftSibling && leftSibling->getCount() < leafSize) //if left & room available
    {
      cout << "trying to pass left " << value << endl;

      if(value < getMinimum())//if the smallest
      {  
		giveleft(value); // remember to update parent
        //return NULL;
      }//if
	  
      else 
      {
        giveleft(values[0]);
		for(int i = 0 ; i < count -1; i++)//shift everything over left
			values[i] = values[i+1];
		count--;
		addElement(value);
/*		last = values[count-1]; //last value
        if(value > last) //find the bigger value of the two
			last = value;
        for(int i = 0 ; i < count -1; i++)//shift everything over left
			values[i] = values[i+1];
		values[count -1] = last;*/
		if(parent)
			parent->update(); 
        //values[0] = value;
	//addElement(value);
        return NULL;
      }//else
    }//if
	
    else
      if(rightSibling && rightSibling->getCount() < leafSize)//if right & room available
      {
        if(value > values[count-1]) //if the value you're trying to insert is > than the max of the current leaf
		{  
			giveRight(value);
			return NULL;
			cout << "Count: " << count << endl;
		}
		
		else 
		{
			giveRight(values[count-1]);//give right largest value
			//addElement(value); 
			values[count-1] = value; //i.e. sets the old value (3) to the new value (2)
			return NULL;
		}//else  
      }//if
      
	  else // if the leaf node is full, split
      {
       return split(value); 
      }

  }//else
  return NULL;
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()