#include<bits/stdc++.h>
using namespace std;

void loop(int node,vector<int> adj[],vector<int> &ans,vector<int> &vis){
    vis[node] = 1;
    ans.push_back(node);
    for(auto it : adj[node]){
        if(!vis[it]){
            loop(it,adj,ans,vis);
        }
    }

}

void bfs(int n, vector<int> adj[]){
    vector<int> vis(n,0);
    vector<int> ans;

    queue<int> q;
    q.push(0);
    vis[0]=1;

    while(!q.empty()){
        auto it = q.front();
        q.pop();

        ans.push_back(it);
        for(auto itr : adj[it]){
            if(!vis[itr]){
                q.push(itr);
                vis[itr] = 1;
            }
        }
    }

    for(auto it:ans){
        cout << it << " ";
    }
    cout << endl;
}

void dfs(int n, vector<int> adj[]){
    vector<int> vis(n,0);
    vector<int> ans;

    for(int i=0;i<n;i++){
        if(!vis[i]){
            loop(i,adj,ans,vis);
        }
    }

    for(auto it:ans){
        cout << it << " ";
    }
    cout << endl;
}


void connected(int n,vector<int> adj[]){
    vector<int> vis(n,0);
    vector<int> ans;
    int cnt = 0;

    for(int i=0;i<n;i++){
        if(!vis[i]){
            cnt++;
            loop(i,adj,ans,vis);
        }
    }

    cout << "connected components are : " << cnt << endl;

}

int main(){
    int n,m; cin>>n>>m;

    vector<vector<int>> adjm(n,vector<int> (n,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>adjm[i][j];
        }
    }

    vector<int> adj[n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjm[i][j]){
                adj[i].push_back(j);
            }
        }
    }

    cout << endl;
    dfs(n,adj);
    bfs(n,adj);
    connected(n,adj);
}