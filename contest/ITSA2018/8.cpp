#include <bits/stdc++.h>
using namespace std;
const int N = 201010;

int BIT[N];
inline int lb(int x){ return x & (-x);}
int id[N];
void modify(int x, int v){
  for(int i=x; i<N; i+=lb(i))
    BIT[i]=max(BIT[i], v);
}
int query(int x){
  int ret=0;
  for(int i=x; i; i-=lb(i))
    ret=max(ret, BIT[i]);
  return ret;
}

int n, x[N], y[N], z[N], sz;
void init(){
  scanf("%d", &n);
  for(int i=0; i<n; i++)
    scanf("%d%d%d", &x[i], &y[i], &z[i]);
  vector<int> li;
  for(int i=0; i<n; i++){
    li.push_back(x[i]);
    li.push_back(y[i]);
  }
  sort(li.begin(), li.end());
  li.resize(unique(li.begin(), li.end())-li.begin());
  for(int i=0; i<n; i++){
    x[i]=lower_bound(li.begin(), li.end(), x[i])-li.begin()+1;
    y[i]=lower_bound(li.begin(), li.end(), y[i])-li.begin()+1;
  }
  sz=li.size();
}

void solve(){
  for(int i=0; i<n; i++)
    id[i]=i;
  sort(id, id+n,
    [&](int id1, int id2){
      if(x[id1] != x[id2]) return x[id1] > x[id2];
      return y[id1] < y[id2];
    });
  for(int i=0; i<N; i++) BIT[i]=0;
  vector< pair<int,int> > wt;
  int ans=0;
  for(int _=0; _<n; _++){
    int i=id[_];
    int val=query(y[i])+z[i];
    modify(y[i], val);
    ans=max(ans, val);
    if(wt.size() and wt.back().first == x[i])
      wt.back().second = max(wt.back().second, val);
    else
      wt.push_back({x[i], val});
  }
  for(size_t i=1; i<wt.size(); i++)
    wt[i].second=max(wt[i].second, wt[i-1].second);
  for(int i=0; i<n; i++)
    y[i]=sz-y[i]+1;
  for(int i=0; i<N; i++) BIT[i]=0;
  for(int _=n-1; _>=0; _--){
    int i=id[_];
    int val=query(y[i])+z[i];
    modify(y[i], val);
    ans=max(ans, val);
    while(wt.size() and wt.back().first <= x[i])
      wt.pop_back();
    if(wt.size())
      ans=max(ans, val+wt.back().second);
  }
  printf("%d\n", ans);
}
int main(){
  int t; scanf("%d", &t); while(t--){
    init();
    solve();
  }
}
