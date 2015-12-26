#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 100010;
const int K = 30;

int tot , ch[ MAXN * 40 ][ 2 ] , cnt[ MAXN * 40 ];
int root[ MAXN ];

inline int bit( int x , int k )
{ return (x >> k) & 1; }

inline int newNode( int old )
{
  int res = ++tot;
  cnt[ res ] = cnt[ old ];
  ch[ res ][ 0 ] = ch[ old ][ 0 ];
  ch[ res ][ 1 ] = ch[ old ][ 1 ];
  return res;
}

int n , p[ MAXN ];

int ins( int tree  , int b , int x )
{
  int res = newNode( tree );
  if( b == -1 )
  {
    cnt[ res ]++;
    return res;
  }
  int cb = bit( x , b );
  ch[ res ][ cb ] = ins( ch[ tree ][ cb ] , b-1 , x );
  cnt[ res ] = 0;
  cnt[ res ] += cnt[ ch[ res ][ 0 ] ];
  cnt[ res ] += cnt[ ch[ res ][ 1 ] ];
  return res;
}

ll qry( int t1 , int t2 , int b , int x )
{
  if( b == -1 ) return 0;
  int cb = bit( x , b );
  if( cnt[ ch[ t1 ][ cb ] ] - cnt[ ch[ t2 ][ cb ] ] > 0 )
  {
    return qry( ch[ t1 ][ cb ] , ch[ t2 ][ cb ] , b-1 , x );
  }
  return (1ll<<b)+qry( ch[ t1 ][ cb^1 ] , ch[ t2 ][ cb^1 ] , b-1 , x );
}

const ll INF = 1000000000000;

ll work( int tree , int b , int l , int r )
{
  if( b == -1 ) return 0;
  if( l >= r ) return 0;
  int mid = l + cnt[ ch[ tree ][ 0 ] ] - 1;
  ll r1 = work( ch[ tree ][ 0 ] , b-1 , l , mid );
  ll r2 = work( ch[ tree ][ 1 ] , b-1 , mid+1 , r );
  ll res = r1 + r2;
  if( mid-l+1 == 0 || r-mid == 0 ) return res;
  if( mid-l+1 <= r-mid )
  {
    ll mn = INF;
    for( int i = l ; i <= mid ; i++ )
    {
      mn = min( mn , qry( root[ r ] , root[ mid ] , K , p[ i ] ) );
    }
    res += mn;
  }
  else
  {
    ll mn = INF;
    for( int i = mid+1 ; i <= r ; i++ )
    {
      mn = min( mn , qry( root[ mid ] , root[ l-1 ] , K , p[ i ] ) );
    }
    res += mn;
  }
  return res;
}

int main(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
  {
    scanf( "%d" , p+i );
  }
  sort( p+1 , p+1+n );
  root[ 0 ] = newNode( 0 );
  for( int i = 1 ; i <= n ; i++ )
  {
    root[ i ] = ins( root[ i-1 ] , K , p[ i ] );
  }
  ll ans = work( root[ n ] , K , 1 , n );
  printf( "%lld\n" , ans );
}
