#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
const LL MN = -(1LL << 31);
LL mn[ N << 2 ] , tg[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void build( int no , int l , int r ){
  mn[ no ] = MN;
  tg[ no ] = MN - 1;
  if( l == r ) return;
  build( L( no ) , l , mid );
  build( R( no ) , mid + 1 , r );
}
void push( int no , int l , int r ){
  if( tg[ no ] == MN - 1 ) return;
  mn[ L( no ) ] = mn[ R( no ) ] = tg[ no ];
  tg[ L( no ) ] = tg[ R( no ) ] = tg[ no ];
  tg[ no ] = MN - 1;
}
void modify( int no , int l , int r , int ql , int qr , LL d ){
  if( r < ql or l > qr ) return;
  if( ql <= l and r <= qr ){
    mn[ no ] = tg[ no ] = d;
    return;
  }
  push( no , l , r );
  modify( L( no ) , l , mid , ql , qr , d );
  modify( R( no ) , mid + 1 , r , ql , qr , d );
  mn[ no ] = min( mn[ L( no ) ] , mn[ R( no ) ] );
}
LL query_min( int no , int l , int r , int ql , int qr ){
  if( l == ql and r == qr ) return mn[ no ];
  push( no , l , r );
  if( qr <= mid ) return query_min( L( no ) , l , mid , ql , qr );
  if( mid < ql ) return query_min( R( no ) , mid + 1 , r , ql , qr );
  return min( query_min( L( no ) , l , mid , ql , mid ) ,
              query_min( R( no ) , mid + 1 , r , mid + 1 , qr ) );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "rmq.in" , "r" , stdin );
  freopen( "rmq.out" , "w" , stdout );
#endif
  int n , m;
  scanf( "%d%d" , &n , &m );
  build( 1 , 1 , n );
  vector< pair<int,pair<int,int>> > vv;
  for( int i = 0 ; i < m ; i ++ ){
    int l , r , v;
    scanf( "%d%d%d" , &l , &r , &v );
    vv.push_back( { v , { l , r } } );
  }
  sort( vv.begin() , vv.end() );
  for( auto i : vv )
    modify( 1 , 1 , n , i.second.first , i.second.second , i.first );
  for( auto i : vv ){
    LL ret = query_min( 1 , 1 , n , i.second.first , i.second.second );
    if( ret != i.first ){
      puts( "inconsistent" );
      return 0;
    }
  }
  puts( "consistent" );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%lld%c" , query_min( 1 , 1 , n , i , i ) , " \n"[ i == n ] );
}
