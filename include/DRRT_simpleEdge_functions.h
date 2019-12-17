#ifndef INCLUDE_DRRT_SIMPLEEDGE_FUNCTIONS_H_
#define INCLUDE_DRRT_SIMPLEEDGE_FUNCTIONS_H_

#include <iostream>
#include <vector>
#include "DRRT_simple_edge.h"
#include <fstream>
#include <iterator>

using std::vector;


float dist(vector<float> x,vector<float> y);
float KDdist(vector<float> x,vector<float> y);
float Wdist(vector<float> x,vector<float> y);
void saturate(vector<float> &newPoint, vector<float> closestPoint, float delta);

template <typename T>
Edge<T> newEdge(T startNode, T endNode){ 
  Edge<T> E;
  E.startNode = startNode;
  E.endNode = endNode;
  return (E);
}

// returns true if the dynamics of the robot and space allow a robot to follow the edge
//
//// Edge version  //checks BVP I think
template <typename T, typename TS>
bool validMove(TS S, Edge<T> edge){
    if (S.spaceHasTime){
        // note that planning happens in reverse time, i.e., time = 0 is at the root
        // of the search tree, and thus the time of startNode must be greater than
        // the time of the end node.
        return (edge.Wdist <= (edge.startNode.position[3] - edge.endNode.position[3])*S.robotVelocity);
    }

  // if space does not have time then we assume that the move is always valid
  return true;
}

////// returns the pose of a robot that is located dist along the edge
////// NOTE THAT 'dist' and 'far' are with respect to whatever type
////// of distance is stored in edge.dist
//
//// simple edge version
template <typename T>
std::vector<float> poseAtDistAlongEdge(Edge<T> edge, float distAlongEdge){ //check with professor the type
  if (edge.dist == 0.0)
    return (edge.endNode.position); //I think copy is not needed. check with professor.

  float ratioAlongEdge = distAlongEdge/edge.dist;
  std::vector<float> ret;
  for(int i=0; i< edge.startNode.position.size(); i++)
    ret.push_back(edge.startNode.position[i] + ratioAlongEdge*(edge.endNode.position[i] - edge.startNode.position[i]));
  return (ret);
}

////// the next function saves the last part of the trajectory into the file filePtr,
////// starting distFromFront from the front. NOTE THAT 'distFromFront' is with
////// respect to whatever type of distance is stored in edge.dist
//
//// Simple Edge
template <typename T> //check the type of the text iterator
void saveEndOfTrajectory(std::ofstream filePtr, Edge<T> edge, float distFromFront){ 
  float ratioAlongEdge = distFromFront/edge.dist;
  vector<float> ret; 
  for(int i=0; i< edge.startNode.position.size(); i++){
    ret.push_back(edge.startNode.position[i] + ratioAlongEdge*(edge.endNode.position[i] - edge.startNode.position[i]));
      
  }
  for (const auto &e : edge.endNode.position) filePtr << e << ",";
}


////// the next function saves the last part of the trajectory into the file filePtr,
// starting timeFromFront from the front
//
//// simple edge version
template <typename T>
void saveEndOfTrajectoryTime(std::ofstream filePtr, Edge<T> edge, float timeFromFront) {
  float ratioAlongEdge = timeFromFront/(edge.startNode.position[3] - edge.endNode.position[3]);
  vector<float> ret;
  for(int i=0; i< edge.startNode.position.size(); i++){
   ret.push_back(edge.startNode.position[i] + ratioAlongEdge*(edge.endNode.position[i] - edge.startNode.position[i]));
   filePtr << ret[i] << ",";
  }
  for (const auto &e : edge.endNode.position) filePtr << e << ",";
}


 // // // NOTE: A version of calculateTrajectory() must be created for whatever edge
 // // // type is being used. FURTHERMORE, the trajectory can be stored in any usefull
 // // // form, but there are a number of functions (e.g., for collision checking) that
 // // // must be modified to use whatever form the trajectory is stored in. For example,
 // // // For a holonomic robot in euclidian space this is simply a straight line and
 // // // the trajectory is implicitly defined by the edge between the nodes. For more
 // // // complex systems the trajectory is not a straight line and is stored as a local
 // // // path (called a trajectory) within the edge. AT THE VERY LEAST this function
 // // // should populate the dist field of edge
 //
 // // basic version, trajectory is implicitly defined as straight path along line
 // // segment between edge.startNode and edge.endNode, Euclidian space is assumed
template <typename T, typename TS>
void calculateTrajectory(TS S, Edge<T> &edge){
  edge.dist = dist(edge.startNode, edge.endNode);
  edge.distOriginal = edge.dist;
  edge.Wdist = Wdist(edge.startNode, edge.endNode);
}


 // // // this calculates a trajectory of what the robot is supposed to do when it is
 // // // hovering "in place"
 //
 // // simple edge version
template <typename T, typename TS>
void calculateHoverTrajectory(TS S, Edge<T> &edge) {
    calculateTrajectory(S, edge);
}
 // // // this saves the trajectory that is stored in the edge to the file
 //
 // simple edge version
template <typename T>
void saveEdgeTrajectory(std::ofstream filePtr , Edge<T> edge) {
  for (const auto &e : edge.startNode.position) filePtr << e << ",";
  for (const auto &e : edge.endNode.position) filePtr << e << ",";
}

void testCase_sef();

#endif