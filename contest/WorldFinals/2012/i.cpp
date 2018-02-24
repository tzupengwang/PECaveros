#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
struct SegT{
  int sum[ N << 1 ] , mn[ N << 1 ];
  void init( int no , int l , int r ){
    sum[ no ] = 0; mn[ no ] = N;
    if( l == r ) return;
    init( L( no ) , l , mid );
    init( R( no ) , mid + 1 , r );
  }
  void modify( int no , int l , int r , int p , int d ){
    if( l == r ){
      sum[ no ] += d;
      if( sum[ no ] ) mn[ no ] = l;
      else mn[ no ] = N;
      return;
    }
    if( p <= mid )
      modify( L( no ) , l , mid , p , d );
    else
      modify( R( no ) , mid + 1 , r , p , d );
    sum[ no ] = sum[ L( no ) ] + sum[ R( no ) ];
    mn[ no ] = min( mn[ L( no ) ] , mn[ R( no ) ] );
  }
  pair<int,int> query( int no , int l , int r , int ql , int qr ){
    if( r < ql or l > qr or ql > qr ) return { 0 , N };
    if( ql <= l and r <= qr ) return { sum[ no ] , mn[ no ] };
    pair<int,int> lret = query( L( no ) , l , mid , ql , qr );
    pair<int,int> rret = query( R( no ) , mid + 1 , r , ql , qr );
    return { lret.first + rret.first,
             min( lret.second , rret.second ) };
  }
} seg;
#define NN 1000000
int R , C , m , n;
set< pair<int,int> > r[ N ] , c[ N ];
vector< pair<int, pair<int,int> > > v[ 2 ][ 2 ];
pair<LL, pair<int,int> > pair_up( int id ,
        const vector< pair<int, pair<int,int> > >& v1 ,
              vector< pair<int, pair<int,int> > >& eve ){
  for( auto i : v1 ){
    eve.push_back( { i.second.first ,
                     { -1 , i.first } } );
    eve.push_back( { i.second.second + 1 ,
                     { -2 , i.first } } );
  }
  sort( eve.begin() , eve.end() );
  LL tans = 0;
  pair<int,int> tp = {0, 0};
  //puts( "======" );
  for( auto ee : eve ){
    if( ee.second.first == -1 ){
      seg.modify( 1 , 1 , NN , ee.second.second , + 1 );
      continue;
    }
    if( ee.second.first == -2 ){
      seg.modify( 1 , 1 , NN , ee.second.second , - 1 );
      continue;
    }
    pair<int,int> ret = seg.query( 1 , 1 , NN , ee.second.first ,
                                                ee.second.second );
    //printf( "Q %d %d\n" , ee.second.first + 1 ,
            //ee.second.second - 1 );
    if( !ret.first ) continue;
    if( !tans ){
      tans = ret.first;
      tp = {ret.second, ee.first};
    }else{
      tans += ret.first;
      pair<int,int> ttp = {ret.second, ee.first};
      tp = min( tp , ttp );
    }
  }
  return {tans, tp};
}
void go_solve(){
  LL ans = 0;
  pair<int,int> pa;
  for( int i = 0 ; i < 2 ; i ++ ){
    LL tans = 0;
    pair<int,int> ppa;
    tie( tans , ppa ) = pair_up( i , v[ i ][ 0 ] , v[ 1 - i ][ 1 ] );
    if( !tans ) continue;
    if( !ans ){
      ans = tans;
      pa = ppa;
    }else{
      ans += tans;
      pa = min( pa , ppa );
    }
  }
  if( !ans )
    puts( "impossible" );
  else
    printf( "%lld %d %d\n" , ans , pa.first , pa.second );
}
void add_seg( int id , int r1 , int c1 , int r2 , int c2 ){
  //printf( "%d %d %d %d %d\n" , id , r1 , c1 , r2 , c2 );
  if( r1 == r2 ) // hor
    v[ id ][ 0 ].push_back( { r1 , { min( c1 , c2 ) + 1,
                                     max( c1 , c2 ) - 1 } } );
  else // ver
    v[ id ][ 1 ].push_back( { c1 , { min( r1 , r2 ) + 1,
                                     max( r1 , r2 ) - 1 } } );
}
void init(){
  for( int i = 0 ; i < N ; i ++ ){
    r[ i ].clear();
    c[ i ].clear();
  }
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ )
      v[ i ][ j ].clear();
  while( m -- ){ // /
    int ri , ci;
    scanf( "%d%d" , &ri , &ci );
    r[ ri ].insert( { ci , 1 } );
    c[ ci ].insert( { ri , 1 } );
  }
  while( n -- ){
    int ri , ci;
    scanf( "%d%d" , &ri , &ci );
    r[ ri ].insert( { ci , 2 } );
    c[ ci ].insert( { ri , 2 } );
  }
}
// 0 > 1 <
// 2 ^ 3 v
int _cs;
int turn( int in_dir , int type ){
  if( type == 1 ){
    if( in_dir == 0 ) return 2;
    if( in_dir == 1 ) return 3;
    if( in_dir == 2 ) return 0;
    if( in_dir == 3 ) return 1;
    assert( false );
    return -1;
  }else{
    if( in_dir == 0 ) return 3;
    if( in_dir == 1 ) return 2;
    if( in_dir == 2 ) return 1;
    if( in_dir == 3 ) return 0;
    assert( false );
    return -1;
  }
  assert( false );
  return -1;
}
bool go( int id , int cr , int cc , int cdir ){
  if( cdir == 0 ){
    auto it = r[ cr ].upper_bound( { cc , 3 } );
    if( it == r[ cr ].end() ){
      if( id == 0 and cr == R ) return true;
      add_seg( id , cr , cc , cr , C + 1 );
    }else{
      pair<int,int> tp = *it;
      int nc = tp.first;
      add_seg( id , cr , cc , cr , nc );
      return go( id , cr , nc , turn( cdir , tp.second ) );
    }
    return false;
  }
  if( cdir == 1 ){
    auto it = r[ cr ].lower_bound( { cc , 0 } );
    if( it == r[ cr ].begin() ){
      add_seg( id , cr , cc , cr , 0 );
    }else{
      pair<int,int> tp = *--it;
      int nc = tp.first;
      add_seg( id , cr , cc , cr , nc );
      return go( id , cr , nc , turn( cdir , tp.second ) );
    }
    return false;
  }
  if( cdir == 3 ){
    auto it = c[ cc ].upper_bound( { cr , 3 } );
    if( it == c[ cc ].end() ){
      add_seg( id , cr , cc , R + 1 , cc );
    }else{
      pair<int,int> tp = *it;
      int nr = tp.first;
      add_seg( id , cr , cc , nr , cc );
      return go( id , nr , cc , turn( cdir , tp.second ) );
    }
    return false;
  }
  if( cdir == 2 ){
    auto it = c[ cc ].lower_bound( { cr , 0 } );
    if( it == c[ cc ].begin() ){
      add_seg( id , cr , cc , 0 , cc );
    }else{
      pair<int,int> tp = *--it;
      int nr = tp.first;
      add_seg( id , cr , cc , nr , cc );
      return go( id , nr , cc , turn( cdir , tp.second ) );
    }
    return false;
  }
  return false;
}
void solve(){
  printf( "Case %d: " , ++ _cs );
  if( go( 0 , 1 , 0 , 0 ) ){
    puts( "0" );
    return;
  }
  go( 1 , R , C + 1 , 1 );
  go_solve();
}
int main(){
  seg.init( 1 , 1 , NN );
  while( scanf( "%d%d%d%d" , &R , &C , &m , &n ) == 4 ){
    init();
    solve();
  }
}
