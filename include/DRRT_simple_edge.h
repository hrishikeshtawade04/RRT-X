#include <iostream>
#include "list.h"

template <typename T>
class SimpleEdge{
    T startNode;
    T endNode;
    float dist;  // the distance between startNode and endNode (i.e., how far the
                 // robot must travel through the -configuration- space to get from
                 // startNode to endNode. This is the distance that is used to
                 // calculate RRTTreeCost and RRTLMC

    float distOriginal; // saves the original value of dist, so we don't need to
                        // recalculate if this edge is removed and then added again

    ListNode<SimpleEdge<T>> *listItemInStartNode; // pointer to this edges location
                                                // in startNode

    ListNode<SimpleEdge<T>> *listItemInEndNode;   // pointer to this edges location
                                                // in endNode

    float Wdist; // this contains the distance that the robot must travel through
                 // the -workspace- along the edge (so far only used for time based
                 // c-spaces)
    SimpleEdge(){}
};