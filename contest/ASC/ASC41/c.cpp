#include <bits/stdc++.h>
using namespace std;
#define N 303030
typedef long long LL;
typedef pair<LL,LL> PLL;
LL n , d[ N ] , t , fr[ N ] , to[ N ] , st[ N ] , dir[ N ];
vector< LL > as[ N ] , at[ N ];
int index( int who , LL att ){
  if( dir[ who ] == 1 ) return att - fr[ who ];
  return fr[ who ] - att;
}
void init(){
  scanf( "%lld" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%lld" , &d[ i ] );
  scanf( "%lld" , &t );
  for( int i = 0 ; i < t ; i ++ ){
    scanf( "%lld%lld%lld" , &fr[ i ] , &to[ i ] , &st[ i ] );
    LL all = abs( fr[ i ] - to[ i ] ) + 1;
    as[ i ].resize( all );
    at[ i ].resize( all );
    if( fr[ i ] < to[ i ] ) dir[ i ] = 1;
    else dir[ i ] = -1;
  }
}
typedef tuple<LL,LL,LL> data;
priority_queue< data , vector< data > , greater< data > > lft[ N ] , rgt[ N ];
set< pair<LL,LL> > S;
LL ndir[ N ] , wt[ N ] , cur[ N ] , wt2[ N ];
void add( int i ){
  if( lft[ i ].size() || rgt[ i ].size() ){
    LL ear = -1;
    if( lft[ i ].size() )
      ear = get<0>( lft[ i ].top() );
    if( rgt[ i ].size() ){
      if( ear == -1 || get<0>( rgt[ i ].top() ) < ear )
        ear = get<0>( rgt[ i ].top() );
    }
    S.insert( { ear , i } );
    cur[ i ] = ear;
  }else cur[ i ] = -1;
}
void solve(){
  for( int i = 0 ; i < t ; i ++ ){
    if( dir[ i ] == 1 )
      lft[ fr[ i ] ].push( make_tuple( st[ i ] , st[ i ] , i ) );
    else
      rgt[ fr[ i ] - 1 ].push( make_tuple( st[ i ] , st[ i ] , i ) );
  }
  for( int i = 1 ; i < n ; i ++ )
    add( i );
  while( S.size() ){
    auto it = *S.begin(); S.erase( it );
    int now = it.second;
    if( rgt[ now ].size() &&
        ( lft[ now ].empty() ||
          get<0>( rgt[ now ].top() ) < get<0>( lft[ now ].top() ) ||
          ( get<0>( rgt[ now ].top() ) == get<0>( lft[ now ].top() ) &&
            ( ( ndir[ now ] != 0 && wt[ now ] > get<0>( lft[ now ].top() ) &&
                ndir[ now ] < 0 ) ||
              ( ( ndir[ now ] == 0 || wt[ now ] <= get<0>( lft[ now ].top() ) ) &&
                get<1>( rgt[ now ].top() ) <= get<1>( lft[ now ].top() ) ) ) ) ) ){
      auto tp = rgt[ now ].top(); rgt[ now ].pop();
      LL who = get<2>( tp );
      int idx = index( who , now + 1 );
      LL st_time = get<0>( tp );
      if( ndir[ now ] > 0 ) st_time = max( st_time , wt[ now ] );
      if( ndir[ now ] < 0 ) st_time = max( st_time , wt2[ now ] );
      ndir[ now ] = -1;
      at[ who ][ idx ] = st_time;
      LL ar_time = st_time + d[ now + 1 ] - d[ now ];
      as[ who ][ idx + 1 ] = ar_time;
      //printf( "Train #%lld from %d to %d since %lld til %lld wt %lld\n" , 
              //who , now + 1 , now , st_time , ar_time , wt[ now ] );
      wt[ now ] = ar_time;
      wt2[ now ] = st_time + 1;
      if( now != to[ who ] )
        rgt[ now - 1 ].push( make_tuple( ar_time + 1 , get<1>( tp ) , who ) );
      if( cur[ now - 1 ] != -1 )
        S.erase( { cur[ now - 1 ] , now - 1 } );
      add( now - 1 );
    }else{
      auto tp = lft[ now ].top(); lft[ now ].pop();
      LL who = get<2>( tp );
      int idx = index( who , now );
      LL st_time = get<0>( tp );
      if( ndir[ now ] < 0 ) st_time = max( st_time , wt[ now ] );
      if( ndir[ now ] > 0 ) st_time = max( st_time , wt2[ now ] );
      ndir[ now ] = +1;
      at[ who ][ idx ] = st_time;
      LL ar_time = st_time + d[ now + 1 ] - d[ now ];
      as[ who ][ idx + 1 ] = ar_time;
      //printf( "Train #%lld from %d to %d since %lld til %lld wt %lld\n" , 
              //who , now , now + 1 , st_time , ar_time , wt[ now ] );
      wt[ now ] = ar_time;
      wt2[ now ] = st_time + 1;
      if( now + 1 != to[ who ] )
        lft[ now + 1 ].push( make_tuple( ar_time + 1 , get<1>( tp ) , who ) );
      if( cur[ now + 1 ] != -1 )
        S.erase( { cur[ now + 1 ] , now + 1 } );
      add( now + 1 );
    }
    add( now );
  }
  for( int i = 0 ; i < t ; i ++ ){
    printf( "Train %d\n" , i + 1 );
    printf( "%lld * %lld\n" , fr[ i ] , at[ i ][ 0 ] );
    for( int j = fr[ i ] + dir[ i ] , k = 1 ; j != to[ i ] ; j += dir[ i ] , k ++ )
      printf( "%d %lld %lld\n" , j , as[ i ][ k ] , at[ i ][ k ] );
    printf( "%lld %lld *\n" , to[ i ] , as[ i ].back() );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "commuter.in" , "r" , stdin );
  freopen( "commuter.out" , "w" , stdout );
#endif
  init();
  solve();
}
