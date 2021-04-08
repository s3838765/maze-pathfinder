#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled)
{
   this->row = row;
   this->col = col;
   this->dist_traveled = dist_traveled;
}

Node::~Node()
{
}

int Node::getRow()
{
   return row;
}

int Node::getCol()
{
   return col;
}

int Node::getDistanceTraveled()
{
   return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
   this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal)
{
   int manhattanDistance = std::abs(this->col - goal->getCol()) + 
                           std::abs(this->row - goal->getRow());
   int estimatedDistance = dist_traveled + manhattanDistance;
   return estimatedDistance;
}

//--------------------------------                             

// Copy constructor
Node::Node(const Node& other)
{
   this->row = other.row;
   this->col = other.col;
   this->dist_traveled = other.dist_traveled;
}

// Checks if the locations of two nodes are equal
bool Node::isEqual(Node* node)
{
   return this->row == node->getRow() && 
          this->col == node->getCol(); 
}

// Checks if calling node can move to the target node
bool Node::canReach(Node* targetNode, Env env)
{
   bool canReach = false;
   if (this->getUpNode(env).isEqual(targetNode) ||
       this->getDownNode(env).isEqual(targetNode) ||
       this->getLeftNode(env).isEqual(targetNode) ||
       this->getRightNode(env).isEqual(targetNode))
   {
      canReach = true;
   }
   return canReach;
}

// Return character of node above the calling node
char Node::getUpChar(Env env)
{
   return env[this->row-1][this->col];
}

// Return character of node below the calling node
char Node::getDownChar(Env env)
{
   return env[this->row+1][this->col];
}

// Return character of node to the left of the calling node
char Node::getLeftChar(Env env)
{
   return env[this->row][this->col-1];
}

// Return character of node to the right of the calling node
char Node::getRightChar(Env env)
{
   return env[this->row][this->col+1];
}

// Return node above the calling node
Node Node::getUpNode(Env env)
{
   return Node(this->row-1, this->col, this->dist_traveled+1);
}

// Return node below the calling node
Node Node::getDownNode(Env env)
{
   return Node(this->row+1, this->col, this->dist_traveled+1);
}

// Return node to the left of the calling node
Node Node::getLeftNode(Env env)
{
   return Node(this->row, this->col-1, this->dist_traveled+1);
}

// Return node to the right of the calling node
Node Node::getRightNode(Env env)
{
   return Node(this->row, this->col+1, this->dist_traveled+1);
}
