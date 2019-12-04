#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using std::endl;
using std::cout;

template <typename T>
class HeapNode{
    public:
    T data;
    int heapIndex;
    bool inHeap;

    HeapNode():heapIndex{-1},inHeap{false}{} // check if data removed works
};

template <typename T>
T keyDefault(HeapNode<T> node);
template <typename T>
bool lessThanDefault(HeapNode<T> a, HeapNode<T> b);
template <typename T>
bool greaterThanDefault(HeapNode<T> a, HeapNode<T> b);
template <typename T>
void markDefault(HeapNode<T> &node);
template <typename T>
void unmarkDefault(HeapNode<T> &node);
template <typename T>
bool markedDefault(HeapNode<T> &node);
template <typename T>
void setIndexDefault(HeapNode<T> &node, int val);
template <typename T>
void unsetIndexDefault(HeapNode<T> &node);
template <typename T>
int getIndexDefault(HeapNode<T> node);
template <typename T>
void swap(HeapNode<T> *x, HeapNode<T> *y);

template <typename T> //, typename TK>
class BinaryHeap{
    public:
    std::vector<HeapNode<T>> heapNode;
    int indexOfLast;
    int parentOfLast;
    // Functions used for interacting with marks and indices.
    T (*key)(HeapNode<T> node);
    bool (*lessThan)(HeapNode<T>,HeapNode<T>);
    bool (*greaterThan)(HeapNode<T>,HeapNode<T>);
    void (*mark)(HeapNode<T>&);
    void (*unmark)(HeapNode<T>&);
    bool (*marked)(HeapNode<T>&);
    void (*setIndex)(HeapNode<T>&, int);
    void (*unsetIndex)(HeapNode<T>&);
    int (*getIndex)(HeapNode<T>);
    

    //Constructor
    BinaryHeap(const int maxSize = 64){
        std::vector<HeapNode<T>> H(maxSize+1);
        heapNode = H; //since we want to start indexing from 1
        indexOfLast = 0;
        parentOfLast = -1;
        key = keyDefault;
        lessThan = lessThanDefault;
        greaterThan = greaterThanDefault;
        mark = markDefault;
        unmark = unmarkDefault;
        marked = markedDefault;
        setIndex = setIndexDefault;
        unsetIndex = unsetIndexDefault;
        getIndex = getIndexDefault;
    }

    
    BinaryHeap(T (*keyarg)(HeapNode<T> node) = keyDefault, bool (*lessThanarg)(HeapNode<T>,HeapNode<T>) = lessThanDefault, 
    bool (*greaterThanarg)(HeapNode<T>,HeapNode<T>) = greaterThanDefault,void (*markarg)(HeapNode<T>&) = markDefault, 
    void (*unmarkarg)(HeapNode<T>&) = unmarkDefault, bool (*markedarg)(HeapNode<T>&) = markedDefault, 
    void (*setIndexarg)(HeapNode<T>&, int) = setIndexDefault, void (*unsetIndexarg)(HeapNode<T>&) = unsetIndexDefault, 
    int (*getIndexarg)(HeapNode<T>) = getIndexDefault,const int maxSize = 64){
        std::vector<HeapNode<T>> H(maxSize+1); // since we want to start indexing from 1
        heapNode = H; 
        indexOfLast = 0;
        parentOfLast = -1;
        key = keyarg;
        lessThan = lessThanarg ;
        greaterThan = greaterThanarg;
        mark = markarg;
        unmark = unmarkarg;
        marked = markedarg;
        setIndex = setIndexarg;
        unsetIndex = unsetIndexarg;
        getIndex = getIndexarg;
    }
    
};

int parent(int i);
int left(int i);
int right(int i);
template <typename T>
void bubbleUp(BinaryHeap<T> &H, int n);
template <typename T>
void bubbleDown(BinaryHeap<T> &H, int n);
template <typename T>
void addToHeap(BinaryHeap<T> &H, HeapNode<T> thisNode);
template <typename T>
std::pair<HeapNode<T> , bool> 
topHeap(BinaryHeap<T> &H);
template <typename T>
std::pair<HeapNode<T> , bool> 
popHeap(BinaryHeap<T> &H);
template <typename T>
void removeFromHeap(BinaryHeap<T> &H, HeapNode<T> &thisNode);
template <typename T>
void updateHeap(BinaryHeap<T> &H, HeapNode<T> thisNode);
template <typename T>
bool checkHeap(BinaryHeap<T> &H);
template <typename T>
std::vector<HeapNode<T>> cleanHeap(BinaryHeap<T> &H);
template <typename T>
void printHeap(BinaryHeap<T> &H);
template <typename T>
void bubbleUpB(BinaryHeap<T> &H, int n);
template <typename T>
void bubbleDownB(BinaryHeap<T> &H, int n);
template <typename T>
void addToHeapB(BinaryHeap<T> &H, HeapNode<T> thisNode);
template <typename T>
std::pair<HeapNode<T> , bool> 
topHeapB(BinaryHeap<T> &H);
template <typename T>
std::pair<HeapNode<T> , bool> 
popHeapB(BinaryHeap<T> &H);
template <typename T>
void removeFromHeapB(BinaryHeap<T> &H, HeapNode<T> &thisNode);
template <typename T>
void updateHeapB(BinaryHeap<T> &H, HeapNode<T> thisNode);
template <typename T>
bool checkHeapB(BinaryHeap<T> &H);
template <typename T>
std::vector<HeapNode<T>> cleanHeapB(BinaryHeap<T> &H);






