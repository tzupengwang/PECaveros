#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL st[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
const LL inf = 1e16;
void build_st( int no , int l , int r ){
  st[ no ] = inf;
  if( l == r ) return;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
}
void modify( int no , int l , int r , int p , LL d ){
  if( l == r ){
    st[ no ] = d;
    return;
  }
  if( p <= mid ) modify( L( no ) , l , mid , p , d );
  else modify( R( no ) , mid + 1 , r , p , d );
  st[ no ] = min( st[ L( no ) ] , st[ R( no ) ] );
}
LL query( int no , int l , int r , int ql , int qr ){
  if( r < ql or l > qr ) return inf;
  if( ql <= l and r <= qr ) return st[ no ];
  return min( query( L( no ) , l , mid , ql , qr ) ,
              query( R( no ) , mid + 1 , r , ql , qr ) );
}
LL n , x[ N ] , r[ N ];
void init(){
  cin >> n;
  for( int i = 1 ; i <= n ; i ++ )
    cin >> x[ i ] >> r[ i ];
}
LL mn[N];
void solve(){
  LL curr = x[1]+r[1];
  for (int i = 2; i <= n; ++i) {
    if (curr < x[i]) {
      puts("-1");
      return;
    }
    curr = max(curr, x[i]+r[i]);
  }
  LL ans = x[n]-x[1];ans *= 3;
  mn[n] = x[n] - r[n];
  for (int i = n-1; i >= 1; --i) {
    mn[i] = min(mn[i+1], (LL)(x[i]-r[i]));
  }
  for (int i = 1; i <= n-1; ++i) {
    if (x[i] < mn[i+1]) {
      puts("-1");
      return;
    }
  }
  cout << ans << endl;
}
int main(){
  init();
  solve();
}
