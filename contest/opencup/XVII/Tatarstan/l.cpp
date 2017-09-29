#include <bits/stdc++.h>
using namespace std;
#define N 2222
#define PB push_back
#define SZ(X) ((int)X.size())
struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  int n, fa[ N * N ], sz[ N * N ];
  vector< pair<int*,int> > h;
  vector<int> sp;
  void init( int tn ){
    n=tn;
    for( int i = 0 ; i < n ; i ++ ){
      fa[ i ]=i;
      sz[ i ]=1;
    }
    sp.clear(); h.clear();
  }
  void assign( int *k, int v ){
    h.PB( {k, *k} );
    *k = v;
  }
  void save(){ sp.PB(SZ(h)); }
  void undo(){
    assert(!sp.empty());
    int last=sp.back(); sp.pop_back();
    while( SZ(h)!=last ){
      auto x=h.back(); h.pop_back();
      *x.first = x.second;
    }
  }
  int f( int x ){
    while( fa[ x ] != x ) x = fa[ x ];
    return x;
  }
  void uni( int x , int y ){
    x = f( x ); y = f( y );
    if( x == y ) return;
    if( sz[ x ] < sz[ y ] ) swap( x, y );
    assign( &sz[ x ] , sz[ x ] + sz[ y ] );
    assign( &fa[ y ] , x);
  }
} djs;
int h , w;
char c[ N ][ N ];
int id( int th , int tw ){
  return th * w + tw;
}
int up[ N ][ N ] , dn[ N ][ N ];
int lf[ N ][ N ] , rg[ N ][ N ];
int main(){
  scanf( "%d%d" , &h , &w );
  for( int i = 0 ; i < h ; i ++ )
    scanf( "%s" , c[ i ] );
  djs.init( h * w );
  for( int i = 0 ; i < h ; i ++ )
    for( int j = 0 ; j < w ; j ++ ){
      up[ i ][ j ] = dn[ i ][ j ] =
      lf[ i ][ j ] = rg[ i ][ j ] = -1;
    }
  for( int i = 0 ; i < h ; i ++ ){
    for( int pre = -1 , j = 0 ; j < w ; j ++ ){
      lf[ i ][ j ] = pre;
      if( c[ i ][ j ] == '+' ) pre = j;
    }
    for( int pre = -1 , j = w - 1 ; j >= 0 ; j -- ){
      rg[ i ][ j ] = pre;
      if( c[ i ][ j ] == '+' ) pre = j;
    }
  }
  for( int j = 0 ; j < w ; j ++ ){
    for( int pre = -1 , i = 0 ; i < h ; i ++ ){
      up[ i ][ j ] = pre;
      if( c[ i ][ j ] == '+' ) pre = i;
    }
    for( int pre = -1 , i = h - 1 ; i >= 0 ; i -- ){
      dn[ i ][ j ] = pre;
      if( c[ i ][ j ] == '+' ) pre = i;
    }
  }
  for( int i = 0 ; i < h ; i ++ )
    for( int j = 0 ; j < w ; j ++ )
      if( c[ i ][ j ] == '+' ){
        if( lf[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( i , lf[ i ][ j ] ) );
        if( rg[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( i , rg[ i ][ j ] ) );
        if( up[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( up[ i ][ j ] , j ) );
        if( dn[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( dn[ i ][ j ] , j ) );
      }
  int ans = 0 , ai = 0 , aj = 0;
  for( int i = 0 ; i < h ; i ++ )
    for( int j = 0 ; j < w ; j ++ )
      if( c[ i ][ j ] == '.' ){
        djs.save();
        if( lf[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( i , lf[ i ][ j ] ) );
        if( rg[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( i , rg[ i ][ j ] ) );
        if( up[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( up[ i ][ j ] , j ) );
        if( dn[ i ][ j ] != -1 )
          djs.uni( id( i , j ) , id( dn[ i ][ j ] , j ) );
        int curans = djs.sz[ djs.f( id( i , j ) ) ] - 1;
        if( curans > ans ){
          ans = curans;
          ai = i + 1;
          aj = j + 1;
        }
        djs.undo();
      }
  printf( "%d\n" , ans );
  if( ans ) printf( "%d %d\n" , ai , aj );
}
