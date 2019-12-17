#include "kdTree_general.h"
#include <math.h>
#include <vector>


using std::endl;
using std::cout;



int parentf(int i) { return i/2;} 
  
// to get index of left child of node at index i 
int left(int i) { return (2*i); } // considering starting index 1

// to get index of right child of node at index i 
int right(int i) { return (2*i + 1); } // considering starting index 1


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
  cout << "Query Node = " << "10, 31" << endl;
  cout << "Nearest Node = " << nearestNode.first.position[0] << "," << nearestNode.first.position[1] << " and Dist = " << nearestNode.second << endl; 
  
}

/*
int main(){
    testcase_kd();
    return 0;
}
*/