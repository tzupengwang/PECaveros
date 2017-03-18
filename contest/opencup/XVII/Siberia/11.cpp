#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

#include <bits/extc++.h>
using namespace __gnu_pbds;
#include <ext/pb_ds/assoc_container.hpp>
// typedef cc_hash_table<LL,int> umap_t;
typedef unordered_map<LL,int> umap_t;

const int MAXN = 1e5+10;

int n , q;
char ip[ MAXN ];

LL P;
LL pw10[ MAXN ];
LL S[ MAXN ];
LL qA[ 111 ];
LL res[ 111 ];
int ql[ 111 ] , qr[ 111 ];

inline void go() {
  umap_t htcnt , htfst;
  for ( int i = n-1 ; i >= 0 ; i-- ) {
    for ( int j = 0 ; j < q ; j++ ) {
      LL tgt = S[ i ] + qA[ j ] * pw10[ i+1 ];
      tgt %= P;
      if ( htfst.count( tgt ) ) {
        res[ j ] += htcnt[ tgt ];
        ql[ j ] = i+2;
        qr[ j ] = htfst[ tgt ]+1;
      }
    }
    htcnt[ S[ i ] ]++;
    if ( !htfst.count( S[ i ] ) ) htfst[ S[ i ] ] = i;
  }
  for ( int j = 0 ; j < q ; j++ ) {
    LL tgt = qA[ j ];
    if ( htfst.count( tgt ) ) {
      res[ j ] += htcnt[ tgt ];
      ql[ j ] = 1;
      qr[ j ] = htfst[ tgt ]+1;
    }
    if ( res[ j ] == 0 ) printf( "0 0 0\n" );
    else
      printf( "%lld %d %d\n" , res[ j ] , n-qr[j]+1 , n-ql[j]+1 );
  }
}

int main() {
  scanf( "%s%d%lld" , ip , &q , &P );
  n = strlen( ip );
  reverse( ip , ip+n );
  for ( int i = 0 ; i < n ; i++ ) ip[ i ] -= '0';
  S[ 0 ] = ip[ 0 ] % P;
  pw10[ 0 ] = 1;
  for ( int i = 1 ; i <= n ; i++ ) {
    pw10[ i ] = ( 10 * pw10[ i-1 ] ) % P;
    S[ i ] = ( S[ i-1 ] + ip[ i ] * pw10[ i ] ) % P;
  }
  for ( int i = 0 ; i < q ; i++ )
    scanf( "%lld" , qA + i );
  go();
}
