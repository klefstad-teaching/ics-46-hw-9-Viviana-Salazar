#include "dijkstras.h"

vector<int> dijkstra_shortest_path(Graph& graph, int source, vector<int>& previous){
    int numVertices = graph.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = -1;

    // Declaring a prio queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({0, source});

    while(!minHeap.empty()){
        // extract w minimum weight
        int u = minHeap.top().second;
        minHeap.pop();

        if(visited[u]){continue;}
        visited[u] = true;

        for( Edge edge : graph[u]){
            int v = edge.dst;
            // second or weight?
            int weight = edge.weight;

            if(!visited[v]&&distances[u] + weight < distances[v]){
                distances[v] = distances[u]+ weight;
                previous[v] = u;
                // switch this?
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    std::stack<int> path_stack;


    for(int v = destination; v!= -1; v = previous[v]){
        path_stack.push(v);
    }

    while (!path_stack.empty()){
        path.push_back(path_stack.top());
        path_stack.pop();
    } 

    return path;
}

void print_path(const vector<int>& v, int total){
    for(size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << total << endl;
}