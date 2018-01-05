#include <bits/stdc++.h>
using namespace std;
#define double long double
double a[ 3 ][ 3 ];
double g[ 3 ][ 3 ];
const double eps = 1e-7;
vector< pair<int,int> > gauss(){
  vector< pair<int,int> > ret;
  for( int i = 0 ; i < 3 ; i ++ ){
    for( int j = 0 ; j < 3 ; j ++ )
      g[ i ][ j ] = a[ i ][ j ];
    g[ i ][ i ] -= 1.;
  }
  int nxt = 0;
  for( int p = 0 ; p < 3 ; p ++ ){
    int who = -1;
    for( int i = nxt ; i < 3 ; i ++ )
      if( fabs( g[ i ][ p ] ) > eps ){
        who = i;
        break;
      }
    if( who == -1 ) continue;
    for( int i = 0 ; i < 3 ; i ++ )
      swap( g[ nxt ][ i ] , g[ who ][ i ] );
    ret.push_back( { nxt , p } );
    double dv = g[ nxt ][ p ];
    for( int i = 0 ; i < 3 ; i ++ )
      g[ nxt ][ i ] /= dv;
    for( int i = 0 ; i < 3 ; i ++ ){
      if( i == nxt ) continue;
      double bns = g[ i ][ p ];
      for( int j = 0 ; j < 3 ; j ++ )
        g[ i ][ j ] -= g[ nxt ][ j ] * bns;
    }
    nxt ++;
  }
  return ret;
}
double v[ 3 ] , rv[ 3 ] , rotv[ 3 ];
double norm( const double* vv ){
  double ret = 0;
  for( int i = 0 ; i < 3 ; i ++ )
    ret += vv[ i ] * vv[ i ];
  return sqrtl( ret );
}
double vv[ 3 ][ 3 ];
void find_v(){
  for( int i = 0 ; i < 3 ; i ++ )
    vv[ 0 ][ i ] = 1;
  for( int cur = 1 ; cur < 3 ; cur ++ ){
    for( int i = 0 ; i < 3 ; i ++ )
      for( int j = 0 ; j < 3 ; j ++ )
        vv[ cur ][ i ] += a[ i ][ j ] * vv[ cur - 1 ][ j ];
  }
  double dif = 0;
  for( int i = 0 ; i < 3 ; i ++ )
    dif += fabs( vv[ 0 ][ i ] - vv[ 1 ][ i ] );
  if( dif < eps ){
    for( int i = 0 ; i < 3 ; i ++ )
      v[ i ] = vv[ 0 ][ i ];
    return;
  }
  for( int i = 1 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      vv[ i ][ j ] -= vv[ 0 ][ j ];
  {
    v[ 0 ] = vv[ 1 ][ 1 ] * vv[ 2 ][ 2 ] - vv[ 1 ][ 2 ] * vv[ 2 ][ 1 ];
    v[ 1 ] = vv[ 1 ][ 2 ] * vv[ 2 ][ 0 ] - vv[ 1 ][ 0 ] * vv[ 2 ][ 2 ];
    v[ 2 ] = vv[ 1 ][ 0 ] * vv[ 2 ][ 1 ] - vv[ 1 ][ 1 ] * vv[ 2 ][ 0 ];
  }
}
int main(){
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      cin >> a[ i ][ j ];
      //scanf( "%lf" , &a[ i ][ j ] );
  find_v();
  //vector< pair<int,int> > ret = gauss();
  //assert( ret.size() == 2u );
  //int other = 3;
  //for( auto i : ret )
    //other -= i.second;
  //v[ other ] = 1;
  //for( auto i : ret ){
    //int row = i.first;
    //int pvt = i.second;
    //v[ pvt ] = v[ other ] * ( -g[ row ][ other ] );
  //}
  {
    double nn = 0;
    for( int i = 0 ; i < 3 ; i ++ )
      nn += v[ i ] * v[ i ];
    nn = sqrtl( nn );
    for( int i = 0 ; i < 3 ; i ++ )
      v[ i ] = v[ i ] / nn;
  }
  {
    if( fabs( v[ 0 ] ) > eps or fabs( v[ 1 ] ) > eps ){
      rv[ 0 ] = -v[ 1 ];
      rv[ 1 ] = v[ 0 ];
      rv[ 2 ] = 0;
    }else{
      rv[ 0 ] = 0;
      rv[ 1 ] = v[ 2 ];
      rv[ 2 ] = -v[ 1 ];
    }
  }
  {
    for( int i = 0 ; i < 3 ; i ++ )
      for( int j = 0 ; j < 3 ; j ++ )
        rotv[ i ] += a[ i ][ j ] * rv[ j ];
  }
  double ang = 0.;
  {
    double in = 0;
    for( int i = 0 ; i < 3 ; i ++ )
      in += rv[ i ] * rotv[ i ];
    ang = acosl( min( (double)1. , max( (double)-1. , in / norm( rv ) / norm( rotv ) ) ) );
    double whi[ 3 ] = {};
    {
      whi[ 0 ] = rv[ 1 ] * rotv[ 2 ] - rv[ 2 ] * rotv[ 1 ];
      whi[ 1 ] = rv[ 2 ] * rotv[ 0 ] - rv[ 0 ] * rotv[ 2 ];
      whi[ 2 ] = rv[ 0 ] * rotv[ 1 ] - rv[ 1 ] * rotv[ 0 ];
    }
    double nei = 0;
    for( int i = 0 ; i < 3 ; i ++ )
      nei += whi[ i ] * v[ i ];
    if( nei < 0 ) ang = -ang;
    ang = (ang / acosl( -1. )) * 180;
    while( ang < -180 ) ang += 360.;
    while( ang > +180 ) ang -= 360.;
    ang = max( ang , (double)-179. );
    ang = min( ang , (double)+179. );
    if( ang > 0 and ang < 1 ) ang = 1;
    if( ang < 0 and ang > -1 ) ang = -1;
  }
  printf( "%.15LF\n%.15LF %.15LF %.15LF\n" , ang , v[ 0 ] , v[ 1 ] , v[ 2 ] );
}
