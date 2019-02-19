#include "timus1752.hpp"
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <queue>

using namespace std;

const int inf = (int)1e9;
const int N = 22000;

int n, q, ld;
vector<int> g[N], g1[N], g2[N];
int used[20100], D1[40100],D2[40100], d[N];
int lvl1[N],lvl2[N];
map<pair<int, int> , int > ans;
vector<int> zp[22000];
vector<pair<int, int> > pro;

int bfs(int A){
    queue<int> qr;
    for(int i = 1; i <= 20010; ++i) used[i] = 0, d[i] = inf;
    used[A] = 1, d[A] = 0;
    qr.push(A);
    int res = -1, maxi = -inf;
    while(!qr.empty()){
        int v = qr.front();
        qr.pop();
        for(int i = 0; i < (int)g[v].size(); ++i){
            int to = g[v][i];
            if(!used[to]){
                if(d[to] > d[v] + 1){
                    d[to] = d[v] + 1;
                }
                if(maxi < d[to]){
                    maxi = d[to];
                    res = to;
                }
                used[to] = 1;
                qr.push(to);
            }
        }
    }
    return res;
}
void solve1(int v, int p = 0, int l = 1){
    D1[l] = v;
    lvl1[v] = l;
    for(int j = 0; j < (int)zp[v].size(); ++j){
        int d = zp[v][j];
        if(d >= l) continue;
        ans[make_pair(v, d)] = D1[l - d];
    }
    for(int i = 0; i < (int)g[v].size(); ++i){
        int to = g[v][i];
        if(to == p) continue;
        solve1(to, v, l + 1);
    }
}

void solve2(int v, int p = 0, int l = 1){
    D2[l] = v;
    lvl2[v] = l;
    for(int j = 0; j < (int)zp[v].size(); ++j){
        int d = zp[v][j];
        if(d >= l) continue;
        ans[make_pair(v, d)] = D2[l - d];
    }
    for(int i = 0; i < (int)g[v].size(); ++i){
        int to = g[v][i];
        if(to == p) continue;
        solve2(to, v, l + 1);
    }
}

int main(){
    #ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    #endif
    cin >> n >> q;
    for(int i = 0, a, b; i < n - 1; ++i){
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int P = bfs(1);
    int Q = bfs(P);
    // P to Q  = diametr
    while(q--){
        int V, d;
        cin >> V >> d;
        zp[V].push_back(d);
        pro.push_back(make_pair(V,d));
    }
    solve1(P);
    solve2(Q);
    for(int i = 0; i < (int)pro.size(); ++i){
        int v = pro[i].first, distance = pro[i].second;
        if(distance == 0)
            cout << v << "\n";
        else
            cout << ans[make_pair(v, distance)] << "\n";
    }
    return 0;
}
