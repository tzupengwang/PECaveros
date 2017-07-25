#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define PB push_back
#define SZ(X) ((int)X.size())
typedef long long LL;
struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  int n, fa[ N ], sz[ N ];
  vector< pair<int*,int> > h;
  vector<int> sp;
  void init( int tn ){
    n=tn;
    for( int i = 1 ; i <= n ; i ++ ){
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
inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
int n , m;
vector< int > v[ N ];
void init(){
  n = getint();
  m = getint();
  djs.init( n );
  while( m -- ){
    int ai = getint();
    int bi = getint();
    djs.uni( ai , bi );
    v[ ai ].push_back( bi );
    v[ bi ].push_back( ai );
  }
}
#define MX (N * 3)
pair<int,int> que[ MX ];
int qf , qt , tag[ N ][ 2 ] , stmp;
int dst[ N ][ 2 ];
int cal( int ui , int vi ){
  ++ stmp;
  qf = qt = 0;
  que[ qt ++ ] = { ui , 0 };
  dst[ ui ][ 0 ] = 0;
  tag[ ui ][ 0 ] = stmp;
  que[ qt ++ ] = { vi , 1 };
  dst[ vi ][ 1 ] = 0;
  tag[ vi ][ 1 ] = stmp;
  while( qf != qt ){
    int now , at;
    tie(now, at) = que[ qf ];
    qf ++; if( qf >= MX ) qf = 0;
    for( auto nxt : v[ now ] ){
      if( tag[ nxt ][ 1 - at ] == stmp )
        return dst[ now ][ at ] + dst[ nxt ][ 1 - at ] + 1;
      if( tag[ nxt ][ at ] == stmp ) continue;
      dst[ nxt ][ at ] = dst[ now ][ at ] + 1;
      tag[ nxt ][ at ] = stmp;
      que[ qt ] = {nxt , at};
      qt ++; if( qt >= MX ) qt = 0;
    }
  }
  assert( false );
  return -1;
}
void solve(){
  int q = getint(); while( q -- ){
    int ui = getint();
    int vi = getint();
    if( djs.f( ui ) != djs.f( vi ) ){
      puts( "-1" );
      continue;
    }
    printf( "%d\n" , cal( ui , vi ) );
  }
}
int main(){
  init();
  solve();
}
