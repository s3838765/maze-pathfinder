/**
 * Executes forward search & backtracking of the path planning algorithm using NodeList and Node Classes
 * 1. forwardSearch: Execute forward search algorithm
 * 2. getNodesExplored: Returns a DEEP COPY of the explored NodeList in forward search
 * 3. getPath: Execute backtracking and get a DEEP COPY of the path the robot should travel (milestone 3)
 */
#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    // TODO
}

PathSolver::~PathSolver(){
    // TODO
    // Deconstruct nodesExplored node list?
}

void PathSolver::forwardSearch(Env env){
    // TODO
    NodeList openList;
    NodeList closedList;
    Node* currentNode = nullptr; // nullptr
    Node* goalNode = nullptr; // nullptr
    Node tempNode = Node(0,0, 100);
    // Node closestNode = tempNode;
    Node* closestNode = new Node(0,0,100);

    // Scan environment and find start and goal nodes
    for (int row = 0; row < ENV_DIM; ++row)
    {
        for (int col = 0; col < ENV_DIM; ++col)
        {
            if (env[row][col] == SYMBOL_START)
            {
                openList.addElement(new Node(row, col, 0));
                delete currentNode;
                currentNode = openList.getNode(0);
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
        if ((currentNode->getUpChar(env) == '.' && 
            !openList.containsNode(currentNode->getUpNode(env)) &&
            !closedList.containsNode(currentNode->getUpNode(env))) ||
            currentNode->getUpNode(env).isEqual(*goalNode))
        {
            openList.addElement(new Node(currentNode->getUpNode(env)));
            std::cout << "Up element " << openList.printLatestNode() << " added to openList" << std::endl;
        }

        // DOWN
        if ((currentNode->getDownChar(env) == '.' && 
            !openList.containsNode(currentNode->getDownNode(env)) &&
            !closedList.containsNode(currentNode->getDownNode(env))) ||
            currentNode->getDownNode(env).isEqual(*goalNode))

        {
            openList.addElement(new Node(currentNode->getDownNode(env)));
            std::cout << "Down element " << openList.printLatestNode() << " added to openList" << std::endl;
        }

        // LEFT
        if ((currentNode->getLeftChar(env) == '.' && 
            !openList.containsNode(currentNode->getLeftNode(env)) &&
            !closedList.containsNode(currentNode->getLeftNode(env))) ||
            currentNode->getLeftNode(env).isEqual(*goalNode))

        {
            openList.addElement(new Node(currentNode->getLeftNode(env)));
            std::cout << "Left element " << openList.printLatestNode() << " added to openList" << std::endl;
        }

        // RIGHT
        if ((currentNode->getRightChar(env) == '.' && 
            !openList.containsNode(currentNode->getRightNode(env)) &&
            !closedList.containsNode(currentNode->getRightNode(env))) ||
            currentNode->getRightNode(env).isEqual(*goalNode))

        {
            openList.addElement(new Node(currentNode->getRightNode(env)));
            std::cout << "Right element " << openList.printLatestNode() << " added to openList" << std::endl;
        }
        


        // Find node with smallest estimated distance (that isn't in the closed list NOT IMPLEMENTED)
        bool closestNodeInitialised = false;
        bool isAReachableNode = false;
        for (int i = 0; i < openList.getLength(); ++i)
        {
            Node* iterationNode = openList.getNode(i);
            // std::cout << "!iteration->isEqual " << (!iterationNode->isEqual(*currentNode)) << std::endl;
            // std::cout << "!closedList.contains iteration " << !closedList.containsNode(*iterationNode) << std::endl;
            // std::cout << "Iteration distance " << iterationNode->getEstimatedDist2Goal(goalNode) << std::endl;
            // std::cout << "Closest node distance " << closestNode->getEstimatedDist2Goal(goalNode) << std::endl;
            // std::cout << "-----------------" << std::endl;

            // If node is valid to be closest (not current node and not in closed list)
            if (!iterationNode->isEqual(*currentNode) && !closedList.containsNode(*iterationNode))
            {
                // If there is no current closest node: Set the closest node to the iteration node
                if (!closestNodeInitialised)
                {
                    if (currentNode->canReach(*iterationNode, env))
                    {
                        closestNode = iterationNode;
                        std::cout << "Initialising closest node (reachable) to " << closestNode->getNodeCoordinatesStr() << std::endl;
                        isAReachableNode = true;
                        closestNodeInitialised = true;
                    }
                    else if (!isAnyReachableNodes(env, *currentNode, closedList))
                    {
                        closestNode = iterationNode;
                        std::cout << "Initialising closest node (unreachable) to " << closestNode->getNodeCoordinatesStr() << std::endl;
                        closestNodeInitialised = true;
                    }
                }

                // std::cout << "iteration estimated distance " << iterationNode->getEstimatedDist2Goal(goalNode) << std::endl;
                // std::cout << "closest node estimated distance " << closestNode->getEstimatedDist2Goal(goalNode) << std::endl;

                if (iterationNode->getEstimatedDist2Goal(goalNode) < closestNode->getEstimatedDist2Goal(goalNode))
                {
                    if (isAReachableNode && currentNode->canReach(*iterationNode, env))
                    {
                        closestNode = iterationNode;
                        std::cout << "Closest node (reachable) set to " << closestNode->getNodeCoordinatesStr() << std::endl;
                    }
                    else if (!isAReachableNode)
                    {
                        closestNode = iterationNode;
                        std::cout << "Closest node (unreachable) set to " << closestNode->getNodeCoordinatesStr() << std::endl;
                    }
                }
                // EXPERIMENTAL
                /**
                 * if horizontal distance > vertical distance
                 *      decrease horizontal distance
                 * else if vertical distance > horizontal distance
                 *      decrease vertical distance
                 */
                // Find best move if there are two equally distant nodes
                // TEST WITH OPEN FIELD
                // else if (iterationNode->getEstimatedDist2Goal(goalNode) == closestNode->getEstimatedDist2Goal(goalNode))
                // {
                //     // if horizontal distance > vertical distance
                //     if (std::abs(iterationNode->getCol() - goalNode->getCol()) >
                //         std::abs(iterationNode->getRow() - goalNode->getRow()) &&
                //         (iterationNode->isEqual(currentNode->getLeftNode(env)) ||
                //         iterationNode->isEqual(currentNode->getRightNode(env))))
                //     {
                //         // decrease horizontal distance (move left or right)
                //         closestNode = iterationNode;
                //         std::cout << "A horizontal node is closer" << std::endl;
                //     }
                //     else if (std::abs(iterationNode->getRow() - goalNode->getRow()) >
                //              std::abs(iterationNode->getCol() - goalNode->getCol()) &&
                //              (iterationNode->isEqual(currentNode->getUpNode(env)) ||
                //              iterationNode->isEqual(currentNode->getDownNode(env))))
                //     {
                //         // decrease vertical distance (move up or down)
                //         closestNode = iterationNode;
                //         std::cout << "A horizontal node is closer" << std::endl;
                //     }
                // }
            }
        }
        

        closedList.addElement(currentNode);
        std::cout << "Previous node " << currentNode->getNodeCoordinatesStr() << " added to closed list" << std::endl;

        if (openList.getLength() != closedList.getLength() && !closestNode->isEqual(*goalNode))
        {
            std::cout << "Current node is now set to " << closestNode->getNodeCoordinatesStr() << std::endl;
            // delete currentNode;
            currentNode = closestNode;
            // *closestNode = tempNode;
            printEnv(env, *currentNode);
        }
        // If goal node is found
        else if (closestNode->isEqual(*goalNode))
        {
            // Inform user, set it as the current node, add it to the closed list
            std::cout << "Goal node has been found at " << goalNode->getNodeCoordinatesStr() << std::endl;
            currentNode = closestNode;
            closedList.addElement(currentNode);
            std::cout << "Goal node added to closed list" << std::endl;
        }
        // No possible moves
        else if (openList.getLength() == closedList.getLength())
        {
            std::cout << "No possible moves found." << std::endl;
        }
    }
    while (!currentNode->isEqual(*goalNode) && openList.getLength() != closedList.getLength());

    std::cout << std::endl;
    printExploredEnv(env, closedList);
    for (int i = 0; i < openList.getLength(); ++i) // <=?
    {
        delete openList.getNode(i);
    }
    // for (int i = 0; i < closedList.getLength(); ++i)
    // {
    //     delete closedList.getNode(i);
    // }
    // delete closestNode; // Don't need? (Doesn't affect memory)
    delete goalNode;

    std::cout << "Exiting pathfinder." << std::endl;

    nodesExplored = &closedList;
}

bool PathSolver::isAnyReachableNodes(Env env, Node currentNode, NodeList closedList)
{
    bool isAnyReachableNodes = false;
    if ((currentNode.getUpChar(env) == SYMBOL_EMPTY && 
        !closedList.containsNode(currentNode.getUpNode(env))) ||
        (currentNode.getDownChar(env) == SYMBOL_EMPTY && 
        !closedList.containsNode(currentNode.getDownNode(env))) ||
        (currentNode.getLeftChar(env) == SYMBOL_EMPTY && 
        !closedList.containsNode(currentNode.getLeftNode(env))) ||
        (currentNode.getRightChar(env) == SYMBOL_EMPTY && 
        !closedList.containsNode(currentNode.getRightNode(env))) ||
        currentNode.getUpChar(env) == SYMBOL_GOAL ||
        currentNode.getDownChar(env) == SYMBOL_GOAL ||
        currentNode.getLeftChar(env) == SYMBOL_GOAL ||
        currentNode.getRightChar(env) == SYMBOL_GOAL)
    {
        isAnyReachableNodes = true;
    }
    return isAnyReachableNodes;
}

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

void PathSolver::printExploredEnv(Env env, NodeList closedList)
{
    for (int row = 0; row < ENV_DIM; ++row)
    {
        for (int col = 0; col < ENV_DIM; ++col)
        {
            if (closedList.containsNode(Node(row, col, 0)))
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

// NodeList* PathSolver::getNodesExplored(){
//     //TODO
// }

// NodeList* PathSolver::getPath(Env env){
//     // TODO
// }
//-----------------------------