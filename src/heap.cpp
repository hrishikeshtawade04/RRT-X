/**
 * @file heap.cpp
 * @author Hrishikesh Tawade
 * @brief 
 * @version 0.1
 * @date 2019-11-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using std::endl;
using std::cout;

template <typename T>
class HeapNode{
    T data;
    int heapIndex;
    bool inHeap;

    HeapNode(T D):data{D},heapIndex{-1},inHeap{false}{}
};
// returns the key value of the node
template <typename T>
T keyDefault(T node){return node.data;}

// less than function
template <typename T>
bool lessThanDefault(T a, T b) {return a.data < b.data;}

// default greater than function
template <typename T>
bool greaterThanDefault(T a, T b){return a.data > b.data;}

// default heap marker function (marks when a node is in the heap)
template <typename T>
void markDefault(T node) {node.inHeap = true;}

// default heap unmarker function (un marks when a node is removed)
template <typename T>
void unmarkDefault(T node){ node.inHeap = false;}

// default heap check marker function (checks if the node is marked)
template <typename T>
bool markedDefault(T node){ return node.inHeap;}

// sets the heap index to the value
template <typename T>
void setIndexDefault(T node, int val){ node.heapIndex = val;}

// set the heap index to the unused value
template <typename T>
void unsetIndexDefault(T node) {node.heapIndex = -1;}

// returns the heap index
template <typename T>
int getIndexDefault(T node){return node.heapIndex;}

template <typename T, typename TK>
class BinaryHeap{
    HeapNode<T> heapNode[];
    int indexOfLast;
    int parentOfLast;
    // Functions used for interacting with marks and indices.
    T (*key)(T node);
    bool (*lessThan)(T,T);
    bool (*greaterThan)(T,T);
    void (*mark)(T);
    void (*unmark)(T);
    bool (*marked)(T);
    void (*setIndex)(T, int);
    void (*unsetIndex)(T);
    int (*getIndex)(T);
    
    /**
    //Constructor
    BinaryHeap(const int maxSize = 64){
        HeapNode<T> H[maxSize];
        heapNode = H; //since we want to start indexing from 1
        indexOfLast = 0;
        parentOfLast = -1;
        key = keyDefault;
        lessThan = lessThanDefault;
        greaterThan = greaterThanDefault;
        mark = markDefault;
        unmark = unmarkDefault;
        marked = markDefault;
        setIndex = setIndexDefault;
        unsetIndex = unsetIndexDefault;
        getIndex = getIndexDefault;
    }
**/
    BinaryHeap(T (*keyarg)(T node) = keyDefault, bool (*lessThanarg)(T,T) = lessThanDefault, bool (*greaterThanarg)(T,T) = greaterThanDefault,
    void (*markarg)(T) = markDefault, void (*unmarkarg)(T) = unmarkDefault, bool (*markedarg)(T) = markedDefault, void (*setIndexarg)(T, int) = setIndexDefault, 
    void (*unsetIndexarg)(T) = unsetIndexDefault, int (*getIndexarg)(T) = getIndexDefault,const int maxSize = 64){
        HeapNode<T> H[maxSize];
        heapNode = H; //since we want to start indexing from 1
        indexOfLast = 0;
        parentOfLast = -1;
        key = keyarg;
        lessThan = lessThanarg ;
        greaterThan = greaterThanarg;
        mark = markarg;
        unmark = unmarkarg;
        marked = markarg;
        setIndex = setIndexarg;
        unsetIndex = unsetIndexarg;
        getIndex = getIndexarg;
    }

};


void testcase(){
    cout << "Test case pending" << endl;
}

int main(){
    testcase();
    return 0;
}


