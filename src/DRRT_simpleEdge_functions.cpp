 #include <iostream>
 #include <vector>
 #include "DRRT_distance_functions.h"
 #include "DRRT_simpleEdge_functions.h"
 #include "DRRT_simple_edge.h"
 #include <fstream>
 #include <iterator>

using std::vector;
/************************* !!!!! critical functions !!!!! **************************
***  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  ***
** ! functions that must be modified vs. the particular C-Space and Workspace  ! **
** ! that are being used !!!                                                   ! **
***  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  !  ***
***********************************************************************************/


/** returns the distance between two points, assuming they are in the C-Space, this
** should obey the triangle inequality, it is used for
*
* use the following version of dist for Euclidian space
*/
float dist(vector<float> x,vector<float> y){
    return (euclidianDist(x,y));
} 


/** This returns the distance that is used internally in the kd-tree (see notes
** there!!! the kd-implimentation handles wrapping dimensions (e.g. a circle or
** taurus) by running multipe searches, 1 for each wrapped identity of the
** querery point. So this is the distance function that is the -non-wrapping-
** version of what the actual distance function between points in the KD space is
*
* use the following version of KDdist for Euclidian space (with and without time)
*/
float KDdist(vector<float> x,vector<float> y) {
    return (euclidianDist(x,y));
}

/** returns the workspace distance between two points, this should obey the triangle
** inequality. e.g., in the current version of this code, it is assumed that the
** workspace is the first two dimensions of the C-space, it is used for calculating
** the "real world" distance that the robot covers (e.g., in a particualr ammount
** of time when determining if a move is possible given robot max speed).
*
* use the following version of Wdist for Euclidian space and Dubbin's space
*/
float Wdist(vector<float> x,vector<float> y) {
    vector<float> x_{x[0], x[1]};
    vector<float> y_{y[0], y[1]};
    return (euclidianDist(x_,y_));
}

// moves newPoint toward closestPoint such that each robot is no
// further than delta, points repesent the cartesian product of R robots
//
// use the following version of saturate for Euclidian space
void saturate(vector<float> &newPoint, vector<float> closestPoint, float delta){ //check delta is float
  float thisDist = dist(newPoint, closestPoint);
  if (thisDist > delta){
    for(int i=0; i<closestPoint.size();i++)  
        newPoint[i] = closestPoint[i]  + (newPoint[i] - closestPoint[i])*1.0*delta/thisDist;
  }
}



 // // // // // // // // // // // // // // // // // // // // // // // // // // collision checking functions  // // // 
 // // // Note, these are only collision checking functions that depend on edge type,  // // //
 // // // more general collision checking functions appear in DRRT.jl                  // // //
 // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //  


 // // // checks if the edge is in collision with a particular obstacle
 // // // (one version for each edge type)
 //
 // // Edge version

//explicitEdgeCheck(S::CSpace{T}, edge::Edge,
//obstacle::OT) where {T, OT} = explicitEdgeCheck2D(obstacle,
//edge.startNode.position, edge.endNode.position, S.robotRadius)


void testCase_sef(){
    vector<float> x{7,4,3};
    vector<float> y{17,6,2};
    std::cout << Wdist(x,y) << std::endl;
    std::cout << KDdist(x,y) << std::endl;
    std::cout << dist(x,y) << std::endl;
}
/*
int main(){
    testCase();
    return 0;
}
*/