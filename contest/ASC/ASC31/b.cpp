#include <bits/stdc++.h>
using namespace std;
#define N 555
int n , m , h , r[ N ] , c[ N ] , w[ N ];
bool wall[ N ][ N ];
char ans[ N ][ N ];
void imp(){
  puts( "inconsistent" );
  exit(0);
}
void init(){
  cin >> n >> m >> h;
  for( int i = 0 ; i < n ; i ++ )
    cin >> r[ i ];
  for( int i = 0 ; i < m ; i ++ )
    cin >> w[ i ];
}
int dlt[ N ] , pre[ N ];
void draw(){
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < m ; j ++ )
      ans[ i ][ j ] = '*';
    ans[ i ][ m ] = '\0';
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( wall[ i ][ j ] ){
        for( int k = 0 ; k < h ; k ++ )
          ans[ i + k ][ j ] = '|';
        ans[ i         ][ j ] = '+';
        ans[ i + h - 1 ][ j ] = '+';
      }
}
int rr[ N ] , cc[ N ];
bool check(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      if( ans[ i ][ j ] == '*' )
        rr[ i ] ++;
      if( ans[ i ][ j ] == '|' )
        cc[ j ] ++;
    }
  for( int i = 0 ; i < n ; i ++ )
    if( r[ i ] != rr[ i ] )
      return false;
  for( int i = 0 ; i < m ; i ++ )
    if( w[ i ] )
      return false;
  return true;
}
void solve(){
  for( int i = 0 ; i < m ; i ++ )
    pre[ i ] = -1;
  int tot = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int nd = m - r[ i ];
    tot += dlt[ i ];
    if( tot > nd and i + h - 1 >= n ) imp();
    vector< pair<int,int> > cand;
    for( int j = 0 ; j < m ; j ++ )
      if( pre[ j ] < i and w[ j ] )
        cand.push_back( { w[ j ] , j } );
    sort( cand.begin() , cand.end() );
    reverse( cand.begin() , cand.end() );
    int mr = nd - tot;
    for( auto jj : cand ){
      int j = jj.second;
      if( mr == 0 ) break;
      w[ j ] --;
      mr --;
      wall[ i ][ j ] = true;
      tot ++;
      dlt[ i + h ] --;
      pre[ j ] = i + h - 1;
    }
    if( mr ) imp();
  }
  draw();
  if( not check() ) imp();
  for( int i = 0 ; i < n ; i ++ )
    puts( ans[ i ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "chip.in" , "r" , stdin );
  freopen( "chip.out" , "w" , stdout );
#endif
  init();
  solve();
}
