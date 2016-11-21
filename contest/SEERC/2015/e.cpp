#include <bits/stdc++.h>
using namespace std;
#define N 20202
#define K 17
int n , m , fee , k , o , at[ K ];
vector< pair<int,int> > v[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ ){
    int d , tu , tv , c;
    scanf( "%d%d%d%d" , &d , &tu , &tv , &c );
    v[ tu ].push_back( { tv , c } );
    if( d == 2 )
      v[ tv ].push_back( { tu , c } );
  }
  scanf( "%d" , &fee );
  scanf( "%d" , &o );
  scanf( "%d" , &k );
  for( int i = 0 ; i < k ; i ++ )
    scanf( "%d" , &at[ i ] );
  at[ k ] = o;
}
int d[ K ][ N ];
int got[ N ] , stmp;
void sp( int id , int st ){
  priority_queue< pair<int,int> ,
                  vector< pair<int,int> > ,
                  greater< pair<int,int> > > heap;
  ++ stmp;
  heap.push( { 0 , st } );
  while( heap.size() ){
    auto tp = heap.top(); heap.pop();
    int dd = tp.first;
    int who = tp.second;
    if( got[ who ] == stmp ) continue;
    got[ who ] = stmp;
    d[ id ][ who ] = dd;
    for( auto nxt : v[ who ] ){
      if( got[ nxt.first ] == stmp ) continue;
      heap.push( { dd + nxt.second , nxt.first } );
    }
  }
}
#define INF 10000000000000000ll
long long cst[ 1 << K ] , dp[ 1 << K ];
long long tdp[ 1 << K ][ K ];
void solve(){
  for( int i = 0 ; i <= k ; i ++ )
    sp( i , at[ i ] );
  for( int i = 0 ; i < ( 1 << k ) ; i ++ ){
    dp[ i ] = cst[ i ] = INF;
    for( int j = 0 ; j < k ; j ++ )
      tdp[ i ][ j ] = INF;
  }
  dp[ 0 ] = cst[ 0 ] = 0;
  tdp[ 0 ][ 0 ] = 0;
  for( int i = 0 ; i < ( 1 << k ) ; i ++ ){
    if( __builtin_popcount( i ) > 4 ) continue;
    for( int j = 0 ; j < k ; j ++ ){
      if( tdp[ i ][ j ] >= INF ) continue;
      cst[ i ] = min( cst[ i ] , tdp[ i ][ j ] + fee );
      int other = ( ( 1 << k ) - 1 ) ^ i;
      while( other ){
        int lb = other & (-other); other -= lb;
        int who = __lg( lb );
        int nxtdp = tdp[ i ][ j ];
        if( i == 0 )
          nxtdp += d[ k ][ at[ who ] ];
        else
          nxtdp += d[ j ][ at[ who ] ];
        if( nxtdp < tdp[ i ^ lb ][ who ] )
          tdp[ i ^ lb ][ who ] = nxtdp;
      }
    }
  }
  for( int msk = 1 ; msk < ( 1 << k ) ; msk ++ )
    for( int submsk = msk ; submsk ; submsk = ( submsk - 1 ) & msk )
      dp[ msk ] = min( dp[ msk ] , dp[ msk ^ submsk ] + cst[ submsk ] );
  printf( "%lld\n" , dp[ ( 1 << k ) - 1 ] );
}
int main(){
  init();
  solve();
}
