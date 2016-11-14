#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define PB push_back
#define SZ(X) ((int)X.size())
struct DisjointSet{
  // save() is like recursive
  // undo() is like return
  int n, fa[ N ], sz[ N ], dep[ N ];
  vector< pair<int*,int> > h;
  vector<int> sp;
  void init( int tn ){
    n=tn;
    for( int i = 0 ; i < n ; i ++ ){
      fa[ i ]=i;
      sz[ i ]=1;
      dep[ i ] = 0;
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
  pair<int,int> f( int x ){
    if( x == fa[ x ] ) return {x, 0};
    pair<int,int> ff = f( fa[ x ] );
    fa[ x ] = ff.first;
    dep[ x ] = ( dep[ x ] + ff.second ) % 2;
    return { ff.first , dep[ x ] };
  }
  void uni( int x , int y ){
    pair<int,int> px = f( x );
    pair<int,int> py = f( y );
    if( px.second != py.second ){
      fa[ py.first ] = px.first;
      dep[ py.first ] = 0;
    }else{
      fa[ py.first ] = px.first;
      dep[ py.first ] = 1;
    }
  }
} djs;
int n , m;
vector< int > v[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ ){
    int ai , bi; scanf( "%d%d" , &ai , &bi );
    if( ai > bi ) swap( ai , bi );
    v[ ai ].push_back( bi );
  }
}
bool flag[ N ] , gg;
int deg[ N ] , bdr , st;
void go( int nnow ){
  priority_queue< pair<int,int> ,
      vector< pair<int,int> > , greater< pair<int,int> > > Q;
  Q.push( { nnow , nnow } ); 
  while( Q.size() ){
    int now = Q.top().first;
    int from = Q.top().second;
    Q.pop();
    if( now != from ){
      if( flag[ now ] ){
        pair<int,int> p1 = djs.f( from );
        pair<int,int> p2 = djs.f( now );
        if( p1.first == p2.first ){
          if( p1.second == p2.second ){
            gg = true;
            return;
          }
        }else{
          if( now % 2 != st % 2 ){
            gg = true;
            return;
          }
          djs.uni( from , now );
        }
      }else{
        djs.uni( from , now );
      }
    }
    if( flag[ now ] ) continue;
    flag[ now ] = true;
    for( int son : v[ now ] ){
      if( son > bdr ) continue;
      Q.push( { son , now } );
    }
  }
}
bool bye( int _bdr ){
  bdr = _bdr;
  for( int i = 1 ; i <= bdr ; i ++ )
    flag[ i ] = false;
  gg = false;
  djs.init( n + 1 );
  for( int i = 1 ; i <= bdr ; i ++ )
    if( !flag[ i ] ){
      st = i;
      go( i );
      if( gg ) return true;
    }
  return false;
}
void solve(){
  int bl = 1 , br = n , ans = n;
  while( bl <= br ){
    int mid = ( bl + br ) >> 1;
    if( bye( mid ) )
      ans = mid , br = mid - 1;
    else
      bl = mid + 1;
  }
  if( !bye( ans ) ) puts( "Tie" );
  else printf( "%s %d\n" , ( ans % 2 ? "Bob" : "Alice" ) , ans );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "jackpot.in" , "r" , stdin );
  freopen( "jackpot.out" , "w" , stdout );
#endif
  init();
  solve();
}
