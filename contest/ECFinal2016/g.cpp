#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 201010
struct Nd{
  int v;
  int tl , tr;
  //Nd *tl , *tr;
  Nd(){
    tl = tr = 0;
    //tl = tr = NULL;
    v = 0;
  }
};
Nd nd[ 300030 * 60 ];
//vector<Nd*> rec;
int _ptr = 0;
int copy( int x ){
  ++ _ptr;
  nd[ _ptr ] = nd[ x ];
  return _ptr;
}
#define mid ((l+r)>>1)
void modify( int now , int l , int r , int p , int v ){
  if( l == r ){
    nd[ now ].v = v;
    return;
  }
  if( p <= mid ){
    nd[ now ].tl = copy( nd[ now ].tl );
    modify( nd[ now ].tl , l , mid , p , v );
  }else{
    nd[ now ].tr = copy( nd[ now ].tr );
    modify( nd[ now ].tr , mid + 1 , r , p , v );
  }
}
int query( int now , int l , int r , int p ){
  if( !now ) return 0;
  if( l == r ) return nd[ now ].v;
  if( p <= mid ) return query( nd[ now ].tl , l , mid , p );
  else return query( nd[ now ].tr , mid + 1 , r , p );
}
int n , m , clr[ N ];
vector< pair<int, pair<int,int> > > e;
vector<int> wss;
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &clr[ i ] );
  e.clear();
  wss.clear();
  while( m -- ){
    int ui , vi , ci;
    scanf( "%d%d%d" , &ui , &vi , &ci );
    e.push_back( { ci , {ui, vi} } );
    wss.push_back( ci );
  }
  wss.push_back( 0 );
  sort( e.begin() , e.end() );
  sort( wss.begin() , wss.end() );
  wss.resize( unique( wss.begin() , wss.end() ) - wss.begin() );
}
//Nd *p[ N ] , *ans[ N ] , *sz[ N ];
int p[ N ] , ans[ N ] , sz[ N ];
unordered_map<int,int> cnt[ N ];
int cans[ N ] , _cs;
int f( int root , int who ){
  while( true ){
    int ret = query( root , 1 , n , who );
    if( ret == who ) return ret;
    who = ret;
  }
}
void solve(){
  _ptr = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    cnt[ i ].clear();
    cnt[ i ][ clr[ i ] ] = 1;
    cans[ i ] = clr[ i ];
  }
  p[ 0 ] = copy( 0 );
  sz[ 0 ] = copy( 0 );
  ans[ 0 ] = copy( 0 );
  for( int i = 1 ; i <= n ; i ++ ){
    modify( p[ 0 ] , 1 , n , i , i );
    modify( sz[ 0 ] , 1 , n , i , 1 );
    modify( ans[ 0 ] , 1 , n , i , cans[ i ] );
  }
  size_t ptr = 0;
  for( size_t i = 1 ; i < wss.size() ; i ++ ){
    p[ i ] = copy( p[ i - 1 ] );
    sz[ i ] = copy( sz[ i - 1 ] );
    ans[ i ] = copy( ans[ i - 1 ] );
    while( ptr < e.size() and e[ ptr ].first == wss[ i ] ){
      int x = e[ ptr ].second.first;
      int y = e[ ptr ].second.second;
      x = f( p[ i ] , x );
      y = f( p[ i ] , y );
      if( x != y ){
        int xsz = query( sz[ i ] , 1 , n , x );
        int ysz = query( sz[ i ] , 1 , n , y );
        if( xsz < ysz ) swap( x , y ) , swap( xsz , ysz );

        modify( p[ i ] , 1 , n , y , x );
        modify( sz[ i ] , 1 , n , x , xsz + ysz );
        int pans = cans[ x ] , pcnt = cnt[ x ][ pans ];
        for( auto pp : cnt[ y ] ){
          cnt[ x ][ pp.first ] += pp.second;
          int ncnt = cnt[ x ][ pp.first ];
          if( ncnt > pcnt or
              (ncnt == pcnt and pp.first < pans ) )
            pans = pp.first , pcnt = ncnt;
        }
        cnt[ y ].clear();
        if( cans[ x ] != pans ){
          cans[ x ] = pans;
          modify( ans[ i ] , 1 , n , x , cans[ x ] );
        }
      }
      ptr ++;
    }
  }
  int lst = 0;
  printf( "Case #%d:\n" , ++ _cs );
  int q; scanf( "%d" , &q ); while( q -- ){
    int qx , qw;
    scanf( "%d%d" , &qx , &qw );
    qx ^= lst; qw ^= lst;
    int qid = upper_bound( wss.begin() , wss.end() , qw ) - wss.begin() - 1;
    int qp = f( p[ qid ] , qx );
    lst = query( ans[ qid ] , 1 , n , qp );
    printf( "%d\n" , lst );
  }
}
int main(){
  int _; scanf( "%d" ,  &_ ); while( _ -- ){
    init();
    solve();
    //for( auto i : rec )
    //  delete i;
    //rec.clear();
  }
}
