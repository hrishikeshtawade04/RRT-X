/**
 * @file list.cpp
 * @author Hrishikesh Tawade
 * @brief a list node (note that key is unused for list opperations, but it is often
 *        helpful to have a key value associated with data)
 * @version 0.1
 * @date 2019-11-20
 * 
 * @copyright MIT Copyright (c) 2019
 * 
 */

#include <iostream>

using std::endl;
using std::cout;

template <typename T>
class ListNode{
    public:
    ListNode child; //Ask professor
    T data; // This will be of different type
    float key;
    // Constructor
    ListNode();
};

template <typename T>
class List{
    public:
    ListNode<T> front; //Ask professor
    int length;

    List(){
        ListNode<T> endNode; //T is for data
        endNode.child = endNode; //linked list formation check
        /**Line 49**/
    }
};

template <typename T, typename TS>
void listPush(T list,TS data){

}

template <typename T, typename TS>
void listPush(T list,TS data, float Key){
    
}

template <typename TS>
void listTop(TS list){
    
}


template <typename TS>
void listTopKey(TS list){
    
}


template <typename TS>
void listPop(TS list){
    
}


template <typename TS>
void listPopKey(TS list){
    
}


template <typename TS>
void listPrint(TS list){
    
}


template <typename TS>
void listEmpty(TS list){
    
}


template <typename TS, typename TN>
void listCopyGuts(TS list, TN nodeExample){
    
}

void testCase(){
    cout << "Test case Here" << endl;
}






int main(){
    testCase();
    return 0;
}