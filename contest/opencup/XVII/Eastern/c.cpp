#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
#define PB push_back
#define SZ(X) ((int)X.size())
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
}djs;
LL cst( int n , int seed ){
  vector< pair<LL, pair<int,int> > > v;
  LL ret = 0 , x = seed;
  for( int i = 2 ; i <= n ; i ++ ){
    x = x * 907LL % 2333333;
    int T = x;
    for( int j = max( 1 , i - 5 ) ; j <= i - 1 ; j ++ ){
      x = x * 907 % 2333333;
      LL w = T ^ x;
      v.push_back( { w , { i , j } } );
    }
  }
  sort( v.begin() , v.end() );
  djs.init( n );
  for( auto e : v ){
    if( djs.f( e.second.first ) ==
        djs.f( e.second.second ) )
      continue;
    ret += e.first;
    djs.uni( e.second.first ,
             e.second.second );
  }
  return ret;
}
int main(){
  int t; cin >> t; while( t -- ){
    int n , s;
    cin >> n >> s;
    if( n < 514 )
      cout << cst( n , s ) << endl;
    else{
      int nn = n % 54 + 54;
      LL ans = cst( nn , s );
      LL dlt = cst( nn + 54 , s ) - ans;
      cout << ans + dlt * ( ( n - nn ) / 54 ) << endl;
    }
  }
}
