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
    std::vector<HeapNode<T>> heapNode;
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
        std::vector<HeapNode<T>> H(maxSize);
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


template <typename T>
void bubbleUp(BinaryHeap<T> H, int n){
    if(n!=1){
        while(n!=1 && H.greaterThan(H.heapNode[parent(n)], H.heapNode[n])){
            int pi = parent(n);
            // swap the heap nodes
            swap(&H.heapNode[pi], &H.heapNode[n]);
            H.setIndex(H.heapNode[parent(n)]); 
            n = parent(n); 
        }
    }
}

template <typename T>
void bubbleDown(BinaryHeap<T> H, int n){
    int child = 0;
    if (2*n == H.indexOfLast)
        child = 2*n;
    else if (2*n+1 > H.indexOfLast)
        return;
    else if (H.lessThan(H.heapNode[2*n,1], H.heapNode[2*n+1,1]))
        child = 2*n;
    else
        child = 2*n+1;

    while (n <= H.parentOfLast && H.lessThan(H.heapNode[child], H.heapNode[n])){
        swap(&H.heapNode[child], &H.heapNode[n]);
        H.setIndex(H.heapNode[child], child);
        H.setIndex(H.heapNode[n], n);
        n = child;
        if (2*n == H.indexOfLast)
            child = 2*n;
        else if (2*n+1 > H.indexOfLast)
            return;
        else if (H.lessThan(H.heapNode[2*n], H.heapNode[2*n+1]))
            child = 2*n;
        else
            child = 2*n+1;

    }
}

template <typename T>
void addToHeap(BinaryHeap<T> H, HeapNode<T> thisNode){
    // double the size
    if(H.indexOfLast == H.heapNode.size()){
        std::vector<HeapNode<T>> newH(H.heapNode.size());  
        H.heapNode.append(newH);
    }
    if (!H.marked(thisNode)){ // not in heap
        H.indexOfLast += 1; // equivalent to the size
        H.parentOfLast = parent(H.indexOfLast); // setting the parent to the newly added node
        H.heapNode[H.indexOfLast] = thisNode;
        H.setIndex(thisNode, H.indexOfLast); //check if index is necessary
        bubbleUp(H, H.indexOfLast);
        H.mark(thisNode);
    }
}

template <typename T>
typename std::conditional<std::is_same<T, bool>::value, bool, HeapNode<T>>::type 
topHeap(BinaryHeap<T> H){
    if (H.indexOfLast < 1)
        return false;
    return H.heapNode[1];
}

template <typename T>
typename std::conditional<std::is_same<T, bool>::value, bool, HeapNode<T>>::type 
popHeap(BinaryHeap<T> H){
    if (H.indexOfLast < 1)
        return false;
    HeapNode<T> oldTopNode = H.heapNode[1];
    H.heapNode[1] = H.heapNode[H.indexOfLast]; // Placing last at the top
    H.setIndex(H.heapNode[1], 1);
    H.indexOfLast -= 1;
    H.parentOfLast = parent(H.indexOfLast);
    bubbleDown(H, 1); // 
    H.unmark(oldTopNode);
    H.unsetIndex(oldTopNode);
    return oldTopNode;
}

template <typename T>
void removeFromHeap(BinaryHeap<T> H, HeapNode<T> thisNode){
    int n = H.getIndex(thisNode);
    HeapNode<T> movedNode = H.heapNode[H.indexOfLast];
    H.heapNode[n] = movedNode;
    H.setIndex(movedNode, n);
    H.indexOfLast -= 1;
    H.parentOfLast = parent(H.indexOfLast);
    bubbleUp(H, n);
    bubbleDown(H, H.getIndex(movedNode));
    H.unmark(thisNode);
    H.unsetIndex(thisNode);
}

template <typename T>
void updateHeap(BinaryHeap<T> H, HeapNode<T> thisNode){
    if(!H.marked(thisNode))
        cout << "Trying to update a node that is not in the heap" << endl;
    else{
        bubbleUp(H, H.getIndex(thisNode));
        bubbleDown(H,H.getIndex(thisNode));
    }
}

template <typename T>
bool checkHeap(BinaryHeap<T> H){
    int i = 2;
    if (H.indexOfLast < 1){
        cout << "Heap is empty" << endl;
        return true;
    }
    else if (H.getIndex(H.heapNode[1]) != 1){
        cout << "There is a problem with the heap (root)" << endl;
        return false;
    }
    while (i <= H.indexOfLast)
        if(H.lessThan(H.heapNode[i], H.heapNode[parent(i)])){
            cout << "There is a problem with the heap order" << endl;
            return false;
        }
        else if(H.getIndex(H.heapNode[i]) != i){
            cout << "There is a problem with the heap node data"  << H.getIndex(H.heapNode[i]) << "!= " << i << endl;
            return false;
        }
        i+=1;
    cout << "The heap is OK" << endl;
    return true;
}

template <typename T>
std::vector<HeapNode<T>> cleanHeap(BinaryHeap<T> H){
    auto first = H.heapNode.cbegin() + 1;
    auto last = H.heapNode.cbegin() + H.indexOfLast;
    std::vector<HeapNode<T>> retNodes(first,last);
    for (int i = 1 ; i <= H.indexOfLast; i++){
        H.unmark(H.heapNode[i]);
        H.unsetIndex(H.heapNode[i]);
    }
}


/*
Functions not implemented
printHeap
printPopAllHeap
*/


void testcase(){
    cout << "Test case pending" << endl;
}

int main(){
    testcase();
    return 0;
}


