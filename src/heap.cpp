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




int parent(int i) { return i/2;} 
  
// to get index of left_ child of node at index i 
int left_(int i) { return (2*i); } // considering starting index 1

// to get index of right child of node at index i 
int right_(int i) { return (2*i + 1); } // considering starting index 1




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
    testcase_heap();
    testcaseB();
    return 0;
}
*/

