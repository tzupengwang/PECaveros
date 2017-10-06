#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define SZ(X) ((int)X.size())
#define PB push_back
#define N 202020
struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  LL n, fa[ N ], sz[ N ];
  vector< pair<LL*,LL> > h;
  vector<int> sp;
  LL ans = 0;
  void init( int tn ){
    n=tn;
    for( int i = 0 ; i < n ; i ++ ){
      fa[ i ]=i;
      sz[ i ]=1;
    }
    sp.clear(); h.clear();
    ans = (LL)n * ( n - 1 ) / 2;
  }
  void assign( LL *k, LL v ){
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
    assign( &ans , ans - (LL)sz[ x ] * sz[ y ] );
    assign( &sz[ x ] , sz[ x ] + sz[ y ] );
    assign( &fa[ y ] , x);
  }
} djs;
int n , m;
#define mid ((l+r)>>1)
vector< pair<int,int> > wt[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
void add( int no , int l , int r , int ql , int qr , int a , int b ){
  if( r < ql or l > qr ) return;
  if( ql <= l and r <= qr ){
    wt[ no ].push_back( { a , b } );
    return;
  }
  add( L( no ) , l , mid , ql , qr , a , b );
  add( R( no ) , mid + 1 , r , ql , qr , a , b );
}
void go( int no , int l , int r ){
  djs.save();
  for( auto i : wt[ no ] )
    djs.uni( i.first , i.second );
  if( l == r ){
    printf( "%lld\n" , djs.ans );
  }else{
    go( L( no ) , l , mid );
    go( R( no ) , mid + 1 , r );
  }
  djs.undo();
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "travel.in" , "r" , stdin );
  freopen( "travel.out" , "w" , stdout );
#endif
  cin >> n >> m;
  while( m -- ){
    int ai , bi;
    cin >> ai >> bi;
    if( ai > bi ) swap( ai , bi );
    add( 1 , 1 , n , 1 , ai - 1 , ai - 1 , bi - 1 );
    add( 1 , 1 , n , ai + 1 , bi - 1 , ai - 1 , bi - 1 );
    add( 1 , 1 , n , bi + 1 , n , ai - 1 , bi - 1 );
  }
  djs.init( n );
  go( 1 , 1 , n );
}
