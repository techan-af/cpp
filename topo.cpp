#include<bits/stdc++.h>
using namespace std;

void dfs(int node,vector<int> adj[],vector<int> &vis,stack<int> &st){

    vis[node] = 1;
    for(auto it : adj[node]){
        if(!vis[it]){
            dfs(it,adj,vis,st);
        }
    }
    st.push(node);

}

void topologicalSortusingBFS(int n, int m, vector<int> adj[]) {

    vector<int> inDegree(n, 0);
    for(int u = 0; u < n; u++){
        for(int v : adj[u]){
            inDegree[v]++;
        }
    }

    queue<int> q;
    for(int i = 0; i < n; i++){
        if(inDegree[i] == 0){
            q.push(i);
        }
    }

    vector<int> topologicalOrder;
    while(!q.empty()){
        int node = q.front();
        q.pop();

        topologicalOrder.push_back(node);

        for(int neighbor : adj[node]){
            inDegree[neighbor]--;
            if(inDegree[neighbor] == 0){
                q.push(neighbor);
            }
        }
    }

    if (topologicalOrder.size() != n) {
        cout << "The graph contains a cycle and cannot be topologically sorted." << endl;
        return;
    }

    for (int node : topologicalOrder) {
        cout << node << " ";
    }
    cout << endl;
}


void topologicalSortusingDFS(int n, int m, vector<int> adj[]){
    stack<int> st;
    vector<int> vis(n+1,0);

    for(int i=0;i<n;i++){
        if(!vis[i]){
            dfs(i,adj,vis,st);
        }
    }

    vector<int> ans;
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }

    for(auto it : ans){
        cout << it << " ";
    }
    cout << endl;
}

int main(){
    int n,m; cin>>n>>m;

    vector<int> adj[n];
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;

        adj[u].push_back(v);
    }

    topologicalSortusingBFS(n,m,adj);
    topologicalSortusingDFS(n,m,adj);
}