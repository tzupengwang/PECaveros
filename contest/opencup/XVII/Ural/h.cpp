#include <bits/stdc++.h>
using namespace std;
#define N 50050
int n , s[ N ] , t[ N ];
string c[ N ];
//char c[ N ][  0 ];
int len[ N ] , vv[ N ];
int m , ks[ N ] , kt[ N ];
string c2[ N ];
//char c2[ N ][ 10 ];
int len2[ N ];
void init(){
  scanf( "%d" , &n );
  int st = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int ki; scanf( "%d" , &ki );
    s[ i ] = st; t[ i ] = st + ki;
    for( int j = s[ i ] ; j < t[ i ] ; j ++ ){
      cin >> c[ j ];
      //scanf( "%s" , c[ j ] );
      //len[ j ] = strlen( c[ j ] );
      len[ j ] = c[ j ].length();
      for( int kk = 0 ; kk < len[ j ] ; kk ++ )
        vv[ j ] |= ( 1 << ( c[ j ][ kk ] - 'a' ) );
    }
    st += ki;
  }
  scanf( "%d" , &m );
  st = 0;
  for( int i = 0 ; i < m ; i ++ ){
    int ki; scanf( "%d" , &ki );
    ks[ i ] = st; kt[ i ] = st + ki;
    for( int j = ks[ i ] ; j < kt[ i ] ; j ++ ){
      cin >> c2[ j ];
      len2[ j ] = c2[ j ].length();
      //scanf( "%s" , c2[ j ] );
      //len2[ j ] = strlen( c2[ j ] );
    }
    st += ki;
  }
}
int bst[ N ] , bw[ N ];
int tag[ 1 << 26 ] , stmp;
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    bst[ i ] = -1;
  for( int i = 0 ; i < m ; i ++ ){
    for( int j = ks[ i ] ; j < kt[ i ] ; j ++ ){
      int vl = 0;
      for( int kk = 0 ; kk < len2[ j ] ; kk ++ )
        vl |= ( 1 << ( c2[ j ][ kk ] - 'a' ) );
      for( int svl = vl ; svl ; svl = ( svl - 1 ) & vl )
        tag[ svl ] = i + 1;
    }
    for( int j = 0 ; j < n ; j ++ ){
      int cc = 0;
      for( int kk = s[ j ] ; kk < t[ j ] ; kk ++ )
        if( tag[ vv[ kk ] ] == i + 1 )
          cc ++;
      if( cc > bst[ j ] )
        bst[ j ] = cc , bw[ j ] = i + 1;
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d\n" , bw[ i ] );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
