#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 30303
int n , m , k;
vector< pair<int,int> > v[ N ] , t[ N ];
void init(){
  scanf( "%d%d%d" , &n , &m , &k );
  k --;
  while( m -- ){
    int ai , bi , ci;
    scanf( "%d%d%d" , &ai , &bi , &ci );
    v[ ai ].push_back( { bi , ci } );
    v[ bi ].push_back( { ai , ci } );
  }
  for( int i = 1 ; i <= n ; i ++ )
    sort( v[ i ].begin() , v[ i ].end() );
}
int fr[ N ] , dst[ N ] , fd[ N ];
bool gt[ N ];
void build_t(){
  priority_queue< pair<int,int> ,
                  vector< pair<int,int > >,
                  greater< pair<int,int > > > heap;
  for( int i = 1 ; i <= n ; i ++ )
    dst[ i ] = 1000000000;
  heap.push( { 0 , 1 } );
  fr[ 1 ] = 1;
  while( heap.size() ){
    int dd , who; tie( dd , who ) = heap.top(); heap.pop();
    if( gt[ who ] ) continue;
    gt[ who ] = true;
    if( who != 1 ){
      //cerr << who << " ";
      //cerr << fr[ who ] << " ";
      //cerr << fd[ who ] << "\n";
      t[ who ].push_back( { fr[ who ] , fd[ who ] } );
      t[ fr[ who ] ].push_back( { who , fd[ who ] } );
    }
    for( auto e : v[ who ] ){
      int nxt = e.first;
      if( gt[ nxt ] ) continue;
      if( dd + e.second >= dst[ nxt ] ) continue;
      dst[ nxt ] = dd + e.second;
      fr[ nxt ] = who;
      fd[ nxt ] = e.second;
      heap.push( { dst[ nxt ] , nxt } );
    }
  }
}
LL ml = 0 , mc = 0;
int sz[ N ] , bst , bwho;
bool blk[ N ];
void gogo( int now , int prt ){
  sz[ now ] = 1;
  for( auto x : t[ now ] ){
    if( x.first == prt ) continue;
    if( blk[ x.first ] ) continue;
    gogo( x.first , now );
    sz[ now ] += sz[ x.first ];
  }
}
void gogo2( int now , int prt , int psz ){
  int mx = psz;
  for( auto x : t[ now ] ){
    if( x.first == prt ) continue;
    if( blk[ x.first ] ) continue;
    mx = max( mx , sz[ x.first ] );
    gogo2( x.first , now , psz + sz[ now ] - sz[ x.first ] );
  }
  if( mx < bst ){
    bst = mx;
    bwho = now;
  }
}

map<int,int> m1 , m2;
map<int,int> c1 , c2;

void gogogo( int now , int prt , int dep , int ddd ){
  if( dep > k ) return;
  auto it = m2.find( dep );
  if( it == m2.end() or ddd > it->second ){
    m2[ dep ] = ddd;
    c2[ dep ] = 1;
  }else if( ddd == it->second )
    c2[ dep ] ++;
  for( auto x : t[ now ] ){
    if( x.first == prt ) continue;
    if( blk[ x.first ] ) continue;
    gogogo( x.first , now , dep + 1 , ddd + x.second );
  }
}

void go( int now ){
  gogo( now , now );
  bst = N;
  bwho = now;
  gogo2( now , now , 0 );

  int root = bwho;
  m1.clear(); m2.clear();
  c1.clear(); c2.clear();
  m1[ 0 ] = 0;
  c1[ 0 ] = 1;
  for( auto x : t[ root ] ){
    if( blk[ x.first ] ) continue;
    m2.clear();
    c2.clear();
    gogogo( x.first , root , 1 , x.second );
    for( auto i : m2 ){
      auto it = m1.find( k - i.first );
      if( it == m1.end() ) continue;
      if( it->second + i.second > ml ){
        ml = it->second + i.second;
        mc = (LL)c1[ k - i.first ] * c2[ i.first ];
      }else if( it->second + i.second == ml )
        mc += (LL)c1[ k - i.first ] * c2[ i.first ];
    }
    for( auto i : m2 ){
      auto it = m1.find( i.first );
      if( it == m1.end() or i.second > it->second ){
        m1[ i.first ] = i.second;
        c1[ i.first ] = c2[ i.first ];
      }else if( i.second == it->second )
        c1[ i.first ] += c2[ i.first ];
    }
  }
  blk[ root ] = true;
  for( auto x : t[ root ] )
    if( !blk[ x.first ] )
      go( x.first );
}
void solve(){
  build_t();
  go( 1 );
  printf( "%lld %lld\n" , ml , mc );
}
int main(){
  init();
  solve();
}
