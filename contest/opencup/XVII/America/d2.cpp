#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 200020
int n , v[ N ] , p[ N ] , sz;
vector<int> s[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d%d" , &v[ i ] , &p[ i ] );
    if( p[ i ] )
      s[ p[ i ] ].push_back( i );
  }
  vector<int> vv;
  for( int i = 1 ; i <= n ; i ++ )
    vv.push_back( v[ i ] );
  sort( vv.begin() , vv.end() );
  vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
  for( int i = 1 ; i <= n ; i ++ )
    v[ i ] = lower_bound( vv.begin() , vv.end() , v[ i ] ) - vv.begin() + 1;
  sz = (int)vv.size();
}
#define lgN 40
#define K (N * 60)
struct Nd{
  int vl , tl , tr , tg;
  Nd(){
    tg = vl = tl = tr = 0;
  }
} pl[ K ];
int que[ K ] , tn , qt;
void build(){
  for( int i = 0 ; i < K ; i ++ )
    que[ i ] = i;
  tn = 1;
  qt = 0;
}
int new_node(){
  if( tn >= K ) tn -= K;
  return que[ tn ++ ];
}
void recycle_unit( int nd ){
  if( !nd ) return;
  if( qt >= K ) qt -= K;
  que[ qt ++ ] = nd;
}
void recycle( int nd ){
  //return;
  if( !nd ) return;
  //printf( "%d %d %d\n" , nd , pl[ nd ].tl , pl[ nd ].tr );
  if( qt >= K ) qt -= K;
  que[ qt ++ ] = nd;
  recycle( pl[ nd ].tl );
  recycle( pl[ nd ].tr );
}
int root[ N ];
#define mid ((l+r)>>1)
void push( int nd1 , int l , int r ){
  if( l == r or pl[ nd1 ].tg == 0 ){
    pl[ nd1 ].tg = 0;
    return;
  }
  if( pl[ nd1 ].tl == 0 ) pl[ nd1 ].tl = new_node();
  if( pl[ nd1 ].tr == 0 ) pl[ nd1 ].tr = new_node();
  int ndl = pl[ nd1 ].tl;
  int ndr = pl[ nd1 ].tr;
  pl[ ndl ].tg = pl[ ndl ].vl =
  pl[ ndr ].tg = pl[ ndr ].vl = pl[ nd1 ].tg;
  pl[ nd1 ].tg = 0;
}
inline int VL( int nd ){
  return nd ? pl[ nd ].vl : 0;
}
int merge( int nd1 , int nd2 , int l , int r ){
  if( nd1 == 0 or nd2 == 0 ) return max( nd1 , nd2 );
  if( pl[ nd1 ].tg and pl[ nd2 ].tg ){
    pl[ nd1 ].tg += pl[ nd2 ].tg;
    pl[ nd1 ].vl = pl[ nd1 ].tg;
    recycle( pl[ nd1 ].tl );
    recycle( pl[ nd1 ].tr );
    pl[ nd1 ].tl = pl[ nd1 ].tr = 0;
    recycle( nd2 );
    return nd1;
  }
  if( l == r ){
    pl[ nd1 ].vl += pl[ nd2 ].vl;
    recycle( nd2 );
    return nd1;
  }
  if( pl[ nd2 ].tg ) swap( nd1 , nd2 );
  if( pl[ nd1 ].tg ){
    push( nd1 , l , r );
    pl[ nd1 ].tl = merge( pl[ nd1 ].tl , pl[ nd2 ].tl , l , mid );
    pl[ nd1 ].tr = merge( pl[ nd1 ].tr , pl[ nd2 ].tr , mid + 1 , r );
    pl[ nd1 ].vl = max( VL( pl[ nd1 ].tl ) , VL( pl[ nd1 ].tr ) );
    recycle_unit( nd2 );
    return nd1;
  }
  pl[ nd1 ].tl = merge( pl[ nd1 ].tl , pl[ nd2 ].tl , l , mid );
  pl[ nd1 ].tr = merge( pl[ nd1 ].tr , pl[ nd2 ].tr , mid + 1 , r );
  pl[ nd1 ].vl = max( VL( pl[ nd1 ].tl ) , VL( pl[ nd1 ].tr ) );
  recycle_unit( nd2 );
  return nd1;
}
void asgn( int nd , int l , int r , int ql , int qr , int qv ){
  if( r < ql or l > qr or ql > qr ) return;
  if( ql <= l and r <= qr ){
    pl[ nd ].tg = pl[ nd ].vl = qv;
    recycle( pl[ nd ].tl );
    recycle( pl[ nd ].tr );
    pl[ nd ].tl = pl[ nd ].tr = 0;
    return;
  }
  push( nd , l , r );
  if( pl[ nd ].tl == 0 ) pl[ nd ].tl = new_node();
  if( pl[ nd ].tr == 0 ) pl[ nd ].tr = new_node();
  asgn( pl[ nd ].tl , l , mid , ql , qr , qv );
  asgn( pl[ nd ].tr , mid + 1 , r , ql , qr , qv );
  pl[ nd ].vl = max( VL( pl[ nd ].tl ) , VL( pl[ nd ].tr ) );
}
int query( int nd , int l , int r , int ql , int qr ){
  if( !nd or r < ql or l > qr or ql > qr ) return 0;
  if( ql <= l and r <= qr ) return pl[ nd ].vl;
  push( nd , l , r );
  return max( query( pl[ nd ].tl , l , mid , ql , qr ) ,
              query( pl[ nd ].tr , mid + 1 , r , ql , qr ) );
}
int query2( int nd , int l , int r , int ud ){
  if( !nd or pl[ nd ].vl < ud ) return r;
  if( l == r or pl[ nd ].tg ) return -1;
  return max( query2( pl[ nd ].tl , l , mid , ud ) ,
              query2( pl[ nd ].tr , mid + 1 , r , ud ) );
}
//void print( int nd , int l , int r ){
  //if( !nd ) return;
  //printf( "%d (%d,%d) -> lc=%d rc=%d vl=%d, tg = %d\n" , nd , l , r ,
          //pl[ nd ].tl , pl[ nd ].tr , 
          //pl[ nd ].vl , pl[ nd ].tg );
  //print( pl[ nd ].tl , l , mid );
  //print( pl[ nd ].tr , mid + 1 , r );
//}
void solve(){
  int ans = 1;
  for( int i = n ; i >= 1 ; i -- ){
    root[ i ] = -1;
    for( int son : s[ i ] ){
      if( root[ i ] == -1 )
        root[ i ] = root[ son ];
      else
        root[ i ] = merge( root[ i ] , root[ son ] , 1 , sz );
      //if( i == 1 ) print( root[ i ] , 1 , sz );
      //puts( "====" );
    }
    if( root[ i ] == -1 ) root[ i ] = new_node();
    int bst = 1 + query( root[ i ] , 1 , sz , 1 , v[ i ] - 1 );
    int pos = query2( root[ i ] , 1 , sz , bst );
    //printf( "%d : \n" , i );
    if( v[ i ] <= pos ){
      //printf( "Assign %d %d -> %d\n" , v[ i ] , pos , bst );
      asgn( root[ i ] , 1 , sz , v[ i ] , pos , bst );
    }
    ans = max( ans , bst );
    ans = max( ans , query( root[ i ] , 1 , sz , 1 , sz ) );
  }
  printf( "%d\n" , ans );
}
int main(){
  build();
  init();
  solve();
}
