#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
void scan( Pt& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
int n , m;
vector< pair<int,Pt> > v[ N ];
Pt ans[ N ];
bool gt[ N ] , gt2[ N ];
LL mnx , mny;
void go( int now , Pt cur ){
  ans[ now ] = cur;
  gt[ now ] = true;
  mnx = min( mnx , cur.X );
  mny = min( mny , cur.Y );
  for( auto i : v[ now ] ){
    if( gt[ i.first ] ) continue;
    go( i.first , cur + i.second );
  }
}
void go2( int now ){
  ans[ now ].X -= mnx + 1e9;
  ans[ now ].Y -= mny + 1e9;
  gt2[ now ] = true;
  for( auto i : v[ now ] ){
    if( gt2[ i.first ] ) continue;
    go2( i.first );
  }
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    for( int i = 1 ; i <= n ; i ++ ){
      v[ i ].clear();
      gt[ i ] = false;
      gt2[ i ] = false;
    }
    while( m -- ){
      int ui , vi; Pt dlt;
      scanf( "%d%d" , &ui , &vi );
      scan( dlt );
      v[ ui ].push_back( { vi , dlt } );
      dlt.X = -dlt.X;
      dlt.Y = -dlt.Y;
      v[ vi ].push_back( { ui , dlt } );
    }
    for( int i = 1 ; i <= n ; i ++ )
      if( not gt[ i ] ){
        mnx = 0; mny = 0;
        go( i , { 0 , 0 } );
        go2( i );
      }
    for( int i = 1 ; i <= n ; i ++ )
      printf( "%lld %lld\n" , ans[ i ].X , ans[ i ].Y );
  }
}
