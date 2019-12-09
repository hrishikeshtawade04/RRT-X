#include "kdTree_general.h"
#include <math.h>
#include <vector>
#define COUNT 10

using std::endl;
using std::cout;

template <typename T>
void KDTreeInit(KDTree<T> &K,int d, float (*f)(std::vector<float>, std::vector<float>)){
    K.d = d;
    K.distanceFunction = f; // check with the professor
    K.treeSize = 0;
}

int parentf(int i) { return i/2;} 
  
// to get index of left child of node at index i 
int left(int i) { return (2*i); } // considering starting index 1

// to get index of right child of node at index i 
int right(int i) { return (2*i + 1); } // considering starting index 1


template <typename T>
bool check(KDTree<T> *tree, int index){
  KDTreeNode<T> node =  tree->tree[index];
  return node.kdInTree;
}
template <typename T> // check with professor TKD?
void  kdInsert(KDTree<T> *tree, int index,KDTreeNode<T> newNode, int cd) {
  if(index > tree->tree.size()){
        std::vector<KDTreeNode<T>> newTree(tree->tree.size());  
        tree->tree.insert(tree->tree.end(), newTree.begin(), newTree.end());
    }
  if(!check(tree,index)){ // adds root
    newNode.kdSplit = cd;
    newNode.kdInTree = true;
    newNode.heapIndex = index;
    tree->treeSize = index; // this differs from heap. because start point is not always left
    tree->tree[index] = newNode;
    return;
  }
  KDTreeNode<T> node = tree->tree[index];
  if ( node.position == newNode.position){ // checks for duplicate nodes
    cout << "node not added since it is a duplicate" << endl;
    return;
  }
  else if (newNode.position[cd] < node.position[cd]){ //adding other nodes in the tree
    kdInsert(tree, left(index),newNode,(cd+1)%tree->d);
  }
  else{ //adding other nodes in the tree
    kdInsert(tree, right(index),newNode,(cd+1)%tree->d);
  }
}


 // prints the sub-tree on the command line using dfs
template <typename T> 
void kdPrintSubTree(KDTreeNode<T> root, int space, KDTree<T> *tree, int index)  
{  
    // Base case  
    if (!root.kdInTree)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
   kdPrintSubTree(tree->tree[right(index)], space, tree,right(index));  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" "; 
    cout << "[";  
    for(int i =0; i< tree->d;i++)
      if (i == (tree->d -1))    
        cout<<root.position[i];
      else
       cout<<root.position[i] << " ";
    cout << "]" << endl;  
  
    // Process left child  
    kdPrintSubTree(tree->tree[left(index)], space, tree,left(index));  
}  
  
// Wrapper over print2DUtil()  
template <typename T> 
void kdPrintTree(KDTree<T> *tree, int index)  
{  
    // Pass initial space count as 0  
    kdPrintSubTree(tree->tree[1], 0,tree,1);  
}


 // returns the nearest node to queryPoint and also its distance
template <typename T>
std::pair<KDTreeNode<T> , float>
kdFindNearest(KDTree<T> &tree, std::vector<float> queryPoint){ 
  // initial search (only search if the space does not wrap around)
  float distToRoot = tree.distanceFunction(queryPoint, tree.tree[1].position);
  std::pair <KDTreeNode<T>, float> LnodeAndDist; 
  LnodeAndDist = kdFindNearestInSubtree(tree.distanceFunction, tree.tree[1], queryPoint, tree.tree[1], distToRoot,&tree);
  return LnodeAndDist;
}

// returns the nearest node to queryPoint in the subtree starting at root
// and also its distance, it takes also takes a suggestion for a
// possible closest node (and uses that if it is best)
template <typename T>
std::pair<KDTreeNode<T> , float>
kdFindNearestInSubtree(float (*distanceFunction)(std::vector<float>, std::vector<float>), KDTreeNode<T> root,
  std::vector<float> queryPoint,KDTreeNode<T> suggestedClosestNode, float suggestedClosestDist,KDTree<T> *tree) {

  // walk down the tree as if the node would be inserted
  KDTreeNode<T> parent = root;
  KDTreeNode<T> currentClosestNode = suggestedClosestNode;
  float currentClosestDist = suggestedClosestDist;

  while (true){
    if (queryPoint[parent.kdSplit] < parent.position[parent.kdSplit]){
      // traverse tree to the left
      if (!check(tree, left(parent.heapIndex))){
        // the queryPoint would be inserted as the left child of the parent
        break;
      }
      parent = tree->tree[left(parent.heapIndex)];
      continue;
    }
    else{
      // traverse tree to the right
      if (!check(tree, right(parent.heapIndex))){
        // the queryPoint would be inserted as the right child of the parent
        break;
      }
      parent = tree->tree[right(parent.heapIndex)];
      continue;
    }
  }

  float newDist = distanceFunction(queryPoint,parent.position);
  if (newDist < currentClosestDist){
    currentClosestNode = parent;
    currentClosestDist = newDist;
  }

  // now walk back up the tree (will break out when done)
  while (true){
    // now check if there could possibly be any closer nodes on the other
    // side of the parent, if not then check grandparent etc.

    float parentHyperPlaneDist = (queryPoint[parent.kdSplit] - parent.position[parent.kdSplit]);

    if (parentHyperPlaneDist > currentClosestDist){
      // then there could not be any closer nodes on the other side of the parent
      // (and the parent itself is also too far away
      if (parent.position == root.position){
        // the parent is the root and we are done
        return std::make_pair(currentClosestNode, currentClosestDist);
      }
      if(parentf(parent.heapIndex) < 1)
        parent = tree->tree[1];
      else
        parent = tree->tree[parentf(parent.heapIndex)];
      
      continue;
    }

    // if we are here, then there could be a closer node on the other side of the
    // parent (including the parent itself)

    // first check the parent itself (if it is not already the closest node)
    if (currentClosestNode.position != parent.position){
      newDist = distanceFunction(queryPoint,parent.position);
      if (newDist < currentClosestDist){
        currentClosestNode = parent;
        currentClosestDist = newDist;
      }
    }

    // now check on the other side of the parent
    if ((queryPoint[parent.kdSplit] < parent.position[parent.kdSplit]) && check(tree, right(parent.heapIndex))){ 
      // queryPoint is on the left side of the parent, so we need to look
      // at the right side of it (if it exists)

      // find right subtree dist
       std::pair <KDTreeNode<float>, float> RnodeAndDist;
       RnodeAndDist = kdFindNearestInSubtree(distanceFunction, tree->tree[right(parent.heapIndex)], queryPoint, currentClosestNode, currentClosestDist, tree);

      if (RnodeAndDist.second < currentClosestDist){
        currentClosestDist = RnodeAndDist.second;
        currentClosestNode = RnodeAndDist.first;
      }
    }
    else if (parent.position[parent.kdSplit] <= queryPoint[parent.kdSplit] && check(tree, left(parent.heapIndex))){
      // queryPoint is on the right side of the parent, so we need to look
      // at the left side of it (if it exists)

      // find left subtree dist
      std::pair <KDTreeNode<float>, float> LnodeAndDist; 
      LnodeAndDist = kdFindNearestInSubtree(distanceFunction, tree->tree[left(parent.heapIndex)], queryPoint, currentClosestNode, currentClosestDist,tree);
      if (LnodeAndDist.second < currentClosestDist){
        currentClosestDist = LnodeAndDist.second;
        currentClosestNode = LnodeAndDist.first;
      }
    }

    if (parent.position == root.position){
        // the parent is the root and we are done
      return std::make_pair(currentClosestNode, currentClosestDist);
    }

    if(parentf(parent.heapIndex) < 1)
        parent = tree->tree[1];
    else
        parent = tree->tree[parentf(parent.heapIndex)];
  }
}

float oneTwoDRobotDist(std::vector<float> poseA, std::vector<float> poseB){ //need to be generalized to higher dimensions 
  return (sqrt(pow(poseA[0]-poseB[0],2)+ pow((poseA[1]-poseB[1]),2))); // 
}


void testcase_kd(){
  KDTree<float> tree(2, oneTwoDRobotDist);
  KDTreeInit(tree,2, oneTwoDRobotDist);
  std::vector<float> a{51,75,25,40,70,70,10,30,35,90,55,1,60,80,1,10,50,50};
  for (int i =0; i<a.size();i = i+2){
    std::vector<float> point{a[i],a[i+1]};
    KDTreeNode<float> newPoint(point);
    kdInsert(&tree,1, newPoint, 0);
  }
  cout << tree.treeSize << endl;
  kdPrintTree(&tree,1);
  std::pair <KDTreeNode<float>, float> nearestNode;
  std::vector<float> queryPoint{10,31};
  nearestNode = kdFindNearest(tree, queryPoint);
  cout << "Nearest Node = " << nearestNode.first.position[0] << "," << nearestNode.first.position[1] << " and Dist = " << nearestNode.second << endl; 
  
}

/*
int main(){
    testcase_kd();
    return 0;
}
*/