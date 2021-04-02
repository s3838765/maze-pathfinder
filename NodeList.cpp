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
}

NodeList::~NodeList(){
    // TODO
    for (int i = 0; i < this->length; ++i)
    {
        delete this->getNode(i);
    }
}

NodeList::NodeList(NodeList& other){
    // TODO
    for (int i = 0; i < other.getLength(); ++i)
    {
        // this->nodes[i] = other.nodes[i];
        this->nodes[i] = new Node(other.getNode(i)->getRow(), 
                                  other.getNode(i)->getCol(), 
                                  other.getNode(i)->getDistanceTraveled());
    }
    this->length = other.getLength();
}

int NodeList::getLength(){
    // TODO
    return this->length;
}

void NodeList::addElement(Node* newPos){
    // TODO
    // nodes[length] = newPos;
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

// bool NodeList::containsNode(Node* node)
// {
//     bool isContained = false;
//     // Search through every element of current NodeList
//     for (int i = 0; i < this->length; ++i)
//     {
//         if (this->getNode(i)->isEqual(node))
//         {
//             isContained = true;
//         }
//     }
//     return isContained;
// }

std::string NodeList::printLatestNode()
{
    return this->getNode(this->length-1)->getNodeCoordinatesStr();
}