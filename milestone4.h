#ifndef MILESTONE4_H
#define MILESTONE4_H

#include "Types.h"
#include <string>

/*
 * This function is to help you dynamically allocate
 *  memory for a generic 2D Environemnt.
 */
Env make_env(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }

   return env;
}

// Populate environment using a string of characters
Env populate_env(Env env, std::string mazeStr, int rows, int cols)
{
   for (int row = 0; row < rows; ++row)
   {
      for (int col = 0; col < cols; ++col)
      {
         // Use mazeStr to set the characters within the env array
         env[row][col] = mazeStr[row*(cols)+col];
      }
   }

   return env;
}

/*
 * This function is to help you delete a 
 * dynamically allocated 2D Environment.
 */
void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete[] env[i];
      }
      delete[] env;
   }
   return;
}

#endif //MILESTONE4_H