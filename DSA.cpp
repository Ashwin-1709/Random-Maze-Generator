#include "bits/stdc++.h"
#include <time.h>
#include <stdlib.h>
using namespace std;
struct DSU
{
  vector<int> parent,sze;
  void build(int n) {
    parent.resize(n,0) , sze.resize(n,-1);
    for(int k = 0 ; k < n ; k++) parent[k] = k , sze[k] = 1;
  }
  int find(int v) {
    if(parent[v] == v) return v;
    else return parent[v] = find(parent[v]);
  }
  void unite(int a , int b) {
    a = find(a) , b = find(b);
    if(a != b) {
      if(sze[a] < sze[b]) swap(a,b);
      parent[b] = a , sze[a] += sze[b];
    }
  }
} dsu;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    srand(time(0));
    auto AssignWeight = [&]()->int {
        return rand() % 150;
    };
    set<array<int,3>>edges,mst;
    int n; cin >> n;
    for(int i = 1 ; i <= n ; i++) {
        int f = (i-1)*n;
        for(int j = f + 1 ; j <= f + n ; j++) {
            if(j < f + n) {
                int getWeight = AssignWeight();
                edges.insert({getWeight,j,j+1});
                edges.insert({getWeight,j+1,j});
            }
            if(j + 10 <= n*n) {
                int getWeight = AssignWeight();
                edges.insert({getWeight,j,j+10});
                edges.insert({getWeight,j+10,j});
            }
        }
    }
    dsu.build(n*n + 1);
    for(auto [w,u,v] : edges) {
        if(dsu.find(u) != dsu.find(v)) {
            dsu.unite(u,v);
            mst.insert({w,u,v});
        }
    }
    for(auto x : mst) edges.erase(x);
    
}