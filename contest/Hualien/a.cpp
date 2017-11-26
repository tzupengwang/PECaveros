#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
LL n , k , a[ N ];
__int128 aa;
bool ok(){
  bool okay = true;
  for( int i = 0 ; i + 1 < n ; i ++ )
    if( abs( a[ i ] - a[ i + 1 ] ) > k ){
      okay = false;
      break;
    }
  if( okay ) return true;
  okay = true;
  for( int i = 1 ; i + 1 < n ; i ++ )
    if( abs( a[ i ] - a[ i + 1 ] ) > k ){
      okay = false;
      break;
    }
  if( okay ) return true;
  okay = true;
  for( int i = 0 ; i + 2 < n ; i ++ )
    if( abs( a[ i ] - a[ i + 1 ] ) > k ){
      okay = false;
      break;
    }
  if( okay ) return true;
  for( int i = 1 ; i + 1 < n ; i ++ ){
    LL ori = a[ i ];
    LL bst = ( a[ i - 1 ] + a[ i + 1 ] ) / 2;
    a[ i ] = bst;
    bool tok = true;
    for( int j = 0 ; j + 1 < n ; j ++ )
      if( abs( a[ j ] - a[ j + 1 ] ) > k ){
        tok = false;
        break;
      }
    if( tok ) return true;
    a[ i ] = ori;
  }
  return false;
}
int main(){
  while( cin >> n and n ){
    cin >> k;
    for( int i = 0 ; i < n ; i ++ )
      cin >> a[ i ];
    puts( ok() ? "Y" : "N" );
  }
}
