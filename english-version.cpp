#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n = 1;
deque<int> eulerCircuit;
map<int, multiset<int>> graph;

bool canVisitAll(int start) {
    queue<int> bfs;
    set<int> visited;
    visited.insert(start);
    bfs.push(start);
    while(!bfs.empty()) {
        int cur = bfs.front(); bfs.pop();
        for(int next : graph[cur])
            if(!visited.count(next)) {
                visited.insert(next);
                bfs.push(next);
            }
    }
    return visited.size() == n;
}


bool isEulerCircuit() {

    if(!canVisitAll(0)) return false;
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
    eulerCircuit.push_front(cur);
}

