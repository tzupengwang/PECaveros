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
vector< int > expr[ N ];
LL dp[ N ];
void solve(){
  build_st( 1 , 1 , n );
  modify( 1 , 1 , n , 1 , dp[ 1 ] - 3 * x[ 1 ] );
  int to = upper_bound( x + 1 , x + n + 1 , x[ 1 ] + r[ 1 ] ) - x;
  expr[ to ].push_back( 1 );
  for( int i = 2 ; i <= n ; i ++ ){
    for( auto j : expr[ i ] )
      modify( 1 , 1 , n , j , inf );
    int til = lower_bound( x + 1 , x + n + 1 , x[ i ] - r[ i ] ) - x;
    //printf( "qq = %d %d\n" , til , i );
    dp[ i ] = min( inf , query( 1 , 1 , n , til , i ) + 3 * x[ i ] );
    to = upper_bound( x + 1 , x + n + 1 , x[ i ] + r[ i ] ) - x;
    modify( 1 , 1 , n , i , dp[ i ] - 3 * x[ i ] );
    expr[ to ].push_back( i );
    //cout << i << " " << dp[ i ] << endl;
  }
  cout << ( dp[ n ] >= inf / 10 ? -1 : dp[ n ] ) << endl;
}
int main(){
  init();
  solve();
}
