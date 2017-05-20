#include <bits/stdc++.h>
using namespace std;
#define N 402020
typedef long long LL;

int n , m ;
struct Edge {
  int u , v , vl;
  Edge( int x , int y , int z ) :
    u( x ) , v( y ) , vl( z ) {}
  Edge(){}
  void read() {
    scanf("%d%d%d", &u, &v, &vl);
  }
} e[ 300005 ] ;
struct Q {
  int id, vl;
  int ax , ay ;
} q[ 300005 ] ;

int qn;
void init() {
  for ( int i = 0 ; i < m ; i ++ ) {
    e[ i ].read();
  }
  scanf( "%d" , &qn ) ;
  for ( int i = 0 ; i < qn ; i ++ ) {
    int vl ;
    scanf( "%d" , &vl ) ;
    q[ i ].id = i;
    q[ i ].vl = vl ;
  }
}

int deg[ 300005 ] ;
int pr[ 300005 ] ;
int sz[ 300005 ] ;
int gd[ 300005 ] ;
int special ;
int nodes , edges ;

int find( int x ) {
  return ( pr[ x ] == x ) ? x : ( pr[ x ] = find( pr[ x ] ) ) ;
}

void modgd( int x , int del ) {
  if ( gd[ x ] == sz[ x ] ) special -- ;
  gd[ x ] += del ;
  //printf( "%d %d %d\n" , x , gd[ x ] , sz[ x ] ) ;
  if ( gd[ x ] == sz[ x ] ) special ++ ;
}

void pushN( int x ) {
  int par = find( x ) ;
  if ( deg[ x ] == 0 ) {
    nodes ++ ;
  } else if ( deg[ x ] == 1 ) {
    nodes -- ;
    edges -- ;
    modgd( par , 1 ) ;
  } else if ( deg[ x ] == 2 ) {
    nodes ++ ;
    edges ++ ;
    modgd( par , -1 ) ;
  }
  deg[ x ] ++ ;
}

void add( Edge ed ) {
  int u = ed.u ;
  int v = ed.v ;

  edges ++ ;
  pushN( u ) ;
  pushN( v ) ;

  //printf( "%d %d --> %d\n" , u , v , special ) ;
  int g1 = find( u ) ;
  int g2 = find( v ) ;

  if ( g1 == g2 ) return ;
  if ( gd[ g1 ] == sz[ g1 ] ) special -- ;
  if ( gd[ g2 ] == sz[ g2 ] ) special -- ;

  pr[ g2 ] = g1 ;
  sz[ g1 ] += sz[ g2 ] ;
  gd[ g1 ] += gd[ g2 ] ;
  if ( gd[ g1 ] == sz[ g1 ] ) special ++ ;
  //printf( "%d %d --> %d\n" , u , v , special ) ;
}

void solve(){
  sort( q , q + qn , [&]( Q x , Q y ) { return x.vl > y.vl ; } ) ;
  sort( e , e + m , [&]( Edge x , Edge y ) { return x.vl > y.vl ; } ) ;
  for ( int i = 1 ; i <= n ; i ++ ) deg[ i ] = 0 , pr[ i ] = i , sz[ i ] = 1 , gd[ i ] = 0 ;

  special = 0 ;
  nodes = edges = 0 ;
  int ptr = 0 ;
  for ( int k = 0 ; k < qn ; k ++ ) {
    while ( ptr < m && e[ ptr ].vl >= q[ k ].vl ) {
      add( e[ ptr ++ ] ) ;
    }
    q[ k ].ax = nodes + special ;
    q[ k ].ay = edges + special ;
  }
  sort( q , q + qn , [&]( Q x , Q y ) { return x.id < y.id ; } ) ;
  for ( int i = 0 ; i < qn ; i ++ ) {
    printf( "%d %d\n" , q[ i ].ax , q[ i ].ay ) ;
  }
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    init();
    solve();
  }
}
