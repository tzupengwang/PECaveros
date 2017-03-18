#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define M 514
vector<int> v;
int p[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  p[ f( x ) ] = f( y );
}
int b , m , nxt[ M ][ M ];
bool same[ M ][ M ];
bool inc[ M ][ M ];
bool gt[ M ][ M ];
bool ac[ M ];
bool Same( int ni , int nj ){
  if( ni > nj ) swap( ni , nj );
  if( ac[ ni ] != ac[ nj ] ) return false;
  if( gt[ ni ][ nj ] ) return same[ ni ][ nj ];
  if( ni == nj or inc[ ni ][ nj ] ) return true;
  inc[ ni ][ nj ] = true;
  for( int i = 0 ; i < b ; i ++ ){
    if( not Same( nxt[ ni ][ i ] , nxt[ nj ][ i ] ) ){
      inc[ ni ][ nj ] = false;
      gt[ ni ][ nj ] = true;
      return same[ ni ][ nj ] = false;
    }
  }
  inc[ ni ][ nj ] = false;
  gt[ ni ][ nj ] = true;
  return same[ ni ][ nj ] = true;
}
void solve(){
  v.clear();
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      same[ i ][ j ] = inc[ i ][ j ] = gt[ i ][ j ] = false;
  for( int i = 0 ; i < m ; i ++ ){
    p[ i ] = i;
    v.push_back( i );
  }
  for( int i = 0 ; i < m ; i ++ ){
    ac[ i ] = ( i == 0 );
    for( int j = 0 ; j < b ; j ++ )
      nxt[ i ][ j ] = ( i * b + j ) % m;
  }
  for( int i = 0 ; i < m ; i ++ )
    for( int j = i + 1 ; j < m ; j ++ )
      if( Same( i , j ) )
        uni( j , i );
  int cc = 0;
  for( int i = 0 ; i < m ; i ++ )
    if( i == f( i ) )
      cc ++;
  int pred = m / __gcd( b , m );

  //assert( pred == cc )
  printf( "%d %d\n" , cc , pred );
}
int main(){
  scanf( "%d%d" , &b , &m );
  //for( b = 2 ; b <= 16 ; b ++ )
    //for( m = 2 ; m <= 2000 ; m ++ )
      solve();
}
