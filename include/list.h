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
void listPush(List<T>& list,T data);

template <typename T> 
void listPush(List<T>& list,T data, float key);

template <typename T>
T listTop(List<T>& list);

template <typename T>
ListNode<T> listTopKey(List<T>& list);

template <typename T> // Tested with listEmpty
T listPop(List<T>& list);

template <typename T>
void listEmpty(List<T>& list);

template <typename T> //
ListNode<T> listPopKey(List<T>& list);
