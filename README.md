# Second Milestone : Shortest Path in a Graph Searcher
In this assigment the main focus is solving a search problem with search algorithms. 
We needed to find the best search algorithm that gives the shortest path between two entries in a matrix.
The search algorithms are able to move left/right and up/down.

### Compilation instructions: 
The program receives multiple of client simultaniously, which means it handles multiple problems at the same time. compile using 'make compile' and run using 'make run', and then send the server the appropriate problem.

### Explaining the graphs:
In this case, the problem is a matrix with cost on each vertex. This cost resembles the cost of passing through the vertex. The input should be line by line, and includes all rows of the matrix. After it will appear the starting index, goal index, and eventually "end", which signifies the end of input. The output will be the best path from Starting point to goal point, which includes the exact path, step by step, and its cumulative cost (in each step).
