#include "list.h"
#include "heap.h"
#include <array>

using std::endl;
using std::cout;

template <typename T>
class KDTreeNode{
    public:
    bool kdInTree = false;             // set to true if this node is in the kd-tree
    bool kdParentExist = false;        // set to true if parent in the tree is used
    bool kdChildLExist = false;        // set to true if left child in the tree is used
    bool kdChildRExist = false;        // set to true if right child in the tree is used

    // data used for heap in KNN-search
    int heapIndex = -1;            // named such to allow the use of default heap functions
    bool inHeap = false;               // ditto
    float data;              // ditto, this will hold the distance

    // more data used for KD Tree
    T position[];        // a dX1 array where d is the dimesnions of the space
    int kdSplit;              // the dimension used for splitting at this node
    KDTreeNode<T> kdParent;   // parent in the tree
    KDTreeNode<T> kdChildL;   // left child in the tree
    KDTreeNode<T> kdChildR;  // right child in the tree

    // constructor
    KDTreeNode(){} // check if data removed works
};

template <typename T, typename TK>
class KDTree{
    public:
    int d;                       // the number of dimensions in the space
    TK (*distanceFunction)(float [], float []);  // the distance function to use: f(poseA, poseB)
    int treeSize;                // the number of nodes in the KD-Tree
    int numWraps;                // the total number of dimensions that wrap
    int wraps[];           // a vector of length d containing a list of
                            // all the dimensions that wrapAround
    float wrapPoints[];  //check with professor // space is assumed to start at 0 and end at
                                // wrapPoints[i] along dimension wraps[i]
    KDTreeNode<T> root;     // changed    the root node
    // Constructor
    KDTree(int darg, TK (*distanceFunctionarg)(float[], float[]),
    int wrapsarg[], float wrapPointsarg[]){
        d = darg;
        distanceFunction = distanceFunctionarg;
        treeSize = 0;
        wraps = wrapsarg;
        numWraps = (sizeof(wrapsarg)/sizeof(*wrapsarg)); //check with professor
        wrapPoints = wrapPointsarg;        
    }
    // Override
    KDTree(int darg, TK (*distanceFunctionarg)(float[], float[])){
        d = darg;
        distanceFunction = distanceFunctionarg;
        treeSize = 0;
        numWraps = 0; //check with professor
    }
    KDTree(){
        d = 0;
        distanceFunction = NULL;
        treeSize = 0;
        numWraps = 0; //check with professor
    }   

};

void testcase(){
    cout << "To be written" << endl;
}
int main(){
    testcase();
    return 0;
}