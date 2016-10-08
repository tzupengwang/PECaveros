#include <bits/stdc++.h>
using namespace std;
#define N 50505
const int mod = 2010;
inline int mul( int x , int y ){
  x *= y;
  if( x >= mod ) return x % mod : x;
}
int mypow( int x , int p ){
  if( p == 0 ) return 1;
  int ret = mypow( mul( x , x ) , p >> 1 );
  if( p & 1 ) ret = mul( ret , x );
  return ret;
}
// struct Seg{
// #define L(X) (X<<1)
// #define R(X) (1+(X<<1))
// #define mid ((l+r)>>1)
  // int bs , b[ N ];
  // int st[ N << 2 ];
  // int tag[ N << 2 ];
  // void init( int _bs ){
    // bs = _bs;
    // b[ 0 ] = 0;
    // for( int i = 1 ; i <= n ; i ++ )
      // b[ i ] = b[ i - 1 ] + mypow( a[ i ] , bs );
  // }
  // void build( int no , int l , int r , bool tgg ){
    // tag[ no ] = 0;
    // if( l == r ){
      // st[ no ] = tgg ? b[ l ] - b[ l - 1 ] : 0;
      // return;
    // }
    // build( L( no ) , l , mid , tgg );
    // build( R( no ) , mid + 1 , r , tgg );
    // st[ no ] = st[ L( no ) ] + st[ R( no ) ];
  // }
  // void push( int no , int l , int r ){
    // if( tag[ no ] == 0 ) return;
    // int xtg = tag[ no ] - 1;
    // tag[ L( no ) ] = tag[ R( no ) ] = xtg + 1;
    // if( xtg ){
      // st[ L( no ) ] = b[ mid ] - b[ l - 1 ];
      // st[ R( no ) ] = b[ r ] - b[ mid ];
    // }else
      // st[ L( no ) ] = st[ R( no ) ] = 0;
    // tag[ no ] = 0;
  // }
  // void modify( int no , int l , int r , int ql , int qr , int xtg ){
    // if( r < ql || l > qr ) return;
    // if( ql <= l && r <= qr ){
      // tag[ no ] = xtg + 1;
      // if( xtg )
        // st[ no ] = b[ r ] - b[ l - 1 ];
      // else
        // st[ no ] = 0;
      // return ;
    // }
    // push( no , l , r );
    // modify( L( no ) , l , mid , ql , qr , xtg );
    // modify( R( no ) , mid + 1 , r , ql , qr , xtg );
  // }
  // int query( int no , int l , int r , int ql , int qr ){
    // if( r < ql || l > qr ) return 0;
    // if( ql <= l && r <= qr ) return st[ no ];
    // return query( L( no ) , l , mid , ql , qr ) +
           // query( R( no ) , mid + 1 , r , ql , qr );
  // }
// } st;
int n , a[ N ] , b[ 12 ][ N ];
int st[ 12 ][ N ];
int pp[ N ];
int tg[ N ];
vector< pair<int,int> > wt;
inline int query( int ql , int qr ){
  long long ans = st[ qr ] - st[ ql - 1 ];
  int ps = 0;
  for( size_t l = 0 , r = 0 ; l < wt.size() ; l = r ){
    while( r < wt.size() && wt[ l ].first == wt[ r ].first ){
      ps += wt[ r ].second;
      r ++;
    }
    if( ps ){
      
    }
  }
}
void rebuild(){
  wt.clear();
  int mr = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    mr += tg[ i ];
    pp[ i ] += mr;
    if( pp[ i ] > 11 ){
      pp[ i ] %= 10;
      if( pp[ i ] < 2 ) pp[ i ] += 10;
    }
    tg[ i ] = 0;
  }
  for( int i = 1 ; i <= n ; i ++ )
    st[ i ] = b[ pp[ i ] ][ i ] + st[ i - 1 ];
}
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
  for( int i = 1 ; i < 12 ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      b[ i ][ j ] = b[ i ][ j - 1 ] + mypow( a[ j ] , i );
  for( int i = 1 ; i <= n ; i ++ )
    pp[ i ] = 1;
}
#define K 600
void solve(){
  int qry; scanf( "%d" , &qry );
  for( int i = 0 ; i < qry ; i ++ ){
    if( i % K == 0 ) rebuild();
    int cmd , ql , qr;
    scanf( "%d%d%d" , &cmd , &ql , &qr );
    if( cmd == 1 ){
      wt.push_back( { ql , +1 } );
      wt.push_back( { qr + 1 , -1 } );
      sort( wt.begin() , wt.end() );
      tg[ ql ] ++;
      tg[ qr + 1 ] --;
    }else
      printf( "%d\n" , query( ql , qr ) );
  }
}
int main(){
  init();
  solve();
}
