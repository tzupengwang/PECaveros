#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 4040
struct Arc{
  int to , cst , nxt;
  Arc(){}
  Arc( int _to , int _cst , int _nxt ){
    to = _to;
    cst = _cst;
    nxt = _nxt;
  }
} e[ N * 2 ];
map< pair<int,int> , int > _id;
int m , from[ N + N ] , nid;
inline int id( const pair<int,int>& p ){
  auto it = _id.find( p );
  if( it != _id.end() ) return it->second;
  from[ nid ] = 0;
  return _id[ p ] = nid ++;
}
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
int ui[ N ] , vi[ N ] , wi[ N ];
void init(){
  scanf( "%d" , &m );
  _id.clear(); nid = 0;
  for( int i = 1 ; i <= m ; i ++ ){
    int a , b , c , d , w;
    scanf( "%d%d%d%d%d" , &a , &b , &c , &d , &w );
    ui[ i ] = id( {a, b} );
    vi[ i ] = id( {c, d} );
    wi[ i ] = w;
    e[ L( i ) ] = Arc(vi[ i ], w, from[ ui[ i ] ]); from[ ui[ i ] ] = L( i );
    e[ R( i ) ] = Arc(ui[ i ], w, from[ vi[ i ] ]); from[ vi[ i ] ] = R( i );
  }
}
const int inf = 1e9;
int ans , blk , cs , got[ N + N ] , stmp;
int solve( int ss , int tt ){
  ++ stmp;
  priority_queue< pair<int,int> ,
          vector< pair<int,int> >,
         greater< pair<int,int> > > heap;
  heap.push( { 0 , ss } );
  while( heap.size() ){
    int td , tn;
    tie( td , tn ) = heap.top(); heap.pop();
    if( tn == tt ) return td;
    if( got[ tn ] == stmp ) continue;
    got[ tn ] = stmp;
    for( int eid = from[ tn ] ; eid ; eid = e[ eid ].nxt ){
      if( eid / 2 == blk ) continue;
      if( got[ e[ eid ].to ] == stmp ) continue;
      heap.push( {td + e[ eid ].cst , e[ eid ].to} );
    }
  }
  return inf;
}
void solve(){
  ans = inf;
  for( int i = 1 ; i <= m ; i ++ ){
    blk = i;
    int ret = solve( ui[ i ] , vi[ i ] );
    if( ret == inf ) continue;
    ans = min( ans , ret + wi[ i ] ); 
  }
  if( ans >= inf ) ans = 0;
  printf( "Case #%d: %d\n" , ++ cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
