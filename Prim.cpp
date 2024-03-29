#include "Prim.h"

//write your Prim's Algorithm here:
Graph<double> prim(Graph<double> g, int root){
    //creating an empty graph (forest) for storing what we have added
    //the false here is for creating an undirected graph (you can refer to the Graph.h provided for implementation details)
    Graph<double> minimum_spanning_tree(false);

    //creating this int array for storing the vertex that have the cheapest connection to a certained vertex (accessed by putting the vertex's storage index (not vertex ID!) into the array index)
    int* cost_of_cheapest_connection_to = new int[g.getNumOfVertex()];
    //setting the default value of each vertex to infinity, assuming no length will be greater than this value
    for (int i = 0; i < g.getNumOfVertex(); ++i){
        cost_of_cheapest_connection_to[i] = 0x7fffffff;
    }

    //creating this int array for storing "which one does the cheapest connection to this vertex connects to?"
    int* source_of_cheapest_connection_to = new int[g.getNumOfVertex()];
    //initializing all of them to be saying "Not connected"
    for (int i = 0; i < g.getNumOfVertex(); ++i){
        source_of_cheapest_connection_to[i] = NOT_CONNECTED;
    }

    //creating a bool vector for storing whether a certain vertex has been visited in the past
    vector<bool> visited;
    visited.resize(g.getNumOfVertex(), false);

    //giving our root a smaller cost_of_cheapest_connection_to value so we could force our algorithm to begin from that point
    cost_of_cheapest_connection_to[root] = 0;

    //while the queue is not empty
    while(minimum_spanning_tree.getNumOfVertex() != g.getNumOfVertex()){
        //First step: finding the UNVISITED vertex with the lowest cost of connection to
        int cheapest_vertex_index = -1;
        int cheapest_vertex_cost = 0x7fffffff;
        for (int i = 0; i < g.getNumOfVertex(); ++i){
            if (cost_of_cheapest_connection_to[i] <= cheapest_vertex_cost && visited[i] ==  false){
                cheapest_vertex_cost = cost_of_cheapest_connection_to[i];
                cheapest_vertex_index = i;
            }
        }

        //Second: we add the found vertex to our minimum spanning tree
        minimum_spanning_tree.addVertex(g.getVertex(cheapest_vertex_index));
        if (root != cheapest_vertex_index) {
            minimum_spanning_tree.addEdge(g.getVertex(cheapest_vertex_index), g.getVertex(source_of_cheapest_connection_to[cheapest_vertex_index]), cheapest_vertex_cost);
        }

        //setting the vertex to be visited
        visited[cheapest_vertex_index] = true;

        //Third: we get the new "cost of cheapest connection to" and "source of cheapest connetion to" values
        vector<double> all_adjacencies = g.getAllAdjacentVertex(g.getVertex(cheapest_vertex_index));
#if DEBUG
        cout << "Adjacency list for " << cheapest_vertex_index << endl;
#endif
        for (vector<double>::iterator it = all_adjacencies.begin(); it != all_adjacencies.end(); it++){
#if DEBUG
            cout << *it << endl;
#endif
            if (visited[g.getIndex(*it)] == false && g.getIndex(*it) != cheapest_vertex_index)
            {
                int cost = g.getEdge(g.getVertex(cheapest_vertex_index), *it);
                if (cost <= cost_of_cheapest_connection_to[g.getIndex(*it)])
                {
                    cost_of_cheapest_connection_to[g.getIndex(*it)] = cost;
                    source_of_cheapest_connection_to[g.getIndex(*it)] = cheapest_vertex_index;
                }
            }
        }
    }

    return minimum_spanning_tree;
}