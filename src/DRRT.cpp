#include <iostream>
#include <fstream>
#include <string>
#include "DRRT_data_structures.h"
#include "DRRT.h"

using std::string;
using std::getline;
using std::endl;
using std::cout;
using std::cerr;
// reads a polygon from a file that is discoverable (always obs, or vanishes
// or appears once the robot gets within sensor range).
// stores each obstacle obsMult times to simulate more complex environments
// whenver this is used for non-experimental pourposes obsMult should be 1

