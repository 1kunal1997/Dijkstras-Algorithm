# Dijkstras-Algorithm
This is a C++ implementation of Dijkstra's shortest path algorithm. This program will prompt the user for cities to start from and end at, and then output the distance and directions of the shortest path connecting those cities. It uses a 2D array to store the distances between cities, using the constant 'INF' if a city is inaccessible. You can make your own set of connected cities by filling in the array, but by default, this arrangement of 9 cities from [GeeksForGeeks](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/) is used:

![image of connected cities](https://www.geeksforgeeks.org/wp-content/uploads/Fig-11.jpg)

## How to Run
Note: Cities named 'A-I' represent the nodes 0-8 in the picture above, respectively.

```
C:\ ..> ./dijkstra.exe
Enter the cities you want to start from and end at (A-I): A E
Shortest path: A H G F E 
Distance: 21
```

## Acknowledgements
Thanks to Brian Mak for the idea, and for helping me write the code in a readable manner.
Thank you to [Computerphile](https://www.youtube.com/watch?v=GazC3A4OQTE&t=13s) for teaching me how the algorithm works.

