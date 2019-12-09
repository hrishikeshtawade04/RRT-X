#include "list.h"
#include "DRRT_simple_edge.h"
#include <vector>

using std::vector;

template <typename T>
class RRTNode{

    // data used for KD Tree
    bool kdInTree = false;           // set to true if this node is in the kd-tree
    bool kdParentExist = false;      // set to true if parent in the tree is used
    bool kdChildLExist = false;      // set to true if left child in the tree is used
    bool kdChildRExist = false;      // set to true if right child in the tree is used

    // data used for heap in KNN-search
    int heapIndex = -1;
    bool inHeap  = false;

    // data used for RRT
    bool rrtParentUsed = false;      
                      // flag for if this node has a parent
    List<Edge<RRTNode<T>>> rrtNeighborsOut; // edges in the graph that can be reached
                                             // from this node. In + this holds such
                                             // nodes in the current D-ball

    List<Edge<RRTNode<T>>> rrtNeighborsIn; // edges in the graph that reach this
                                             // node. In + this holds such nodes in the
                                             // current D-ball
    int priorityQueueIndex = -1;
    bool inPriorityQueue = false;
    List<Edge<RRTNode<T>>> SuccessorList;
    List<Edge<RRTNode<T>>> InitialNeighborListOut;
    List<Edge<RRTNode<T>>> InitialNeighborListIn;

    bool inOSQueue = false;
    bool isMoveGoal = false;

    std::vector<float> position; // check right according to constructor
    int kdSplit;
    RRTNode<T> *kdParent; 
    RRTNode<T> *kdChildL;
    RRTNode<T> *kdChildR;

    // check removed the unwanted variables for RRT, RRT*, RRT#
    List<Edge<RRTNode<T>>> successorListItemInParent;

    RRTNode(){}
    RRTNode(vector<float> A): position(A){}
};


////// This holds an obstacle, there are many types of obstacles each with their
////// own type of behaviour
template <typename T>
class Obstacle{
  int kind;    // 1 = ball
               // 2 = axis aligned hyperrectangle,
               // 3 = polygon
               // 4 = polygon with safe direction
               // 5 = high dimensional prismatic polygon
               // 6 = polygon that moves in time along a predefined path
               // 7 = similar to 6 but the robot does not "know" obstacle path a priori

  float startTime;  // obstacle appears this long after the start of the run
                      // 0 by default

  float lifeSpan;   // the lifespan of the obstacle (defaults to Inf)
  bool obstacleUnused; // if true, then this obstacle will not be checked


  bool senseableObstacle; // true if this obstacle can be sensed by the robot
                          // i.e., may change state after the robot gets close enough
                          // is set to false after sensing by robot happens, the
                          // distance at which sensing occours is set in the part of
                          // the code pertaining to the robot (and not here)
                          // default is false

  bool obstacleUnusedAfterSense; // obstacleUnused is set to this value after the
                                 // robot senses this obstacle, default is true


  vector<float> position; // initial position of obstacle

  // data for D-dimensional ball obstacles (kind = 1) and as bound on obstacle
  // (all kinds)
  float radius;

  // data for an axis aligned D-dimensional hyperrectangle obstacle (kind = 2)
  vector<float> span; // distance away from the center that this obstacle spans

  
  // stuff for time obstacles (kind = 6,7)
  float velocity;       // speed that the obstacle moves at
  vector<vector<float>> vectorpath; //check with professor // were p[i,:] is the i-th point of an offset path this
                                // obstacle follows, note that p[1,:] should be [0, 0]
                                // this path the robot knows about

  // the following two field is used to keep track of original values, values
  // used for collision checking are calculated as needed vs. the relivant time
  // projection by adding the current offset path value to the following
  vector<float> originalPolygon;


  float nextDirectionChangeTime; // this is the next time that a direction change
                                   // of this obs will occour (unknown to robot).
                                   // note that time count's down to 0, so this is
                                   // generally less than the current time associated
                                   // with robot's state as it moves

  long int nextDirectionChangeInd;     // unknownPath index of nextDirectionChangeTime
  float lastDirectionChangeTime;  // unknownPath time of last change

  // constructors:
  // ball:
  Obstacle(int kind, vector<float> position, float radius){
      kind = 0.0, 
      Inf, 
      false, 
      false, true, position, radius)
  }

};


int main(){
    return 0;
}