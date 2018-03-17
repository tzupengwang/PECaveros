#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define MV 111
#define FZ(X) memset(X, 0, sizeof(X))
struct MaxClique{
  int V , ans , dp[ MV ];
  int el[ MV ][ MV / 30 + 1 ];
  int s[ MV ][ MV / 30 + 1 ];
  vector<int> sol;
  void init( int v ){
    V = v; ans = 0;
    FZ(el);
    FZ(dp);
  }
  // 0 base
  void addEdge(int u, int v){
    if(u > v) swap(u, v);
    if(u == v) return;
    el[u][v/32] |= (1<<(v%32));
  }
  bool dfs(int v, int k){
    int c = 0, d = 0;
    for(int i=0; i<(V+31)/32; i++) {
      s[k][i] = el[v][i];
      if(k != 1) s[k][i] &= s[k-1][i];
      c += __builtin_popcount(s[k][i]);
    }
    if(c == 0){
      if(k > ans){
        ans = k;
        sol.clear();
        sol.push_back(v);
        return 1;
      }
      return 0;
    }
    for(int i=0; i<(V+31)/32; i++) {
      for(int a = s[k][i]; a ; d++) {
        if(k + (c-d) <= ans) return 0;
        int lb = a&(-a), lg = 0;
        a ^= lb;
        while(lb!=1){
          lb = (unsigned int)(lb) >> 1;
          lg ++;
        }
        int u = i*32 + lg;
        if(k + dp[u] <= ans) return 0;
        if(dfs(u, k+1)) {
          sol.push_back(v);
          return 1;
        }
      }
    }
    return 0;
  }
  int solve(){
    for(int i=V-1; i>=0; i--){
      dfs(i, 1);
      dp[i] = ans;
    }
    return ans;
  }
} solver;
#define N 111
LL n , d , x[ N ] , y[ N ];
LL sqr( LL _ ){ return _ * _; }
inline LL dist( int id1 , int id2 ){
  return sqr( x[id1] - x[id2] ) +
         sqr( y[id1] - y[id2] );
}
int main(){
  cin >> n >> d;
  for( int i = 0 ; i < n ; i ++ )
    cin >> x[ i ] >> y[ i ];
  d *= d;
  solver.init( n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      if( dist( i , j ) <= d )
        solver.addEdge( i , j );
  int ret = solver.solve();
  printf( "%d\n" , ret );
  sort( solver.sol.begin() , solver.sol.end() );
  for( int i = 0 ; i < ret ; i ++ )
    printf( "%d%c" , solver.sol[ i ] + 1 , " \n"[ i + 1 == ret ] );
}
