#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , a , b;
vector< int > v[ 5 ];
void init(){
  scanf( "%d%d%d" , &n , &a , &b );
  for( int i = 0 ; i < 5 ; i ++ )
    v[ i ].clear();
  for( int i = 0 ; i < n ; i ++ ){
    int x; scanf( "%d" , &x );
    v[ x + 2 ].push_back( i + 1 );
  }
}
int minn , pos , bst , b2 , gd , _cs;
void find_ans(){
  int now = gd;
  vector< int > ans;
  if( now % 2 ){ // -
    int n2 = max( 0 , now - (int)v[ 1 ].size() );
    int n1 = now - n2;
    for( int i = 0 ; i < n2 ; i ++ )
      ans.push_back( v[ 0 ][ i ] );
    for( int i = 0 ; i < n1 ; i ++ )
      ans.push_back( v[ 1 ][ i ] );
    int nd = a - now;
    for( int i = 2 ; i < 5 ; i ++ ){
      int got = min( nd , (int)v[ i ].size() );
      nd -= got;
      for( int j = 0 ; j < got ; j ++ )
        ans.push_back( v[ i ][ j ] );
    }
  }else{ // >= 0
    int n2 = min( now , (int)v[ 0 ].size() );
    for( int i = 0 ; i < n2 ; i ++ )
      ans.push_back( v[ 0 ][ i ] );
    int n1 = now - n2;
    for( int i = 0 ; i < n1 ; i ++ )
      ans.push_back( v[ 1 ][ i ] );
    int nd = a - now , mst = b - now;
    int got2 = min( mst , (int)v[ 4 ].size() );
    n2 += got2;
    nd -= got2;
    for( int i = 0 ; i < got2 ; i ++ )
      ans.push_back( v[ 4 ][ i ] );
    for( int i = 3 ; i >= 2 && nd > 0 ; i -- ){
      int gg = min( nd , (int)v[ i ].size() );
      nd -= gg;
      for( int j = 0 ; j < gg ; j ++ )
        ans.push_back( v[ i ][ j ] );
    }
  }
  sort( ans.begin() , ans.end() );
  printf( "Case #%d:\n" , ++ _cs );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
void gogo( int now ){
  if( now > b ) return;
  if( now % 2 ){ // -
    if( bst >= 0 ) return;
    int n2 = max( 0 , now - (int)v[ 1 ].size() );
    int nd = a - now;
    if( nd > pos ) return;
    if( b - now > 0 && v[ 2 ].size() ){
      bst = 0; b2 = 0; gd = now;
      return;
    }
    nd -= (int)v[ 3 ].size();
    if( nd > 0 ) n2 += nd;
    if( n2 < b2 ){
      b2 = n2; gd = now;
    }
  }else{ // >= 0
    int n2 = min( now , (int)v[ 0 ].size() );
    int nd = a - now , mst = b - now;
    int got2 = min( mst , (int)v[ 4 ].size() );
    n2 += got2;
    nd -= got2;
    if( nd > (int)v[ 2 ].size() + (int)v[ 3 ].size() ) return;
    if( nd > 0 ) nd -= (int)v[ 3 ].size();
    if( nd > 0 ){
      if( bst < 0 ){
        bst = 0; b2 = 0; gd = now;
      }
      return;
    }
    if( bst <= 0 || n2 > b2 ){
      bst = 1; b2 = n2; gd = now;
    }
  }
}
void solve(){
  bst = -1; b2 = N;
  minn = (int)( v[ 0 ].size() +
               v[ 1 ].size() );
  pos = (int)( v[ 2 ].size() +
               v[ 3 ].size() +
               v[ 4 ].size() );
  for( int i = 0 ; i <= minn ; i ++ )
    gogo( i );
  find_ans();
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
