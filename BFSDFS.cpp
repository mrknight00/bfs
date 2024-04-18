
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
 
using namespace std;
 
const int MAX = 100; // Maximum size for the graph
 
vector<int> graph[MAX]; // Graph representation
bool visited[MAX];      // Array to mark visited nodes
 
// Breadth-First Search function
void bfs(int start_node) {
   queue<int> q;
   q.push(start_node);
   visited[start_node] = true;
 
   while (!q.empty()) {
       int current_node = q.front();
       q.pop();
       cout << current_node << " ";
 
       #pragma omp parallel for
       for (int i = 0; i < graph[current_node].size(); i++) {
           int adj_node = graph[current_node][i];
           if (!visited[adj_node]) {
               #pragma omp critical
               {
                   visited[adj_node] = true;
                   q.push(adj_node);
               }
           }
       }
   }
}
 
// Depth-First Search function
void dfs(int start_node) {
   stack<int> s;
   s.push(start_node);
 
   while (!s.empty()) {
       int current_node = s.top();
       s.pop();
       if (!visited[current_node]) {
           visited[current_node] = true;
           cout << current_node << " ";
 
           #pragma omp parallel for
           for (int i = 0; i < graph[current_node].size(); i++) {
               int adj_node = graph[current_node][i];
               if (!visited[adj_node]) {
                   #pragma omp critical
                   {
                       s.push(adj_node);
                   }
               }
           }
       }
   }
}
 
int main() {
   int n, m; // n: number of nodes, m: number of edges
   cout << "Enter the number of nodes and edges: ";
   cin >> n >> m;
 
   // Input edges
   cout << "Enter the edges (node pairs):\n";
   for (int i = 0; i < m; i++) {
       int u, v;
       cin >> u >> v;
       graph[u].push_back(v);
       graph[v].push_back(u); // For undirected graph
   }
 
   // Initialize visited array
   #pragma omp parallel for
   for (int i = 0; i < n; i++) {
       visited[i] = false;
   }
 
   cout << "Breadth-First Search (BFS): ";
   bfs(0); // Start BFS from node 0
   cout << endl;
 
   // Reset visited array
   #pragma omp parallel for
   for (int i = 0; i < n; i++) {
       visited[i] = false;
   }
 
   cout << "Depth-First Search (DFS): ";
   dfs(0); // Start DFS from node 0
   cout << endl;
 
   return 0;
}