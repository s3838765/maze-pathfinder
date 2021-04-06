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
   this->nodes = new Node*[length];
}

// Overloaded
NodeList::NodeList(int rows, int cols)
{
   this->length = 0;
   int MAX_DIM = (rows-2)*(cols-2);
   this->nodes = new Node*[MAX_DIM];
}

NodeList::~NodeList(){
   // TODO
   for (int i = 0; i < this->length; ++i)
   {
      delete this->getNode(i);
   }
   delete[] this->nodes;
   nodes = nullptr;
}

NodeList::NodeList(NodeList& other){
   // TODO
   this->length = other.getLength();
   nodes = new Node*[length];
   for (int i = 0; i < other.getLength(); ++i)
   {
      // this->nodes[i] = other.nodes[i];
      this->nodes[i] = new Node(other.getNode(i)->getRow(), 
                                other.getNode(i)->getCol(), 
                                other.getNode(i)->getDistanceTraveled());
   }
}

// Overloaded
NodeList::NodeList(NodeList& other, int rows, int cols){
   // TODO
   this->length = other.getLength();
   int MAX_DIM = (cols-2)*(cols-2);
   nodes = new Node*[MAX_DIM];
   for (int i = 0; i < other.getLength(); ++i)
   {
      // this->nodes[i] = other.nodes[i];
      this->nodes[i] = new Node(other.getNode(i)->getRow(), 
                                other.getNode(i)->getCol(), 
                                other.getNode(i)->getDistanceTraveled());
   }
}

int NodeList::getLength(){
   // TODO
   return this->length;
}

void NodeList::addElement(Node* newPos){
   // TODO
   // delete[] this->nodes;
   // this->nodes = new NodeList*()
   nodes[length] = new Node(newPos->getRow(),
                            newPos->getCol(),
                            newPos->getDistanceTraveled());
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

// Get index of particular node in nodelist
Node* NodeList::getNodeAtIndex(Node node)
{
   Node* returnNode = nullptr;
   for (int i = 0; i < this->length; ++i)
   {
      if (this->getNode(i)->isEqual(&node))
      {
         returnNode = this->getNode(i);
      }
   }
   return returnNode;
}

int NodeList::getNodeIndex(Node node)
{
   int nodeIndex = 0;
   for (int i = 0; i < this->length; ++i)
   {
      if (this->getNode(i)->isEqual(&node))
      {
         nodeIndex = i;
      }
   }
   return nodeIndex;
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

std::string NodeList::printLatestNode()
{
   return this->getNode(this->length-1)->getNodeCoordinatesStr();
}