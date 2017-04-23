#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300010;
const int INF  = 1e9;

int n , L , R;
int a[ MAXN ] , s[ MAXN ];
int dp[ MAXN ];

typedef tuple<int,int,int> Dat;
set<Dat> st;

inline int sgn( int x ) {
  if ( x == 0 ) return 0;
  return x > 0 ? 1 : -1;
}

int main() {
  scanf( "%d%d%d" , &n , &L , &R );
  for ( int i = 1 ; i <= n ; i++ ) {
    scanf( "%d" , a+i );
    s[ i ] = s[ i-1 ] + a[ i ];
  }
  fill( dp , dp+n+1 , -INF );
  dp[ 0 ] = 0;
  int cl = 0 , cr = -1;
  for ( int i = 1 ; i <= n ; i++ ) {
    while ( cr < i-L ) {
      cr++;
      st.insert( make_tuple( -dp[ cr ] , s[ cr ] , cr ) );
    }
    while ( cl < i-R ) {
      st.erase( make_tuple( -dp[ cl ] , s[ cl ] , cl ) );
      cl++;
    }
    if ( st.size() > 0 ) {
      auto tp = *st.begin();
      auto tp2 = tp;
      auto ptr = st.upper_bound(make_tuple(get<0>(tp),INF,INF));
      if ( ptr != st.end() ) tp2 = *ptr;
      //printf( "%d -> %d [%d, %d]\n" , i , get<2>(tp) , cl , cr );
      int tmp1 = -get<0>(tp) + sgn( s[ i ] - get<1>(tp) );
      int tmp2 = -get<0>(tp2) + sgn( s[ i ] - get<1>(tp2) );
      dp[ i ] = max( tmp1 , tmp2 );
    }
    //printf ( "%d %d\n" , i , dp[ i ] ) ;
  }
  if ( dp[ n ] <= -1e8 ) puts( "Impossible" );
  else printf( "%d\n" , dp[ n ] );
}
