#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

#include <iostream>
#include <deque> // gives more flexibility
#include <array>
#include <cmath>

using std::endl;
using std::cout;
using std::deque;

template <typename T>
class ListNode{
    public:
    T data; 
    float key = std::nan("1"); // check with professor
    /**Line 49**/
};

template <typename T>//
class List{
    public:
    deque <ListNode<T>> list;
    int length = 0;
};

template <typename T>//
void listPush(List<T>& list,T data){ 
    ListNode<T> newNode; 
    newNode.data = data;
    list.list.push_front(newNode);
    list.length = list.list.size(); 
}

// Overrided
template <typename T> 
void listPush(List<T>& list,T data, float key){
    ListNode<T> newNode; 
    newNode.data = data;
    newNode.key = key;
    list.list.push_front(newNode); 
    list.length = list.list.size();
}

template <typename T>
T listTop(List<T>& list){ //
    if (!list.list.empty()) {
        return list.list.front().data; 
    }
     
}

template <typename T>
ListNode<T> listTopKey(List<T>& list){ 
    if (!list.list.empty()) {
        return (list.list.front()); 
    }    
}

template <typename T> // Tested with listEmpty
T listPop(List<T>& list){
    if (!list.list.empty()) {
        ListNode<T> oldTop;
        oldTop = list.list.front();
        list.list.pop_front();
        list.length = list.list.size();
        return oldTop.data;
    } 
}

template <typename T>
void listEmpty(List<T>& list){   //
    while(!list.list.empty())
        listPop(list);
}


template <typename T> //
ListNode<T> listPopKey(List<T>& list){
    if (!list.list.empty()) {
        ListNode<T> oldTop;
        oldTop = list.list.front();
        list.list.pop_front();
        list.length = list.list.size();
        return oldTop;
    } 
}


void testCase_list();

#endif  // INCLUDE_LIST_H_
