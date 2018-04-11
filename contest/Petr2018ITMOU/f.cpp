#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define K 256
int mod;
struct Mat{
  int n , v[ K ][ K ];
  Mat( int _n = 0 ){
    n = _n;
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        v[ i ][ j ] = 0;
  }
  Mat operator*( const Mat& he ) const{
    Mat ret( n );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        for( int k = 0 ; k < n ; k ++ )
          ret.a[ i ][ j ] = add( ret.a[ i ][ j ] , 
              mul( a[ i ][ k ] , he.a[ k ][ j ] ) );
    return ret;
  }
  Mat operator^( LL tk ) const{
    Mat I( n ) , A( n );
    for( int i = 0 ; i < n ; i ++ ){
      for( int j = 0 ; j < n ; j ++ )
        A.a[ i ][ j ] = a[ i ][ j ];
      I.a[ i ][ i ] = 1;
    }
    while( tk ){
      if( tk & 1LL ) I = I * A;
      A = A * A; tk >>= 1;
    }
    return I;
  }
};
int n , m , id[ 1 << 11 ] , nid , cand[ 1 << 11 ];
void go( int now , int pre , int msk ){
  if( now == n ){
    cand[ nid ] = msk;
    id[ msk ] = nid ++;
    return;
  }
  go( now + 1 , 0 , msk );
  if( pre != 1 )
    go( now + 1 , 1 , msk | (1 << pre) );
}
Mat A;
int main(){
  scanf( "%d%d%d" , &n , &m , &mod );
  go( 0 , 0 , 0 );
  cerr << "# of statr = " << nid << endl;
  A = Mat( nid );
  for( int i = 0 ; i < nid ; i ++ )
    for( int j = 0 ; j < nid ; j ++ )
      if( good(  )
}
