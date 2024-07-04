# AI for Robotics II
## Assignment 2: Task and Motion Planning
# Introduction

The aim of this assignment is to work on task motion planning, focusing
on the merge of cpp code with a planning problem.\
In particular, the goal is moving the robot R in order to collect any 2
assignment reports placed in the corner of the environment given and
bringing them to the submission desk while minimizing its motion cost.
The motion cost is the length of the path covered by the robot.

# Mapping

Firstly, with the aim of mapping the environment, all the way-points
have been chosen, starting with the points given. All the
[red]{style="color: Red"} points in the graph are the given ones: the
starting position (0,0), the corners (the environment is coincident with
a 3$\times3$ square) and the submission desk. Then 24 points have been
randomly extracted. Taking advantage of these 30 points a graph has been
created. This has been done by developing the class `roadMap`. The nodes
are the way-points, while the edges have been created connecting each
node with the k (which is equal to 5) nearest one. The graph obtained,
shown in the Figure below, is an oriented weighted graph; where the
weight of the edges is given by the distance between the nodes.

![graph](https://github.com/Tabi43/Bender/assets/114100814/a41ca6d2-7b7b-4cc6-9f13-e585365775b0)


In order to move around in the graph, the Dijkstra algorithm has been
implemented. It computes the shortest path among two nodes, which are
given by input, and returns the path as a list of way-point and the
actual distance between them by summing all the edges weight. This class
is then used in `VisitSolver`.

# CPP

The provided `VisitSolver` file has been modified to adapt the previous
code to the new functionalities. As first step the variable `roadMap`
has been created as a graph object. Then, after the map of way-point has
been created by the function `parseWaypoint`, the map is used to
initialize the graph. It was then turn to modify the function
`calculateExternal` in order to associate the actual distance traveled
to the variable dummy. The cost to move from a region to another one is
calculated by *distance_euc*, which takes as input two regions, checks
which way-points are associated to them and then gives them to the
Dijkstra algorithm function of the `roadMap`.\
At this point a modification to the CMake file was needed: the file
roadmap.cpp has been added in add_library and add_executable.

# PDDL

Concerning the PDDL, it has been necessary to modify as follows the
domain and the problem files given. This has been done in order to take
into account the fact that the robot has now to handle the assignment
reports.

-   Domain:\
    Different features have been added:

    -   The type to model the assignment reports (*assignment*);

    -   The predicates to describe whether the assignment is in a region
        (*ass_in*) or on the robot (*on_robot*);

    -   The function to count how many reports are on the robot
        (*ass_on_rob*);

    -   The two durative-actions to take a report (*take_ass*) and to
        drop a pair of them (*drop_ass*).

-   Problem: Each aspect of the problem has been modified:

    -   object:\
        4 assignments have been added;

    -   init:\
        Each report is located in a different corner and the robot has
        not any report;

    -   goal:\
        All the reports must be at the submission desk.
