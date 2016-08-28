#include <bits/stdc++.h>
using namespace std;
typedef int state;
const double eps = 1e-9;
bool equal( double x , double y ){
  return fabs( x - y ) < eps;
}
#define N 9
#define K 256
int n , m;
char c[ 2 ][ N ][ N ];
inline int enc( int xn , int xm ){
  return xn * m + xm;
}
bool dif[ N ][ N ];
inline state init_state(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( c[ 0 ][ i ][ j ] != c[ 1 ][ i ][ j ] ){
        for( int ii = 0 ; ii <= i ; ii ++ )
          for( int jj = 0 ; jj <= j ; jj ++ )
            dif[ ii ][ jj ] = false;
        dif[ i ][ j ] = true;
      }else dif[ i ][ j ] = false;
  state nst = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( dif[ i ][ j ] )
        nst |= ( 1 << enc( i , j ) );
  return nst;
}
inline state reduce_state( const state& nst ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( ( nst >> enc( i , j ) ) & 1 ){
        for( int ii = 0 ; ii <= i ; ii ++ )
          for( int jj = 0 ; jj <= j ; jj ++ )
            dif[ ii ][ jj ] = false;
        dif[ i ][ j ] = true;
      }else dif[ i ][ j ] = false;
  state nxtst = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( dif[ i ][ j ] )
        nxtst |= ( 1 << enc( i , j ) );
  return nxtst;
}
inline state next_state( const state& ns , int xn , int xm , int blk ){
  state nxt_st = ns;
  for( int i = 0 ; i <= xn ; i ++ )
    for( int j = 0 ; j <= xm ; j ++ )
      if( ( blk == 1 && ( c[ 1 ][ i ][ j ] == 'B' ) ) ||
          ( blk == 0 && ( c[ 1 ][ i ][ j ] == 'W' ) ) )
        nxt_st &= ( ~( 1 << enc( i , j ) ) );
      else
        nxt_st |= ( 1 << enc( i , j ) );
  return nxt_st;
}
bool init(){
  scanf( "%d%d" , &n , &m );
  if( n == 0 && m == 0 ) return false;
  for( int _ = 0 ; _ < 2 ; _ ++ )
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%s" , c[ _ ][ i ] );
  return true;
}
vector< state > st;
inline int which_state( const state& ts ){
  return lower_bound( st.begin() , st.end() , ts ) - st.begin();
}
inline void add_state( const vector<int>& up ){
  int nown = n , nowm = 0;
  state nst = 0;
  for( int go_up : up ){
    if( go_up ){
      if( nown > 0 && nowm > 0 )
        nst |= ( 1 << enc( nown - 1 , nowm - 1 ) );
      nown --;
    }else nowm ++;
  }
  assert( nown == 0 && nowm == m );
  nst = reduce_state( nst );
  if( nst == 0 ) return;
  st.push_back( nst );
}
void build_state(){
  st.clear();
  vector< int > up;
  for( int i = 0 ; i < m ; i ++ ) up.push_back( 0 );
  for( int i = 0 ; i < n ; i ++ ) up.push_back( 1 );
  do add_state( up );
  while( next_permutation( up.begin() , up.end() ) );
  sort( st.begin() , st.end() );
}
double dp[ K ][ K ];
int st_sz;
void gauss_elimination(){
  for( int i = 0 ; i < st_sz ; i ++ ){
    int ii = i;
    while( ii < st_sz && equal( dp[ ii ][ i ] , 0 ) ) ii ++;
    assert( ii < st_sz );
    for( int j = 0 ; j <= st_sz ; j ++ )
      swap( dp[ i ][ j ] , dp[ ii ][ j ] );
    double norm = dp[ i ][ i ];
    for( int j = 0 ; j <= st_sz ; j ++ )
      dp[ i ][ j ] /= norm;
    for( int j = 0 ; j < st_sz ; j ++ ){
      if( i == j ) continue;
      double dlt = dp[ j ][ i ] / dp[ i ][ i ];
      for( int k = 0 ; k <= st_sz ; k ++ )
        dp[ j ][ k ] -= dp[ i ][ k ] * dlt;
    }
  }
}
void find_ans(){
  for( int i = 0 ; i < st_sz ; i ++ ){
    for( int j = 0 ; j <= st_sz ; j ++ )
      dp[ i ][ j ] = 0;
    dp[ i ][ i ] = 1;
  }
  for( int _ = 0 ; _ < st_sz ; _ ++ )
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < m ; j ++ )
        for( int b = 0 ; b < 2 ; b ++ ){
          state nxt_st = reduce_state( next_state( st[ _ ] , i , j , b ) );
          dp[ _ ][ st_sz ] += (double)( i + 1 ) * ( j + 1 ) / ( n * m * 2 );
          if( nxt_st == 0 ) continue;
          int who = which_state( nxt_st );
          dp[ _ ][ who ] -= 1. / ( n * m * 2 );
        }
  gauss_elimination();
}
void solve(){
  build_state();
  st_sz = (int)st.size();
  find_ans();
  int my_state = init_state();
  double ans = my_state ? dp[ which_state( my_state ) ][ st_sz ] :
                          0;
  printf( "%.9f\n" , ans );
}
int main(){
  while( init() ) solve();
}
