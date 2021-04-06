/**
 * 1. Reads environment from standard input
 * 2. Execute forward search algorithm
 * 3. Gets the nodes explored in the forward search
 * 4. Gets the full navigation path (milestone 3)
 * 5. Outputs environment with path to standard output (milestone 3)
 */
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);
Env readCustomEnv();

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);

int main(int argc, char** argv){
   // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
   // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
   // AS YOU GO ALONG.
   // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
   // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
   // testNode();
   // testNodeList();
   // std::cout << "DONE TESTING" << std::endl << std::endl;

   // Load Environment 
   Env env = readCustomEnv();
   // readEnvStdin(env);
   // readCustomEnv();

   // Solve using forwardSearch
   // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
   PathSolver* pathSolver = new PathSolver();
   pathSolver->forwardSearch(env);

   NodeList* exploredPositions = nullptr;
   exploredPositions = pathSolver->getNodesExplored();

   // Get the path
   // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
   NodeList* solution = pathSolver->getPath(env);

   printEnvStdout(env, solution);

   delete pathSolver;
   delete exploredPositions;
   delete solution;
   for (int i = 0; i < ENV_DIM; ++i)
   {
      delete[] env[i];
   }
   delete[] env;
}

void readEnvStdin(Env env) {
   //TODO 
   // x represents columns and y represents rows
   for (int row = 0; row < ENV_DIM; ++row)
   {
      for (int col = 0; col < ENV_DIM; ++col)
      {
         // Store this position in list
         std::cin >> env[row][col];
      }
   }
}

Env readCustomEnv()
{
   Env env = nullptr;
   int cols = 0;
   int rows = 0;
   std::string mazeStr;

   bool colsDefined = false;
   do {
      std::string input = "";
      std::getline(std::cin, input);
      mazeStr += input;
      if (!colsDefined)
      {
         cols = mazeStr.length();
         colsDefined = true;
      }
      rows++;
   } while (std::cin.peek() != EOF);
   std::cout << "EOF Reached. Dimensions of maze were " << rows << "x" << cols << std::endl;

   env = new char*[rows];
   for (int row = 0; row < rows; ++row)
   {
      env[row] = new char[cols];
      for (int col = 0; col < cols; ++col)
      {
         std::cout << mazeStr[(row*cols)+col];
         env[row][col] = mazeStr[(row*cols)+col];
      }
      std::cout << std::endl;
   }
   
   return env;
}

void printEnvStdout(Env env, NodeList* solution) {
   //TODO
   for (int row = 0; row < ENV_DIM; ++row)
   {
      for (int col = 0; col < ENV_DIM; ++col)
      {
         // If the node currently being scanned is within the solution
         Node scanningNode = Node(row, col, 0);
         bool solutionNode = false;
         if (solution->getLength() > 0 &&
             solution->containsNode(scanningNode) && env[row][col] != SYMBOL_GOAL)
         {
            // check direction of next node and print direction
            // and next element is x direction
            // If the solution contains the node above the currently scanned node
            // and the next node in solution is the node above
            Node* solutionScanningNode = solution->getNodeAtIndex(scanningNode);
            Node* nextNode = solution->getNextNode(solution->getNodeIndex(*solutionScanningNode));
            if (solution->containsNode(solutionScanningNode->getUpNode(env))
                && solutionScanningNode->getUpNode(env).isEqual(nextNode))
            {
               std::cout << "^";
               solutionNode = true;
            }
            else if (solution->containsNode(solutionScanningNode->getDownNode(env))
                     && solutionScanningNode->getDownNode(env).isEqual(nextNode))

            {
               std::cout << "v";
               solutionNode = true;
            }
            else if (solution->containsNode(solutionScanningNode->getLeftNode(env))
                     && solutionScanningNode->getLeftNode(env).isEqual(nextNode))
            {
               std::cout << "<";
               solutionNode = true;
            }
            else if (solution->containsNode(solutionScanningNode->getRightNode(env))
                     && solutionScanningNode->getRightNode(env).isEqual(nextNode))
            {
               std::cout << ">";
               solutionNode = true;
            }
            else
            {

            }
         }
         if (solutionNode != true)
         {
            std::cout << env[row][col];
         }
      }
      if (row != ENV_DIM-1)
      {
         std::cout << std::endl;
      }
   }
}

void testNode() {
   std::cout << "TESTING Node" << std::endl;

   // Make a Node and print out the contents
   Node* node = new Node(1, 1, 2);
   std::cout << node->getRow() << ",";
   std::cout << node->getCol() << ",";
   std::cout << node->getDistanceTraveled() << std::endl;
   delete node;

   // Change Node and print again
   node = new Node(4, 2, 3);
   std::cout << node->getRow() << ",";
   std::cout << node->getCol() << ",";
   std::cout << node->getDistanceTraveled() << std::endl;
   delete node;
}

void testNodeList() {
   std::cout << "TESTING NodeList" << std::endl;

   // Make a simple NodeList, should be empty size
   NodeList* nodeList = new NodeList();
   std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

   // Add a Node to the NodeList, print size
   Node* b1 = new Node(1, 1, 1);
   nodeList->addElement(b1);
   std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

   // Add second Nodetest
   Node* b2 = new Node(0, 0, 1);
   nodeList->addElement(b2);
   std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

   // Test Get-ith - should be 0,0,1
   Node* getB = nodeList->getNode(1);
   std::cout << getB->getRow() << ",";
   std::cout << getB->getCol() << ",";
   std::cout << getB->getDistanceTraveled() << std::endl;

   // Print out the NodeList
   std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}