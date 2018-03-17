#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
int n;
void to( int a , int b ){
  printf( "%d to %d\n" , a , b );
}
int _arr[ 100000 ];
int* arr = _arr + 50000;
int dep , stka[ N ] , stkb[ N ] , lmx , rmx;
bool dfs( int ndep ){
  if( dep == ndep ){
    if( arr[ rmx ] or arr[ rmx - 1 ] )
      return false;
    for( int l = lmx , r = rmx - 2 ; l < r ; l ++ , r -- ){
      if( arr[ l ] != 1 )
        return false;
      if( arr[ r ] != 2 )
        return false;
    }
    for( int i = 0 ; i < ndep ; i ++ )
      to( stka[ i ] , stkb[ i ] );
    return true;
  }
  for( int i = lmx ; i + 1 <= rmx ; i ++ ){
    if( !arr[ i ] or !arr[ i + 1 ] ) continue;
    int aa = arr[ i ] , bb = arr[ i + 1 ];
    arr[ i ] = arr[ i + 1 ] = 0;
    for( int j = lmx ; j + 1 <= rmx ; j ++ ){
      if( i == j or arr[ j ] or arr[ j + 1 ] ) continue;
      arr[ j ] = aa;
      arr[ j + 1 ] = bb;
      stka[ ndep ] = i;
      stkb[ ndep ] = j;
      if( dfs( ndep + 1 ) )
        return true;
      arr[ j ] = arr[ j + 1 ] = 0;
    }
    arr[ i ] = aa;
    arr[ i + 1 ] = bb;
  }
  return false;
}
void gogo( int l , int r ){
  dep = r - l + 1;
  int lx = l * 2 - 1 , rx = r * 2;
  lmx = lx - 2; rmx = rx;
  for( int i = lmx ; i <= rmx ; i ++ )
    arr[ i ] = 0;
  for( int i = lmx + 2 ; i <= rmx ; i += 2 ){
    arr[ i ] = 2;
    arr[ i + 1 ] = 1;
  }
  assert( dfs( 0 ) );
}
void go( int l , int r ){
  int len = r - l + 1;
  int lx = l * 2 - 1 , rx = r * 2;
  if( len == 3 ){
    to( lx + 1 , lx - 2 );
    to( rx - 1 , lx + 1 );
    to( lx + 2 , lx - 4 );
    return;
  }
  if( len <= 6 ){
    gogo( l , r );
    return;
  }
  if( len == 7 ){
    to( lx + 7 , lx - 2 );
    to( lx + 4 , lx + 7 );
    to( lx + 11 , lx + 4 );
    to( lx + 2 , lx + 11 );
    to( lx + 8 , lx + 2 );
    to( lx - 1 , lx + 8 );
    to( lx + 12 , lx - 1 );
//8 to -1
//5 to 8
//12 to 5
//3 to 12
//9 to 3
//0 to 9
//13 to 0
    return;
  }
  to( rx - 2 , lx - 2 );
  to( lx + 2 , rx - 2 );
  go( l + 2 , r - 2 );
  to( lx - 1 , rx - 5 );
  to( rx - 1 , lx - 1 );
}
int main(){
  scanf( "%d" , &n );
  go( 1 , n );
}
