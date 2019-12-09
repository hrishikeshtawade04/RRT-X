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
SimpleEdge<T> newEdge(T startNode, T endNode);
template <typename T, typename TS>
bool validMove(TS S, SimpleEdge<T> edge);
template <typename T>
std::vector<float> poseAtDistAlongEdge(SimpleEdge<T> edge, float distAlongEdge);
template <typename T> //check the type of the text iterator
void saveEndOfTrajectory(std::ofstream filePtr, SimpleEdge<T> edge, float distFromFront);
template <typename T>
void saveEndOfTrajectoryTime(std::ofstream filePtr, SimpleEdge<T> edge, float timeFromFront);
template <typename T, typename TS>
void calculateTrajectory(TS S, SimpleEdge<T> &edge);
template <typename T, typename TS>
void calculateHoverTrajectory(TS S, SimpleEdge<T> &edge);
template <typename T>
void saveEdgeTrajectory(std::ofstream filePtr , SimpleEdge<T> edge);
void testCase_sef();
#endif