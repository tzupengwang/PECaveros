#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int add( int a , int b , int p ){
  a += b;
  return a >= p ? a - p : a;
}
int sub( int a , int b , int p ){
  a -= b;
  return a < 0 ? a + p : a;
}
int mul( LL a , LL b , int p ){
  a *= b;
  return a >= p ? a % p : a;
}
typedef pair<int,int> Int;
const int m1 = 12721;
const int m2 = 13331;
const int p1 = 1000000007;
const int p2 = 1000000009;
Int operator+( const Int& a , const Int& b ){
  return { add( a.first , b.first , p1 ) ,
           add( a.second , b.second , p2 ) };
}
Int operator-( const Int& a , const Int& b ){
  return { sub( a.first , b.first , p1 ) ,
           sub( a.second , b.second , p2 ) };
}
Int operator*( const Int& a , const Int& b ){
  return { mul( a.first , b.first , p1 ) ,
           mul( a.second , b.second , p2 ) };
}
Int base = { m1 , m2 };
Int node = { 1 , 1 };
#define N 101010
struct Tree{
  int n;
  vector< int > v[ N ];
  void init( int _n ){
    n = _n;
    for( int i = 1 ; i <= n ; i ++ )
      v[ i ].clear();
    for( int i = 1 ; i < n ; i ++ ){
      int ui , vi;
      scanf( "%d%d" , &ui , &vi );
      v[ ui ].push_back( vi );
      v[ vi ].push_back( ui );
    }
    hash( 1 , 1 );
    hash2( 1 , 1 , { 0 , 0 } , 0 );
  }
  Int hsh[ N ] , thsh[ N ];
  int sz[ N ];
  void hash( int now , int prt ){
    sz[ now ] = 1;
    thsh[ now ] = node;
    for( int son : v[ now ] ){
      if( son == prt ) continue;
      hash( son , now );
      sz[ now ] += sz[ son ];
      thsh[ now ] = thsh[ now ] + thsh[ son ] *
        make_pair( sz[ son ] , sz[ son ] ) * base;
    }
  }
  void hash2( int now , int prt , Int tson , int tsz ){
    hsh[ now ] = thsh[ now ] + tson * make_pair( tsz , tsz ) * base;
    for( int son : v[ now ] ){
      if( son == prt ) continue;
      hash2( son , now , hsh[ now ] -
             thsh[ son ] * make_pair( sz[ son ] , sz[ son ] ) * base ,
             tsz + sz[ now ] - sz[ son ] );
    }
  }
} t[ 2 ];
int n;
void init(){
  cin >> n;
  t[ 0 ].init( n );
  t[ 1 ].init( n + 1 );
}
void solve(){
  set<Int> S;
  for( int i = 1 ; i <= t[ 0 ].n ; i ++ ){
    //S.insert( t[ 0 ].hsh[ i ] );
    S.insert( node + t[ 0 ].hsh[ i ] * make_pair( n , n ) * base );
    //cout << t[ 0 ].hsh[ i ].first << " ";
    //cout << t[ 0 ].hsh[ i ].second << endl;
  }
  for( int i = 1 ; i <= t[ 1 ].n ; i ++ ){
    if( t[ 1 ].v[ i ].size() != 1u ) continue;
    if( S.count( t[ 1 ].hsh[ i ] ) ){
      cout << i << endl;
      exit(0);
    }
  }
}
int main(){
  init();
  solve();
}
