#ifndef INCLUDE_DRRT_DATA_STRUCTURES_H_
#define INCLUDE_DRRT_DATA_STRUCTURES_H_

#include "list.h"
#include "DRRT_simple_edge.h"
#include <vector>
#include <limits>

using std::vector;

template <typename T>
class RRTNode{
    public:
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

    std::vector<float> position; //float it should be right according to constructor
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
class Obstacle{
  public:
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
  Obstacle(int kindArg, vector<float> positionArg, float radiusArg){
      kind = kindArg; 
      startTime = 0.0;
      lifeSpan = std::numeric_limits<float>::infinity();
      bool obstacleUnused = false; 
      bool senseableObstacle = false;
      bool obstacleUnusedAfterSense = true;
      position = positionArg;
      radius = radiusArg;
  }
  Obstacle(){} 
};


template <typename T>
class CSpace{
    ////// the configuration space. This holds data about the start, goal, obstacles, etc.
////// and is used for sampling new points.
  public:
  int d;                          // dimensions
  List<Obstacle> obstacles;       // a list of obstacles
  float obsDelta;               // the granularity of obstacle checks on edges
  vector<float> lowerBounds;     // 1XD array containing the lower bounds
  vector<float> upperBounds;     // 1XD array containing the upper bounds
  vector<float> width;           // 1XD array containing upper_bounds-lower_bounds
  vector<float> start;           // 1XD array containing the start location
  vector<float> goal;            // 1XD array containing the goal location

  // flags that indicate what type of search space we are using (these are mosly here
  // to reduce the ammoung of duplicate code for similar spaces, althouth they should
  // probably one day be replaced with a different approach that takes advantage of
  // Julia's multiple dispatch and polymophism)

  bool spaceHasTime;              // if true then the 3rd dimension of the space is
                                  // time
  bool spaceHasTheta;             // if true then the 4th dimension of the space is
                                  // theta, in particular a dubins system is used

  // stuff for sampling functions
  float pGoal;                  // the probability that the goal is sampled

  RRTNode<T> (*randNode)(CSpace<T> S);             // the sampling function to use (takes a Cspace)

  RRTNode<T> goalNode;            // the goal node
  RRTNode<T> root;                // the root node
  RRTNode<T>  moveGoal;           // the current movegoal (robot position) node
  int itsUntilSample;             // a count down to sample a particular point
  vector<float> itsSamplePoint;  // sample this when itsUntilSample == 0

  vector<float> timeSamplePoint; // sample this when waitTime has passed
  float waitTime;               // time to// wait in seconds
  unsigned long int startTimeNs;             // time this started
  float elapsedTime;            // elapsed time since start (where time spent saving
                                  // experimental data has been removed)
  Obstacle obstaclesToRemove;     // an obstacle to remove

  float robotRadius;            // robot radius
  float robotVelocity;          // robot velocity (used for dubins w/o time)

  float dubinsMinVelocity;     // min velocity of dubins car (for dubins + time)
  float dubinsMaxVelocity;     // max velocity of dubins car (for dubins + time)


  List<vector<float>> sampleStack; // points to sample in the future

  float hypervolume;            // hypervolume of space

  float delta;                  // RRT paramiter delta

  float minTurningRadius;       // min truning radius, e.g., for dubins car

  long int fileCtr;                  // file counter, used for debugging only

  float warmupTime;             // the ammount of warm up time allowed (obstacles are
                                  // are ignored for warm up time)
  bool inWarmupTime;              // true if we are in the warmup time

  CSpace(int D, float obsDeltaArg, vector<float> L, vector<float> U, vector<float> S, vector<float> G){ 
        d = D;                         // dimensions
        obsDelta = obsDeltaArg;              // the granularity of obstacle checks on edges
        lowerBounds = L;     // 1XD array containing the lower bounds
        upperBounds = U;     // 1XD array containing the upper bounds
        start = S;           // 1XD array containing the start location
        goal  = G;            // 1XD array containing the goal location
        for (int i =0 ; i < lowerBounds.size();i++)
            width.push_back(upperBounds[i] - lowerBounds[i]);           // 1XD array containing upper_bounds-lower_bounds
        spaceHasTime = false;
        spaceHasTheta = false;
        hypervolume = 0.0; // flag indicating that this needs to be calculated
        inWarmupTime = false;
        warmupTime = 0.0; // default value for time for build graph with no obstacles
    }
};

// queue data structure used for RRTx
template <typename A, typename B>
class rrtXQueue{
  public:  
  BinaryHeap<A,B> Q;  // normal queue (sorted based on cost from goal)
  List<A> OS;        // obstacle successor stack
  CSpace<float> S;
  float changeThresh;  // the threshold of local changes that we care about
  rrtXQueue();
};



#endif