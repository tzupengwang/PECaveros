#include <bits/stdc++.h>
using namespace std;
#define N 4040
typedef long long LL;
LL n , T;
vector< pair< LL , pair<LL,LL> > > vv;
void init(){
  scanf( "%lld%lld" , &n , &T );
  for( int i = 0 ; i < n ; i ++ ){
    LL ti , pi , fi;
    scanf( "%lld%lld%lld" , &ti , &pi , &fi );
    if( ti > T ) continue;
    vv.push_back( { fi , { ti , pi } } );
  }
  sort( vv.begin() , vv.end() );
}
LL dp[ N ][ N ] , t[ N ] , p[ N ] , f[ N ];
// dp[ i ][ j ] = pi - fi^2 + dp[ i' ][ j - ti ] - fi'^2 + 2 fi fi'
//              = ( ..... ) + ( ...................... ) + 2  x fi'
deque< pair<LL,LL> > dq[ N ];
#define INF16 10000000000000000LL
#define M first
#define C second
void add( int cur , int tt ){
  LL m = 2 * f[ cur ];
  LL c = dp[ cur ][ tt ] - f[ cur ] * f[ cur ];
  //printf( "%d %d m=%lld c=%lld\n" , cur , tt , m , c );
  if( dq[ tt ].empty() ){
    dq[ tt ].push_back( { m , c } );
    return;
  }
  while( dq[ tt ].size() ){
    if( dq[ tt ].back().first == m ){
      if( dq[ tt ].back().second >= c )
        return;
      dq[ tt ].pop_back();
      continue;
    }
    if( dq[ tt ].size() > 1u ){
      int dqsz = (int)dq[ tt ].size();
      pair<LL,LL> pre = dq[ tt ][ dqsz - 2 ];
      pair<LL,LL> now = dq[ tt ][ dqsz - 1 ];
      if( ( pre.C - now.C ) * ( m     - pre.M ) >= 
          ( pre.C - c     ) * ( now.M - pre.M ) ){
        dq[ tt ].pop_back();
        continue;
      }else break;
    }else break;
  }
  //printf( "add %d %d m=%lld, c=%lld\n" , cur , tt , m , c );
  dq[ tt ].push_back( { m , c } );
}
// dp[ i ][ j ] = pi - fi^2 + dp[ i' ][ j - ti ] - fi'^2 + 2 fi fi'
//              = ( ..... ) + ( ...................... ) + 2  x fi'
LL query( LL xx , LL tt ){
  if( dq[ tt ].empty() ) return -INF16;
  while( dq[ tt ].size() > 1u ){
    pair<LL,LL> pre = dq[ tt ][ 0 ];
    pair<LL,LL> now = dq[ tt ][ 1 ];
    if( ( pre.C - now.C ) <= ( now.M - pre.M ) * xx )
      dq[ tt ].pop_front();
    else
      break;
  }
  //printf( "query %lld %lld m=%lld, c=%lld\n" ,
          //xx , tt , dq[ tt ].front().M , dq[ tt ].front().C );
  return dq[ tt ].front().M * xx + dq[ tt ].front().C;
}
void solve(){
  n = (int)vv.size();
  for( int i = 0 ; i < n ; i ++ ){
    f[ i ] = vv[ i ].first;
    t[ i ] = vv[ i ].second.first;
    p[ i ] = vv[ i ].second.second;
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j <= T ; j ++ ){
      dp[ i ][ j ] = -INF16;
      if( j >= t[ i ] )
        dp[ i ][ j ] = p[ i ];
    }
  LL ans = -INF16;
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j <= T ; j ++ ){
      if( j )
        dp[ i ][ j ] = max( dp[ i ][ j ] , dp[ i ][ j - 1 ] );
      if( j >= t[ i ] ){
        LL bst = p[ i ] - f[ i ] * f[ i ] + query( f[ i ] , j - t[ i ] );
        //printf( "%d %d bst = %lld\n" , i , j , bst );
        dp[ i ][ j ] = max( dp[ i ][ j ] , bst );
      }
      //if( dp[ i ][ j ] > -INF16 )
        //printf( "%d %d %lld\n" , i , j , dp[ i ][ j ] );
      ans = max( ans , dp[ i ][ j ] );
    }
    for( int j = 0 ; j <= T ; j ++ )
      if( dp[ i ][ j ] > -INF16 )
        add( i , j );     
  }
  cout << ans << endl;
}
int main(){
  init();
  solve();
}
