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
    /**
     * Input E environment
     * Input S start location
     * Input G goal location
     * Let P be a list of positions the robot can reach, with distances (initially S). Called the open list
     * Let C be a list of positions that have been explored, with distances (initially empty). Called the closed list
     * 
     * Repeat (Do)
     *  Select node p from open list P that has the smallest estimated distance to goal (and is not in C)
     *  For every position (q) in the environment (E) that the robot can reach from p (current position)
     *      Set distance_travelled of q to be one more than p
     *      Add q to open list P if not already in it
     *  End
     *  Add p to closed list C
     * (While) Until the robot reaches the goal (p==G), or no such position p can be found
     */


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
        for (int i = 0; i < openList.getLength(); ++i)
        {
            // std::cout << "ENTERED FOR LOOP" << std::endl;
            Node* iterationNode = openList.getNode(i);
            // TODO: Set closestnode to find first element that meets conditions and go from there
            // iterationNode not current node
            // iterationNode not in closed list
            // iterationNode < closestNode
            // std::cout << "!iteration->isEqual " << (!iterationNode->isEqual(*currentNode)) << std::endl;
            // std::cout << "!closedList.contains iteration " << !closedList.containsNode(*iterationNode) << std::endl;
            // std::cout << "Iteration distance " << iterationNode->getEstimatedDist2Goal(goalNode) << std::endl;
            // std::cout << "Closest node distance " << closestNode->getEstimatedDist2Goal(goalNode) << std::endl;
            
            // Give closestNode an initial value
            if (!iterationNode->isEqual(*currentNode) && !closedList.containsNode(*iterationNode) && !closestNodeInitialised)
            {
                std::cout << "INITIALISING CLOSEST NODE" << std::endl;
                closestNode = iterationNode;
                closestNodeInitialised = true;
            }
            if (!iterationNode->isEqual(*currentNode) && !closedList.containsNode(*iterationNode) && 
                iterationNode->getEstimatedDist2Goal(goalNode) < closestNode->getEstimatedDist2Goal(goalNode))
            {
                std::cout << "CLOSEST NODE " << iterationNode->getNodeCoordinatesStr() << std::endl;
                // delete closestNode;
                closestNode = iterationNode;
            }
        }
        
        if (closestNode->isEqual(*goalNode))
        {
            std::cout << "Current node is the goal node!" << std::endl;
            closedList.addElement(closestNode);
        }

        printEnv(env, *currentNode);
        std::cout << "Current node is now set to " << closestNode->getNodeCoordinatesStr() << std::endl;
        closedList.addElement(currentNode);
        std::cout << "Previous node " << currentNode->getNodeCoordinatesStr() << " added to closed list" << std::endl;
        // delete currentNode;
        currentNode = closestNode;
        // *closestNode = tempNode;
    }
    while (!currentNode->isEqual(*goalNode) /* or no such positions can be found */);

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