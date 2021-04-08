#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
   this->length = 0;
   this->nodes = new Node*[this->length];
}

NodeList::~NodeList()
{
   for (int i = 0; i < this->length; ++i)
   {
      delete this->nodes[i];
   }
   delete[] this->nodes;
   this->nodes = nullptr;
}

NodeList::NodeList(NodeList& other)
{
   this->length = other.getLength();
   nodes = new Node*[length];
   for (int i = 0; i < other.getLength(); ++i)
   {
      this->nodes[i] = new Node(*other.getNode(i));
   }
}

int NodeList::getLength()
{
   return this->length;
}


/**
 * This implementation of adding an element is inefficient when it comes to
 * time (as it has to copy an array every time an element is added), but is
 * memory efficient as it does not store any unused variables. Alternatively,
 * the array could instead double it's size (rather than adding one). This
 * would benefit the time complexity, with a small tradeoff for the space
 * complexity. I have implemented it this way, as this is what I understood
 * was expected as per the assignment specification.
 */

// Add a new node to the nodes attribute of NodeList
// Dynamically resize nodes array to the number of nodes stored inside
void NodeList::addElement(Node* newPos)
{
   // Create a temporary list and deep copy all values of original list into it
   Node** tempList = new Node*[this->length];
   for (int i = 0; i < this->length; ++i)
   {
      tempList[i] = new Node(*nodes[i]);
   }

   // Completely delete all original nodes
   for (int i = 0; i < this->length; ++i)
   {
      delete this->nodes[i];
      this->nodes[i] = nullptr;
   }
   delete[] this->nodes;
   this->nodes = nullptr;

   // Create a new nodes array with 1 extra length
   this->nodes = new Node*[length+1];

   // Copy the values from tempList to nodes
   // Simultaneously delete tempList nodes as they are copied
   for (int i = 0; i < this->length; ++i)
   {
      this->nodes[i] = new Node(tempList[i]->getRow(),
                                tempList[i]->getCol(),
                                tempList[i]->getDistanceTraveled());
      delete tempList[i];
      tempList[i] = nullptr;
   }
   delete[] tempList;
   tempList = nullptr;

   // Add the new position to the nodes array
   nodes[length] = new Node(*newPos);

   // Increment the length counter
   length++;
}

Node* NodeList::getNode(int i)
{
   return nodes[i];
}

// Checks if the calling nodelist contains the given node within it
bool NodeList::containsNode(Node node)
{
   // Search through every element of current NodeList
   // Check each node and see if it is equal to the passed in node
   bool isContained = false;
   for (int i = 0; i < this->length; ++i)
   {
      if (this->getNode(i)->isEqual(&node))
      {
         isContained = true;
      }
   }
   return isContained;
}

// Returns the node after the given index
Node* NodeList::getNextNode(int nodeIndex)
{
   Node* nextNode = nullptr;
   if (nodeIndex < this->getLength()-1)
   {
      nextNode = this->getNode(nodeIndex+1);
   }
   return nextNode;
}
