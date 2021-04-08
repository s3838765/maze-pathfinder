/**
 * Provides method for storing Node objects.
 * Stores array of node objects.
 * Need to track the number of position objects
 */
#include "NodeList.h"
#include <iostream>


NodeList::NodeList(){
   // TODO

   this->length = 0;
   // int MAX_DIM = (envRows-2)*(envCols-2);
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

NodeList::NodeList(NodeList& other){
   // TODO
   this->length = other.getLength();
   nodes = new Node*[length];
   for (int i = 0; i < other.getLength(); ++i)
   {
      this->nodes[i] = new Node(*other.getNode(i));
      // this->nodes[i] = new Node(other.getNode(i)->getRow(), 
      //                           other.getNode(i)->getCol(), 
      //                           other.getNode(i)->getDistanceTraveled());
   }
}

// // Overloaded
// NodeList::NodeList(NodeList& other, int rows, int cols){
//    // TODO
//    this->length = other.getLength();
//    int MAX_DIM = (cols-2)*(cols-2);
//    nodes = new Node*[MAX_DIM];
//    for (int i = 0; i < other.getLength(); ++i)
//    {
//       // this->nodes[i] = other.nodes[i];
//       this->nodes[i] = new Node(other.getNode(i)->getRow(), 
//                                 other.getNode(i)->getCol(), 
//                                 other.getNode(i)->getDistanceTraveled());
//    }
// }

int NodeList::getLength(){
   // TODO
   return this->length;
}

// void NodeList::addElement(Node* newPos)
// {
//    nodes[length] = new Node(newPos->getRow(),
//                             newPos->getCol(),
//                             newPos->getDistanceTraveled());
// }

void NodeList::addElement(Node* newPos){
   // TODO
   // Create tempList
   Node** tempList = new Node*[length]; // COPY NODES INTO TEMPLIST
   // Deep copy values from nodes into tempList
   for (int i = 0; i < this->length; ++i)
   {
      tempList[i] = new Node(nodes[i]->getRow(),
                             nodes[i]->getCol(),
                             nodes[i]->getDistanceTraveled());
   }

   // Completely delete nodes
   for (int i = 0; i < length; ++i)
   {
      // std::cout << "Deleting " << this->nodes[i]->getNodeCoordinatesStr() << std::endl;
      delete this->nodes[i];
      this->nodes[i] = nullptr;
   }
   delete[] this->nodes;
   this->nodes = nullptr;

   // Create a new nodes array with 1 extra length
   this->nodes = new Node*[length+1];
   // Copy the values from tempList to nodes
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

   // Add the new value to nodes
   nodes[length] = new Node(newPos->getRow(),
                            newPos->getCol(),
                            newPos->getDistanceTraveled());
   // std::cout << "New node added at index " << length << std::endl;
   // std::cout << "Newest node: " << this->nodes[length]->getNodeCoordinatesStr() << std::endl;
   // std::cout << std::endl;
   length++;
}

Node* NodeList::getNode(int i){
   // TODO
   return nodes[i];
}

bool NodeList::containsNode(Node node)
{
   bool isContained = false;
   // Search through every element of current NodeList
   for (int i = 0; i < this->length; ++i)
   {
      if (this->getNode(i)->isEqual(&node))
      {
         isContained = true;
      }
   }
   return isContained;
}

Node* NodeList::getNextNode(int nodeIndex)
{
   Node* nextNode = nullptr;
   if (nodeIndex < this->getLength()-1)
   {
      nextNode = this->getNode(nodeIndex+1);
   }
   return nextNode;
}
