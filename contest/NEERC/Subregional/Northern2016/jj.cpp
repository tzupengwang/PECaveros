#include <bits/stdc++.h>
using namespace std;
vector< double > Max( const vector<double> v1 , const vector<double> v2 ){
  vector< double > vv( 256 );
  for( int i = 0 ; i < 256 ; i ++ )
    vv[ i ] = 0;
  for( int i = 0 ; i < 256 ; i ++ )
    for( int j = 0 ; j < 256 ; j ++ )
      vv[ max( i , j ) ] += v1[ i ] * v2[ j ];
  return vv;
}
vector< double > Div( const vector<double> v1 , const vector<double> v2 ){
  vector< double > vv( 256 );
  for( int i = 0 ; i < 256 ; i ++ )
    vv[ i ] = 0;
  for( int i = 0 ; i < 256 ; i ++ )
    for( int j = 0 ; j < 256 ; j ++ )
      if( j )
        vv[ i / j ] += v1[ i ] * v2[ j ];
  return vv;
}
int main(){
  vector< double > uni( 256 );
  for( int i = 0 ; i < 256 ; i ++ )
    uni[ i ] = 1. / 256.;
  vector< double > mx = Max( uni , uni );
  vector< double > mx2 = Max( mx , mx );
  vector< double > mx4 = Max( mx2 , mx2 );
  vector< double > mx8 = Max( mx4 , mx4 );
  vector< double > mx16 = Max( mx8 , mx8 );
  vector< double > mx32 = Max( mx16 , mx16 );
  vector< double > mx64 = Max( mx32 , mx32 );
  vector< double > tmx = mx;
  for( int i = 0 ; i < 10 ; i ++ )
    tmx = Max( tmx , tmx );
  vector< double > ret = Div( tmx , mx8 );
  for( int i = 0 ; i <= 5 ; i ++ )
    printf( "%d %.12f\n" , i , ret[ i ] );
}
