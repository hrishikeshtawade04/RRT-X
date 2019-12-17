#include "heap.h"
#include "list.h"
#include "kdTree_general.h"
#include "DRRT_distance_functions.h"
#include "DRRT_simple_edge.h"
#include "DRRT_data_structures.h"
#include "DRRT_SimpleEdge_functions.h"
#include "DRRT.h"
#include <string>
#include <fstream>
#include <limits>

//const Edge{T} = SimpleEdge{T} // converted the edge directly instead

using std::string;
using std::ofstream;

/**--------------------------------------------------------------------------------**
**------------- after this line is code used for most recent version -------------**
**--------------------------------------------------------------------------------**

** this runs the specified algorithm in a static 2D environemnt and
** saves data in ./temp to allow debugging
** NOTE: plot resulting simulation with make "make_video.m"
*/

void Static_2D_Debug(){

  string algorithmName = "RRTx";  // this is the algorithm to run, valid options are:
                         // "RRT", "RRT*", "RRT//", and "RRTx"

  float changeThresh = 1.0;     // ONLY USED FOR RRTx

  string expName = "Debug";      // the name of this experiment (for naming output files)

  float total_time = 50000.0;       // total planning time (move after this, and keep planning)
  float slice_time = 1.0/10.0;       // for saving data

  float envRad = 50.0;          // environment spans -envRad to envRad in each dimension
  float robotRad = 0.5; 
  vector<float> start{0.0, -40.0};   // robot goes to here (start location of search tree)
  vector<float> goal{-40.0, 40.0};    // robot comes from here (goal location of search tree)

  ofstream expFile;
  //obstacleFile = "environments/empty.txt"
  system("MD experiments");
  expFile.open("experiments/" + expName + ".txt");
  
  bool MoveRobot = false;
  bool saveVideoData = true;

  int d = 2;                // number of dimensions
  int timeOut = std::numeric_limits<int>::max(); // a backup timeout in seconds
  bool saveTree = true;      // if true then saves the tree in out.txt

  vector<float> lowerBounds(d,-envRad);
  vector<float> upperBounds(d,envRad);
  cout << lowerBounds.size() << " " << lowerBounds[0] << lowerBounds[1] << endl; 
  
    
  CSpace<float> C(d, -1.0, lowerBounds, upperBounds, start, goal);

  // init robot radii
  C.robotRadius =  robotRad;

  // init robot velocity
  C.robotVelocity = 2.0;

  string obstacleFile = "environments/rand_Static.txt";

  // load obstacles
  vector<float> obstaclePosition{10,30};
  Obstacle ob(1,obstaclePosition,0.5);
  ob.senseableObstacle = false;
  ob.obstacleUnusedAfterSense = false;
  ob.obstacleUnused = false;
  listPush(C.obstacles,ob);
  
 
  // set up sampling function
  C.pGoal = .01; // sequence changed from original code
  C.randNode = randNodeOrFromStack; // use this function to return random nodes
  // space paramiters
  C.spaceHasTime = false;
  C.spaceHasTheta = false;

  string dataFile = "experiments/$(expName)/debug_data.txt";

  RRTX(C, total_time, slice_time, 5.0, 100.0, changeThresh, algorithmName, MoveRobot, saveVideoData, saveTree, dataFile);
}
/*
int main(){
    Static_2D_Debug();
    return 0;
}
*/



