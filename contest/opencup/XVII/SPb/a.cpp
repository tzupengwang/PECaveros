#include <bits/stdc++.h>
using namespace std;
#define N 404040
typedef long long LL;
int st[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void build_st( int no , int l , int r ){
  st[ no ] = N;
  if( l == r ) return;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
}
void modify( int no , int l , int r , int p , int x ){
  st[ no ] = min( st[ no ] , x );
  if( l == r ) return;
  if( p <= mid ) modify( L( no ) , l , mid , p , x );
  else modify( R( no ) , mid + 1 , r , p , x );
}
int query( int no , int l , int r , int ql , int qr ){
  if( r < ql or l > qr ) return N;
  if( ql <= l and r <= qr ) return st[ no ];
  return min( query( L( no ) , l , mid , ql , qr ) ,
              query( R( no ) , mid + 1 , r , ql , qr ) );
}
LL n , s , a[ N ];
void init(){
  scanf( "%lld%lld" , &n , &s );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &a[ i ] );
    a[ i ] += a[ i - 1 ];
  }
}
vector<LL> li;
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    li.push_back( a[ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    li.push_back( a[ i ] - s );
  sort( li.begin() , li.end() );
  li.resize( unique( li.begin() , li.end() ) - li.begin() );
  int ans = -1 , al = -1 , ar = -1;
  build_st( 1 , 1 , li.size() );
  for( int i = 0 ; i <= n ; i ++ ){
    int pos = lower_bound( li.begin() , li.end() , a[ i ] ) - li.begin() + 1;
    if( i ){
      int ppos = lower_bound( li.begin() , li.end() , a[ i ] - s ) - li.begin() + 1;
      int ret = query( 1 , 1 , li.size() , ppos , li.size() );
      if( ret < i ){
        int len = i - ret;
        if( len > ans ){
          ans = len;
          al = ret;
          ar = n - i;
        }
      }
    }
    modify( 1 , 1 , li.size() , pos , i );
  }
  printf( "%d\n" , ans );
  if( ans != -1 )
    printf( "%d %d\n" , al , ar );
}
int main(){
  init();
  solve();
}
