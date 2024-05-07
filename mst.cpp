#include<bits/stdc++.h>
using namespace std;

class DSU{
    public:
    vector<int> parent,rank;

    public:
    DSU(int n){
        parent.resize(n+1);
        rank.resize(n+1,0);
        for(int i=0;i<=n;i++){
            parent[i]=i;
        }
    }

    int findulp(int node){
        if(parent[node] == node){
            return node;
        }

        return parent[node] = findulp(parent[node]);
    }

    void unionbyrank(int u,int v){
        int up = findulp(u);
        int vp = findulp(v);

        if(up == vp) return;

        if(rank[up] > rank[vp]){
            parent[vp] = up;
        }else if(rank[vp] > rank[up]){
            parent[up] = vp;
        }else{
            parent[up] = vp;
            rank[vp]++;
        }
    }

};

void primsalgo(vector<vector<pair<int,int>>> adj,int n){

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> > pq;
    vector<int> vis(n+1,0);

    // dist  node
    pq.push({0,0});
    int sum=0;

    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();

        int dist = it.first;
        int node = it.second;
        if(vis[node] == 1) continue;
        vis[node] = 1;
        sum += dist;

        for(auto itr : adj[node]){
            if(!vis[itr.first]){
                pq.push({itr.second,itr.first});
            }
        }
    }

    cout << "Minimum cost is : " << sum << endl;

}

void kruskalalgo(vector<vector<pair<int,int>>> adj,int n){
    vector<pair<int,pair<int,int>>> edges;

    for(int i=0;i<n;i++){
        for(auto it : adj[i]){
            int u = i, v = it.first, w = it.second;
            edges.push_back({w,{u,v}});
        }
    }

    DSU ds(n+1);
    // wt start dest
    sort(edges.begin(),edges.end());

    int sum = 0;
    for(auto it : edges){
        int w = it.first, u = it.second.first, v = it.second.second;
        if(ds.findulp(u) != ds.findulp(v)){
            sum+=w;
            ds.unionbyrank(u,v);
        }
    }

    cout << "Minimum cost is : " << sum << endl;
}

int main(){

    int n,m; cin>>n>>m;
    vector<vector<pair<int,int>>> adj(n+1);

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    kruskalalgo(adj,n);
    primsalgo(adj,n);
}