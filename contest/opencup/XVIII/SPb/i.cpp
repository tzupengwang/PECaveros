#include <bits/stdc++.h>
using namespace std;
#define N 514
pair<int,int> p[ N ];
#define X first
#define Y second
inline int ask( int a , int b ){
#ifdef eddy
  int ret = p[ a ].X * p[ b ].Y - p[ b ].X * p[ a ].Y;
  return ret > 0 ? 1 : 0;
#else
  printf( "? %d %d\n" , a , b );
  fflush( stdout );
  int r; scanf( "%d" , &r );
  return r;
#endif
}
inline void answer( const vector<int>& v , bool ok ){
  if( ok ) puts( "! YES" );
  else puts( "! NO" );
  if( not ok ) printf( "%d " , (int)v.size() );
  for( size_t i = 0 ; i < v.size() ; i ++ )
    printf( "%d%c" , v[ i ] , " \n"[ i + 1 == v.size() ] );
  fflush( stdout );
  exit(0);
}
int n;
void merge_sort( vector<int>& vv , int l , int r ){
  if( l >= r ) return;
  int mid = (l + r) >> 1;
  merge_sort( vv , l , mid );
  merge_sort( vv , mid + 1 , r );
  vector<int> vl , vr;
  for( int i = l ; i <= mid ; i ++ )
    vl.push_back( vv[ i ] );
  for( int i = mid + 1 ; i <= r ; i ++ )
    vr.push_back( vv[ i ] );
  int ptr = l;
  size_t lptr = 0 , rptr = 0;
  while( lptr < vl.size() and rptr < vr.size() ){
    if( ask( vl[ lptr ] , vr[ rptr ] ) ){
      vv[ ptr ++ ] = vl[ lptr ];
      lptr ++;
    }else{
      vv[ ptr ++ ] = vr[ rptr ];
      rptr ++;
    }
  }
  while( lptr < vl.size() ){
    vv[ ptr ++ ] = vl[ lptr ];
    lptr ++;
  }
  while( rptr < vr.size() ){
    vv[ ptr ++ ] = vr[ rptr ];
    rptr ++;
  }
}
int main(){
#ifdef eddy
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d%d" , &p[ i ].X , &p[ i ].Y );
#else
  scanf( "%d" , &n );
#endif
  if( n == 1 ) answer( {1} , 1 );
  if( n == 2 ){
    if( ask( 1 , 2 ) )
      answer( {1, 2} , 1 );
    else
      answer( {2, 1} , 1 );
  }
  vector<int> up , dn;
  for( int i = 2 ; i <= n ; i ++ )
    if( ask( 1 , i ) )
      up.push_back( i );
    else
      dn.push_back( i );
  merge_sort( up , 0 , (int)up.size() - 1 );
  merge_sort( dn , 0 , (int)dn.size() - 1 );
  vector<int> ans;
  for( auto i : dn )
    ans.push_back( i );
  ans.push_back( 1 );
  for( auto i : up )
    ans.push_back( i );
  answer( ans , !ask( ans.back() , ans[ 0 ] ) );
}
