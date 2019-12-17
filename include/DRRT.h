#ifndef INCLUDE_DRRT_H_
#define INCLUDE_DRRT_H_

#include "DRRT_data_structures.h"
#include "kdTree_general.h"
#include "DRRT_simpleEdge_functions.h"
#include <string>
#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "list.h"
#include <vector>
#include <chrono>
#include <cmath>

using std::string;
using std::vector;

// returns a random node from S
template <typename T>
RRTNode<T> randNodeDefault(CSpace<T> S){
    vector<float> position(S.lowerBounds.size());
    srand(time(0)); 
    for(int i =0; i< S.lowerBounds.size(); i++){
        float a = rand()%1;
        position.push_back(S.lowerBounds[i] + a*S.width[i]);
    }    
    return RRTNode<T>(position);
}

// returns a random node from S, or the goal with probability pGoal
template <typename T>
RRTNode<T> randNodeOrGoal(CSpace<T> S){
  srand(time(0));
  if (rand()%1 > S.pGoal)
    return randNodeDefault(S);
  return S.goalNode;
}


// this returns a random node unless there are points in the sample
// stack, in which case it returns the first one of those
template <typename T>
RRTNode<T> randNodeOrFromStack(CSpace<T> S){ 
  if (S.sampleStack.length > 0)
    return RRTNode<T>(listPop(S.sampleStack));
  else
    return randNodeOrGoal(S);
}

// S is the CSpace, the algorithm runs until either N nodes have been sampled
// or TimeOut seconds pass, delta is the saturation distance, ballConstant is
// the ball constant
template <typename TS>
void RRTX(TS S, float total_planning_time, float slice_time,
  float delta, float ballConstant, float changeThresh,
  string searchType, bool MoveRobotFlag,bool saveVideoData,
  bool saveTree, string dataFile){

    // NOTE THIS IS HARD CODED HERE (SHOULD PROBABLY MAKE INPUT ARGUMENT)
    float robotSensorRange = 20.0; // used for "sensing" obstacles
    RRTNode<float> T;
    // This part is integrated in the arguments
    /*
    if length(statsArgs) >= 2
    dataFileName = statsArgs[2]
    else
    dataFileName = "data.txt"
    end
    */

   auto start = std::chrono::high_resolution_clock::now();
   //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << "ns\n";
   auto save_elapsed_time = 0.0; // will hold save time to correct for time spent
                                 // writing to files (only used for visualization video)
   
    ////// do initialization stuff:

    // init a KDtree that will be used
    // MAKE SURE THIS USES APPROPERIATE DISTANCE FUNCTION !!!!!!!!!
    if (S.spaceHasTheta){
        // using dubins car, 4th dimension wraps around at 0 == 2pi
        vector<int> wrapsarg{4}; 
        vector<float> wrapPointsarg{2*3.14}; // substituting instead of pi
        KDTree<RRTNode<float>> KD(S.d, KDdist, wrapsarg, wrapPointsarg); // KDdist is from simple edge functions
    }
    else
        KDTree<RRTNode<float>> KD(S.d, KDdist);
    

    // only writing here RRTX searchtype
    //rrtXQueue<RRTNode<float>, vector<float>> Q;
    //Q.Q = BinaryHeap{RRTNode{Float64}, typeof((Float64, Float64))}(keyQ, lessQ, greaterQ, markQ, unmarkQ, markedQ, setIndexQ, unsetIndexQ, getIndexQ)
    //Q.OS = JList{RRTNode{Float64}}()
    //Q.S = S
    //Q.changeThresh = changeThresh




  }


#endif