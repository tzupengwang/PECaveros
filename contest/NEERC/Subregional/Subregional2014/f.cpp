#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define K 55
int BIT[ N ] , lb[ N ];
int n , s , k , u[ N ];
void build(){
  for( int i = 0 ; i < N ; i ++ )
    lb[ i ] = i & (-i);
}
void modify( int x ){
  for( int i = x ; i <= n ; i += lb[ i ] )
    BIT[ i ] ++;
}
int query( int x ){
  int sum = 0;
  for( int i = x ; i ; i -= lb[ i ] )
    sum += BIT[ i ];
  return sum;
}
void init(){
  scanf( "%d%d%d" , &n , &s , &k );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &u[ i ] );
}
int cst[ N ][ N ] , dp[ N ][ K ];
bool cmp( pair<int,int> p1 , pair<int,int> p2 ){
  if( p1.first != p2.first )
    return p1.first < p2.first;
  return p1.second > p2.second;
}
void solve(){
  vector< pair< int , int > > vv;
  for( int i = 1 ; i <= n ; i ++ )
    vv.push_back( { u[ i ] , i } );
  sort( vv.begin() , vv.end() , cmp );
  for( int l = 1 ; l <= s ; l ++ ){
    size_t ptr = 0;
    while( ptr < vv.size() && vv[ ptr ].first < l ) ptr ++;
    int tcst = 0;
    for( int i = 0 ; i <= n ; i ++ ) BIT[ i ] = 0;
    for( int r = l ; r <= s ; r ++ ){
      while( ptr < vv.size() && vv[ ptr ].first <= r ){
        tcst += query( vv[ ptr ].second - 1 );
        modify( vv[ ptr ].second );
        ptr ++;
      }
      cst[ l ][ r ] = tcst;
    }
  }
  for( int i = 1 ; i <= s ; i ++ )
    dp[ i ][ 1 ] = cst[ 1 ][ i ];
  int ans = dp[ s ][ 1 ];
  for( int i = 2 ; i <= k ; i ++ ){
    for( int j = i ; j <= s ; j ++ ){
      dp[ j ][ i ] = 1000000000;
      for( int p = j - 1 ; p >= i - 1 ; p -- )
        dp[ j ][ i ] = min( dp[ j ][ i ] , dp[ p ][ i - 1 ] +
                                           cst[ p + 1 ][ j ] );
    }
    ans = min( ans , dp[ s ][ i ] );
  }
  printf( "%d\n" , ans );
}
int main(){
  freopen( "flight.in" , "r" , stdin );
  freopen( "flight.out" , "w" , stdout );
  build();
  init();
  solve();
}
