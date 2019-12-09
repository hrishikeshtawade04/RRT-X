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
#include "heap.h"

using std::endl;
using std::cout;


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
void markDefault(HeapNode<T> &node) {node.inHeap = true;}

// default heap unmarker function (un marks when a node is removed)
template <typename T>
void unmarkDefault(HeapNode<T> &node){ node.inHeap = false;}

// default heap check marker function (checks if the node is marked)
template <typename T>
bool markedDefault(HeapNode<T> &node){ return node.inHeap;}

// sets the heap index to the value
template <typename T>
void setIndexDefault(HeapNode<T> &node, int val){ node.heapIndex = val;}

// set the heap index to the unused value
template <typename T>
void unsetIndexDefault(HeapNode<T> &node) {node.heapIndex = -1;}

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


int parent(int i) { return i/2;} 
  
// to get index of left_ child of node at index i 
int left_(int i) { return (2*i); } // considering starting index 1

// to get index of right child of node at index i 
int right_(int i) { return (2*i + 1); } // considering starting index 1


template <typename T>
void bubbleUp(BinaryHeap<T> &H, int n){
    if(n!=1){
        while(n!=1 && H.greaterThan(H.heapNode[parent(n)], H.heapNode[n])){
            int pi = parent(n);
            // swap the heap nodes
            swap(&H.heapNode[pi], &H.heapNode[n]);
            H.setIndex(H.heapNode[pi],pi); 
            H.setIndex(H.heapNode[n], n);
            n = parent(n); 
        }
    }
}

template <typename T>
void bubbleDown(BinaryHeap<T> &H, int n){
    int lefti = left_(n);
    int righti = right_(n);
    int smallest = n;

    // Finding the left is smaller or right
    if(lefti <= H.indexOfLast && H.lessThan(H.heapNode[lefti], H.heapNode[n])){
        smallest = lefti;
    }
    if (righti <= H.indexOfLast && H.lessThan(H.heapNode[righti], H.heapNode[smallest])){
        smallest = righti;
    }
    if(smallest != n){
        swap(&H.heapNode[smallest], &H.heapNode[n]);
        H.setIndex(H.heapNode[smallest], smallest);
        H.setIndex(H.heapNode[n], n);
        bubbleDown(H,smallest);
    }
}

template <typename T>
void addToHeap(BinaryHeap<T> &H, HeapNode<T> thisNode){
    // double the size
    if(H.indexOfLast == H.heapNode.size()){
        cout << H.heapNode.size();
        std::vector<HeapNode<T>> newH(H.heapNode.size());  
        H.heapNode.insert(H.heapNode.end(), newH.begin(), newH.end());
    }
    if (!H.marked(thisNode)){ // not in heap
        H.indexOfLast += 1; // equivalent to the size
        H.parentOfLast = parent(H.indexOfLast); // setting the parent to the newly added node
        H.heapNode[H.indexOfLast] = thisNode;
        H.setIndex(H.heapNode[H.indexOfLast], H.indexOfLast); //check if index is necessary
        H.mark(H.heapNode[H.indexOfLast]); //changed
        bubbleUp(H, H.indexOfLast);
        
    }
}

template <typename T>
std::pair<HeapNode<T> , bool> 
topHeap(BinaryHeap<T> &H){
    if (H.indexOfLast < 1){
        HeapNode<T> blank;
        return std::make_pair(blank,false);
    }
    return std::make_pair(H.heapNode[1],true);
}

template <typename T>
std::pair<HeapNode<T> , bool> 
popHeap(BinaryHeap<T> &H){
    if (H.indexOfLast < 1){
        cout << "Returning blank node" << endl;
        HeapNode<T> blank;
        return std::make_pair(blank,false);
    }
    HeapNode<T> oldTopNode = H.heapNode[1];
    H.heapNode[1] = H.heapNode[H.indexOfLast]; // Placing last at the top
    H.setIndex(H.heapNode[1], 1);
    H.indexOfLast -= 1;
    H.parentOfLast = parent(H.indexOfLast);
    bubbleDown(H, 1); 
    H.unmark(oldTopNode);
    H.unsetIndex(oldTopNode);
    return std::make_pair(oldTopNode,true);
}

// Ask professor how this works
template <typename T>
void removeFromHeap(BinaryHeap<T> &H, HeapNode<T> &thisNode){
    int n = H.getIndex(thisNode);
    H.heapNode[n] = H.heapNode[H.indexOfLast]; //changed
    H.setIndex(H.heapNode[n], n);
    H.indexOfLast -= 1;
    H.parentOfLast = parent(H.indexOfLast);
    bubbleUp(H, n);
    bubbleDown(H, n); // changed
    //H.unmark(thisNode); // changed
    //H.unsetIndex(thisNode); // changed
}

template <typename T>
void updateHeap(BinaryHeap<T> &H, HeapNode<T> thisNode){
    if(!H.marked(thisNode))
        cout << "Trying to update a node that is not in the heap" << endl;
    else{
        bubbleUp(H, H.getIndex(thisNode));
        bubbleDown(H,H.getIndex(thisNode));
    }
}

// Assumes that the key 
template <typename T>
bool checkHeap(BinaryHeap<T> &H){
    int i = 2;
    if (H.indexOfLast < 1){
        cout << "Heap is empty" << endl;
        return true;
    }
    if (H.getIndex(H.heapNode[1]) != 1){
        cout << "There is a problem with the heap (root)" << endl;
        return false;
    }
    while (i <= H.indexOfLast){
        if(H.lessThan(H.heapNode[i], H.heapNode[parent(i)])){
            cout << "There is a problem with the heap order" << endl;
            return false;
        }
        if(H.getIndex(H.heapNode[i]) != i){
            cout << "There is a problem with the heap node index"  << H.getIndex(H.heapNode[i]) << "!= " << i << endl;
            return false;
        }
        i+=1;
    }
    cout << "The heap is OK" << endl;
    return true;
}

// check if this  really works
template <typename T>
std::vector<HeapNode<T>> cleanHeap(BinaryHeap<T> &H){
    auto first = H.heapNode.cbegin() + 1;
    auto last = H.heapNode.cbegin() + H.indexOfLast;
    std::vector<HeapNode<T>> retNodes(first,last);
    for (int i = 1 ; i <= H.indexOfLast; i++){
        H.unmark(H.heapNode[i]);
        H.unsetIndex(H.heapNode[i]);
    }
}

template <typename T>
void printHeap(BinaryHeap<T> &H){
    cout << "Printing heap sequence = ";     
    for(int i = 1; i< H.indexOfLast+1; i++){
        cout << H.heapNode[i].data << " ";
    }
    cout << endl;
}
/*
Functions not implemented
printHeap
printPopAllHeap
*/

/*
###############################################################################
# Use these functions instead if we want the heap to return the biggest thing #
###############################################################################

# compares a node n with its parent, and switches them if the parent's
# cost is less than the node's cost. Repeats if a switch happens.
*/

template <typename T>
void bubbleUpB(BinaryHeap<T> &H, int n){
    if(n!=1){
        while(n!=1 && H.lessThan(H.heapNode[parent(n)], H.heapNode[n])){
            int pi = parent(n);
            // swap the heap nodes
            swap(&H.heapNode[pi], &H.heapNode[n]);
            H.setIndex(H.heapNode[pi],pi); 
            H.setIndex(H.heapNode[n], n);
            n = parent(n); 
        }
    }
}

template <typename T>
void bubbleDownB(BinaryHeap<T> &H, int n){
    int lefti = left_(n);
    int righti = right_(n);
    int largest = n;

    // Finding the left is smaller or right
    if(lefti <= H.indexOfLast && H.greaterThan(H.heapNode[lefti], H.heapNode[n])){
        largest = lefti;
    }
    if (righti <= H.indexOfLast && H.greaterThan(H.heapNode[righti], H.heapNode[largest])){
        largest = righti;
    }
    if(largest != n){
        swap(&H.heapNode[largest], &H.heapNode[n]);
        H.setIndex(H.heapNode[largest], largest);
        H.setIndex(H.heapNode[n], n);
        bubbleDownB(H,largest);
    }
}

template <typename T>
void addToHeapB(BinaryHeap<T> &H, HeapNode<T> thisNode){
    // double the size
    if(H.indexOfLast == H.heapNode.size()){
        cout << H.heapNode.size();
        std::vector<HeapNode<T>> newH(H.heapNode.size());  
        H.heapNode.insert(H.heapNode.end(), newH.begin(), newH.end());
    }
    if (!H.marked(thisNode)){ // not in heap
        H.indexOfLast += 1; // equivalent to the size
        H.parentOfLast = parent(H.indexOfLast); // setting the parent to the newly added node
        H.heapNode[H.indexOfLast] = thisNode;
        H.setIndex(H.heapNode[H.indexOfLast], H.indexOfLast); //check if index is necessary
        H.mark(H.heapNode[H.indexOfLast]); //changed
        bubbleUpB(H, H.indexOfLast);
        
    }
}

template <typename T>
std::pair<HeapNode<T> , bool> 
topHeapB(BinaryHeap<T> &H){
    return topHeap(H);
}

template <typename T>
std::pair<HeapNode<T> , bool> 
popHeapB(BinaryHeap<T> &H){
    if (H.indexOfLast < 1){
        cout << "Returning blank node" << endl;
        HeapNode<T> blank;
        return std::make_pair(blank,false);
    }
    HeapNode<T> oldTopNode = H.heapNode[1];
    H.heapNode[1] = H.heapNode[H.indexOfLast]; // Placing last at the top
    H.setIndex(H.heapNode[1], 1);
    H.indexOfLast -= 1;
    H.parentOfLast = parent(H.indexOfLast);
    bubbleDownB(H, 1); 
    H.unmark(oldTopNode);
    H.unsetIndex(oldTopNode);
    return std::make_pair(oldTopNode,true);
}

// Ask professor how this works
template <typename T>
void removeFromHeapB(BinaryHeap<T> &H, HeapNode<T> &thisNode){
    int n = H.getIndex(thisNode);
    H.heapNode[n] = H.heapNode[H.indexOfLast]; //changed
    H.setIndex(H.heapNode[n], n);
    H.indexOfLast -= 1;
    H.parentOfLast = parent(H.indexOfLast);
    bubbleUpB(H, n);
    bubbleDownB(H, n); // changed
    //H.unmark(thisNode); // changed
    //H.unsetIndex(thisNode); // changed
}

template <typename T>
void updateHeapB(BinaryHeap<T> &H, HeapNode<T> thisNode){
    if(!H.marked(thisNode))
        cout << "Trying to update a node that is not in the heap" << endl;
    else{
        bubbleUpB(H, H.getIndex(thisNode));
        bubbleDownB(H,H.getIndex(thisNode));
    }
}

// Assumes that the key 
template <typename T>
bool checkHeapB(BinaryHeap<T> &H){
    int i = 2;
    if (H.indexOfLast < 1){
        cout << "Heap is empty" << endl;
        return true;
    }
    if (H.getIndex(H.heapNode[1]) != 1){
        cout << "There is a problem with the heap (root)" << endl;
        return false;
    }
    while (i <= H.indexOfLast){
        if(H.greaterThan(H.heapNode[i], H.heapNode[parent(i)])){
            cout << "There is a problem with the heap order" << endl;
            return false;
        }
        if(H.getIndex(H.heapNode[i]) != i){
            cout << "There is a problem with the heap node index"  << H.getIndex(H.heapNode[i]) << "!= " << i << endl;
            return false;
        }
        i+=1;
    }
    cout << "The heap is OK" << endl;
    return true;
}

// check if this  really works
template <typename T>
std::vector<HeapNode<T>> cleanHeapB(BinaryHeap<T> &H){
    return cleanHeap(H);
}



void testcase_heap(){
    BinaryHeap<float> H(7);
    cout << "Size of heap  = " << H.heapNode.size() << endl; 
    for(int i = 1; i<8 ;i++){
        cout << "Adding node number " << i << endl;
        HeapNode<float> node;
        node.data = 8-i;
        addToHeap(H, node); 
    }
    printHeap(H);
    checkHeap(H);
    removeFromHeap(H, H.heapNode[3]);
    printHeap(H);
    checkHeap(H);
    updateHeap(H, H.heapNode[4]);
    printHeap(H);
    std::pair <HeapNode<float>, bool> poppedNode;
    poppedNode = popHeap(H);
    while(poppedNode.second){
        cout << "Data of the Popped node = " << poppedNode.first.data << " and status = " << poppedNode.second << endl;
        poppedNode = popHeap(H);
    }
}


void testcaseB(){
    BinaryHeap<float> H(7);
    cout << "Size of heap  = " << H.heapNode.size() << endl; 
    for(int i = 1; i<8 ;i++){
        cout << "Adding node number " << i << endl;
        HeapNode<float> node;
        node.data = i;
        addToHeapB(H, node); 
    }
    printHeap(H);
    checkHeapB(H);
    removeFromHeapB(H, H.heapNode[3]);
    printHeap(H);
    checkHeapB(H);
    updateHeapB(H, H.heapNode[4]);
    cout << "After update " << endl;
    printHeap(H);
    std::pair <HeapNode<float>, bool> poppedNode;
    poppedNode = popHeapB(H);
    while(poppedNode.second){
        cout << "Data of the Popped node = " << poppedNode.first.data << " and status = " << poppedNode.second << endl;
        poppedNode = popHeapB(H);
    }
}

/*
int main(){
    //testcase();
    testcaseB();
    return 0;
}
*/

