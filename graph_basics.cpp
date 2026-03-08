#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph{
    int V;
    vector<vector<int>> adj;
public:
    Graph(int V){
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
    }
    void bfs(int startnode){
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(startnode);
        visited[startnode] = true;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            cout << curr << " ";
            for(int neighbor : adj[curr]){
                if(!visited[neighbor]){
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
    void dfs(int startnode){
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(startnode);
        visited[startnode] = true;
        while(!s.empty()){
            int curr = s.top();
            s.pop();
            cout << curr << " ";
            for(int neighbor : adj[curr]){
                if(!visited[neighbor]){
                    s.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
    void dfs_recursive(int startnode){
        vector<bool> visited(V, false);
        dfs_recursive_helper(startnode, visited);
    }
    void dfs_recursive_helper(int node, vector<bool>& visited){
        visited[node] = true;
        cout << node << " ";
        for(int neighbor : adj[node]){
            if(!visited[neighbor]){
                dfs_recursive_helper(neighbor, visited);
            }
        }
    }
    int shortest_path(int startnode, int target){
        vector<int> dist(V, -1);
        queue<int> q;
        q.push(startnode);
        dist[startnode] = 0;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            for(int neighbor : adj[curr]){
                if(dist[neighbor] == -1){
                    dist[neighbor] = dist[curr] + 1;
                    q.push(neighbor);
                }
            }
        }
        return dist[target];
    }
    bool is_cyclic(){
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);
        for(int i = 0; i < V; i++){
            if(!visited[i]){
                if(is_cyclic_helper(i, visited, recStack)){
                    return true;
                }
            }
        }
        return false;
    }
    bool is_cyclic_helper(int node, vector<bool>& visited, vector<bool>& recStack){
        visited[node] = true;
        recStack[node] = true;
        for(int neighbor : adj[node]){
            if(!visited[neighbor] && is_cyclic_helper(neighbor, visited, recStack)){
                return true;
            }
            else if(recStack[neighbor]){
                return true;
            }
            return false;
        }
        recStack[node] = false;
        return false;
    }
    bool is_bipartite(){
        vector<int> color(V, -1);
        for(int i = 0; i < V; i++){
            if(color[i] == -1){
                if(!is_bipartite_helper(i, color)){
                    return false;
                }
            }
        }
        return true;
    }
    bool is_bipartite_helper(int node, vector<int>& color){
        queue<int> q;
        q.push(node);
        color[node] = 0;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            for(int neighbor : adj[curr]){
                if(color[neighbor] == -1){
                    color[neighbor] = 1 - color[curr];
                    q.push(neighbor);
                }
                else if(color[neighbor] == color[curr]){
                    return false;
                }
            }
        }
        return true;
    }
    bool isReachable(int startnode, int target, vector<bool>& visited){
        if(startnode == target){
            return true;
        }
        visited[startnode] = true;
        for(int neighbor : adj[startnode]){
            if(!visited[neighbor]){
                if(isReachable(neighbor, target, visited)){
                    return true;
                }
            }
        }
        return false;
    }
};

int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    cout << "BFS: ";
    g.bfs(0);
    cout << endl;
    cout << "DFS: ";
    g.dfs(0);
    cout << endl;
    cout << "DFS Recursive: ";
    g.dfs_recursive(0);
    cout << endl;

    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 4);
    vector<bool> visited(5, false);
    cout << "Is 0 Reachable to 4: " << g2.isReachable(0, 4, visited) << endl;
    cout << "Is Graph Cyclic: " << g2.is_cyclic() << endl;
    cout << "Is Graph Bipartite: " << g2.is_bipartite() << endl;

    Graph g3(5);
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(1, 3);
    g3.addEdge(2, 4);
    cout << "Shortest Path from 0 to 4: " << g3.shortest_path(0, 4) << endl;

    Graph g4(5);
    g4.addEdge(0, 1);
    g4.addEdge(1, 2);
    g4.addEdge(2, 3);
    g4.addEdge(1, 3);
    cout << "Is Graph Bipartite: " << g4.is_bipartite() << endl;
    return 0;
}