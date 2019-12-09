#ifndef INCLUDE_KDTREE_GENERAL_H_
#define INCLUDE_KDTREE_GENERAL_H_

#include "heap.h"
#include <math.h>
#include <vector>

template <typename T>
class KDTreeNode{
    public:
    bool kdInTree = false;             // set to true if this node is in the kd-tree

    // data used for heap in KNN-search
    int heapIndex = -1;            // named such to allow the use of default heap functions
    bool inHeap = false;               // ditto
    float data;              // ditto, this will hold the distance

    // more data used for KD Tree
    int kdSplit;              // the dimension used for splitting at this node
    std::vector<T> position;        // a dX1 array where d is the dimesnions of the space
    // constructor
    KDTreeNode(std::vector<T> value): position(value){} // check if data removed works
    KDTreeNode(){}
};


template <typename T>
class KDTree{
    public:
    int d;                       // the number of dimensions in the space
    float (*distanceFunction)(std::vector<float>, std::vector<float>);  // the distance function to use: f(poseA, poseB)
    int treeSize;                // the number of nodes in the KD-Tree
    int numWraps;                // the total number of dimensions that wrap
    std::vector<KDTreeNode<T>> tree;
    int wraps[];           // a vector of length d containing a list of
                            // all the dimensions that wrapAround
    float wrapPoints[];  //check with professor // space is assumed to start at 0 and end at
                                // wrapPoints[i] along dimension wraps[i]
    // Constructor
    KDTree(int darg, float (*distanceFunctionarg)(std::vector<float>, std::vector<float>),
    int wrapsarg[], float wrapPointsarg[]){
        std::vector<KDTreeNode<T>> H(64);
        tree = H;
        d = darg;
        distanceFunction = distanceFunctionarg;
        treeSize = 0;
        wraps = wrapsarg;
        numWraps = (sizeof(wrapsarg)/sizeof(*wrapsarg)); //check with professor
        wrapPoints = wrapPointsarg;        
    }
    // Override
    KDTree(int darg, float (*distanceFunctionarg)(std::vector<float>, std::vector<float>)){
        std::vector<KDTreeNode<T>> H(64);
        tree = H;
        d = darg;
        distanceFunction = distanceFunctionarg;
        treeSize = 0;
        numWraps = 0; //check with professor
    }
    KDTree(){
        std::vector<KDTreeNode<T>> H(64);
        tree = H;
        d = 0;
        distanceFunction = NULL;
        treeSize = 0;
        numWraps = 0; //check with professor
    }   
};

template <typename T>
void KDTreeInit(KDTree<T> &K,int d, float (*f)(std::vector<float>, std::vector<float>));
int parentf(int i);
int left(int i);
int right(int i);
template <typename T>
bool check(KDTree<T> *tree, int index);
template <typename T> // check with professor TKD?
void  kdInsert(KDTree<T> *tree, int index,KDTreeNode<T> newNode, int cd);
template <typename T> 
void kdPrintSubTree(KDTreeNode<T> root, int space, KDTree<T> *tree, int index);
template <typename T> 
void kdPrintTree(KDTree<T> *tree, int index);
template <typename T>
std::pair<KDTreeNode<T> , float>
kdFindNearest(KDTree<T> &tree, std::vector<float> queryPoint);
template <typename T>
std::pair<KDTreeNode<T> , float>
kdFindNearestInSubtree(float (*distanceFunction)(std::vector<float>, std::vector<float>), KDTreeNode<T> root,
  std::vector<float> queryPoint,KDTreeNode<T> suggestedClosestNode, float suggestedClosestDist,KDTree<T> *tree);
float oneTwoDRobotDist(std::vector<float> poseA, std::vector<float> poseB);
void testcase_kd();

#endif







