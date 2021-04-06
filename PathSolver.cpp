/**
 * Executes forward search & backtracking of the path planning algorithm using NodeList and Node Classes
 * 1. forwardSearch: Execute forward search algorithm
 * 2. getNodesExplored: Returns a DEEP COPY of the explored NodeList in forward search
 * 3. getPath: Execute backtracking and get a DEEP COPY of the path the robot should travel (milestone 3)
 */
#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver() {
   // TODO
}

PathSolver::~PathSolver() {
   // TODO
   delete nodesExplored;
}

void PathSolver::forwardSearch(Env env) {
   // TODO
   NodeList* closedList = new NodeList();
   NodeList* openList = new NodeList();
   // NodeList* openList = nullptr;
   // NodeList* closedList = nullptr;
   Node* currentNode = nullptr;
   Node* goalNode = nullptr;
   Node* closestNode = nullptr;

   // Scan environment and find start and goal nodes
   for (int row = 0; row < ENV_DIM; ++row)
   {
      for (int col = 0; col < ENV_DIM; ++col)
      {
         if (env[row][col] == SYMBOL_START)
         {
            Node* tempNode = new Node(row, col, 0);
            openList->addElement(tempNode);
            delete tempNode;
            delete currentNode;
            currentNode = openList->getNode(0);
         }
         else if (env[row][col] == SYMBOL_GOAL)
         {
            delete goalNode;
            goalNode = new Node(row, col, 0);
         }
         // std::cout << env[row][col];
      }
      // std::cout << " " << row << std::endl;
   }
   // std::cout << "Goal Node: " << goalNode->getNodeCoordinatesStr() << std::endl;


   do
   {
      // std::cout << "------------------------------------------" << std::endl;
      Node* tempNode = nullptr;
      // Check up down left right for open spaces, add any possible moves to openList
      // UP
      if ((currentNode->getUpChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getUpNode(env)) &&
         !closedList->containsNode(currentNode->getUpNode(env))) ||
         currentNode->getUpNode(env).isEqual(goalNode))
      {
         // Node* tempNode = new Node(currentNode->getUpNode(env));
         tempNode = new Node(currentNode->getUpNode(env));
         openList->addElement(tempNode);
         delete tempNode;
         // std::cout << "Up element " << openList->printLatestNode()
                                    // << " added to openList" << std::endl;
      }

      // DOWN
      if ((currentNode->getDownChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getDownNode(env)) &&
         !closedList->containsNode(currentNode->getDownNode(env))) ||
         currentNode->getDownNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getDownNode(env));
         openList->addElement(tempNode);
         delete tempNode;
         // std::cout << "Down element " << openList->printLatestNode()
                              // << " added to openList" << std::endl;
      }

      // LEFT
      if ((currentNode->getLeftChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getLeftNode(env)) &&
         !closedList->containsNode(currentNode->getLeftNode(env))) ||
         currentNode->getLeftNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getLeftNode(env));
         openList->addElement(tempNode);
         delete tempNode;
         // std::cout << "Left element " << openList->printLatestNode()
                              // << " added to openList" << std::endl;
      }

      // RIGHT
      if ((currentNode->getRightChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getRightNode(env)) &&
         !closedList->containsNode(currentNode->getRightNode(env))) ||
         currentNode->getRightNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getRightNode(env));
         openList->addElement(tempNode);
         delete tempNode;
         tempNode = nullptr;
         // std::cout << "Right element " << openList->printLatestNode()
                                 // << " added to openList" << std::endl;
      }
      tempNode = nullptr;

      // Find node with smallest estimated distance
      bool closestNodeInitialised = false;
      for (int i = 0; i < openList->getLength(); ++i)
      {
         Node* iterationNode = openList->getNode(i);

         // If node is valid to be closest (not current node and not in closed list)
         if (!iterationNode->isEqual(currentNode) &&
             !closedList->containsNode(*iterationNode))
         {
         if (!closestNodeInitialised)
         {
               // delete closestNode;
               closestNode = iterationNode;
               // std::cout << "Initialising closest node to "
                        //  << closestNode->getNodeCoordinatesStr() << std::endl;
               closestNodeInitialised = true;
         }

         if (iterationNode->getEstimatedDist2Goal(goalNode) <
             closestNode->getEstimatedDist2Goal(goalNode))
         {
               // delete closestNode;
               closestNode = iterationNode;
               // std::cout << "Closest node set to "
                        //  << closestNode->getNodeCoordinatesStr() << std::endl;
         }
         }
      }


      closedList->addElement(currentNode);
      // std::cout << "Previous node " << currentNode->getNodeCoordinatesStr()
               //  << " added to closed list" << std::endl;

      if (openList->getLength() != closedList->getLength() &&
          !closestNode->isEqual(goalNode))
      {
         // std::cout << "Current node is now set to "
                  //  << closestNode->getNodeCoordinatesStr() << std::endl;
         // delete currentNode;
         currentNode = closestNode;
         // printEnv(env, *currentNode);
      }
      // If goal node is found
      else if (closestNode->isEqual(goalNode))
      {
         // Inform user, set it as the current node, add it to the closed list
         // std::cout << "Goal node has been found at " 
                  //  << goalNode->getNodeCoordinatesStr() << std::endl;
         currentNode = closestNode;
         closedList->addElement(currentNode);
         // std::cout << "Goal node added to closed list" << std::endl;
      }
      // No possible moves
      // else if (openList->getLength() == closedList->getLength())
      // {
      //    std::cout << "No possible moves found." << std::endl;
      // }
   }
   while (!currentNode->isEqual(goalNode) && 
          openList->getLength() != closedList->getLength());

   // std::cout << std::endl;
   // printExploredEnv(env, closedList);
   delete openList;
   nodesExplored = new NodeList(*closedList); // For milestone 3
   delete closedList;
   // delete closestNode; // Don't need? (Doesn't affect memory)
   delete goalNode;

   // std::cout << "Exiting pathfinder." << std::endl;
}

void PathSolver::forwardSearch(Env env, int rows, int cols) {
   // TODO
   NodeList* closedList = new NodeList(rows, cols);
   NodeList* openList = new NodeList(rows, cols);
   // NodeList* openList = nullptr;
   // NodeList* closedList = nullptr;
   Node* currentNode = nullptr;
   Node* goalNode = nullptr;
   Node* closestNode = nullptr;

   // Scan environment and find start and goal nodes
   for (int row = 0; row < rows; ++row)
   {
      for (int col = 0; col < cols; ++col)
      {
         if (env[row][col] == SYMBOL_START)
         {
            Node* tempNode = new Node(row, col, 0);
            openList->addElement(tempNode);
            delete tempNode;
            delete currentNode;
            currentNode = openList->getNode(0);
         }
         else if (env[row][col] == SYMBOL_GOAL)
         {
            delete goalNode;
            goalNode = new Node(row, col, 0);
         }
      }
   }

   do
   {
      Node* tempNode = nullptr;
      // Check up down left right for open spaces, add any possible moves to openList
      // UP
      if ((currentNode->getUpChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getUpNode(env)) &&
         !closedList->containsNode(currentNode->getUpNode(env))) ||
         currentNode->getUpNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getUpNode(env));
         openList->addElement(tempNode);
         delete tempNode;
      }

      // DOWN
      if ((currentNode->getDownChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getDownNode(env)) &&
         !closedList->containsNode(currentNode->getDownNode(env))) ||
         currentNode->getDownNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getDownNode(env));
         openList->addElement(tempNode);
         delete tempNode;
      }

      // LEFT
      if ((currentNode->getLeftChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getLeftNode(env)) &&
         !closedList->containsNode(currentNode->getLeftNode(env))) ||
         currentNode->getLeftNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getLeftNode(env));
         openList->addElement(tempNode);
         delete tempNode;
      }

      // RIGHT
      if ((currentNode->getRightChar(env) == SYMBOL_EMPTY &&
         !openList->containsNode(currentNode->getRightNode(env)) &&
         !closedList->containsNode(currentNode->getRightNode(env))) ||
         currentNode->getRightNode(env).isEqual(goalNode))
      {
         tempNode = new Node(currentNode->getRightNode(env));
         openList->addElement(tempNode);
         delete tempNode;
         tempNode = nullptr;
      }
      tempNode = nullptr;

      // Find node with smallest estimated distance
      bool closestNodeInitialised = false;
      for (int i = 0; i < openList->getLength(); ++i)
      {
         Node* iterationNode = openList->getNode(i);

         // If node is valid to be closest (not current node and not in closed list)
         if (!iterationNode->isEqual(currentNode) &&
             !closedList->containsNode(*iterationNode))
         {
         if (!closestNodeInitialised)
         {
               closestNode = iterationNode;
               closestNodeInitialised = true;
         }

         if (iterationNode->getEstimatedDist2Goal(goalNode) <
             closestNode->getEstimatedDist2Goal(goalNode))
         {
               closestNode = iterationNode;
         }
         }
      }

      closedList->addElement(currentNode);

      if (openList->getLength() != closedList->getLength() &&
          !closestNode->isEqual(goalNode))
      {
         currentNode = closestNode;
      }
      // If goal node is found
      // No possible moves
      // else if (openList->getLength() == closedList->getLength())
      // {
      //    // std::cout << "No possible moves found." << std::endl;
      // }
      else if (openList->getLength() != closedList->getLength() && 
               closestNode->isEqual(goalNode))
      {
         // Inform user, set it as the current node, add it to the closed list
         currentNode = closestNode;
         closedList->addElement(currentNode);
      }
   }
   while (!currentNode->isEqual(goalNode) && 
          openList->getLength() != closedList->getLength());

   if (openList->getLength() == closedList->getLength())
   {
      // std::cout << "No possible moves found." << std::endl;
      closedList->addElement(currentNode);
   }

   // std::cout << std::endl;
   // printExploredEnv(env, closedList);
   delete openList;
   nodesExplored = new NodeList(*closedList); // For milestone 3
   delete closedList;
   delete goalNode;
}

NodeList* PathSolver::getNodesExplored(){
   //TODO
   return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env){
   // TODO
   // Set tracking node to last node explored (goal node), add to optimal path
   NodeList* optimalPath = new NodeList();
   Node* trackingNode = nodesExplored->getNode(nodesExplored->getLength()-1);
   // std::cout << "tracking node: " << trackingNode->getNodeCoordinatesStr() << std::endl;
   optimalPath->addElement(trackingNode);
   // std::cout << "tracking node added to optimal path" << std::endl;

   // Scan through nodesExplored backwards and add every reachable node to optimal path
   for (int i = nodesExplored->getLength()-1; i > 0; --i) //>=
   {
      Node* iterationNode = nodesExplored->getNode(i);
      // std::cout << "iteration node: " << iterationNode->getNodeCoordinatesStr() << std::endl;
      if (iterationNode->getDistanceTraveled() == trackingNode->getDistanceTraveled()-1)
      {
         if (trackingNode->canReach(iterationNode, env))
         {
            // std::cout << "tracking node " << trackingNode->getNodeCoordinatesStr()
                     //  << " can reach iteration node at "
                     //  << iterationNode->getNodeCoordinatesStr() << std::endl;
            // delete trackingNode;
            trackingNode = iterationNode;
            // std::cout << "tracking node now equal to " 
                     //  << trackingNode->getNodeCoordinatesStr() << std::endl;
            optimalPath->addElement(iterationNode);
            // std::cout << "iteration node " << iterationNode->getNodeCoordinatesStr()
                     //  << " has been added to the optimal path." << std::endl;
            
         }
      }
   }
   // Reverse optimal path
   for (int i = 0; i < optimalPath->getLength()/2; ++i)
   {
      Node temp = *optimalPath->getNode(i);
      *optimalPath->getNode(i) = *optimalPath->getNode(optimalPath->getLength()-1-i);
      *optimalPath->getNode(optimalPath->getLength()-1-i) = temp;
   }
   return optimalPath;
}

//--------------------------------                             

NodeList* PathSolver::getPath(Env env, int rows, int cols){
   // TODO
   // Set tracking node to last node explored (goal node), add to optimal path
   NodeList* optimalPath = new NodeList(rows, cols);
   Node* trackingNode = nodesExplored->getNode(nodesExplored->getLength()-1);
   optimalPath->addElement(trackingNode);

   // Scan through nodesExplored backwards and add every reachable node to optimal path
   for (int i = nodesExplored->getLength()-1; i > 0; --i) //>=
   {
      Node* iterationNode = nodesExplored->getNode(i);
      if (iterationNode->getDistanceTraveled() == trackingNode->getDistanceTraveled()-1)
      {
         if (trackingNode->canReach(iterationNode, env))
         {
            trackingNode = iterationNode;
            optimalPath->addElement(iterationNode);
         }
      }
   }

   // Reverse optimal path
   for (int i = 0; i < optimalPath->getLength()/2; ++i)
   {
      Node temp = *optimalPath->getNode(i);
      *optimalPath->getNode(i) = *optimalPath->getNode(optimalPath->getLength()-1-i);
      *optimalPath->getNode(optimalPath->getLength()-1-i) = temp;
   }
   return optimalPath;
}