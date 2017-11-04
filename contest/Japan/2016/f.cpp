#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
map<string,int> name2id;
int id;
inline int iid( const string& ss ){
  auto it = name2id.find( ss );
  if( it != name2id.end() ) return it->second;
  return name2id[ ss ] = id ++;
}
inline int getid(){
  string ss;
  cin >> ss;
  return iid( ss );
}
#define N 1021
#define M 101010
int p , q , d , x[ M ] , y[ M ] , s[ N ] , t[ N ] , mcnt;
vector< int > who[ N ][ N ];
void init(){
  p = getid();
  q = getid();
  cin >> d;
  for( int i = 0 ; i < d ; i ++ ){
    s[ i ] = mcnt;
    int mi; cin >> mi; while( mi -- ){
      x[ mcnt ] = getid();
      y[ mcnt ] = getid();
      who[ x[ mcnt ] ][ y[ mcnt ] ].push_back( i );
      mcnt ++;
    }
    t[ i ] = mcnt;
  }
}
bool in[ N ][ N ] , got[ N ];
int wt[ N ] , wtsz;
inline void st( int p1 , int p2 ){
  in[ p1 ][ p2 ] = true;
  for( auto i : who[ p1 ][ p2 ] ){
    if( got[ i ] ) continue;
    got[ i ] = true;
    wt[ wtsz ++ ] = i;
  }
}
inline void add( int p1 , int p2 ){
  if( in[ p1 ][ p2 ] ) return;
  st( p1 , p2 );
  for( int i = 0 ; i < id ; i ++ )
    if( in[ i ][ p1 ] )
      add( i , p2 );
  for( int i = 0 ; i < id ; i ++ )
    if( in[ p2 ][ i ] )
      add( p1 , i );
  //for( int i = 0 ; i < id ; i ++ )
    //for( int j = 0 ; j < id ; j ++ )
      //if( in[ i ][ p1 ] and in[ p2 ][ j ] )
        //st( i , j );
}
void solve(){
  add( p , q );
  for( int i = 0 ; i < wtsz ; i ++ ){
    int now = wt[ i ];
    for( int j = s[ now ] ; j < t[ now ] ; j ++ )
      add( x[ j ] , y[ j ] );
  }
  bool ok = true;
  for( int i = 0 ; i < id ; i ++ )
    for( int j = i + 1 ; j < id ; j ++ )
      if( in[ i ][ j ] and in[ j ][ i ] )
        ok = false;
  puts( ok ? "Yes" : "No" );
}
int main(){
  init();
  solve();
}
