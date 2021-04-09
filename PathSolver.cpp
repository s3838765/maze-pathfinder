#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver() 
{
}

PathSolver::~PathSolver() 
{
   delete nodesExplored;
}

// Original forwardSearch, still works, assuming the environment is 20x20
void PathSolver::forwardSearch(Env env) 
{
   NodeList* openList = new NodeList();
   NodeList* closedList = new NodeList();
   Node* currentNode = nullptr;
   Node* goalNode = nullptr;

   // Scan through environment to find start and goal node locations
   for (int row = 0; row < ENV_DIM; ++row)
   {
      for (int col = 0; col < ENV_DIM; ++col)
      {
         if (env[row][col] == SYMBOL_START)
         {
            // Node* tempNode = new Node(row, col, 0);
            // openList->addElement(tempNode);
            openList->addElement(new Node(row, col, 0));
            // delete tempNode;
            delete currentNode;
            currentNode = new Node(*openList->getNode(0));
         }
         else if (env[row][col] == SYMBOL_GOAL)
         {
            delete goalNode;
            goalNode = new Node(row, col, 0);
         }
      }
   }

   // Loop through algorithm until goal node is reached (or not reachable)
   do
   {
      // Node* tempNode = nullptr;
      // Add reachable nodes (unexplored non-walls) to the open list
      // UP
      if ((currentNode->getUpChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getUpNode(env))) ||
          currentNode->getUpNode(env).isEqual(goalNode))
      {
         // tempNode = new Node(currentNode->getUpNode(env));
         // openList->addElement(tempNode);
         openList->addElement(new Node(currentNode->getUpNode(env)));
         // delete tempNode;
      }
      // DOWN
      if ((currentNode->getDownChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getDownNode(env))) ||
          currentNode->getDownNode(env).isEqual(goalNode))
      {
         // tempNode = new Node(currentNode->getDownNode(env));
         // openList->addElement(tempNode);
         openList->addElement(new Node(currentNode->getDownNode(env)));
         // delete tempNode;
      }
      // LEFT
      if ((currentNode->getLeftChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getLeftNode(env))) ||
          currentNode->getLeftNode(env).isEqual(goalNode))
      {
         // tempNode = new Node(currentNode->getLeftNode(env));
         // openList->addElement(tempNode);
         openList->addElement(new Node(currentNode->getLeftNode(env)));
         // delete tempNode;
      }
      // RIGHT
      if ((currentNode->getRightChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getRightNode(env))) ||
          currentNode->getRightNode(env).isEqual(goalNode))
      {
         // tempNode = new Node(currentNode->getRightNode(env));
         // openList->addElement(tempNode);
         openList->addElement(new Node(currentNode->getRightNode(env)));
         // delete tempNode;
      }
      // tempNode = nullptr;

      // Set current node to the closest (estimated) node
      Node previousNode = Node(0,0,0);
      bool currentNodeMoved = false;
      for (int i = 0; i < openList->getLength(); ++i)
      {
         Node* iterationNode = openList->getNode(i);

         // If the current iteration is a valid position to move to
         if (!iterationNode->isEqual(currentNode) &&
             !closedList->containsNode(*iterationNode))
         {
            // Move the current node to the first valid node
            if (!currentNodeMoved)
            {
               previousNode = *currentNode;
               delete currentNode;
               currentNode = new Node(*iterationNode);
               currentNodeMoved = true;
            }
            // Move the current node to any nodes that are closer
            if (iterationNode->getEstimatedDist2Goal(goalNode) <
                currentNode->getEstimatedDist2Goal(goalNode) &&
                !iterationNode->isEqual(&previousNode))
            {
               delete currentNode;
               currentNode = new Node(*iterationNode);
            }
         }
      }

      // If there are still nodes to be added to the closed list
      if (openList->getLength() != closedList->getLength() &&
          !currentNode->isEqual(goalNode))
      {
         // The current node has moved to a reachable node
         if (currentNodeMoved)
         {
            closedList->addElement(&previousNode);
         }
         // The node has not moved (there are no more reachable nodes)
         else
         {
            closedList->addElement(currentNode);
         }
      }
      // If the goal is reached
      else if (openList->getLength() != closedList->getLength() && 
               currentNode->isEqual(goalNode))
      {
         // Add both previous and current nodes to closed list
         // This is done because the while loop will not do another iteration
         // So we need to add the required nodes to the closed list
         closedList->addElement(&previousNode);
         closedList->addElement(currentNode);
      }
      
      // If the goal node cannot be reached (everything has been explored)
      if (openList->getLength() == closedList->getLength() &&
         !currentNode->isEqual(goalNode))
      {
         // Print all visited nodes with an 'x'
         printVisitedNodes(env, *closedList, ENV_DIM, ENV_DIM);
      }

   }
   while (!currentNode->isEqual(goalNode) && 
          openList->getLength() != closedList->getLength());

   // Deep copy the closed list to nodesExplored
   this->nodesExplored = new NodeList(*closedList);

   // Free memory
   delete currentNode;
   delete openList;
   delete closedList;
   delete goalNode;
   currentNode = nullptr;
   openList = nullptr;
   closedList = nullptr;
   goalNode = nullptr;
}

// Milestone 4 forwardSearch, can search through environments of any size
void PathSolver::forwardSearch(Env env, int rows, int cols) 
{
   NodeList* openList = new NodeList();
   NodeList* closedList = new NodeList();
   Node* currentNode = nullptr;
   Node* goalNode = nullptr;

   // Scan through environment to find start and goal node locations
   for (int row = 0; row < rows; ++row)
   {
      for (int col = 0; col < cols; ++col)
      {
         if (env[row][col] == SYMBOL_START)
         {
            currentNode = new Node(row, col, 0);
            openList->addElement(currentNode);
         }
         else if (env[row][col] == SYMBOL_GOAL)
         {
            goalNode = new Node(row, col, 0);
         }
      }
   }

   // Loop through algorithm until goal node is reached (or not reachable)
   do
   {
      // Add reachable nodes (unexplored non-walls) to the open list
      // Temp nodes are used to add nodes to the open list without causing leaks
      Node* tempNode = nullptr;
      // UP
      if ((currentNode->getUpChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getUpNode(env))) ||
          currentNode->getUpNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getUpNode(env));
         openList->addElement(tempNode);
         delete tempNode;
      }
      // DOWN
      if ((currentNode->getDownChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getDownNode(env))) ||
          currentNode->getDownNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getDownNode(env));
         openList->addElement(tempNode);
         delete tempNode;
      }
      // LEFT
      if ((currentNode->getLeftChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getLeftNode(env))) ||
          currentNode->getLeftNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getLeftNode(env));
         openList->addElement(tempNode);
         delete tempNode;
      }
      // RIGHT
      if ((currentNode->getRightChar(env) == SYMBOL_EMPTY &&
          !openList->containsNode(currentNode->getRightNode(env))) ||
          currentNode->getRightNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getRightNode(env));
         openList->addElement(tempNode);
         delete tempNode;
      }
      tempNode = nullptr;

      // Set current node to the closest (estimated) node
      Node previousNode = Node(0,0,0);
      bool currentNodeMoved = false;
      for (int i = 0; i < openList->getLength(); ++i)
      {
         Node* iterationNode = openList->getNode(i);

         // If the current iteration is a valid position to move to
         if (!iterationNode->isEqual(currentNode) &&
             !closedList->containsNode(*iterationNode))
         {
            // Move the current node to the first valid node
            if (!currentNodeMoved)
            {
               previousNode = *currentNode;
               delete currentNode;
               currentNode = new Node(*iterationNode);
               currentNodeMoved = true;
            }
            // Move the current node to any nodes that are closer
            if (iterationNode->getEstimatedDist2Goal(goalNode) <
                currentNode->getEstimatedDist2Goal(goalNode) &&
                !iterationNode->isEqual(&previousNode))
            {
               delete currentNode;
               currentNode = new Node(*iterationNode);
            }
         }
      }

      // If there are still nodes to be added to the closed list
      if (openList->getLength() != closedList->getLength())
      {
         // If the goal node is not reached
         if (!currentNode->isEqual(goalNode))
         {
            // If the current node has moved to a reachable node
            if (currentNodeMoved)
            {
               closedList->addElement(&previousNode);
            }
            // If the node has not moved (there are no more reachable nodes)
            else
            {
               closedList->addElement(currentNode);
            }
         }
         // If the goal is reached
         else
         {
            // Add both previous and current nodes to closed list
            // This is done because the while loop will not do another iteration
            // So we need to add the required nodes to the closed list
            closedList->addElement(&previousNode);
            closedList->addElement(currentNode);
         }
      }
      
      // If the goal node cannot be reached (everything has been explored)
      if (openList->getLength() == closedList->getLength() &&
         !currentNode->isEqual(goalNode))
      {
         // Print all visited nodes with an 'x'
         printVisitedNodes(env, *closedList, rows, cols);
      }
   }
   while (!currentNode->isEqual(goalNode) && 
          openList->getLength() != closedList->getLength());

   // Deep copy the closed list to nodesExplored
   this->nodesExplored = new NodeList(*closedList);

   // Free memory
   delete currentNode;
   delete openList;
   delete closedList;
   delete goalNode;
   currentNode = nullptr;
   openList = nullptr;
   closedList = nullptr;
   goalNode = nullptr;
}

// Returns a deep copy of the explored NodeList in forward search
NodeList* PathSolver::getNodesExplored() 
{
   return new NodeList(*nodesExplored);
}

// Use explored nodes to generate the shortest path from S to G
NodeList* PathSolver::getPath(Env env)
{
   // Set tracking node to last node explored (goal node), add to optimal path
   NodeList* optimalPath = new NodeList();
   Node* trackingNode = nodesExplored->getNode(nodesExplored->getLength()-1);
   optimalPath->addElement(trackingNode);

   // Scan through nodesExplored backwards, add reachable nodes to optimal path
   for (int i = nodesExplored->getLength()-1; i > 0; --i)
   {
      Node* iterationNode = nodesExplored->getNode(i);

      // If the iteration node can be reached from the tracking node
      if (trackingNode->canReach(iterationNode, env))
      {
         // Move tracking nodes position & add to optimal path
         trackingNode = iterationNode;
         optimalPath->addElement(iterationNode);
      }
   }

   // Reverse optimal path
   for (int i = 0; i < optimalPath->getLength()/2; ++i)
   {
      Node temp = *optimalPath->getNode(i);
      *optimalPath->getNode(i) = 
                           *optimalPath->getNode(optimalPath->getLength()-1-i);
      *optimalPath->getNode(optimalPath->getLength()-1-i) = temp;
   }
   return optimalPath;
}

//--------------------------------                             

// Prints given maze along with the visited nodes marked as 'x'
void PathSolver::printVisitedNodes(Env env, NodeList visitedList, int rows, 
                                                                       int cols)
{
   Node* startNode = visitedList.getNode(0);
   for (int row = 0; row < rows; ++row)
   {
      for (int col = 0; col < cols; ++col)
      {
         // Print 'x' for every visited node, but do not cover the start node
         if (visitedList.containsNode(Node(row, col, 0)) &&
             !Node(row, col, 0).isEqual(startNode))
         {
            std::cout << "x";
         }
         else
         {
            std::cout << env[row][col];
         }
      }
      if (row != rows-1)
      {
         std::cout << std::endl;
      }
   }
}
