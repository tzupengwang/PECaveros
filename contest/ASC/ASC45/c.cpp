//by tzupengwang™
#include<bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;

int n ;
void init() {
  scanf( "%d" , &n ) ;
  if ( n == 0 ) exit( 0 ) ;
}

struct stt {
  stt( ui _j , ui _A , ui _ai , ui _stk ) : j( _j ) , A( _A ) , ai( _ai ) , stk( _stk ) {}
  ui j , A , ai , stk ;
  bool operator< ( const stt &x ) const {
    return tie( j , A , ai , stk ) < tie( x.j , x.A , x.ai , x.stk ) ;
  }
} ;

map< stt , ll > mp[ 35 ] ;

int v[ 100 ] ;

void process() {
  mp[ 1 ].clear() ;
  mp[ 1 ][ stt( 0 , 0 , 0 , 0 ) ] = 1 ;
  for ( int i = 1 ; i < n ; i ++ ) {
    mp[ i + 1 ].clear() ;
    for ( auto st : mp[ i ] ) {
      stt nst = st.first ; ll num = st.second ;
      //printf( "stt %d %u %u %u %u %lld\n" , i , nst.j , nst.A , nst.ai , nst.stk , num ) ;
      for ( int nxt = nst.ai ; nxt <= nst.A + 1 ; nxt ++ ) {
        ui nA = nst.A , stk = nst.stk , ai = nst.ai ;
        if ( nxt > nst.j ) nA ++ ;
        while ( stk ) {
          int lb = stk & (-stk) ;
          if ( __lg( lb ) < nxt ) {
            stk -= lb ;
            ai = __lg( lb ) ;
          } else break ;
        }
        if ( nxt > ai ) stk |= ( 1U << nxt ) ;
        mp[ i + 1 ][ stt( nxt , nA , ai , stk ) ] += num ;
      }
    }
  }
  ll ans = 0 ;
  for ( auto st : mp[ n ] ) {
    stt nst = st.first ;
      //printf( "stt %d %u %u %u %u %lld\n" , n , nst.j , nst.A , nst.ai , nst.stk , st.second ) ;
    ans += st.second ;
  }
  cout << ans << endl ;
}

int main() {
  freopen("catalian.in","r",stdin);
  freopen("catalian.out","w",stdout);
  int cnt = 1 ;
  while( 1 ) {
    init() ;
    printf( "Case #%d: " , cnt ++ ) ;
    process() ;
  }
  return 0 ;
}

