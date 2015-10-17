#include <bits/stdc++.h>
using namespace std;
#define N 110
int __ = 1 , n , p , len , ans;
char c[ N ];
vector<int> num, op;
// 0 + 1 - 2 *
void init(){
  num.clear();
  op.clear();
  char ctmp;
  while( scanf( "%[^+-*=]%c" , c , &ctmp ) ){
    num.push_back( atoi( c ) );
    if( ctmp == '+' ) op.push_back( 0 );
    if( ctmp == '-' ) op.push_back( 1 );
    if( ctmp == '*' ) op.push_back( 2 );
    if( ctmp == '=' ){
      scanf( "%d" , &ans );
      break;
    }
  }
  n = (int)num.size();
}
int cal( int _a , int _b , int _op ){
  if( _op == 0 ) return ( _a + _b ) % p;
  if( _op == 1 ) return ( _a - _b + p ) % p;
  if( _op == 2 ) return ( _a * _b ) % p;
  return 0;
}
vector<int> v[ 16 ][ 16 ];
vector<int> vf[ 16 ][ 16 ];
vector<int> vfl[ 16 ][ 16 ];
vector<int> vfr[ 16 ][ 16 ];
int sidx[ 16 ][ 16 ][ 2000 ];
bool dp[ 2000 ];
int from[ 2000 ];
int fl[ 2000 ];
int fr[ 2000 ];
void print( int l , int r , int vl ){
  if( l == r ){
    printf( "%d" , num[ l ] );
    return;
  }
  int nidx = sidx[ l ][ r ][ vl ];
  int mid = vf[ l ][ r ][ nidx ];
  int lvl = vfl[ l ][ r ][ nidx ];
  int rvl = vfr[ l ][ r ][ nidx ];
  if( l < mid ) printf( "(" );
  print( l , mid , lvl );
  if( l < mid ) printf( ")" );
  if( op[ mid ] == 0 ) putchar( '+' );
  if( op[ mid ] == 1 ) putchar( '-' );
  if( op[ mid ] == 2 ) putchar( '*' );
  if( mid + 1 < r ) printf( "(" );
  print( mid + 1 , r , rvl );
  if( mid + 1 < r ) printf( ")" );
}
void find_ans(){
  if( !dp[ ans % p ] ){
    puts( "0" );
    return;
  }
  print( 0 , n - 1 , ans % p );
  printf( "=%d\n" , ans );
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i ; j < n ; j ++ ){
      v[ i ][ j ].clear();
      vf[ i ][ j ].clear();
      vfl[ i ][ j ].clear();
      vfr[ i ][ j ].clear();
    }
  for( int i = 0 ; i < n ; i ++ )
    v[ i ][ i ].push_back( num[ i ] % p );
  for( int i = 2 ; i <= n ; i ++ )
    for( int j = 0 ; j <= n - i ; j ++ ){
      int l = j , r = j + i - 1;
      for( int k = 0 ; k < 2000 ; k ++ )
        dp[ k ] = false;
      for( int k = l ; k < r ; k ++ ){
        for( int i1 = 0 ; i1 < (int)v[ l ][ k ].size() ; i1 ++ )
          for( int i2 = 0 ; i2 < (int)v[ k + 1 ][ r ].size() ; i2 ++ ){
            int vl = cal( v[ l ][ k ][ i1 ] , v[ k + 1 ][ r ][ i2 ] , op[ k ] );
            dp[ vl ] = true;
            from[ vl ] = k;
            fl[ vl ] = v[ l ][ k ][ i1 ];
            fr[ vl ] = v[ k + 1 ][ r ][ i2 ];
          }
      }
      for( int k = 0 ; k < 2000 ; k ++ ) if( dp[ k ] ){
        sidx[ l ][ r ][ k ] = (int)v[ l ][ r ].size();
        v[ l ][ r ].push_back( k );
        vf[ l ][ r ].push_back( from[ k ] );
        vfl[ l ][ r ].push_back( fl[ k ] );
        vfr[ l ][ r ].push_back( fr[ k ] );
      }
    }
  find_ans();
}
int main(){
  scanf( "%d" , &__ );
  scanf( "%d" , &p );
  while( __ -- ){
    init();
    solve();
  }
}
