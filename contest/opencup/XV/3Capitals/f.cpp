#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202020
#define MAGIC 3
inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
int n , q , r[ N ] , x[ N ][ 4 ] , y[ N ][ 4 ];
int qx1[ N ] , qx2[ N ] , qy1[ N ] , qy2[ N ];
bool gg[ N ];
inline int rand( int lb , int rb ){
  return (long long)rand() * rand() % (rb - lb + 1) + lb;
}
LL goal;
vector<int> lix , liy;
int where( const vector<int>& vv , int tar ){
  return lower_bound( vv.begin() , vv.end() , tar ) - vv.begin() + 1;
}
#define X 2048576
LL lb[ X ] , bit[ X ];
inline void reset(){
  fill( bit , bit + X , 0 );
}
inline void modify( int p , LL v ){
  for( int i = p ; i < X ; i += lb[ i ] )
    bit[ i ] += v;
}
inline LL query( int p ){
  LL ret = 0;
  for( int i = p ; i ; i -= lb[ i ] )
    ret += bit[ i ];
  return ret;
}
vector< pair<int,int> > wt[ X ];
vector< pair< pair<int,int> , pair<int,int> > > qry[ X ];
LL qsr[ N ];
int main(){
  clock_t s = clock();
  for( int i = 0 ; i < X ; i ++ )
    lb[ i ] = i & (-i);
  n = getint();
  q = getint();
  //n = 200000;
  //q = 200000;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 4 ; j ++ ){
      x[ i ][ j ] = getint();
      y[ i ][ j ] = getint();
      //x[ i ][ j ] = rand( 0 , 1e9 );
      //y[ i ][ j ] = rand( 0 , 1e9 );
      lix.push_back( x[ i ][ j ] );
      liy.push_back( x[ i ][ j ] );
    }
  for( int i = 0 ; i < q ; i ++ ){
    qx1[ i ] = getint();
    qy1[ i ] = getint();
    qx2[ i ] = getint();
    qy2[ i ] = getint();
    //qx1[ i ] = rand( 0 , 1e9 );
    //qy1[ i ] = rand( 0 , 1e9 );
    //qx2[ i ] = rand( 0 , 1e9 );
    //qy2[ i ] = rand( 0 , 1e9 );
    //if( qx1[ i ] > qx2[ i ] ) swap( qx1[ i ] , qx2[ i ] );
    //if( qy1[ i ] > qy2[ i ] ) swap( qy1[ i ] , qy2[ i ] );
    lix.push_back( qx1[ i ] - 1 );
    lix.push_back( qx2[ i ] );
    liy.push_back( qy1[ i ] - 1 );
    liy.push_back( qy2[ i ] );
  }
  {
    sort( lix.begin() , lix.end() );
    lix.resize( unique( lix.begin() , lix.end() ) - lix.begin() );
    sort( liy.begin() , liy.end() );
    liy.resize( unique( liy.begin() , liy.end() ) - liy.begin() );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < 4 ; j ++ ){
        x[ i ][ j ] = where( lix , x[ i ][ j ] );
        y[ i ][ j ] = where( liy , y[ i ][ j ] );
        wt[ x[ i ][ j ] ].push_back( { y[ i ][ j ] , i } );
      }
    for( int i = 0 ; i < q ; i ++ ){
      qx1[ i ] = where( lix , qx1[ i ] - 1 );
      qx2[ i ] = where( lix , qx2[ i ] );
      qy1[ i ] = where( liy , qy1[ i ] - 1 );
      qy2[ i ] = where( liy , qy2[ i ] );
      qry[ qx2[ i ] ].push_back( { { qy1[ i ] , qy2[ i ] } , { +1 , i } } );
      qry[ qx1[ i ] ].push_back( { { qy1[ i ] , qy2[ i ] } , { -1 , i } } );
    }
  }
  int xsz = (int)lix.size();
  for( int _ = 0 ; _ < MAGIC ; _ ++ ){
    for( int i = 0 ; i < n ; i ++ )
      r[ i ] = rand( 0 , 1e9 );
    for( int i = 0 ; i < q ; i ++ )
      qsr[ i ] = 0;
    goal = 2LL * accumulate( r , r + n , 0LL );
    reset();
    for( int j = 1 ; j <= xsz ; j ++ ){
      for( auto k : wt[ j ] )
        modify( k.first , r[ k.second ] );
      for( auto qq : qry[ j ] ){
        LL got = query( qq.first.second ) - query( qq.first.first );
        qsr[ qq.second.second ] += got * qq.second.first;
      }
    }
    for( int i = 0 ; i < q ; i ++ )
      if( qsr[ i ] != goal )
        gg[ i ] = true;
    if( (clock() - s) > 4 * CLOCKS_PER_SEC ) break;
  }
  for( int i = 0 ; i < q ; i ++ )
    puts( gg[ i ] ? "NO" : "YES" );
}
