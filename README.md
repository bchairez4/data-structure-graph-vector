# data-structure-graph-vector

Created by Brian Chairez

This C++ project implements the graph data structure using a std::vector of user defined nodes.
This implementation of a graph data structure is both unweighted and directed, this means there are no weights or costs associated to the nodes that are connected and that each connection to a node is one-way and must be directly specified.
The vector of nodes acts as the adjacency list and each node in the vector contains it's data and another vector that acts as it's respective edge list. 

Both the adjacency list and the edge list are implemented using raw pointers. 
This is done so the adjacency list can call "new" (as well as "delete" to memory manage) to create new nodes when needed and each node's neighbor can be represented in the adjacency list by simply pointing to the node that has been already created to minimize space usage.

Current Issue: erase_neighbors() when deleting a node vertex from the adjacency list does not function corrently. Only if the very first neighbor in a vertex's edge list is the corresponding node will it successfully remove. Neighbors located in the middle or the end of the edge list do not get removed.
