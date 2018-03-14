#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 402020
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
vector<int> st[ N << 2 ];
void add_cir( int no , int l , int r , int ql , int qr , int who ){
  if( r < ql or l > qr ) return;
  if( ql <= l and r <= qr ){
    st[ no ].push_back( who );
    return;
  }
  add_cir( L( no ) , l , mid , ql , qr , who );
  add_cir( R( no ) , mid + 1 , r , ql , qr , who );
}
int ans , cur;
int n , t[ N ] , x[ N ] , y[ N ];
bool died[ N ];
LL sqr( LL _ ){ return _ * _; }
void check( int cid ){
  if( sqr( x[ cid ] - x[ cur ] ) +
      sqr( y[ cid ] - y[ cur ] ) <
      sqr( y[ cid ] ) ){
    ans = cid;
    died[ cid ] = true;
  }
}
void query( int no , int l , int r , int qx ){
  for( size_t i = 0 ; i < st[ no ].size() ; i ++ ){
    int cid = st[ no ][ i ];
    if( died[ cid ] ){
      swap( st[ no ][ i ] , st[ no ].back() );
      st[ no ].pop_back();
      i --;
      continue;
    }
    check( cid );
  }
  if( ans != -1 ) return;
  if( l == r ) return;
  if( qx <= mid ) query( L( no ) , l , mid , qx );
  else query( R( no ) , mid + 1 , r , qx );
}
vector<int> li;
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d%d%d" , &t[ i ] , &x[ i ] , &y[ i ] );
    if( t[ i ] == 1 ){
      li.push_back( x[ i ] - y[ i ] );
      li.push_back( x[ i ] + y[ i ] );
    }else if( y[ i ] >= 0 )
      li.push_back( x[ i ] );
  }
  sort( li.begin() , li.end() );
  li.resize( unique( li.begin() , li.end() ) - li.begin() );
}
void solve(){
  int lsz = li.size();
  for( int i = 1 ; i <= n ; i ++ ){
    if( t[ i ] == 1 ){
      int lx = lower_bound( li.begin() , li.end() , x[ i ] - y[ i ] ) - li.begin();
      int rx = lower_bound( li.begin() , li.end() , x[ i ] + y[ i ] ) - li.begin();
      add_cir( 1 , 0 , lsz - 1 , lx , rx , i );
      continue;
    }
    if( y[ i ] < 0 ){
      puts( "-1" );
      continue;
    }
    cur = i;
    ans = -1;
    query( 1 , 0 , lsz - 1 , lower_bound( li.begin() , li.end() , x[ i ] ) - li.begin() );
    printf( "%d\n" , ans );
  }
}
int main(){
  init();
  solve();
}
