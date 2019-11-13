Michael Otte
MIT
2014


This contains the code that was used for the paper 
"RRT-X: Real-Time Motion Planning/Replanning for Environments 
with Unpredictable Obstacles," 
WAFR 2014, 
Michael Otte and Emilio Frazzoli


The code is written in the Julia language, see:
http://julialang.org/
for more information

In general you will find 4 types of files in addition to this 
readme. The planning/replanning code for RRTX is written in 
julia code and has the ".jl" extension. I have also included
scripts for creating environments with obstacles, as well as 
files that can be used to create movies from output files.
Both of the latter are matlab code (".m" file extensions).
Names should be descriptive enough to determine what is what.
Finally, some pre-created environments appear in the folder
"environments." The are defined by text in text files.
However, I suspect that not all environemnts included are
valid with respect to the current version of the code. 
Environments essentially have a list of obstacles. There
are many different possible types of obstacles. They 
Vary both on how they are defined (sphere, polygon, etc.)
as well as how they change vs. time. Look into the comments
in the obstacle data structure and/or the obstacle generation
files to see how this this info is saved in files (different
obstacles types are denoted by a different integer flag, and
will require/assume different information is stored the file.

RRTX code:
To get started I suggest running any of the function in:
-experimentsForPaper.jl
-dubinsExperimentsForPaper.jl
This will produce output that you can render using the 
appropriate make_movie function (see function header 
of whatever simulation you ran for the appropriate render
function)

The meat of the code appears in:
-DRRT.jl
   Contains all functions (except those dependent on edge type)
-DRRT_data_structures.jl
   Contains all data structures (except edge types)
-DRRT_distance_functions.jl
   Contains all of the distance functions that may be used.
   In general, these are renamed and accessed indirectly using 
   Julia's function behavior, e.g., newFunction() = oldFunction()
   In order to make the code more general.

An edge data structure and some functions associated with it
are also required and will depend on the type of robotic system 
being used. For example, use: 
-DRRT_SimpleEdge.jl
-DRRT_SimpleEdge_functions.jl
*or*
-DRRT_DubinsEdge.jl
-DRRT_DubinsEdge_functions.jl
depending on if you want a holonomic system or a Dubins system,
respectively. New systems will require their own versions of 
the data structure and functions in these two files. 
Also, the abstract type "Edge" is aliased to be whatever type
of edge you are using. This was done in an attempt to increase 
speed---Julia is faster if it knows more about the types of 
things being used.

I have also included a few basic data structures that I use
(heap, kd-tree, lists, etc.). These are also in Julia and 
written by me. Obviously, they can also be used as stand alone
code for their respective data structures.



Note that, in general, the time required to render the 
videos takes much longer to run than RRTX takes to run.
However, movies that show "real-time" performance, once output,
because the frame-rate is set to 1/"slice-time" that was used. 
(i.e., is correct with respect to the runtime because RRTX code
saves output files every "slice-time" seconds). Also note that
the time required to output the data files is not included in
the total runtime (i.e., we keep track of the cumulative time 
spent saving data and then subtract that from total time when 
calculating slice time. When no video data is output (e.g.,
for repeated trials used to generate statistics for paper) then
no time is subtracted from the total runtime.



v0.2:
fixed a few function that were depriciated in julia. Also made work
(I think) on 32 bit in addition to 64 bit chips.

