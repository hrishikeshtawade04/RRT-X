#ifndef INCLUDE_DRRT_H_
#define INCLUDE_DRRT_H_

#include "DRRT_data_structures.h"
#include <string>
#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "list.h"

using std::string;

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



#endif