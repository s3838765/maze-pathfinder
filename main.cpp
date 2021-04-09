/**
 * To implement the pathfinder, I incrementally developed the functionality,
 * beginning from extremely basic tests, up to more complex tests (as shown
 * within the tests and in the readme file). This would help me to identify
 * exactly what the issues were as they happened, rather than looking for
 * them after attempting a complicated maze.
 * The biggest issue I had was converting the NodeList attribute nodes to a
 * dynamic array. At first it seemed it would be a simple task, however, it
 * seemed to have caused issue after issue within the memory (leaking). This
 * lead to another issue where I had a single 12 byte leak, and spent two days
 * trying to fix it. This issue was finally fixed by changing some of the logic
 * in the code and refactoring. It is now working perfectly with no leaks.
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

// Milestone 4: Read custom environment
Env readCustomEnv();
int getEnvRows(Env env);
int getEnvCols(Env env);

// Print blank environment
void printEnv(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution, int rows, int cols);

int* envCols = new int(0);
int* envRows = new int(0);

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

   // Solve using forwardSearch
   // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
   PathSolver* pathSolver = new PathSolver();

   // The following line will work assuming the env is 20x20
   // pathSolver->forwardSearch(env);
   
   pathSolver->forwardSearch(env, *envRows, *envCols);

   NodeList* exploredPositions = nullptr;
   exploredPositions = pathSolver->getNodesExplored();

   // Get the path
   // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
   NodeList* solution = pathSolver->getPath(env);

   // Print shortest path with directions
   printEnvStdout(env, solution, *envRows, *envCols);

   // Free memory
   delete pathSolver;
   delete exploredPositions;
   delete solution;
   for (int i = 0; i < *envRows; ++i)
   {
      delete[] env[i];
   }
   delete[] env;
   delete envRows;
   delete envCols;
}

// Read environment input of any size
Env readCustomEnv()
{
   int* cols = envCols;
   int* rows = envRows;
   std::string mazeStr;

   bool colsDefined = false;
   // Collect inputted lines until end of file
   do 
   {
      std::string input = "";
      // Get every inputted line and concatenate to a string
      std::getline(std::cin, input);
      mazeStr += input;
      
      // Define the number of columns in the maze (using the first row inputted)
      if (!colsDefined)
      {
         *cols = mazeStr.length();
         colsDefined = true;
      }
      (*rows)++;
   } 
   while (std::cin.peek() != EOF);

   // Create environment based on number of rows
   Env env = new char*[*rows];
   for (int row = 0; row < *rows; ++row)
   {
      // Create a new character array for every row
      env[row] = new char[*cols];
      for (int col = 0; col < *cols; ++col)
      {
         // Use mazeStr to set the characters within the env array
         env[row][col] = mazeStr[row*(*cols)+col];
      }
   }
   return env;
}

// Prints given maze with the solution, including directional arrows
void printEnvStdout(Env env, NodeList* solution, int rows, int cols) {
   // If the last node is the goal node
   Node* finalNode = solution->getNode(solution->getLength()-1);
   if (env[finalNode->getRow()][finalNode->getCol()] == SYMBOL_GOAL)
   {
      // Iterate through every node in the solution
      for (int i = 0; i < solution->getLength()-1; ++i)
      {
         // Check which direction the next node is, set the character
         // at that position to the respective arrow
         Node solutionNode = *solution->getNode(i);
         if (solutionNode.getUpNode(env).isEqual(solution->getNextNode(i)))
         {
            env[solutionNode.getRow()][solutionNode.getCol()] = '^';
         }
         else if (solutionNode.getDownNode(env).isEqual(solution->
                                                               getNextNode(i)))
         {
            env[solutionNode.getRow()][solutionNode.getCol()] = 'v';
         }
         else if (solutionNode.getLeftNode(env).isEqual(solution->
                                                               getNextNode(i)))
         {
            env[solutionNode.getRow()][solutionNode.getCol()] = '<';
         }
         else if (solutionNode.getRightNode(env).isEqual(solution->
                                                               getNextNode(i)))
         {
            env[solutionNode.getRow()][solutionNode.getCol()] = '>';
         }
      }

      // Print out the environment
      for (int row = 0; row < rows; ++row)
      {
         for (int col = 0; col < cols; ++col)
         {
            std::cout << env[row][col];
         }
         // Don't print out newline if it is the last row of the maze
         if (row != rows-1)
         {
            std::cout << std::endl;
         }
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
   delete b1;
   b1 = nullptr;

   // Add second Nodetest
   Node* b2 = new Node(0, 0, 1);
   nodeList->addElement(b2);
   std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
   delete b2;
   b2 = nullptr;

   // Test Get-ith - should be 0,0,1
   Node* getB = nodeList->getNode(1);
   std::cout << getB->getRow() << ",";
   std::cout << getB->getCol() << ",";
   std::cout << getB->getDistanceTraveled() << std::endl;
   delete nodeList;

   // Print out the NodeList
   std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}