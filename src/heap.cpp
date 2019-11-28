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
T keyDefault(HeapNode<T> node){return node.data;}

// less than function
template <typename T>
bool lessThanDefault(HeapNode<T> a, HeapNode<T> b) {return a.data < b.data;}

// default greater than function
template <typename T>
bool greaterThanDefault(HeapNode<T> a, HeapNode<T> b){return a.data > b.data;}

// default heap marker function (marks when a node is in the heap)
template <typename T>
void markDefault(HeapNode<T> node) {node.inHeap = true;}

// default heap unmarker function (un marks when a node is removed)
template <typename T>
void unmarkDefault(HeapNode<T> node){ node.inHeap = false;}

// default heap check marker function (checks if the node is marked)
template <typename T>
bool markedDefault(HeapNode<T> node){ return node.inHeap;}

// sets the heap index to the value
template <typename T>
void setIndexDefault(HeapNode<T> node, int val){ node.heapIndex = val;}

// set the heap index to the unused value
template <typename T>
void unsetIndexDefault(HeapNode<T> node) {node.heapIndex = -1;}

// returns the heap index
template <typename T>
int getIndexDefault(HeapNode<T> node){return node.heapIndex;}

template <typename T>
void swap(HeapNode<T> *x, HeapNode<T> *y) 
{ 
    HeapNode<T> temp = *x; 
    *x = *y; 
    *y = temp; 
} 

template <typename T> //, typename TK>
class BinaryHeap{
    HeapNode<T> heapNode[];
    int indexOfLast;
    int parentOfLast;
    // Functions used for interacting with marks and indices.
    T (*key)(HeapNode<T> node);
    bool (*lessThan)(HeapNode<T>,HeapNode<T>);
    bool (*greaterThan)(HeapNode<T>,HeapNode<T>);
    void (*mark)(HeapNode<T>);
    void (*unmark)(HeapNode<T>);
    bool (*marked)(HeapNode<T>);
    void (*setIndex)(HeapNode<T>, int);
    void (*unsetIndex)(HeapNode<T>);
    int (*getIndex)(HeapNode<T>);
    
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
    BinaryHeap(T (*keyarg)(HeapNode<T> node) = keyDefault, bool (*lessThanarg)(HeapNode<T>,HeapNode<T>) = lessThanDefault, bool (*greaterThanarg)(HeapNode<T>,HeapNode<T>) = greaterThanDefault,
    void (*markarg)(HeapNode<T>) = markDefault, void (*unmarkarg)(HeapNode<T>) = unmarkDefault, bool (*markedarg)(HeapNode<T>) = markedDefault, void (*setIndexarg)(HeapNode<T>, int) = setIndexDefault, 
    void (*unsetIndexarg)(HeapNode<T>) = unsetIndexDefault, int (*getIndexarg)(HeapNode<T>) = getIndexDefault,const int maxSize = 64){
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
int parent(int i) { return i/2;} 
  
// to get index of left child of node at index i 
int left(int i) { return (2*i); } // considering starting index 1

// to get index of right child of node at index i 
int right(int i) { return (2*i + 1); } // considering starting index 1

/**
template <typename T>
void bubbleUp(BinaryHeap<T> H, int n){
    if(n!=1){
        while(n!=1 && H.greaterThan(H.heapNode[parent(n)], H.heapNode[n]))
    }
}
**/
void testcase(){
    cout << "Test case pending" << endl;
}

int main(){
    testcase();
    return 0;
}


