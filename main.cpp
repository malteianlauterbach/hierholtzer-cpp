#include <bits/stdc++.h>
using namespace std;

int n = 5;
deque<int> eulerKreis;
map<int, multiset<int>> graph;
// checkt ob der Algorithmus alle Felder besuchen kann und fährt diese entsprechend der Regeln ab.
bool kannAllesBesuchen(int start) {
    queue<int> bfs;
    set<int> besucht;
    besucht.insert(start);
    bfs.push(start);
    while(!bfs.empty()) {
        int cur = bfs.front(); bfs.pop();
        for(int next : graph[cur])
            if(!besucht.count(next)) {
                besucht.insert(next);
                bfs.push(next);
            }
    }
    return besucht.size() == n;
}

// Testet ob der vorliegende Graph eine Eulergraph ist
bool istEulerKreis() {
    // bei allen Nodes: indegree = outdegree
    if(!kannAllesBesuchen(0)) return false;
    map<int,int> indegree;
    map<int,int> outdegree;
    for(auto edges : graph) {
        for(auto next : edges.second) {
            indegree[next]++;
        }
    }
    for(auto out: outdegree) {
        int x = out.first;
        if(out.second != indegree[x]) return false;
    }
    return true;
}

void hierholzer(int cur) {
    while(graph[cur].size()) {
        int next = *graph[cur].begin();
        graph[cur].erase(graph[cur].begin());
        hierholzer(next);
    }
    eulerKreis.push_front(cur);
}

void findEulerKreis(vector<vector<int>>& edges) {
    eulerKreis.clear();
    graph.clear();
    for(auto edge : edges)
        graph[edge[0]].insert(edge[1]);
    cout << (istEulerKreis() ? "ist eulerkreis" : "nicht eulerkreis") << endl;
    
    hierholzer(0);
}

int main() {
    vector<vector<int>> edges = {{0,1},{1,2},{1,3},{2,1},{3,4},{4,0},{5,1},{1,6},{7,6}};
    findEulerKreis(edges);
    for(auto x : eulerKreis)
        printf("%d ", x);
}