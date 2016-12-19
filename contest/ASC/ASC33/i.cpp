#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
int n;
int lx[ 2 ] , ly[ 2 ] , rx[ 2 ] , ry[ 2 ];
const int dx[]={1,1,0,-1,-1,-1,0,1};
const int dy[]={0,1,1,1,0,-1,-1,-1};
int dir[ 2 ];
inline int Dir( int ddx , int ddy ){
  ddx /= max( 1 , abs( ddx ) );
  ddy /= max( 1 , abs( ddy ) );
  for( int ndir = 0 ; ndir < 8 ; ndir ++ )
    if( ddx == dx[ ndir ] &&
        ddy == dy[ ndir ] )
      return ndir;
  return 0;
}
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < 2 ; i ++ )
    scanf( "%d%d%d%d" , &lx[ i ] , &ly[ i ] , &rx[ i ] , &ry[ i ] );
  for( int i = 0 ; i < 2 ; i ++ ){
    int ddx = rx[ i ] - lx[ i ];
    int ddy = ry[ i ] - ly[ i ];
    dir[ i ] = Dir( ddx , ddy );
  }
}
const int N = 100;
const int hf = N / 2 - 25;
double dst[ N ][ N ][ 8 ];
int got[ N ][ N ][ 8 ] , stp;
int fx[ N ][ N ][ 8 ];
int fy[ N ][ N ][ 8 ];
int fd[ N ][ N ][ 8 ];
pair<double,int> cal( int sx , int sy , int sdir , int tx , int ty , int tdir ){
  ++ stp;
typedef pair<double, pair< pair<int,int> , int > > data;
  priority_queue< data , vector<data> , greater<data> > heap;
  heap.push( { 0 , { { sx , sy } , sdir } } );
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      for( int k = 0 ; k < 8 ; k ++ )
        dst[ i ][ j ][ k ] = 1e9;
  dst[ sx + hf ][ sy + hf ][ sdir ] = 0;
  while( heap.size() ){
    auto td = heap.top(); heap.pop();
    int nx = td.second.first.first;
    int ny = td.second.first.second;
    int nd = td.second.second;
    if( got[ nx + hf ][ ny + hf ][ nd ] == stp ) continue;
    got[ nx + hf ][ ny + hf ][ nd ] = stp;
    dst[ nx + hf ][ ny + hf ][ nd ] = td.first;
    int ld = ( nd + 1 ) % 8;
    int rd = ( nd + 7 ) % 8;
    for( int nxtdir : { ld , nd , rd } ){
      for( int k = 1 ; ; k ++ ){
        int ddx = k * dx[ nxtdir ];
        int ddy = k * dy[ nxtdir ];
        if( ddx * ddx + ddy * ddy < n * n ) continue;
        if( ddx * ddx + ddy * ddy >= 16 * n * n ) break;
        int nxtx = nx + ddx;
        int nxty = ny + ddy;
        if( nxtx + hf < 0 || nxtx + hf >= N ||
            nxty + hf < 0 || nxty + hf >= N ) break;
        if( got[ nxtx + hf ][ nxty + hf ][ nxtdir ] == stp ) continue;
        //printf( "%d %d -> %d %d\n" , nx , ny , nxtx , nxty );
        double nxtv = dst[ nx + hf ][ ny + hf ][ nd ] + sqrt( ddx * ddx + ddy * ddy );
        //if( sx == 10 && sy == 0 && tx == 10 && ty == 25 ){
          //if( nx == 21 && ny == 0 && nxtdir == 1 )
            //printf( "%d %d\n" , nxtx , nxty );
          //if( nx == 10 && ny == 0 && nxtx == 21 && nxty == 0 )
            //printf( "1 %d %.12f\n" , stp , nxtv );
          //if( nx == 21 && ny == 0 && nxtx == 36 && nxty == 15 )
            //printf( "2 %d %.12f\n" , stp , nxtv );
          //if( nx == 36 && ny == 15 && nxtx == 36 && nxty == 25 )
            //printf( "3 %d %.12f\n" , stp , nxtv );
        //}
        if( nxtv < dst[ nxtx + hf ][ nxty + hf ][ nxtdir ] ){
          dst[ nxtx + hf ][ nxty + hf ][ nxtdir ] = nxtv;
          //printf( "%d %d %d updates %.6f\n" , nxtx , nxty , nd , )
          fx[ nxtx + hf ][ nxty + hf ][ nxtdir ] = nx;
          fy[ nxtx + hf ][ nxty + hf ][ nxtdir ] = ny;
          fd[ nxtx + hf ][ nxty + hf ][ nxtdir ] = nd;
          heap.push( { nxtv , { { nxtx , nxty } , nxtdir } } );
        }
      }
    }
  }
  double bst = 1e9;
  int who = 0;
  for( int i = 0 ; i < 8 ; i ++ ){
    int dlt = ( i - tdir + 8 ) % 8;
    if( dlt == 1 || dlt == 7 || dlt == 0 ){
      if( dst[ tx + hf ][ ty + hf ][ i ] < bst ){
        bst = dst[ tx + hf ][ ty + hf ][ i ];
        who = i;
      }
    }
  }
  return { bst , who };
}
void go( int sx , int sy , int sdir , int tx , int ty , int tdir ){
  vector< pair<int,int> > vv;
  //printf( "%d %d %d %d\n" , sx , sy , tx , ty );
  //printf( "%.9f\n" , dst[ tx + hf ][ ty + hf ][ tdir ] );
  while( tx != sx || ty != sy ){
    vv.push_back( { tx , ty } );
    int px = fx[ tx + hf ][ ty + hf ][ tdir ];
    int py = fy[ tx + hf ][ ty + hf ][ tdir ];
    int pd = fd[ tx + hf ][ ty + hf ][ tdir ];
    tx = px;
    ty = py;
    tdir = pd;
  }
  vv.push_back( { sx , sy } );
  reverse( vv.begin() , vv.end() );
  size_t sz = 2;
  for( size_t i = 2 ; i < vv.size() ; i ++ )
    if( Dir( vv[ sz - 1 ].first - vv[ sz - 2 ].first ,
             vv[ sz - 1 ].second - vv[ sz - 2 ].second ) ==
        Dir( vv[ i ].first - vv[ sz - 1 ].first,
             vv[ i ].second - vv[ sz - 1 ].second ) )
      vv[ sz - 1 ] = vv[ i ];
    else
      vv[ sz ++ ] = vv[ i ];
  vv.resize( sz );
  printf( "%d\n" , (int)vv.size() - 1 );
  for( auto i : vv )
    printf( "%d %d\n" , i.first , i.second );
  exit( 0 );
}
void solve(){
  pair<double,int> ans1 = cal( rx[ 0 ] , ry[ 0 ] , dir[ 0 ] , 
                               lx[ 1 ] , ly[ 1 ] , dir[ 1 ] );
  pair<double,int> ans2 = cal( rx[ 0 ] , ry[ 0 ] , dir[ 0 ] , 
                               rx[ 1 ] , ry[ 1 ] , ( dir[ 1 ] + 4 ) % 8 );
  pair<double,int> ans3 = cal( lx[ 0 ] , ly[ 0 ] , ( dir[ 0 ] + 4 ) % 8 , 
                               lx[ 1 ] , ly[ 1 ] , dir[ 1 ] );
  pair<double,int> ans4 = cal( lx[ 0 ] , ly[ 0 ] , ( dir[ 0 ] + 4 ) % 8 , 
                               rx[ 1 ] , ry[ 1 ] , ( dir[ 1 ] + 4 ) % 8 );
  double bst = min( min( ans1.first , ans2.first ) ,
                    min( ans3.first , ans4.first ) );
  //printf( "%.12f\n" , bst );
  if( ans1.first == bst ){
    cal( rx[ 0 ] , ry[ 0 ] , dir[ 0 ] , lx[ 1 ] , ly[ 1 ] , dir[ 1 ] );
     go( rx[ 0 ] , ry[ 0 ] , dir[ 0 ] , lx[ 1 ] , ly[ 1 ] , ans1.second );
  }else if( ans2.first == bst ){
    cal( rx[ 0 ] , ry[ 0 ] , dir[ 0 ] , rx[ 1 ] , ry[ 1 ] , ( dir[ 1 ] + 4 ) % 8 );
     go( rx[ 0 ] , ry[ 0 ] , dir[ 0 ] , rx[ 1 ] , ry[ 1 ] , ans2.second );
  }else if( ans3.first == bst ){
    cal( lx[ 0 ] , ly[ 0 ] , ( dir[ 0 ] + 4 ) % 8 , lx[ 1 ] , ly[ 1 ] , dir[ 1 ] );
     go( lx[ 0 ] , ly[ 0 ] , ( dir[ 0 ] + 4 ) % 8 , lx[ 1 ] , ly[ 1 ] , ans3.second );
  }else if( ans4.first == bst ){
    cal( lx[ 0 ] , ly[ 0 ] , ( dir[ 0 ] + 4 ) % 8 , rx[ 1 ] , ry[ 1 ] , ( dir[ 1 ] + 4 ) % 8 );
     go( lx[ 0 ] , ly[ 0 ] , ( dir[ 0 ] + 4 ) % 8 , rx[ 1 ] , ry[ 1 ] , ans4.second );
  }else
    assert( false );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "railroad.in" , "r" , stdin );
  freopen( "railroad.out" , "w" , stdout );
#endif
  init();
  solve();
}
