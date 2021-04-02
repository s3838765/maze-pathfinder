/**
 * Executes forward search & backtracking of the path planning algorithm using NodeList and Node Classes
 * 1. forwardSearch: Execute forward search algorithm
 * 2. getNodesExplored: Returns a DEEP COPY of the explored NodeList in forward search
 * 3. getPath: Execute backtracking and get a DEEP COPY of the path the robot should travel (milestone 3)
 */
#include "PathSolver.h"
#include <iostream>
#include <unistd.h>

PathSolver::PathSolver(){
    // TODO
}

PathSolver::~PathSolver(){
    // TODO
    // Deconstruct nodesExplored node list?
    delete this->nodesExplored;
}

void PathSolver::forwardSearch(Env env){
    // TODO
    NodeList* openList = new NodeList();
    NodeList* closedList = new NodeList();
    Node* currentNode = nullptr;
    Node* goalNode = nullptr;
    // Node closestNode = tempNode;
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
            std::cout << env[row][col];
        }
        std::cout << " " << row << std::endl;
    }
    std::cout << "Goal Node: " << goalNode->getNodeCoordinatesStr() << std::endl;


    do 
    {
        std::cout << "------------------------------------------" << std::endl;
        // Check up down left right for open spaces, add any possible moves to openList
        // UP
        if ((currentNode->getUpChar(env) == SYMBOL_EMPTY && 
            !openList->containsNode(currentNode->getUpNode(env)) &&
            !closedList->containsNode(currentNode->getUpNode(env))) ||
            currentNode->getUpNode(env).isEqual(goalNode))
        {
            // openList.addElement(new Node(currentNode->getUpNode(env)));
            Node* tempNode = new Node(currentNode->getRow()-1, currentNode->getCol(), currentNode->getDistanceTraveled()+1);
            openList->addElement(tempNode);
            delete tempNode;
            // openList.addElement(new Node(currentNode->getRow()-1, currentNode->getCol(), currentNode->getDistanceTraveled()+1));
            std::cout << "Up element " << openList->printLatestNode() << " added to openList" << std::endl;
        }

        // DOWN
        if ((currentNode->getDownChar(env) == SYMBOL_EMPTY && 
            !openList->containsNode(currentNode->getDownNode(env)) &&
            !closedList->containsNode(currentNode->getDownNode(env))) ||
            currentNode->getDownNode(env).isEqual(goalNode))

        {
            // openList.addElement(new Node(currentNode->getDownNode(env)));
            Node* tempNode = new Node(currentNode->getRow()+1, currentNode->getCol(), currentNode->getDistanceTraveled()+1);
            openList->addElement(tempNode);
            delete tempNode;
            // openList.addElement(new Node(currentNode->getRow()+1, currentNode->getCol(), currentNode->getDistanceTraveled()+1));
            std::cout << "Down element " << openList->printLatestNode() << " added to openList" << std::endl;
        }

        // LEFT
        if ((currentNode->getLeftChar(env) == SYMBOL_EMPTY && 
            !openList->containsNode(currentNode->getLeftNode(env)) &&
            !closedList->containsNode(currentNode->getLeftNode(env))) ||
            currentNode->getLeftNode(env).isEqual(goalNode))

        {
            // openList.addElement(new Node(currentNode->getLeftNode(env)));
            Node* tempNode = new Node(currentNode->getRow(), currentNode->getCol()-1, currentNode->getDistanceTraveled()+1);
            openList->addElement(tempNode);
            delete tempNode;
            // openList.addElement(new Node(currentNode->getRow(), currentNode->getCol()-1, currentNode->getDistanceTraveled()+1));
            std::cout << "Left element " << openList->printLatestNode() << " added to openList" << std::endl;
        }

        // RIGHT
        if ((currentNode->getRightChar(env) == SYMBOL_EMPTY && 
            !openList->containsNode(currentNode->getRightNode(env)) &&
            !closedList->containsNode(currentNode->getRightNode(env))) ||
            currentNode->getRightNode(env).isEqual(goalNode)) //?????

        {
            // openList.addElement(new Node(currentNode->getRightNode(env)));
            // openList->addElement(currentNode->getRightNode(env));
            // Node* tempNode = &(currentNode->getRightNode(env));
            // openList->addElement(currentNode);
            Node* tempNode = new Node(currentNode->getRow(), currentNode->getCol()+1, currentNode->getDistanceTraveled()+1);
            openList->addElement(tempNode);
            delete tempNode;
            tempNode = nullptr;
            std::cout << "Right element " << openList->printLatestNode() << " added to openList" << std::endl;
        }

        // Find node with smallest estimated distance (that isn't in the closed list NOT IMPLEMENTED)
        bool closestNodeInitialised = false;
        // bool isAReachableNode = false;
        for (int i = 0; i < openList->getLength(); ++i)
        {
            Node* iterationNode = openList->getNode(i);

            // If node is valid to be closest (not current node and not in closed list)
            if (!iterationNode->isEqual(currentNode) && !closedList->containsNode(*iterationNode))
            {
                if (!closestNodeInitialised)
                {
                    // delete closestNode;
                    closestNode = iterationNode;
                    std::cout << "Initialising closest node to " << closestNode->getNodeCoordinatesStr() << std::endl;
                    closestNodeInitialised = true;
                }

                if (iterationNode->getEstimatedDist2Goal(goalNode) < closestNode->getEstimatedDist2Goal(goalNode))
                {
                    // delete closestNode;
                    closestNode = iterationNode;
                    std::cout << "Closest node set to " << closestNode->getNodeCoordinatesStr() << std::endl;
                }
            }
        }
        

        std::cout << "Distance travelled: " << currentNode->getDistanceTraveled() << std::endl;
        std::cout << "Estimated Distance: " << currentNode->getEstimatedDist2Goal(goalNode) << std::endl;
        closedList->addElement(currentNode);
        std::cout << "Previous node " << currentNode->getNodeCoordinatesStr() << " added to closed list" << std::endl;

        if (openList->getLength() != closedList->getLength() && !closestNode->isEqual(goalNode))
        {
            std::cout << "Current node is now set to " << closestNode->getNodeCoordinatesStr() << std::endl;
            // delete currentNode;
            currentNode = closestNode;
            printEnv(env, *currentNode);
        }
        // If goal node is found
        else if (closestNode->isEqual(goalNode))
        {
            // Inform user, set it as the current node, add it to the closed list
            std::cout << "Goal node has been found at " << goalNode->getNodeCoordinatesStr() << std::endl;
            currentNode = closestNode;
            closedList->addElement(currentNode);
            std::cout << "Goal node added to closed list" << std::endl;
        }
        // No possible moves
        else if (openList->getLength() == closedList->getLength())
        {
            std::cout << "No possible moves found." << std::endl;
        }
    // usleep(50000);
    }
    while (!currentNode->isEqual(goalNode) && openList->getLength() != closedList->getLength());

    std::cout << std::endl;
    // printExploredEnv(env, closedList);
    delete openList;
    // nodesExplored = new NodeList(closedList); // For milestone 3
    delete closedList;
    // delete closestNode; // Don't need? (Doesn't affect memory)
    delete goalNode;

    std::cout << "Exiting pathfinder." << std::endl;

}

// bool PathSolver::isAnyReachableNodes(Env env, Node currentNode, NodeList closedList)
// {
//     bool isAnyReachableNodes = false;
//     if ((currentNode.getUpChar(env) == SYMBOL_EMPTY && 
//         !closedList.containsNode(currentNode.getUpNode(env))) ||
//         (currentNode.getDownChar(env) == SYMBOL_EMPTY && 
//         !closedList.containsNode(currentNode.getDownNode(env))) ||
//         (currentNode.getLeftChar(env) == SYMBOL_EMPTY && 
//         !closedList.containsNode(currentNode.getLeftNode(env))) ||
//         (currentNode.getRightChar(env) == SYMBOL_EMPTY && 
//         !closedList.containsNode(currentNode.getRightNode(env))) ||
//         currentNode.getUpChar(env) == SYMBOL_GOAL ||
//         currentNode.getDownChar(env) == SYMBOL_GOAL ||
//         currentNode.getLeftChar(env) == SYMBOL_GOAL ||
//         currentNode.getRightChar(env) == SYMBOL_GOAL)
//     {
//         isAnyReachableNodes = true;
//     }
//     return isAnyReachableNodes;
// }

void PathSolver::printEnv(Env env, Node currentNode)
{
    for (int row = 0; row < ENV_DIM; ++row)
    {
        for (int col = 0; col < ENV_DIM; ++col)
        {
            if (row == currentNode.getRow() && col == currentNode.getCol())
            {
                std::cout << "x";
            }
            else
            {
                std::cout << env[row][col];
            }
        }
        std::cout << " " << row;
        std::cout << std::endl;
    }
}

// void PathSolver::printExploredEnv(Env env, NodeList closedList)
// {
//     for (int row = 0; row < ENV_DIM; ++row)
//     {
//         for (int col = 0; col < ENV_DIM; ++col)
//         {
//             if (closedList.containsNode(Node(row, col, 0)))
//             {
//                 std::cout << "x";
//             }
//             else
//             {
//                 std::cout << env[row][col];
//             }
//         }
//         std::cout << " " << row;
//         std::cout << std::endl;
//     }

// }

// NodeList* PathSolver::getNodesExplored(){
//     //TODO
// }

// NodeList* PathSolver::getPath(Env env){
//     // TODO
// }
//-----------------------------