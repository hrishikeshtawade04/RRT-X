[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

# Overview

RRT-X Dynamic obstacle avoidance algorithm (developed by Michael Otte, MIT 2014) 

For more details kindly refer to the paper  
"RRT-X: Real-Time Motion Planning/Replanning for Environments 
with Unpredictable Obstacles," 
WAFR 2014, 
Michael Otte and Emilio Frazzoli

- The code was initially written in the Julia language (http://julialang.org/) by Professor Michael Otte. 
- Sharan Nayak worked on making it compatible to newer Julia versions (https://gitlab.com/Otte-Lab) 

This repository contains the C++ version of the code developed by me. Following is the instruction to compile. You will have to uncomment the main of the particular file you want to run and then execute the suitable compilation code for it. 
```
g++ -std=c++11  -I../include list.cpp -o lit
g++ -std=c++11  -I../include heap.cpp -o heap
g++ -std=c++11  -I../include kdtree_general.cpp -o kdtree
g++ -std=c++11  -I../include DRRT_simpleEdge_functions.cpp DRRT_distance_functions.cpp -o simplef
g++ -std=c++11  -I../include DRRT_* list.cpp heap.cpp kdTree_general.cpp experimentsForPaper.cpp -o rrtx
```

