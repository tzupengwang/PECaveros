#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> frac;
#define P first
#define Q second
#define N 99
int n;
frac tar;
inline frac operator-( const frac& lhs , const frac& rhs ){
  frac tmp( lhs.P * rhs.Q - lhs.Q * rhs.P , lhs.Q * rhs.Q );
  LL xx = __gcd( abs( tmp.P ) , abs( tmp.Q ) );
  tmp.P /= xx; tmp.Q /= xx;
  if( tmp.Q < 0 ) tmp.P = -tmp.P , tmp.Q = -tmp.Q;
  return tmp;
}
inline frac operator+( const frac& lhs , const frac& rhs ){
  frac tmp( lhs.P * rhs.Q + lhs.Q * rhs.P , lhs.Q * rhs.Q );
  LL xx = __gcd( abs( tmp.P ) , abs( tmp.Q ) );
  tmp.P /= xx; tmp.Q /= xx;
  if( tmp.Q < 0 ) tmp.P = -tmp.P , tmp.Q = -tmp.Q;
  return tmp;
}
void scan( frac& x ){
  scanf( "%lld%lld" , &x.P , &x.Q );
}
frac p[ N ];
LL pp[ N ];
void init(){
  scanf( "%d" , &n );
  scan( tar );
  for( int i = 0 ; i < n ; i ++ ){
    scan( p[ i ] );
    pp[ i ] = p[ i ].P * tar.Q - p[ i ].Q * tar.P;
    continue;
    //frac tp = p[ i ] - tar;
    //p[ i ] = frac( tp.P * p[ i ].Q , tmp.Q );
    //LL gg = __gcd( abs( p[ i ].P ) , abs( p[ i ].Q ) );
    //p[ i ].P /= gg; p[ i ].Q /= gg;
  }
}
void solve(){
  if( n < 20 ){
    int ans = 0;
    for( int i = 1 ; i < ( 1 << n ) ; i ++ ){
      LL tmp = 0;
      for( int j = 0 ; j < n ; j ++ )
        if( ( i >> j ) & 1 )
          tmp = tmp + pp[ j ];
      if( tmp == 0 )
        ans ++;
    }
    printf( "%d\n" , ans );
    exit( 0 );
  }
  LL ans = 0;
  map<LL,int> M;
  int hf = n / 2;
  for( int i = 1 ; i < ( 1 << hf ) ; i ++ ){
    LL tmp = 0;
    for( int j = 0 ; j < hf ; j ++ )
      if( ( i >> j ) & 1 )
        tmp = tmp + pp[ j ];
    if( tmp == 0 )
      ans ++;
    M[ tmp ] ++;
  }
  int nhf = n - hf;
  for( int i = 1 ; i < ( 1 << nhf ) ; i ++ ){
    LL tmp = 0;
    for( int j = 0 ; j < nhf ; j ++ )
      if( ( i >> j ) & 1 )
        tmp = tmp + pp[ hf + j ];
    if( tmp == 0 )
      ans ++;
    auto it = M.find( -tmp );
    if( it != M.end() )
      ans += it->second;
  }
  printf( "%lld\n" , ans );
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  init();
  solve();
}
