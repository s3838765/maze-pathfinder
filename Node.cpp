/**
 * Represents a position of the robot
 * Tuple (col, row, dist_traveled); The x-y location of the robot and distance it took to reach that position (from start)
 * Contains getters and setters for dist_travelled
 */

#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    // TODO
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){
    // TODO
}

int Node::getRow(){
    // TODO
    return row;
}

int Node::getCol(){
    // TODO
    return col;
}

int Node::getDistanceTraveled(){
    // TODO
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    // TODO
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    // TODO
    int manhattanDistance = std::abs(this->col - goal->getCol()) + std::abs(this->row - goal->getRow());
    int estimatedDistance = dist_traveled + manhattanDistance;
    return estimatedDistance;
}
    
//--------------------------------                             

char Node::getUpChar(Env env)
{
    return env [this->row-1] [this->col];
}

char Node::getDownChar(Env env)
{
    return env [this->row+1] [this->col];
}

char Node::getLeftChar(Env env)
{
    return env [this->row] [this->col-1];
}

char Node::getRightChar(Env env)
{
    return env [this->row] [this->col+1];
}

std::string Node::getNodeCoordinatesStr()
{
    std::string nodeCoordinates;
    nodeCoordinates += "(";
    nodeCoordinates += std::to_string(this->col);
    nodeCoordinates += ",";
    nodeCoordinates += std::to_string(this->row);
    nodeCoordinates += ")";
    return nodeCoordinates;
}

bool Node::isEqual(Node node)
{
    return this->row == node.getRow() && 
           this->col == node.getCol(); 
}

Node Node::getUpNode(Env env)
{
    return Node(this->row-1, this->col, this->dist_traveled+1);
}

Node Node::getDownNode(Env env)
{
    
    return Node(this->row+1, this->col, this->dist_traveled+1);
}

Node Node::getLeftNode(Env env)
{
    
    return Node(this->row, this->col-1, this->dist_traveled+1);
}

Node Node::getRightNode(Env env)
{
    
    return Node(this->row, this->col+1, this->dist_traveled+1);
}

bool Node::canReach(Node targetNode, Env env)
{
    bool isReachable = false;
    if (this->getUpNode(env).isEqual(targetNode) ||
        this->getDownNode(env).isEqual(targetNode) ||
        this->getLeftNode(env).isEqual(targetNode) ||
        this->getRightNode(env).isEqual(targetNode))
    {
        isReachable = true;
    }
    return isReachable;
}
