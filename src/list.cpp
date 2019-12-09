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

// Read Queue

#include <iostream>
#include <deque> // gives more flexibility
#include <array>
#include <cmath>
#include "list.h"

using std::endl;
using std::cout;
using std::deque;




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
void testCase_list(){
    List<std::array<int, 3>> L;
    //List<std::array<int, 3>> L;
    std::array<int, 3> a{ {1, 1, 1} };
    std::array<int, 3> b{ {2, 2, 2} };
    std::array<int, 3> c{ {3, 3, 3} };
    std::array<int, 3> d{{0,0,0}};
    ListNode<std::array<int, 3>> testNode;

    listPush(L,a);
    
    d = listTop(L);
    cout << "Top = " << d[0] << " " << d[1] << " " << d[2] << endl;
    
    listPush(L,b,1);
    
    testNode = listTopKey(L);
    cout << "Key = " << testNode.key << endl;
    
    testNode = listPopKey(L);
    cout << "Popped Node key= " << testNode.key << endl;
    
    listPush(L,c);
    d = listTop(L);
    cout << "Top = " << d[0] << " " << d[1] << " " << d[2] << endl;

    cout << "List length = " << L.length << endl;
    cout << "List length = " << L.length << endl;
    listEmpty(L);
    cout << "List length = " << L.length << endl;

}

/*
int main(){
    testCase();
    return 0;
}
*/