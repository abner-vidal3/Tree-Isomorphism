#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define vvi vector<vector<int>>
using ll = long long;
const int mxn = 1e5;
int n, subtr[2][mxn], id;
vector<int> adj[2][mxn], cen[2];
map<vector<int>,int> mp;
void reset(){
    cen[0].clear(); cen[1].clear();
    id = 0;
    mp.clear();
    for (int i = 0; i < n; i++){
        adj[0][i].clear();
        adj[1][i].clear();
    }
}
void dfs1(int t,int u, int p){
    subtr[t][u] = 1;
    bool fg = 1;
    for (int to : adj[t][u]){
        if (to == p) continue;
        dfs1(t,to,u);
        subtr[t][u] += subtr[t][to];
        if (2*subtr[t][to] > n) fg = 0;
    }
    if (2*n-2*subtr[t][u] > n) fg = 0;
    if (fg) cen[t].push_back(u);
}
int dfs2(int t, int u, int p){
    vector<int> eq;
    for (int to : adj[t][u])
        if (to != p)
            eq.push_back(dfs2(t,to,u));
    sort(eq.begin(),eq.end());
    if (mp.find(eq) == mp.end())
        mp[eq] = id++;
    return mp[eq];
}
void solve(){
    cin >> n;
    reset();
    for (int t = 0; t < 2; t++){
        for (int i = 1; i < n; i++){
            int a,b;
            cin >> a >> b, a--, b--;
            adj[t][a].push_back(b);
            adj[t][b].push_back(a);
        }
        dfs1(t,0,-1);
    }
    for (int c1 : cen[0])
        for (int c2 : cen[1])
            if (dfs2(0,c1,-1) == dfs2(1,c2,-1)){
                cout << "YES" << endl;
                return;
            }
    cout << "NO" << endl;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}