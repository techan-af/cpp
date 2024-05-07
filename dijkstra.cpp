#include<bits/stdc++.h>
using namespace std;

void dijkstra(vector<vector<pair<int,int>> > adj,int n,int S, int E){

    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>> > pq;
    vector<int> vis(n+1,0);

    vector<int> dist(n+1,1e9);
    // dist node
    pq.push({0,S});
    dist[S] = 0;
    
    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();

        int wt = it.first;
        int node = it.second; 
        
        for(auto itr : adj[node]){
            int adjnode = itr.first;
            int adjw = itr.second;

            if(wt+adjw < dist[adjnode]){
                dist[adjnode] = wt + adjw;
                pq.push({dist[adjnode],adjnode});
            }
        }
    }

    if(dist[E] == 1e18) cout << "Not reached" << endl;
    else cout << "reached " << dist[E] << endl;


}

int main(){
    int n,m; cin>>n>>m;
    vector<vector<pair<int,int>> > adj(n+1);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    dijkstra(adj,n,1,5);
}
/*
5 5
1 2 6
1 3 7
2 3 2
3 4 4
4 5 5

*/