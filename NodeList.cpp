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
    // delete[] nodes;
    // delete[] *nodes;
}

NodeList::NodeList(NodeList& other){
    // TODO
    for (int i = 0; i < other.getLength(); ++i)
    {
        this->nodes[i] = other.nodes[i];
    }
    this->length = other.getLength();
}

int NodeList::getLength(){
    // TODO
    return this->length;
}

void NodeList::addElement(Node* newPos){
    // TODO
    nodes[length] = newPos;
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
        if (this->getNode(i)->isEqual(node))
        {
            isContained = true;
        }
    }
    return isContained;
}

std::string NodeList::printLatestNode()
{
    return this->getNode(this->length-1)->getNodeCoordinatesStr();
}