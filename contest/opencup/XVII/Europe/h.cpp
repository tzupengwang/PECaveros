#include <bits/stdc++.h>
using namespace std;
#define PB push_back
#define MP make_pair
#define SZ(X) (int)(X.size())
const int N = 1e6+10;
struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  int n, fa[ N ], sz[ N ];
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

const int Q = 3e5+10;
const int L = 1005;

int n;
char ip[ L ][ L ];
int id[ L ][ L ];
int s[ L ][ L ];

int q;
struct XD {
  int a , b , c , d;
  void read() {
    scanf( "%d%d%d%d" , &a , &b , &c , &d );
  }
} qs[ Q ];

inline int enc( int i , int j ) {
  return (i-1)*n+j;
}

void input() {
  scanf( "%d" , &n );
  for ( int i = 1 ; i <= n ; i++ ) scanf( "%s" , ip[ i ] + 1 );
  for ( int i = 1 ; i <= n ; i++ ) for ( int j = 1 ; j <= n ; j++ ) {
    id[ i ][ j ] = enc( i , j );
    s[i][j] = ip[i][j]=='#';
    s[i][j] += s[i-1][j]+s[i][j-1]-s[i-1][j-1];
  }
  scanf( "%d" , &q );
  for ( int i = 1 ; i <= q ; i++ ) {
    qs[ i ].read();
  }
}

inline int gets( int a , int b , int c , int d ) {
  return s[c][d]-s[c][b-1]-s[a-1][d]+s[a-1][b-1];
}

inline bool cansq( int i , int j , int k ) {
  int a = i-k , b = j-k;
  int c = i+k , d = j+k;
  if ( a < 1 || b < 1 ) return 0;
  if ( c > n || d > n ) return 0;
  return gets( a , b , c , d ) == 0;
}

int lim[ N ];
vector<pair<int,int>> wlim[ L ];

void predo() {
  for ( int i = 1 ; i <= n ; i++ ) for ( int j = 1 ; j <= n ; j ++ ) {
    if ( ip[i][j] == '#' ) {
      lim[ id[i][j] ] = 0;
      continue;
    }
    int l = 0 , r = n , tmp = 0;
    while ( l <= r ) {
      int mid = ( l+r ) / 2;
      if ( cansq( i , j , mid ) ) {
        tmp = mid;
        l = mid+1;
      } else r = mid-1;
    }
    lim[ id[i][j] ] = tmp*2+1;
    wlim[ lim[id[i][j]] ].push_back( { i , j } );
  }
}

int ans[ Q ];

int dx[] = { 0 , 1 , 0 , -1 };
int dy[] = { 1 , 0 , -1 , 0 };

inline void add( int l , int r ) {
  for ( int i = l ; i <= r ; i++ ) {
    for ( auto p : wlim[ i ] ) {
      int x , y;tie( x , y ) = p;
      for ( int k = 0 ; k < 4 ; k++ ) {
        int tx = x+dx[k];
        int ty = y+dy[k];
        if ( 1 > tx || n < tx ) continue;
        if ( 1 > ty || n < ty ) continue;
        if ( lim[ id[tx][ty] ] < l ) continue;
        djs.uni( id[x][y] , id[tx][ty] );
      }
    }
  }
}

void DC( int l , int r , vector<int>&allq ) {
  if ( l > r ) return;

  int mid = ( l+r ) / 2;

  djs.save();

  add( mid , r );

  vector<int> sm , bg;

  for( int i : allq ) {
    XD qq = qs[ i ];
    int t1 = djs.f( id[qq.a][qq.b] );
    int t2 = djs.f( id[qq.c][qq.d] );
    if ( t1 == t2 ) {
      ans[ i ] = mid;
      bg.push_back( i );
    } else {
      sm.push_back( i );
    }
  }

  DC( l , mid-1 , sm );

  djs.undo();

  DC( mid+1 , r , bg );

}

void solve() {
  djs.init( n*n );
  vector<int> allq;
  for ( int i = 1 ; i <= q ; i++ ) allq.push_back( i );
  DC( 1 , n , allq );
  for ( int i = 1 ; i <= q ; i++ ) printf( "%d\n" , ans[ i ] );
}

int main(){
  input();
  predo();
  solve();
}
