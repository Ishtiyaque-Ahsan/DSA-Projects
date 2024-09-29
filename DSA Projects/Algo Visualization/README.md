Implemented below algorithms in Java to graphically visualize them using Java Swing and AWT.<br/>
• Convex Hull problem using the Graham scan Algorithm<br/>
        
          The Convex Hull problem involves finding the smallest convex polygon that can enclose a set of points in a 2D plane.
          The Graham Scan Algorithm is a method used to solve this by first sorting the points based on their polar angle relative to a reference point 
          (usually the point with the lowest y-coordinate). 
          The algorithm then processes the points, adding them to the hull while ensuring that each new point maintains the convexity of the shape 
          by checking for counter-clockwise turns. It runs in O(n log n) time due to the sorting step, making it efficient for large datasets.


        • Edmond Karp Algorithm to find max flow in a graph network<br/>
        
          The Edmonds-Karp Algorithm is an implementation of the Ford-Fulkerson method for finding the maximum flow in a flow network.
          It uses Breadth-First Search (BFS) to find the shortest augmenting path from the source to the sink in terms of the number of edges. 
          By repeatedly augmenting flow along these paths, the algorithm improves the flow until no more augmenting paths exist. 
          Its time complexity is O(V × E²), where V is the number of vertices and E is the number of edges. 
          It guarantees the maximum flow by ensuring BFS finds the shortest paths in each iteration.






