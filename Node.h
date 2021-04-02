#ifndef COSC_ASSIGN_ONE_NODE
#define COSC_ASSIGN_ONE_NODE

#include "Types.h"
#include <string>

class Node{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Desctructor
    Node(int row, int col, int dist_traveled);
    ~Node();

    // get row-coodinate of the node
    int getRow();

    // get column-coodinate of the node
    int getCol();

    //getter and setter for distance traveled
    int getDistanceTraveled();
    void setDistanceTraveled(int dist_traveled);

    //getter for estimated dist to goal - need to return -> Manhatten distance + distance traveled
    int getEstimatedDist2Goal(Node* goal);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    char getUpChar(Env env);
    char getDownChar(Env env);
    char getLeftChar(Env env);
    char getRightChar(Env env);
    std::string getNodeCoordinatesStr();
    // bool isEqual(Node node);
    bool isEqual(Node* node);
    // void getReachableNodes(Env env, NodeList openList);
    Node getUpNode(Env env);
    Node getDownNode(Env env);
    Node getLeftNode(Env env);
    Node getRightNode(Env env);
    // bool canReach(Node targetNode, Env env);


private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    int row;
    int col;
    int dist_traveled;  // distance from start node

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

};

#endif //COSC_ASSIGN_ONE_NODE