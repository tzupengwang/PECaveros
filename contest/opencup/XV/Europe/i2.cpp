#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
#define M 101010
struct DJS{
  int p[ N ] , sz[ N ] , size;
  void init( int n ){
    for( int i = 0 ; i <= n ; i ++ ){
      p[ i ] = i;
      sz[ i ] = 1;
    }
    size = n;
  }
  int f( int x ){
    return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
  }
  void uni( int x , int y ){
    x = f( x );
    y = f( y );
    if( x == y ) return;
    if( sz[ x ] > sz[ y ] ) swap( x , y );
    p[ x ] = y;
    sz[ y ] = max( sz[ x ] + 1 , sz[ y ] );
    size --;
  }
} djs;
int n , m , x[ M ] , y[ M ] , w[ M ] , ord[ M ];
vector<int> vv;
bool cmp( int id1 , int id2 ){
  return w[ id1 ] < w[ id2 ];
}
vector<int> bst[ M ];
int st[ M ] , sm , vsz;
void init(){
  scanf( "%d%d" , &n , &m );
  vv.clear();
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d%d" , &x[ i ] , &y[ i ] , &w[ i ] );
    ord[ i ] = i;
    vv.push_back( w[ i ] );
  }
  sort( ord , ord + m , cmp );
  sort( vv.begin() , vv.end() );
  vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
  vsz = vv.size();
  int ptr = 0;
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    while( ptr < m and w[ ord[ ptr ] ] < vv[ i ] ) ptr ++;
    st[ i ] = ptr;
  }
  st[ vsz ] = m;
  sm = 1;
  while( sm * sm <= m ) sm ++;
  for( int i = 0 ; i * sm < m ; i ++ ){
    djs.init( n );
    for( int j = i * sm ; j < m ; j ++ ){
      int who = ord[ j ];
      if( djs.f( x[ who ] ) == djs.f( y[ who ] ) )
        continue;
      djs.uni( x[ who ] , y[ who ] );
      bst[ i ].push_back( j );
      if( djs.size == 1 ) break;
    }
  }
}
int ans;
void solve(){
  ans = 0;
  int q; scanf( "%d" , &q ); while( q -- ){
    int li , ri; scanf( "%d%d" , &li , &ri );
    li -= ans; ri -= ans;
    ri ++;
    li = lower_bound( vv.begin() , vv.end() , li ) - vv.begin();
    ri = lower_bound( vv.begin() , vv.end() , ri ) - vv.begin();
    li = st[ li ];
    ri = st[ ri ];
    djs.init( n );
    ans = 0;
    while( li < ri and li % sm ){
      int who = ord[ li ++ ];
      if( djs.f( x[ who ] ) != djs.f( y[ who ] ) ){
        ans += w[ who ];
        djs.uni( x[ who ] , y[ who ] );
      }
      if( djs.size == 1 ) break;
    }
    if( li < ri and djs.size > 1 ){
      for( int _ : bst[ li / sm ] ){
        if( _ >= ri ) break;
        int who = ord[ _ ];
        if( djs.f( x[ who ] ) != djs.f( y[ who ] ) ){
          ans += w[ who ];
          djs.uni( x[ who ] , y[ who ] );
          if( djs.size == 1 ) break;
        }
      }
    }
    printf( "%d\n" , ans );
  }
  for( int i = 0 ; i * sm < m ; i ++ )
    bst[ i ].clear();
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
