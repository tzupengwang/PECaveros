#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define lgN 20
#define N 300030
#define Q 30030
typedef long long LL;
inline int getint(){
  int _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
int n , m , a[ N ] , ad[ lgN ][ N ] , bt[ N ];
LL ps[ N ];
inline int And( int l , int r ){
  int cbt = bt[ r - l + 1 ];
  return ad[ cbt ][ l ] &
         ad[ cbt ][ r - (1 << cbt) + 1 ];
}
inline void build_table(){
  for( int i = 1 ; i < N ; i ++ )
    bt[ i ] = __lg( i );
  for( int i = 1 ; i <= n ; i ++ )
    ad[ 0 ][ i ] = abs( a[ i ] );
  for( int j = 1 ; j < lgN ; j ++ )
    for( int i = 1 ; i + (1 << j) - 1 <= n ; i ++ )
      ad[ j ][ i ] = ad[ j - 1 ][ i ] &
                     ad[ j - 1 ][ i + (1 << (j - 1)) ];
  for( int i = 1 ; i <= n ; i ++ )
    ps[ i ] = ps[ i - 1 ] + a[ i ];
}
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
struct SegT{
  LL bs[ N << 2 ] , x[ N << 2 ] , bsx[ N << 2 ];
  void pull( int no , int l , int r ){
    bs[ no ] = max( bs[ L( no ) ] , bs[ R( no ) ] );
    bsx[ no ] = max( bsx[ L( no ) ] , bsx[ R( no ) ] );
  }
  void push( int no , int l , int r ){
    for( int id : { L( no ) , R( no ) } )
      if( x[ no ] > x[ id ] ){
        x[ id ] = x[ no ];
        bsx[ id ] = max( bsx[ id ] , bs[ id ] + x[ id ] );
      }
  }
  void build_st( int no , int l , int r ){
    x[ no ] = -1000000000000000LL;
    if( l == r ){
      bs[ no ] = ps[ l ];
      bsx[ no ] = bs[ no ] + x[ no ];
      return;
    }
    build_st( L( no ) , l , mid );
    build_st( R( no ) , mid + 1 , r );
    pull( no , l , r );
  }
  void maximize( int no , int l , int r , int ql , int qr , LL vv ){
    if( r < ql or l > qr ) return;
    if( vv <= x[ no ] ) return;
    if( ql <= l and r <= qr ){
      x[ no ] = vv;
      bsx[ no ] = max( bsx[ no ] , bs[ no ] + vv );
      return;
    }
    push( no , l , r );
    maximize( L( no ) , l , mid , ql , qr , vv );
    maximize( R( no ) , mid + 1 , r , ql , qr , vv );
    pull( no , l , r );
  }
  LL query( int no , int l , int r , int ql , int qr ){
    if( r < ql or l > qr ) return 0;
    if( ql <= l and r <= qr ) return bsx[ no ];
    push( no , l , r );
    return max( query( L( no ) , l , mid , ql , qr ) ,
                query( R( no ) , mid + 1 , r , ql , qr ) );
  }
} segT;

int ql[ Q ] , qr[ Q ];

LL qans[ N ];
int nxt[ N ][ lgN ] , nct[ N ];
int pre[ N ][ lgN ] , pct[ N ];
LL ans[ Q ];
vector<int> wt[ N ];
void build_qans(){
  for( int i = 1 ; i <= n ; i ++ ){
    int ct = 0;
    nxt[ i ][ ct ++ ] = i;
    int lst = i , vl = abs( a[ i ] );
    while( lst <= n ){
      int bl = lst + 1 , br = n , ba = n + 1;
      while( bl <= br ){
        int bmid = (bl + br) >> 1;
        if( And( i , bmid ) != vl )
          ba = bmid , br = bmid - 1;
        else
          bl = bmid + 1;
      }
      nxt[ i ][ ct ++ ] = lst = ba;
      if( ba <= n ) vl = And( i , ba );
    }
    nct[ i ] = ct;
  }
  segT.build_st( 1 , 1 , n );
  for( int i = n ; i >= 1 ; i -- ){
    for( int k = 0 ; k + 1 < nct[ i ] ; k ++ ){
      int lb = nxt[ i ][ k ] , rb = nxt[ i ][ k + 1 ] - 1;
      segT.maximize( 1 , 1 , n , lb , rb , And( i , lb ) - ps[ i - 1 ] );
    }
    for( int qid : wt[ i ] )
      ans[ qid ] = max( 0LL , segT.query( 1 , 1 , n , i , qr[ qid ] ) );
  }
}

void init(){
  n = getint();
  m = getint();
  //n = 300000;
  //m = 30000;
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = getint();
    //a[ i ] = rand() % 200001 - 100000;
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d" , &ql[ i ] , &qr[ i ] );
    //ql[ i ] = i + 1, qr[ i ] = n - i;
    wt[ ql[ i ] ].push_back( i );
  }
  build_table();
  build_qans();
}
void solve(){
  for( int qid = 0 ; qid < m ; qid ++ )
    printf( "%lld\n" , ans[ qid ] );
}
int main(){
  init();
  solve();
}
