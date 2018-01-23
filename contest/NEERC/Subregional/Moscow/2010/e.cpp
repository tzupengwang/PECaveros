#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define M 101010
int two[ N ] , bit[ M ];
void build(){
  two[ 0 ] = 1;
  for( int i = 1 ; i < 20 ; i ++ )
    two[ i ] = two[ i - 1 ] << 1;
  bit[ 1 ] = 0;
  int nxt = 2 , bt = 0;
  for( int i = 2 ; i < M ; i ++ ){
    bit[ i ] = bt;
    if( i == nxt ){
      nxt <<= 1;
      bt ++;
    }
  }
}
typedef long long LL;
typedef pair<int,int> PII;
int stu[ M << 2 ] , stD[ M << 2 ];
int tagu[ M << 2 ] , tagd[ M << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void build_st( int no , int l , int r ){
  tagu[ no ] = stu[ no ] = M;
  tagd[ no ] = stD[ no ] = 0;
  if( l == r ) return;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
}
void push( int no , int l , int r ){
  if( tagu[ no ] != M ){
    stu[ L( no ) ] = min( stu[ L( no ) ] , tagu[ no ] );
    tagu[ L( no ) ] = min( tagu[ L( no ) ] , tagu[ no ] );
    stu[ R( no ) ] = min( stu[ R( no ) ] , tagu[ no ] );
    tagu[ R( no ) ] = min( tagu[ R( no ) ] , tagu[ no ] );
    tagu[ no ] = M;
  }
  if( tagd[ no ] != 0 ){
    stD[ L( no ) ] = max( stD[ L( no ) ] , tagd[ no ] );
    tagd[ L( no ) ] = max( tagd[ L( no ) ] , tagd[ no ] );
    stD[ R( no ) ] = max( stD[ R( no ) ] , tagd[ no ] );
    tagd[ R( no ) ] = max( tagd[ R( no ) ] , tagd[ no ] );
    tagd[ no ] = 0;
  }
}
void modify( int no , int l , int r , int ql , int qr , int vl ){
  if( r < ql || l > qr || ql > qr ) return;
  if( ql <= l && r <= qr ){
    stu[ no ] = min( stu[ no ] , vl );
    stD[ no ] = max( stD[ no ] , vl );
    tagu[ no ] = min( tagu[ no ] , vl );
    tagd[ no ] = max( tagd[ no ] , vl );
    return;
  }
  push( no , l , r );
  modify( L( no ) , l , mid , ql , qr , vl );
  modify( R( no ) , mid + 1 , r , ql , qr , vl );
}
PII query( int no , int l , int r , int p ){
  if( l == r ) return { stu[ no ] , stD[ no ] };
  if( p <= mid ) return query( L( no ) , l , mid , p );
  push( no , l , r );
  return query( R( no ) , mid + 1 , r , p );
}
int n , m , a , b;
int cntl[ N ] , cntr[ N ];
int cntu[ N ] , cntd[ N ];
int l[ M ] , r[ M ] , u[ M ] , d[ M ];
LL ans;
#define K 20
int rmql[ M ][ K ] , rmqr[ M ][ K ];
PII query_lr( int ql , int qr ){
  int len = qr - ql + 1;
  int nbt = bit[ len ];
  return { min( rmql[ ql ][ nbt ] , rmql[ qr - two[ nbt ] + 1 ][ nbt ] ),
           max( rmqr[ ql ][ nbt ] , rmqr[ qr - two[ nbt ] + 1 ][ nbt ] ) };
}
void init(){
  scanf( "%d%d%d%d" , &n , &m , &a , &b );
  build_st( 1 , 0 , m - 1 );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d%d" , &l[ i ] , &r[ i ] );
    l[ i ] --; r[ i ] --;
    rmql[ i ][ 0 ] = l[ i ];
    rmqr[ i ][ 0 ] = r[ i ];
    modify( 1 , 0 , m - 1 , l[ i ] , r[ i ] , i );
  }
  for( int i = 1 ; i < K ; i ++ )
    for( int j = 0 ; j + two[ i ] - 1 < n ; j ++ ){
      rmql[ j ][ i ] = min( rmql[ j ][ i - 1 ] , rmql[ j + two[ i - 1 ] ][ i - 1 ] );
      rmqr[ j ][ i ] = max( rmqr[ j ][ i - 1 ] , rmqr[ j + two[ i - 1 ] ][ i - 1 ] );
    }
  for( int i = 0 ; i < n ; i += a ){
    int li = M , ri = 0;
    for( int j = i ; j < min( n , i + a ) ; j ++ ){
      li = min( li , l[ j ] );
      ri = max( ri , r[ j ] );
    }
    int lb = li / b , rb = ri / b;
    ans += ( rb - lb + 1 );
  }
  for( int i = 0 ; i < m ; i ++ ){
    PII tp = query( 1 , 0 , m - 1 , i );
    if( tp.first > tp.second ){
      u[ i ] = M; d[ i ] = 0;
    }
    u[ i ] = tp.first;
    d[ i ] = tp.second;
  }
  for( int i = 0 ; i < m ; i += b ){
    int uu = M , dd = 0;
    for( int j = i ; j < min( m , i + b ) ; j ++ ){
      uu = min( uu , u[ j ] );
      dd = max( dd , d[ j ] );
    }
    if( uu > dd ) continue;
    cntu[ uu % a ] ++;
    cntd[ dd % a ] ++;
  }
}
void solve(){
  for( int i = 0 ; i < a ; i ++ ){
    for( int j = 0 ; j < b ; j ++ )
      cntl[ j ] = cntr[ j ] = 0;
    LL tans = 0;
    if( i ){
      PII tp = query_lr( 0 , i - 1 );
      cntl[ tp.first % b ] ++;
      cntr[ tp.second % b ] ++;
      int lb = tp.first / b , rb = tp.second / b;
      tans += rb - lb + 1; 
    }
    for( int j = i ; j < n ; j += a ){
      PII tp = query_lr( j , min( n - 1 , j + a - 1 ) );
      cntl[ tp.first % b ] ++;
      cntr[ tp.second % b ] ++;
      int lb = tp.first / b , rb = tp.second / b;
      tans += rb - lb + 1;
    }
    // printf( "%lld\n" , tans );
    for( int j = 0 ; j < b ; j ++ ){
      ans = min( ans , tans );
      tans += cntl[ j ] - cntr[ j ];
    }
  }
  cout << ans << endl;
}
int main(){
  build();
  init();
  solve();
}
